/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdint.h>
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xiic.h"
#include "sleep.h"
#include "xintc.h"
#include "xil_exception.h"
#include "xuartlite.h"


#define BTN_ADDR XPAR_AXI_BTN_GPIO_0_BASEADDR
#define BTN_CHANNEL 1
#define I2C_ADDR XPAR_AXI_IIC_0_BASEADDR
#define STOPWATCH_ADDR XPAR_MYIP_STOP_WATCH_0_BASEADDR
#define UART_ADDR XPAR_AXI_UARTLITE_0_BASEADDR

#define INTC_ADDR XPAR_XINTC_0_BASEADDR
#define BTN_VEC_ID XPAR_FABRIC_AXI_BTN_GPIO_0_INTR
#define UART_VEC_ID XPAR_FABRIC_AXI_UARTLITE_0_INTR

XIic i2c_inst;
XGpio btn_inst;
XIntc intc_inst;
XUartLite uart_inst;
volatile unsigned int *stopwatch_inst = (volatile unsigned int *)STOPWATCH_ADDR;

void btn_isr(void *CallBackRef);
void RecvHandler(void *CallBackRef, unsigned int EventData);
void SendHandler(void *CallBackRef, unsigned int EventData);
void lcdCommand(uint8_t command);
void lcdData(uint8_t data);
void i2cLCD_Init();
void lcdString(char *str);
void moveCursor(uint8_t row, uint8_t col);
void lcdClear();

volatile uint8_t btn_value;
volatile uint8_t btn_valid = 0;

int main () {
    init_platform();
    print("Success Start INTC Stopwatch\n");

    XGpio_Initialize(&btn_inst, BTN_ADDR);
    XGpio_SetDataDirection(&btn_inst, BTN_CHANNEL, 0b1111);
    XIic_Initialize(&i2c_inst, I2C_ADDR);
    XIntc_Initialize(&intc_inst, INTC_ADDR);
    XUartLite_Initialize(&uart_inst, UART_ADDR);

    XIntc_Connect(&intc_inst, BTN_VEC_ID,
        (XInterruptHandler)btn_isr, (void *)&btn_inst);
    XIntc_Connect(&intc_inst, UART_VEC_ID,
        (XInterruptHandler)XUartLite_InterruptHandler, (void *)&uart_inst);
    XIntc_Enable(&intc_inst, BTN_VEC_ID);
    XIntc_Enable(&intc_inst, UART_VEC_ID);
    XIntc_Start(&intc_inst, XIN_REAL_MODE);

    XGpio_InterruptEnable(&btn_inst, BTN_CHANNEL);
    XGpio_InterruptGlobalEnable(&btn_inst);

    XUartLite_SetRecvHandler(&uart_inst, RecvHandler, &uart_inst);
    XUartLite_SetSendHandler(&uart_inst, SendHandler, &uart_inst);
    XUartLite_EnableInterrupt(&uart_inst);

    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
        (Xil_ExceptionHandler)XIntc_InterruptHandler, &intc_inst);
    Xil_ExceptionEnable();

    i2cLCD_Init();
    moveCursor(0, 0);
    lcdString("TIME 00:00:00:00");
    moveCursor(1, 0);
    lcdString("LAP  00:00:00:00");

    char lcd_sec[16], lcd_lap[16];
    while (1) {
        if (btn_valid) {
            if (btn_value == 0b0001) stopwatch_inst[0] = stopwatch_inst[0] ^ 0b0001;
            else if (btn_value == 0b0010) stopwatch_inst[0] = stopwatch_inst[0] | 0b0010;
            else if (btn_value == 0b0100) stopwatch_inst[0] = stopwatch_inst[0] | 0b0100;

            sprintf(lcd_lap,  "%02d:%02d:%02d:%02d",
                stopwatch_inst[5], stopwatch_inst[6], stopwatch_inst[7], stopwatch_inst[8]);
            moveCursor(1, 5);
            lcdString(lcd_lap);

            stopwatch_inst[0] = stopwatch_inst[0] & 0b1001;
            printf("Input Button %d\n", btn_value);
            btn_value = 0;
            btn_valid = 0;
        }

        sprintf(lcd_sec, "%02d:%02d:%02d:%02d",
            stopwatch_inst[1], stopwatch_inst[2], stopwatch_inst[3], stopwatch_inst[4]);

        moveCursor(0, 5);
        lcdString(lcd_sec);
        msleep(1);
    }

    cleanup_platform();
    return 0;
}

