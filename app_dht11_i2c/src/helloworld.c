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
#include <xiic_l.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"        // Platform 설정 Header
#include "sleep.h"
#include "xiic.h"               // I2C 통신 Header

#define DHT11_ADDR XPAR_MYIP_DHT11_0_BASEADDR
#define I2C_ADDR XPAR_AXI_IIC_0_BASEADDR

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

int main() {
    init_platform();
    print("Success Start DHT11\n");

    volatile unsigned int *dht11_inst = (volatile unsigned int *)DHT11_ADDR;    // DHT11 초기화
    XIic_Initialize(&i2c_inst, I2C_ADDR);   // I2C 통신 초기화

    i2cLCD_Init();
    moveCursor(0, 0);
    lcdString("Humidity    : ");
    moveCursor(1, 0);
    lcdString("Temperature : ");

    char lcd_humi[20];
    char lcd_tmpr[20];
    uint32_t dht_cnt = 1;
    while (1) {
        printf("Humidity : %d, Temperature : %d, Count : %d\n", dht11_inst[0], dht11_inst[1], dht_cnt);
        dht_cnt++;

        sprintf(lcd_humi, "%2d", dht11_inst[0]);
        sprintf(lcd_tmpr, "%2d", dht11_inst[1]);
        
        moveCursor(0, 14);
        lcdString(lcd_humi);
        moveCursor(1, 14);
        lcdString(lcd_tmpr);

        // sprintf(lcd_humi, "Humidity : %d", dht11_inst[0]);
        // sprintf(lcd_tmpr, "Temperature : %d", dht11_inst[1]);
        // printf("%s, %s\n", lcd_humi, lcd_tmpr);

        // moveCursor(0, 0);
        // lcdString(lcd_humi);
        // moveCursor(1, 0);
        // lcdString(lcd_tmpr);
        sleep(5);
    }

    cleanup_platform();
    return 0;
}
