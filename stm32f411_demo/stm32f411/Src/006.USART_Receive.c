/*
 * 006.USART_Receive.c
 *
 *  Created on: Sep 9, 2023
 *      Author: Dell
 */


#include <stdio.h>
#include <string.h>
#include "stm32f411.h"
#include "stm32f411_gpio_driver.h"
#include "stm32f411_uart_driver.h"


char msg[16];

USART_Handle_t usart2_handle;



void USART2_Init()
{
	usart2_handle.pUSARTx = USART2;
	usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	usart2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	usart2_handle.USART_Config.USART_Mode = USART_MODE_ONLY_RX;//generates sclk of 8MHz
	usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	usart2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	usart2_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;

	USART_PeriClockControl(USART2, ENABLE);
	USART_Init(&usart2_handle);

}

void USART2_GPIOInits()
{
	GPIO_Handle_t usart_gpios;

	usart_gpios.pGPIOx = GPIOA;
	usart_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	usart_gpios.GPIO_PinConfig.GPIO_PinAltFunMode = 7;
	usart_gpios.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	usart_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	usart_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&usart_gpios);

	//USART2 RX
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&usart_gpios);
}

int main()
{
	USART2_GPIOInits();
	USART2_Init();

	USART_PeripheralControl(USART2, ENABLE);


	while(1)
	{
		USART_ReceiveData(&usart2_handle, (uint8_t*)msg, 6);
	}

	return 0;
}