void btn_isr(void *CallBackRef) {
    XGpio *Gpio_ptr = (XGpio *)CallBackRef;
    // Interrupt 발생 Pin 확인, 상태 읽기
    btn_value = XGpio_DiscreteRead(Gpio_ptr, BTN_CHANNEL);

    if (btn_value) btn_valid = 1;
    else if (btn_value == 0) btn_valid = 0;

    // Clear 않으면 ISR 계속 재실행
    XGpio_InterruptClear(&btn_inst, BTN_CHANNEL);
}

void RecvHandler(void *CallBackRef, unsigned int EventData) {
    uint8_t rxData;
    // 받은 Data를 사용하지 않더라도 Recv 해줘야 Interrupt 해제
    XUartLite_Recv(CallBackRef, &rxData, 1);
    printf("recv %c\n", rxData);
    return;
}

void SendHandler(void *CallBackRef, unsigned int EventData) {
    return;
}

void lcdCommand(uint8_t command) {
	uint8_t high_nibble, low_nibble;
	uint8_t i2c_buffer[4];

	high_nibble = command & 0xf0;
	low_nibble = (command << 4) & 0xf0;

    // LCD Data d7 d6 d5 d4 BL en rw rs
	i2c_buffer[0] = high_nibble | 0x0c;		// Backlight = 1, en = 1, rs = 0, rw = 0
	i2c_buffer[1] = high_nibble | 0x08;		// Backlight = 1, en = 0, rs = 0, rw = 0
	i2c_buffer[2] = low_nibble  | 0x0c;		// Backlight = 1, en = 1, rs = 0, rw = 0
	i2c_buffer[3] = low_nibble  | 0x08;		// Backlight = 1, en = 0, rs = 0, rw = 0

	XIic_Send(i2c_inst.BaseAddress, 0x27, i2c_buffer, 4, XIIC_STOP);
}

void lcdData(uint8_t data) {
	uint8_t high_nibble, low_nibble;
	uint8_t i2c_buffer[4];

	high_nibble = data & 0xf0;
	low_nibble = (data << 4) & 0xf0;

    // LCD Data d7 d6 d5 d4 BL en rw rs
	i2c_buffer[0] = high_nibble | 0x0d;     // Backlight = 1, en = 1, rs = 0, rw = 1
	i2c_buffer[1] = high_nibble | 0x09;     // Backlight = 1, en = 0, rs = 0, rw = 1
	i2c_buffer[2] = low_nibble  | 0x0d;     // Backlight = 1, en = 1, rs = 0, rw = 1
	i2c_buffer[3] = low_nibble  | 0x09;     // Backlight = 1, en = 0, rs = 0, rw = 1

	XIic_Send(i2c_inst.BaseAddress, 0x27, i2c_buffer, 4, XIIC_STOP);
}

void i2cLCD_Init() {
	msleep(50);
	lcdCommand(0x33);
    msleep(5);
	lcdCommand(0x32);
    msleep(5);
	lcdCommand(0x28);
    msleep(5);
	lcdCommand(0x0c);
    msleep(5);
	lcdCommand(0x06);
    msleep(5);
	lcdCommand(0x01);
    msleep(2);
}

void lcdString(char *str) {
	while(*str)lcdData(*str++);
}

void moveCursor(uint8_t row, uint8_t col) {
	lcdCommand(0x80 | row << 6 | col);
}

void lcdClear() {
    lcdCommand(0x01);
}
