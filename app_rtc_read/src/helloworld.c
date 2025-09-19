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
#include <sys/_intsup.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "sleep.h"

volatile unsigned int *rtc_inst = (volatile unsigned int *)XPAR_MYIP_RTC_READ_0_BASEADDR;

char* rtcDays[8] = {
		"Day", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

uint8_t bcd_to_dec(uint8_t bcd);

int main () {
    init_platform();
    print("Success Start RTC\n");

    uint8_t sec, min, hour;
    uint8_t date, month, day, year;

    while (1) {
        if (rtc_inst[9] == 0) {
            rtc_inst[0] = 1;
        }
        
        if (rtc_inst[8] == 1) {
            rtc_inst[0] = 0;
            sec   = bcd_to_dec(rtc_inst[1]);
            min   = bcd_to_dec(rtc_inst[2]);
            hour  = bcd_to_dec(rtc_inst[3]);
            date  = bcd_to_dec(rtc_inst[4]);
            month = bcd_to_dec(rtc_inst[5]);
            day   = bcd_to_dec(rtc_inst[6]);
            year  = bcd_to_dec(rtc_inst[7]);
            printf("20%02d-%02d-%02d(%s) %02d:%02d:%02d\n", year, month, date, rtcDays[day], hour, min, sec);
            sleep(1);
        }
    }

    cleanup_platform();
    return 0;
}

uint8_t bcd_to_dec(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}