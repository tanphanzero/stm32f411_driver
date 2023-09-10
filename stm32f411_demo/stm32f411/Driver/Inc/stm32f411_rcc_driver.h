/*
 * stm32f411_rcc.h
 *
 *  Created on: Sep 9, 2023
 *      Author: Dell
 */

#ifndef INC_STM32F411_RCC_DRIVER_H_
#define INC_STM32F411_RCC_DRIVER_H_

#include "stm32f411.h"

uint32_t Get_PLL_P_CLK(void);
uint32_t Get_PLL_R_CLK(void);

uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);


#endif /* INC_STM32F411_RCC_DRIVER_H_ */
