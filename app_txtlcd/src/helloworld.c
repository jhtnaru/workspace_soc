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

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "sleep.h"

#define TXTLCD_ADDR XPAR_MYIP_IIC_TXTLCD_0_BASEADDR

void lcdCommand(uint8_t command, volatile unsigned int *txtlcd_inst) {
    while (txtlcd_inst[3]);
    txtlcd_inst[0] = 0x27;      // addr
    txtlcd_inst[1] = command;   // send_buffer
    txtlcd_inst[2] = 0x01;      // send = 1, rs = 0;
    while (txtlcd_inst[3]);
    txtlcd_inst[2] = 0;         // send = 0, rs = 0;
}

void lcdData(uint8_t data, volatile unsigned int *txtlcd_inst) {
    while (txtlcd_inst[3]);
    txtlcd_inst[0] = 0x27;
    txtlcd_inst[1] = data;
    txtlcd_inst[2] = 0x03;      // send = 1, rs = 1;
    while (txtlcd_inst[3]);
    txtlcd_inst[2] = 0;         // send = 0, rs = 0;
}

void i2cLCD_Init(volatile unsigned int *txtlcd_inst) {
	msleep(50);
	lcdCommand(0x33, txtlcd_inst);
    msleep(5);
	lcdCommand(0x32, txtlcd_inst);
    msleep(5);
	lcdCommand(0x28, txtlcd_inst);
    msleep(5);
	lcdCommand(0x0c, txtlcd_inst);
    msleep(5);
	lcdCommand(0x06, txtlcd_inst);
    msleep(5);
	lcdCommand(0x01, txtlcd_inst);
    msleep(2);
}

void lcdString(char *str, volatile unsigned int *txtlcd_inst) {
	while(*str)lcdData(*str++, txtlcd_inst);
}

void moveCursor(uint8_t row, uint8_t col, volatile unsigned int *txtlcd_inst) {
	lcdCommand(0x80 | row << 6 | col, txtlcd_inst);
}

void lcdClear(volatile unsigned int *txtlcd_inst) {
    lcdCommand(0x01, txtlcd_inst);
}

int main () {
    init_platform();
    print("Success Start txtlcd\n");

    volatile unsigned int *txtlcd_inst = (volatile unsigned int *)TXTLCD_ADDR;    

    i2cLCD_Init(txtlcd_inst);
    moveCursor(0, 0, txtlcd_inst);
    lcdString("Humidity    : 11", txtlcd_inst);
    moveCursor(1, 0, txtlcd_inst);
    lcdString("Temperature : 11", txtlcd_inst);

    while (1) {
    
    }

    cleanup_platform();
    return 0;
}
