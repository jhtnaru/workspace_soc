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

#define SENSOR_D_ADDR XPAR_MYIP_SENSOR_DGT_0_BASEADDR

volatile unsigned int *sensor_d_inst = (volatile unsigned int *)SENSOR_D_ADDR;

int main () {
    init_platform();
    print("Success Start Sensor Digital\n");

    while (1) {
        printf("Sensor %d\n", sensor_d_inst[0]);
        msleep(500);
    }

    cleanup_platform();
    return 0;
}
