/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// register address
#define GPIOA_BASE	0x40010800
#define GPIOA_CRL	*(volatile unsigned int *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH	*(volatile unsigned int *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR	*(volatile unsigned int *)(GPIOA_BASE + 0x0C)
#define GPIOA_IDR	*(volatile unsigned int *)(GPIOA_BASE + 0x08)

#define GPIOB_BASE	0x40010C00
#define GPIOB_CRL	*(volatile unsigned int *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH	*(volatile unsigned int *)(GPIOB_BASE + 0x04)
#define GPIOB_ODR	*(volatile unsigned int *)(GPIOB_BASE + 0x0C)
#define GPIOB_IDR	*(volatile unsigned int *)(GPIOB_BASE + 0x08)

#define RCC_BASE	0x40021000
#define RCC_APB2ENR	*(volatile unsigned int *)(RCC_BASE + 0x18)






void clock_init(void)
{
	// INIT CLOCK FOR GPIO
	RCC_APB2ENR |= (1<<2);
	RCC_APB2ENR |= (1<<3);

}
void GPIO_init(void)
{
	//port A pin1 input floating register
	GPIOA_CRL = 0x0 ;
	//00: Input mode (reset state)
	//01: Floating input (reset state)
	GPIOA_CRL |= (0x4<<4);


	//port A pin13 input floating register
	GPIOA_CRH = 0x0 ;
	//00: Input mode (reset state)
	//01: Floating input (reset state)
	GPIOA_CRH |= (0x4<<20);


	//===========================

	//port B pin1 output Open-drain mode
	GPIOB_CRL = 0x0 ;
	//01: Output mode, max speed 10 MHz
	//01: General purpose output Open-drain
	GPIOB_CRL |=(0x5<<4);


	//port B pin13 output Open-drain mode
	GPIOB_CRH = 0x0 ;
	//01: Output mode, max speed 10 MHz
	//01: General purpose output Open-drain
	GPIOB_CRH |=(0x5<<20);

}
void delay()
{
	unsigned int i;
	for(i =0; i< 1000; i++);
}


int main(void)
{
	clock_init();
	GPIO_init();
	GPIOB_ODR |=(1<<1);
	GPIOB_ODR |=(1<<13);
	while(1)
	{
		if(((GPIOA_IDR & (1<<1)) >> 1) == 0)
		{
			GPIOB_ODR ^= (1<<1);
			while(((GPIOA_IDR & (1<<1)) >> 1) == 0);
		}
		if(((GPIOA_IDR & (1<<13)) >> 13) == 1)// multiple pressing
		{
			GPIOB_ODR ^=(1<<13);
		}

		delay();

	}
}
