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

#define ULTRASONIC_ADDR XPAR_MYIP_ULTRASONIC_0_BASEADDR

int main()
{
    init_platform();

    print("Hello World\n");
    print("Successfully ran Hello World application\n");

    volatile unsigned int *ultrasonic_inst = (volatile unsigned int *)ULTRASONIC_ADDR;

    while (1) {
        printf("Distance : %d\n", ultrasonic_inst[0]);
        msleep(500);
    }

    cleanup_platform();
    return 0;
}
