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
#include "sleep.h"
#include "xintc.h"
#include "xil_exception.h"
#include "xuartlite.h"

#define BTN_ADDR XPAR_AXI_BTN_GPIO_0_BASEADDR
#define BTN_CHANNEL 1
#define UART_ADDR XPAR_AXI_UARTLITE_0_BASEADDR
#define FAN_ADDR XPAR_MYIP_FAN_0_BASEADDR

#define INTC_ADDR XPAR_XINTC_0_BASEADDR
#define BTN_VEC_ID XPAR_FABRIC_AXI_BTN_GPIO_0_INTR
#define UART_VEC_ID XPAR_FABRIC_AXI_UARTLITE_0_INTR

XGpio btn_inst;
XIntc intc_inst;
XUartLite uart_inst;
volatile unsigned int *fan_inst = (volatile unsigned int *)FAN_ADDR;

void btn_isr(void *CallBackRef);
void RecvHandler(void *CallBackRef, unsigned int EventData);
void SendHandler(void *CallBackRef, unsigned int EventData);

volatile uint8_t btn_value;
volatile uint8_t btn_valid = 0;

int main () {
    init_platform();
    print("Success Start Fan Motor\n");

    XGpio_Initialize(&btn_inst, BTN_ADDR);
    XGpio_SetDataDirection(&btn_inst, BTN_CHANNEL, 0b1111);
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

    fan_inst[0] = 0b001;
    fan_inst[1] = 0;
    fan_inst[2] = 1;
    fan_inst[3] = 100;

    while (1) {
        if (btn_valid) {
            if (btn_value == 0b0001) {
                fan_inst[1] = fan_inst[1] ^ 0b1;
                if (fan_inst[1]) print("Fan Start\n");
                else if (fan_inst[1] == 0) print("Fan Stop\n");
            }
            else if (btn_value == 0b0010) {
                if (fan_inst[0] == 0b100) fan_inst[0] = 0b001;
                else fan_inst[0] = fan_inst[0] << 1;
                switch (fan_inst[0]) {
                    case 0b001 : print("IDLE Mode\n"); break;
                    case 0b010 : print("Digital Mode\n"); break;
                    case 0b100 : print("Analog Mode\n"); break;
                    default    : print("Default Mode\n"); break;
                }
            }
            else if (btn_value == 0b0100) {
                fan_inst[2] = fan_inst[2] ^ 0b1;
                if (fan_inst[2]) print("Forward\n");
                else if (fan_inst[2] == 0) print("Reverse\n");
            }
            else if (btn_value == 0b1000) {
                if (fan_inst[3] >= 250) fan_inst[3] = 100;
                else fan_inst[3] = fan_inst[3] + 10;
                printf("Angle %d\n", fan_inst[3]);
            }
            btn_value = 0;
            btn_valid = 0;
        }
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
