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
#include "xgpio.h"
#include "xiic.h"
#include "sleep.h"

#define BTN_ADDR XPAR_AXI_GPIO_0_BASEADDR
#define BTN_CHANNEL 1
#define IIC_ADDR XPAR_AXI_IIC_0_BASEADDR
#define STOPWATCH_ADDR XPAR_MYIP_STOP_WATCH_0_BASEADDR

int main () {
    init_platform();
    print("Success Start Stopwatch\n");

    XGpio btn_inst;
    XGpio_Initialize(&btn_inst, BTN_ADDR);
    XGpio_SetDataDirection(&btn_inst, BTN_CHANNEL, 0b1111);

    XIic iic_inst;
    XIic_Initialize(&iic_inst, IIC_ADDR);

    volatile unsigned int *stopwatch_inst = (volatile unsigned int *)STOPWATCH_ADDR;

    while (1) {
        stopwatch_inst[0] = 1;
        printf("sec : %2d, csec : %2d\n", stopwatch_inst[1], stopwatch_inst[2]);
        sleep(1);
    }

    cleanup_platform();
    return 0;
}
