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

#define BTN_ADDR XPAR_AXI_GPIO_0_BASEADDR
#define BTN_CHANNEL 1
#define I2C_ADDR XPAR_AXI_IIC_0_BASEADDR
#define STOPWATCH_ADDR XPAR_MYIP_STOP_WATCH_0_BASEADDR

XIic i2c_inst;

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

int main () {
    init_platform();
    print("Success Start Stopwatch\n");

    XGpio btn_inst;
    XGpio_Initialize(&btn_inst, BTN_ADDR);
    XGpio_SetDataDirection(&btn_inst, BTN_CHANNEL, 0b1111);

    XIic_Initialize(&i2c_inst, I2C_ADDR);
    volatile unsigned int *stopwatch_inst = (volatile unsigned int *)STOPWATCH_ADDR;

    i2cLCD_Init();
    moveCursor(0, 0);
    lcdString("TIME 00:00:00:00");
    moveCursor(1, 0);
    lcdString("LAP  00:00:00:00");

    char lcd_sec[16], lcd_lap[16];

    uint8_t btn_value;
    uint8_t bnt_prev = 0;
    while (1) {
        btn_value = XGpio_DiscreteRead(&btn_inst, BTN_CHANNEL);

        if (btn_value && !bnt_prev) {
            bnt_prev = 1;
            if (btn_value == 0b0001) {
                stopwatch_inst[0] = stopwatch_inst[0] ^ 0b0001;
            }
            else if (btn_value == 0b0010) {
                stopwatch_inst[0] = stopwatch_inst[0] | 0b0010;
                sprintf(lcd_lap,  "%02d:%02d:%02d:%02d",
                    stopwatch_inst[5], stopwatch_inst[6], stopwatch_inst[7], stopwatch_inst[8]);
            }
            else if (btn_value == 0b0100) {
                stopwatch_inst[0] = stopwatch_inst[0] | 0b0100;
                sprintf(lcd_lap,  "%02d:%02d:%02d:%02d",
                    stopwatch_inst[5], stopwatch_inst[6], stopwatch_inst[7], stopwatch_inst[8]);
            }
            moveCursor(1, 5);
            lcdString(lcd_lap);
        }
        else if (btn_value == 0) {
            bnt_prev = 0;
            stopwatch_inst[0] = stopwatch_inst[0] & 0b1001;
        }

        sprintf(lcd_sec, "%02d:%02d:%02d:%02d",
            stopwatch_inst[1], stopwatch_inst[2], stopwatch_inst[3], stopwatch_inst[4]);

        moveCursor(0, 5);
        lcdString(lcd_sec);

        // stopwatch_inst[0] = 1;
        // moveCursor(0, 4);
        // lcdData(stopwatch_inst[1]/10%10 + '0');
        // lcdData(stopwatch_inst[1]%10 + '0');
        // lcdData(':');
        // lcdData(stopwatch_inst[2]/10%10 + '0');
        // lcdData(stopwatch_inst[2]%10 + '0');

        msleep(10);
    }

    cleanup_platform();
    return 0;
}