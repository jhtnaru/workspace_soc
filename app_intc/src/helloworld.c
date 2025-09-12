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
#include <stdio.h>          // 기본 출력이 UART로 되어 있음
#include <sys/_intsup.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xintc.h"          // Interrupt 사용 Header
#include "xuartlite.h"      // UART 사용 Header, 수신을 위해서 별도 초기화 필요
#include "xil_exception.h"  // 예외 처리 Header, Interrupt도 일종의 예외 처리

// Base Address 선언, UART, Button, Interrupt
#define UART_ADDR XPAR_AXI_UARTLITE_0_BASEADDR
#define BTN_ADDR XPAR_AXI_BTN_GPIO_0_BASEADDR
#define INTC_ADDR XPAR_XINTC_0_BASEADDR

// Interrupt ID 선언, UART 0, Button 1
#define UART_VEC_ID XPAR_FABRIC_AXI_UARTLITE_0_INTR
#define BTN_VEC_ID XPAR_FABRIC_AXI_BTN_GPIO_0_INTR

#define BTN_CHANNEL 1

XUartLite uart_inst;
XGpio btn_inst;
XIntc intc_inst;

void btn_isr(void *CallBackRef);
void RecvHandler(void *CallBackRef, unsigned int EventData);
void SendHandler(void *CallBackRef, unsigned int EventData);

int main () {
    init_platform();        // BSP 제공 초기화 함수, Console 초기화, Cache, Timer 등 Setting
    print("Success Start INTC\n");

    // UART, GPIO(Button), Interrupt 초기화
    XUartLite_Initialize(&uart_inst, UART_ADDR);
    XGpio_Initialize(&btn_inst, BTN_ADDR);
    XIntc_Initialize(&intc_inst, INTC_ADDR);

    // GPIO 각 bit 입˙출력 방향 결정
    XGpio_SetDataDirection(&btn_inst, BTN_CHANNEL, 0b1111);

    // Interrupt Controller에 ISR 등록 및 허용
    // XIntc_Connect, XIntc_Enable, XIntc_Start
    // Interrupt 발생시 호출될 ISR(Handler) 연결
    // UART 제공 Libarary Handler 연결,  내부적으로 RX / TX Event 처리하고 recv / send Callback 호출
    XIntc_Connect(&intc_inst, UART_VEC_ID,
        (XInterruptHandler)XUartLite_InterruptHandler, (void *)&uart_inst);
    XIntc_Connect(&intc_inst, BTN_VEC_ID,
        (XInterruptHandler)btn_isr, (void *)&btn_inst);
    // Interrupt Controller 내부 Mask 해제(Enable)하여 들어오는 IRQ 허용
    XIntc_Enable(&intc_inst, UART_VEC_ID);
    XIntc_Enable(&intc_inst, BTN_VEC_ID);
    // Interrupt Controller 시작, 내부 동작 활성화, XIN_REAL_MODE 실제 Hardware Mode 동작
    XIntc_Start(&intc_inst, XIN_REAL_MODE);

    // 장치 Level Interrupt 허용
    // GPIO 장치 내부 특정 Channel 또는 Pin의 Interrupt 발생 허용, 장치 Level Interrupt Mask
    XGpio_InterruptEnable(&btn_inst, BTN_CHANNEL);
    // GPIO 장치 Global Interrupt 출력 활성화, GPIO Interrupt 발생하면 신호를 Interrupt Controller 전달
    XGpio_InterruptGlobalEnable(&btn_inst);

    // UART 경우에만 송수신 Interrupt Handler 별도 연결 필요
    // UART 내부 ISR에서 Event 발생 시 호출할 사용자 Callback 등록
    XUartLite_SetRecvHandler(&uart_inst, RecvHandler, &uart_inst);
    XUartLite_SetSendHandler(&uart_inst, SendHandler, &uart_inst);
    // UART 장치 내부 Interrupt 허용, Register Level
    XUartLite_EnableInterrupt(&uart_inst);

    // CPU에서 Interrupt 예외 처리 허용 및 XIntc Handler 연결
    // Xil_ExceptionInit, Xil_ExceptionRegisterHandler, Xil_ExceptionEnable
    Xil_ExceptionInit();        // CPU 예외 처리 System 초기화
    // CPU가 Interrupt 받았을 때 실행할 최상위 Handler 등록
    // XIL_EXCEPTION_ID_INT - CPU가 Interrupt 받았을 때 이 Handler 실행
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
        (Xil_ExceptionHandler)XIntc_InterruptHandler, &intc_inst);
    Xil_ExceptionEnable();      // CPU Level Interrupt 허용

    while (1) {
    
    }

    cleanup_platform();
    return 0;
}

void btn_isr(void *CallBackRef) {
    unsigned int btn_value;
    XGpio *Gpio_ptr = (XGpio *)CallBackRef;
    // Interrupt 발생 Pin 확인, 상태 읽기
    btn_value = XGpio_DiscreteRead(Gpio_ptr, BTN_CHANNEL);

    if (btn_value == 0b0001) print("Button 0 Rising\n");
    else if (btn_value == 0b0010) print("Button 1 Rising\n");
    else if (btn_value == 0b0100) print("Button 2 Rising\n");
    else if (btn_value == 0b1000) print("Button 3 Rising\n");
    else if (btn_value == 0) print("Button Falling\n");

    // Clear 않으면 ISR 계속 재실행
    XGpio_InterruptClear(&btn_inst, BTN_CHANNEL);
}

void RecvHandler(void *CallBackRef, unsigned int EventData) {
    uint8_t rxData;
    // 받은 Data를 사용하지 않더라도 Recv 해줘야 Interrupt 해제
    XUartLite_Recv(CallBackRef, &rxData, 1);
    printf("recv %c\n", rxData);
    return;
}

void SendHandler(void *CallBackRef, unsigned int EventData) {
    return;
}