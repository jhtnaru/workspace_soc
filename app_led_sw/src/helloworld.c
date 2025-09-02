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
#include "xparameters.h"    // 각종 설정값 확인
#include "sleep.h"          // Delay 함수 사용 위한 Header
#include "xgpio.h"          // GPIO 사용 위한 Header

// 접근을 위한 기본 주소값 선언
#define GPIO_ADDR XPAR_AXI_GPIO_LED_SW_BASEADDR
#define LED_CHANNEL 1
#define SW_CHANNEL 2

int main() {
    init_platform();

    print("Hello World\n\r");
    print("Successfully ran Hello World application");

    XGpio gpio_device;      // GPIO 사용을 위한 구조체 선언
    // 선언한 GPIO 구조체와 GPIO Port 연결
    XGpio_Initialize(&gpio_device, GPIO_ADDR);
    
    // Port, Channel의 Input, Output 설정
    XGpio_SetDataDirection(&gpio_device,
        LED_CHANNEL, 0);
    XGpio_SetDataDirection(&gpio_device,
        SW_CHANNEL, 0xffff);

    u32 data;
    while (1) {
        // print("Hello\n\r");
        // Input Port Read
        data = XGpio_DiscreteRead(&gpio_device, SW_CHANNEL);
        printf("swtich : %04x\n", data);
        // Output Port Write
        XGpio_DiscreteWrite(&gpio_device, LED_CHANNEL, data);
        sleep(1);
    }

    cleanup_platform();
    return 0;
}