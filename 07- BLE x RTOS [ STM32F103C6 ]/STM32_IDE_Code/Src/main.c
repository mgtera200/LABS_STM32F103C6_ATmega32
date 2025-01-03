/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

//////////////////////////////
// Eng. TERA
////////////////////////////

#include "STM32F103x8.h"
#include "Scheduler.h"
#include "core_cm3.h"
#include "CortexMx_OS_Porting.h"
#include "USART_DRIVER.h"
#include "GPIO_DRIVER.h"

// Task
Task_Creation Task1, Task2;




// Buffers for USART data
uint16_t buff;
uint16_t buffer;

// Flags for task activation
uint8_t task1_flag = 0, task2_flag = 0;

// USART callback function to handle incoming data
void Usart_callback(interrupts_Bits *IRQ)
{
    MCAL_USART_ReceiveChar(USART1, &buff);

    switch (buff)
    {
    case 0x10:
        if (task1_flag == 0)
        {
            task1_flag = 1;
        }
        break;

    case 0x20:
        if (task2_flag == 0)
        {
            task2_flag = 1;
        }
        break;

    case 0x11:
        task1_flag = 0;
        MCAL_GPIO_WritePin(GPIOB, 9, 0);
        break;

    case 0x22:
        task2_flag = 0;
        MCAL_GPIO_WritePin(GPIOB, 8, 0);
        break;
    }
}

// Function to send a command over USART
void sendCommand(char *command)
{
    uint8_t length = strlen(command);

    for (int i = 0; i <= length; i++)
    {
        buffer = (uint16_t)command[i];
        MCAL_USART_SendChar(USART1, &buffer);
    }
}

// Task 1: Toggles GPIO pin based on flag
void task1(void)
{
    while (1)
    {
        while (task1_flag == 1)
        {
            MCAL_GPIO_TogglePin(GPIOB, 9);
            teraRTOS_TaskWait(100, &Task1);
        }
    }
}

// Task 2: Toggles GPIO pin based on flag
void task2(void)
{
    while (1)
    {
        while (task2_flag == 1)
        {
            MCAL_GPIO_TogglePin(GPIOB, 8);
            teraRTOS_TaskWait(200, &Task2);
        }
    }
}

// Main entry point of the program
int main(void)
{
    TERA_RTOS_ErrorType Error;

    // Initialize hardware (Clock, Reset, etc.)
    HW_init();
    GPIOB_CLOCK_EN();
    USART1_CLOCK_EN();

    // GPIO Pin configuration
    Pin_Config_t Pin_config;
    Pin_config.Pin_Num = 8;
    Pin_config.mode = Output_Push_pull;
    Pin_config.Speed_Output = speed_10;
    MCAL_GPIO_Init(GPIOB, &Pin_config);

    Pin_config.Pin_Num = 9;
    Pin_config.mode = Output_Push_pull;
    Pin_config.Speed_Output = speed_10;
    MCAL_GPIO_Init(GPIOB, &Pin_config);

    // USART initialization
    USART_Config_t UART_CNFG_s;
    UART_CNFG_s.Async_EN = USART_Enable;
    UART_CNFG_s.Async_Config_s.Baud_Rate = 9600;
    UART_CNFG_s.Async_Config_s.Stop_Bits = Stop_1;
    UART_CNFG_s.Async_Config_s.Word_Length = Eight_bits;
    UART_CNFG_s.interrupts_CNFG.RX_Interrupt_Enable_Or_Disable = USART_Enable;
    UART_CNFG_s.CallBack_FN = Usart_callback;
    MCAL_USART_Init(USART1, &UART_CNFG_s);
    MCAL_USART_GPIO_Pins_Config(USART1);

    // Send initialization commands via USART
    sendCommand("AT+RESET\r\n");
    sendCommand("AT+NAMETERA\r\n");
    sendCommand("AT+UUID0xFFE0\r\n");
    sendCommand("AT+CHAR0xDEAD\r\n");

    // Initialize RTOS
    if (TERA_RTOS_init() != NoError)
        while (1);

    // Configure and create Task 1
    Task1.Stack_Size = 1024;
    Task1.TaskEntry_Ptr = task1;
    Task1.Priority = 4;
    strcpy(Task1.TaskName, "Task_1");
    Error = teraRTOS_CreateTask(&Task1);

    // Configure and create Task 2
    Task2.Stack_Size = 1024;
    Task2.TaskEntry_Ptr = task2;
    Task2.Priority = 4;
    strcpy(Task2.TaskName, "Task_2");
    Error = teraRTOS_CreateTask(&Task2);

    // Activate tasks
    teraRTOS_ActivateTask(&Task1);
    teraRTOS_ActivateTask(&Task2);

    // Start the RTOS
    teraRTOS_START();

    // Infinite loop (Idle task)
    while (1)
    {
    }
}
