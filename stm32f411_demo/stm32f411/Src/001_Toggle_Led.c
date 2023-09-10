/*
 * 001_Toggle_Led.c
 *
 *  Created on: Sep 4, 2023
 *      Author: Dell
 */

#include "stm32f411_gpio_driver.h"
#include "stm32f411.h"

void delay()
{
	for (int i = 0; i < 500000; i++);
}


int main()
{
	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_Pinconfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_Pinconfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_Pinconfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_Pinconfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_Pinconfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_Init(&GpioLed);

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
		delay();
	}
}

