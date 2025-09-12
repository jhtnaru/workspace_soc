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
#include "sleep.h"

#define PWM0_ADDR XPAR_MYIP_PWM_0_BASEADDR
#define PWM1_ADDR XPAR_MYIP_PWM_1_BASEADDR
#define PWM2_ADDR XPAR_MYIP_PWM_2_BASEADDR
#define PWM3_ADDR XPAR_MYIP_PWM_3_BASEADDR
#define PWM4_ADDR XPAR_MYIP_PWM_4_BASEADDR

int main()
{
    init_platform();
    print("Success Start PWM 5ea\n");

    volatile unsigned int *pwm0_inst = (volatile unsigned int *)PWM0_ADDR;
    volatile unsigned int *pwm1_inst = (volatile unsigned int *)PWM1_ADDR;
    volatile unsigned int *pwm2_inst = (volatile unsigned int *)PWM2_ADDR;
    volatile unsigned int *pwm3_inst = (volatile unsigned int *)PWM3_ADDR;
    volatile unsigned int *pwm4_inst = (volatile unsigned int *)PWM4_ADDR;

    uint8_t pwm0_duty = 0;
    uint8_t pwm1_duty = 60;
    uint8_t pwm2_duty = 120;
    uint8_t pwm3_duty = 180;
    uint8_t pwm4_duty = 240;
    uint8_t updown_flag0 = 1, updown_flag1 = 1, updown_flag2 = 1, updown_flag3 = 1, updown_flag4 = 1;
    while (1) {
        if (pwm0_duty >= 250) updown_flag0 = 0;
        else if (pwm0_duty <= 0) updown_flag0 = 1;
        if (pwm1_duty >= 250) updown_flag1 = 0;
        else if (pwm1_duty <= 0) updown_flag1 = 1;
        if (pwm2_duty >= 250) updown_flag2 = 0;
        else if (pwm2_duty <= 0) updown_flag2 = 1;
        if (pwm3_duty >= 250) updown_flag3 = 0;
        else if (pwm3_duty <= 0) updown_flag3 = 1;
        if (pwm4_duty >= 250) updown_flag4 = 0;
        else if (pwm4_duty <= 0) updown_flag4 = 1;

        if (updown_flag0) pwm0_duty++;
        else if (updown_flag0 == 0) pwm0_duty--;
        if (updown_flag1) pwm1_duty++;
        else if (updown_flag1 == 0) pwm1_duty--;
        if (updown_flag2) pwm2_duty++;
        else if (updown_flag2 == 0) pwm2_duty--;
        if (updown_flag3) pwm3_duty++;
        else if (updown_flag3 == 0) pwm3_duty--;
        if (updown_flag4) pwm4_duty++;
        else if (updown_flag4 == 0) pwm4_duty--;

        pwm0_inst[0] = pwm0_duty;
        pwm1_inst[0] = pwm1_duty;
        pwm2_inst[0] = pwm2_duty;
        pwm3_inst[0] = pwm3_duty;
        pwm4_inst[0] = pwm4_duty;
        msleep(10);
    }

    cleanup_platform();
    return 0;
}
