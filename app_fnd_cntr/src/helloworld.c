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
#include "xgpio.h"

#define BTN_ADDR XPAR_AXI_GPIO_BTN_BASEADDR
#define BTN_CHANNEL 1
#define FND_ADDR XPAR_MYIP_FND_0_BASEADDR

int main() {
    init_platform();

    print("Hello World\n");
    print("Successfully ran Hello World application\n");

    XGpio btn_inst;
    XGpio_Initialize(&btn_inst, BTN_ADDR);
    XGpio_SetDataDirection(&btn_inst, BTN_CHANNEL, 0xf);

    // fnd_cntr[0] → fnd_value, fnd_cntr[1] → hex_bcd
    // fnd_cntr Port 초기화, 배열처럼 연결
    volatile unsigned int *fnd_cntr = (volatile unsigned int *)FND_ADDR;
    fnd_cntr[1] = 0;
    // fnd_cntr[0] = 0x1234;

    uint32_t btn_data;
    uint32_t data = 0, btn_cnt = 0;
    uint8_t btn_vaild = 0;
    while (1) {
        btn_data = XGpio_DiscreteRead(&btn_inst, BTN_CHANNEL);
        if (btn_data != 0 && btn_vaild == 0) {
            btn_cnt++;
            if (btn_cnt >= 10000) {
                btn_vaild = 1;
                btn_cnt = 0;
                switch (btn_data) {
                    case 1: data = data + 1; break;
                    case 2: data = data + 10; break;
                    case 4: data = data - 10; break;
                    case 8: data = data - 1; break;
                }
                printf("btn_data %d\n", btn_data);
            }
        }   
        else if (btn_data == 0) {
            btn_vaild = 0;
        }

        fnd_cntr[0] = data;
    }

    cleanup_platform();
    return 0;
}
