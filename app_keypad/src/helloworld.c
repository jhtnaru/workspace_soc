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

#define KEYPAD_ADDR XPAR_MYIP_KEYPAD_0_BASEADDR

int main()
{
    init_platform();
    print("Success Start Keypad\n");

    volatile unsigned int *keypad_inst = (volatile unsigned int *)KEYPAD_ADDR;
    
    uint8_t key_prev = 0;
    while (1) {
        if (keypad_inst[1] && !key_prev) {
            key_prev = 1;
            printf("Key : %d\n", keypad_inst[0]);
        }
        else if (!keypad_inst[1]) {
            key_prev = 0;
        }
    }

    cleanup_platform();
    return 0;
}
