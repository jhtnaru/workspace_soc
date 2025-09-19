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
#include "xgpio.h"
#include "sleep.h"

#define BTN_ADDR XPAR_AXI_BTN_GPIO_0_BASEADDR
#define BTN_CHANNEL 1
#define PWM_ADDR XPAR_MYIP_PWM_4096STEP_0_BASEADDR

int main () {
    init_platform();
    print("Success Start PWM\n");

    XGpio btn_inst;
    XGpio_Initialize(&btn_inst, BTN_ADDR);
    XGpio_SetDataDirection(&btn_inst, BTN_CHANNEL, 0b1111);

    volatile unsigned int *pwm_inst = (volatile unsigned int *)PWM_ADDR;

    uint8_t btn_value = 0, bnt_prev = 0;
    uint8_t pwm_mode = 0, duty_mode = 0, duty_dir = 0;
    uint32_t pwm_duty = 0;
    printf("PWM Mode %d, Duty Mode %d\n", pwm_mode, duty_mode);
    while (1) {
        btn_value = XGpio_DiscreteRead(&btn_inst, BTN_CHANNEL);

        if (btn_value && !bnt_prev) {
            bnt_prev = 1;
            if (btn_value == 0b0001) {
                if (pwm_mode >= 4) pwm_mode = 0;
                else pwm_mode++;
                printf("PWM Mode %d, Duty Mode %d\n", pwm_mode, duty_mode);
            }
            else if (btn_value == 0b0010) {
                if (pwm_duty >= 10) pwm_duty = pwm_duty - 10;
                printf("PWM Duty %d\n", pwm_duty);
            }
            else if (btn_value == 0b0100) {
                if (pwm_duty <= 4085) pwm_duty = pwm_duty + 10;
                printf("PWM Duty %d\n", pwm_duty);
            }
            else if (btn_value == 0b1000) {
                duty_mode = duty_mode ^ 0b1;
                printf("PWM Mode %d, Duty Mode %d\n", pwm_mode, duty_mode);
            }
        }
        else if (btn_value == 0) {
            bnt_prev = 0;
        }

        if (duty_mode == 0) {
            if (pwm_mode == 0) {
                if (duty_dir == 0) {
                    if (pwm_duty >= 525) duty_dir = 1;
                    else pwm_duty = pwm_duty + 5;
                }
                else if (duty_dir == 1) {
                    if (pwm_duty <= 85) duty_dir = 0;
                    else pwm_duty = pwm_duty - 5;
                }
            }
            else {
                if (duty_dir == 0) {
                    if (pwm_duty >= 4080) duty_dir = 1;
                    else pwm_duty = pwm_duty + 15;
                }
                else if (duty_dir == 1) {
                    if (pwm_duty <= 15) duty_dir = 0;
                    else pwm_duty = pwm_duty - 15;
                }                
            }
        }
        
        pwm_inst[0] = 1 << pwm_mode;
        pwm_inst[1] = pwm_duty;
        msleep(15);
    }

    cleanup_platform();
    return 0;
}
