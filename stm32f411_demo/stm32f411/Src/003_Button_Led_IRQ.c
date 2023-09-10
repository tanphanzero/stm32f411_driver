/*
 * 003_Button_Led_IRQ.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Dell
 */


#include <stdint.h>
#include <stdio.h>
#include "stm32f411_gpio_driver.h"
#include "stm32f411.h"
int a = 0;
void delay()
{
	for (int i = 0; i < 500000; i++);
}

int main(void) {

	GPIO_Handle_t GpioLed ,GPIObutton ;
	GpioLed.pGPIOx = GPIOD ;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GpioLed.GPIO_PinConfig.GPIO_PinAltFunMode = 0;

//	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_Init(&GpioLed);

	GPIObutton.pGPIOx = GPIOA ;
	GPIObutton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIObutton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIObutton.GPIO_PinConfig.GPIO_PinOPType = 0;
	GPIObutton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIObutton.GPIO_PinConfig.GPIO_PinAltFunMode = 0;

	GPIO_Init(&GPIObutton);
//	GPIO_PeriClockControl(GPIOA, ENABLE);

	//IRQ configurations

	GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI0 , 15);

	while(1);

	return 0;
}

void EXTI0_IRQHandler(void){
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_0);
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
	a++;
}

