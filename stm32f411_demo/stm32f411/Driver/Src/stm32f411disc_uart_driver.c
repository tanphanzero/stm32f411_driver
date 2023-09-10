/*
 * stm32f411disc_uart_driver.c
 *
 *  Created on: Sep 9, 2023
 *      Author: Dell
 */

#include "stm32f411_uart_driver.h"
#include "stm32f411_rcc_driver.h"
#include <stddef.h>
#include <stdio.h>

void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{

    // Variable to hold the APB clock
    uint32_t PCLKx;

    uint32_t usartdiv;

    // variables to hold Mantissa and Fraction values
    uint32_t M_part, F_part;

    uint32_t tempreg = 0;

    // Get the value of APB bus clock in to the variable PCLKx
    if (pUSARTx == USART1 || pUSARTx == USART6)
    {
        // USART1 and USART6 are hanging on APB2 bus
        PCLKx = RCC_GetPCLK2Value();
    }
    else
    {
        PCLKx = RCC_GetPCLK1Value();
    }

    // Check for OVER8 configuration bit
    if (pUSARTx->CR1 & (1 << USART_CR1_OVER8))
    {
        // OVER8 = 1 , over sampling by 8
        usartdiv = ((25 * PCLKx) / (2 * BaudRate));
    }
    else
    {
        // over sampling by 16
        usartdiv = ((25 * PCLKx) / (4 * BaudRate));
    }

    // Calculate the Mantissa part
    M_part = usartdiv / 100;

    // Place the Mantissa part in appropriate bit position . refer USART_BRR
    tempreg |= M_part << 4;

    // Extract the fraction part
    F_part = (usartdiv - (M_part * 100));

    // Calculate the final fractional
    if (pUSARTx->CR1 & (1 << USART_CR1_OVER8))
    {
        // OVER8 = 1 , over sampling by 8
        F_part = (((F_part * 8) + 50) / 100) & ((uint8_t)0x07);
    }
    else
    {
        // over sampling by 16
        F_part = (((F_part * 16) + 50) / 100) & ((uint8_t)0x0F);
    }

    // Place the fractional part in appropriate bit position . refer USART_BRR
    tempreg |= F_part;

    // copy the value of tempreg in to BRR register
    pUSARTx->BRR = tempreg;
}

void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        if (pUSARTx == USART1)
            USART1_PCLK_EN();
        else if (pUSARTx == USART2)
            USART2_PCLK_EN();
        else if (pUSARTx == USART6)
            USART6_PCLK_EN();
    }
    else
    {
        if (pUSARTx == USART1)
            USART1_PCLK_DI();
        else if (pUSARTx == USART2)
            USART2_PCLK_DI();
        else if (pUSARTx == USART6)
            USART6_PCLK_DI();
    }
}

void USART_Init(USART_Handle_t *pUSARTHandle)
{
    uint32_t temp = 0;

    // USART TX AND RX ENGINES ACC TO USART MODE CONFIGURATIONS
    if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
    {
        temp |= (1 << USART_CR1_RE);
    }
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
    {
        temp |= (1 << USART_CR1_TE);
    }
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
    {
        // Implement the code to enable the both Transmitter and Receiver bit fields
        temp |= ((1 << USART_CR1_RE) | (1 << USART_CR1_TE));
    }

    temp |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M;

    // configuring parity bits

    if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
    {
        // enable parity control
        temp |= (1 << USART_CR1_PCE);
    }
    else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
    {
        // Implement the code to enable the parity control
        temp |= (1 << USART_CR1_PCE);

        // Implement the code to enable ODD parity
        temp |= (1 << USART_CR1_PS);
    }

    // configuring the CR1 REgister
    pUSARTHandle->pUSARTx->CR1 = temp;

    // cr2 configuration
    temp = 0;
    if (pUSARTHandle->USART_Config.USART_NoOfStopBits == USART_STOPBITS_0_5)
    {
        temp |= (1 << USART_CR2_STOP);
    }
    else if (pUSARTHandle->USART_Config.USART_NoOfStopBits == USART_STOPBITS_2)
    {
        temp |= (2 << USART_CR2_STOP);
    }
    else if (pUSARTHandle->USART_Config.USART_NoOfStopBits == USART_STOPBITS_1_5)
    {
        temp |= (3 << USART_CR2_STOP);
    }
    // program the CR2 Register
    pUSARTHandle->pUSARTx->CR2 = temp;
    // configuring CR3 Register

    temp = 0;
    if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
    {
        temp |= (1 << USART_CR3_CTSE);
    }
    else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
    {
        temp |= (1 << USART_CR3_RTSE);
    }
    else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
    {
        temp |= (1 << USART_CR3_CTSE);
        temp |= (1 << USART_CR3_RTSE);
    }
    pUSARTHandle->pUSARTx->CR3 = temp;

    USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baud);
}

void USART_DeInit(USART_RegDef_t *pUSARTx)
{
    if (pUSARTx == USART1)
        USART1_REG_RESET();
    else if (pUSARTx == USART2)
        USART2_REG_RESET();
    else if (pUSARTx == USART6)
        USART6_REG_RESET();
}

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
	{
		pUSARTx->CR1 |= (1 << 13);
	}
	else
	{
		pUSARTx->CR1 &= ~(1 << 13);
	}
}


uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName)
{
    if (pUSARTx->SR & StatusFlagName)
    {
        return SET;
    }
    return RESET;
}

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    uint16_t *pdata;

    for (uint32_t i = 0; i < Len; i++)
    {
    	//wait until TXE flag is set in SR
        while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TXE));

        // check usart word length for 8 or 9 bits
        if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
        {
        	//load the DR with 2byte
            pdata = (uint16_t *)pTxBuffer;
            pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x1ff);

            // check for parity
            if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
            {
            	//bits of user data will be sent 9bit (2byte)
                pTxBuffer++;
                pTxBuffer++;
            }
            else //USART_PARITY_ENABLE, sent 8bit
            {
                pTxBuffer++;
            }
        }
        else //USART_WordLength = 8bit
        {
        	//This is 8bit data transfer
            pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0xff);
            //increment the buffer address
            pTxBuffer++;
        }
    }
    while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TC));
}

void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    // Loop over until "Len" number of bytes are transferred
    for (uint32_t i = 0; i < Len; i++)
    {
        //wait until RXNE flag is set in the SR
        while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_RXNE))
            ;

        // Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
        if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
        {
            // We are going to receive 9bit data in a frame
            // Now, check are we using USART_ParityControl control or not
            if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
            {
                // No parity is used , so all 9bits will be of user data
                // read only first 9 bits so mask the DR with 0x01FF
                *((uint16_t *)pRxBuffer) = (pUSARTHandle->pUSARTx->DR & (uint16_t)0x01FF);

                // Now increment the pRxBuffer two times
                pRxBuffer++;
                pRxBuffer++;
            }
            else
            {
                // Parity is used, so 8bits will be of user data and 1 bit is parity
                *pRxBuffer = (pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
                pRxBuffer++;
            }
        }
        else
        {
            // We are going to receive 8bit data in a frame
            // Now, check are we using USART_ParityControl control or not
            if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
            {
                // No parity is used , so all 8bits will be of user data

                // read 8 bits from DR
                *pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
            }
            else
            {
                // Parity is used, so , 7 bits will be of user data and 1 bit is parity
                // read only 7 bits , hence mask the DR with 0X7F
                *pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0x7F);
            }
            // Now , increment the pRxBuffer
            pRxBuffer++;
        }
    }
}

void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName)
{
	pUSARTx->SR &= ~(StatusFlagName);
}

void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (IRQNumber <= 31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if (IRQNumber > 31 && IRQNumber < 64)
		{
			//program ISER1 register
			*NVIC_ISER1 |= (1 << IRQNumber % 32);
		}
		else if (IRQNumber >= 64 && IRQNumber < 96)
		{
			//program ISER2 register
			*NVIC_ISER2 |= (1 << IRQNumber % 64);
		}
	}
	else
	{
		if (IRQNumber <= 31)
		{
			//program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if (IRQNumber > 31 && IRQNumber < 64)
		{
			//program ICER1 register
			*NVIC_ICER1 |= (1 << IRQNumber % 32);
		}
		else if (IRQNumber >= 64 && IRQNumber < 96)
		{
			//program ICER2 register
			*NVIC_ICER2 |= (1 << IRQNumber % 64);
		}
	}
}

void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	uint8_t ipr = IRQNumber/4;
	uint8_t irq = IRQNumber%4;

	*(NVIC_PR_BASE_ADDR + ipr) |= (IRQPriority << (8*irq + 4));
}


//*********------------COPY------------||----||----||------------COPY------------*********
//*********------------COPY------------||----||----||------------COPY------------*********
//*********------------COPY------------\/----\/----\/------------COPY------------*********
void USART_IRQHandling(USART_Handle_t *pHandle)
{
    uint8_t interruptEnFlag = 0;
    uint8_t flag = 0;

    // RXNE & RXNEIE
    interruptEnFlag = ((pHandle->pUSARTx->CR1 >> USART_CR1_RXNEIE) & 0x1);
    flag = ((pHandle->pUSARTx->SR >> USART_SR_RXNE) & 0x1);
    if (interruptEnFlag && flag)
    {
        if (pHandle->RxState == USART_BUSY_IN_RX && pHandle->RxLen > 0)
        {
            if (pHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
            {
                if (pHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
                {
                    // 9bits no parity
                    *((uint16_t *)pHandle->pRxBuffer) = pHandle->pUSARTx->DR & ((uint16_t)0x1FF);
                    pHandle->pRxBuffer++;
                    pHandle->pRxBuffer++;
                    pHandle->RxLen--;
                }
                else
                {
                    // 9bits w parity
                    *pHandle->pRxBuffer = pHandle->pUSARTx->DR & ((uint8_t)0xFF);
                    pHandle->pRxBuffer++;
                    pHandle->RxLen--;
                }
            }
            else
            {
                if (pHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
                {
                    // 8 bits no parity
                    *pHandle->pRxBuffer = ((uint8_t)pHandle->pUSARTx->DR) & ((uint8_t)0xFF);
                }
                else
                {
                    // 8 bits w parity
                    *pHandle->pRxBuffer = ((uint8_t)pHandle->pUSARTx->DR & ((uint8_t)0x7F));
                }
                pHandle->pRxBuffer++;
                pHandle->RxLen--;
            }
        }
        if (pHandle->RxLen <= 0)
        {
            // disable interrupts:
            pHandle->pUSARTx->CR1 &= ~(0x1 << USART_CR1_RXNEIE);

            // reset handle
            pHandle->pRxBuffer = NULL;
            pHandle->RxLen = 0;
            pHandle->RxState = USART_READY;

            // notify
            USART_ApplicationEventCallback(pHandle, USART_EVENT_RX_CMPLT);
        }
    }

    // TXE & TXEIE
    interruptEnFlag = ((pHandle->pUSARTx->CR1 >> USART_CR1_TXEIE) & 0x1);
    flag = ((pHandle->pUSARTx->SR >> USART_SR_TXE) & 0x1);
    if (interruptEnFlag && flag)
    {
        if (pHandle->TxState == USART_BUSY_IN_TX && pHandle->TxLen > 0)
        {
            if (pHandle->USART_Config.USART_WordLength == USART_WORDLEN_8BITS)
            {
                // 8 bits
                pHandle->pUSARTx->DR = (uint8_t)*pHandle->pTxBuffer;
                pHandle->pTxBuffer++;
                pHandle->TxLen--;
            }
            else
            {
                // 9bits
                if (pHandle->USART_Config.USART_ParityControl != USART_PARITY_DISABLE)
                {
                    // 9bits parity enabled
                    pHandle->pUSARTx->DR = *pHandle->pTxBuffer;
                    pHandle->pTxBuffer++;
                    pHandle->TxLen--;
                }
                else
                {
                    // 9bits no parity
                    pHandle->pUSARTx->DR = (*((uint16_t *)pHandle->pTxBuffer) & ((uint16_t)0x1FF));
                    pHandle->pTxBuffer++;
                    pHandle->pTxBuffer++;
                    pHandle->TxLen--;
                }
            }
        }
    }

    // TC & TCIE
    interruptEnFlag = ((pHandle->pUSARTx->CR1 >> USART_CR1_TCIE) & 0x1);
    flag = ((pHandle->pUSARTx->SR >> USART_SR_TC) & 0x1);
    if (interruptEnFlag && flag)
    {
        if (pHandle->TxLen <= 0 && pHandle->TxState == USART_BUSY_IN_TX)
        {
            // clear TC flag
            // pHandle->pUSARTx->SR &= ~(0x1 << USART_SR_TC);

            // disable interrupts:
            pHandle->pUSARTx->CR1 &= ~(0x1 << USART_CR1_TXEIE);
            pHandle->pUSARTx->CR1 &= ~(0x1 << USART_CR1_TCIE);

            // reset handle
            pHandle->pTxBuffer = NULL;
            pHandle->TxLen = 0;
            pHandle->TxState = USART_READY;

            // notify
            USART_ApplicationEventCallback(pHandle, USART_EVENT_TX_CMPLT);
        }
    }

    if (pHandle->pUSARTx == USART1 || pHandle->pUSARTx == USART2 || pHandle->pUSARTx == USART6)
    {
        // CTS & CTSIE
        interruptEnFlag = ((pHandle->pUSARTx->CR3 >> USART_CR3_CTSIE) & 0x1);
        flag = ((pHandle->pUSARTx->SR >> USART_SR_CTS) & 0x1);
        if (interruptEnFlag && flag)
        {
            pHandle->pUSARTx->SR &= ~(0x1 << USART_SR_CTS);
            USART_ApplicationEventCallback(pHandle, USART_EVENT_CTS);
        }
    }

    // ORE & RXNEIE
    interruptEnFlag = ((pHandle->pUSARTx->CR1 >> USART_CR1_RXNEIE) & 0x1);
    flag = ((pHandle->pUSARTx->SR >> USART_SR_ORE) & 0x1);
    if (flag && interruptEnFlag)
    {
        USART_ApplicationEventCallback(pHandle, USART_ERR_ORE);
    }

    // IDLE & IDLEIE
    interruptEnFlag = ((pHandle->pUSARTx->CR1 >> USART_CR1_IDLEIE) & 0x1);
    flag = ((pHandle->pUSARTx->SR >> USART_SR_IDLE) & 0x1);
    if (flag && interruptEnFlag)
    {
        USART_ApplicationEventCallback(pHandle, USART_EVENT_IDLE);
    }

    // PE & PEIE
    interruptEnFlag = ((pHandle->pUSARTx->CR1 >> USART_CR1_PEIE) & 0x1);
    flag = ((pHandle->pUSARTx->SR >> USART_SR_PE) & 0x1);
    if (flag && interruptEnFlag)
    {
        USART_ApplicationEventCallback(pHandle, USART_EVENT_PE);
    }

    // LBD & LBDIE
    interruptEnFlag = ((pHandle->pUSARTx->CR2 >> USART_CR2_LBDIE) & 0x1);
    flag = ((pHandle->pUSARTx->SR >> USART_SR_LBD) & 0x1);
    if (flag && interruptEnFlag)
    {
        pHandle->pUSARTx->SR &= ~(0x1 << USART_SR_LBD);
        USART_ApplicationEventCallback(pHandle, USART_EVENT_LBD);
    }

    // multibuffer errors
    interruptEnFlag = ((pHandle->pUSARTx->CR3 >> USART_CR3_EIE) & 0x1);
    if (interruptEnFlag)
    {
        // NF
        flag = ((pHandle->pUSARTx->SR >> USART_ERR_NF) & 0x1);
        if (flag)
        {
            USART_ApplicationEventCallback(pHandle, USART_ERR_NF);
        }

        // ORE
        flag = ((pHandle->pUSARTx->SR >> USART_SR_ORE) & 0x1);
        if (flag)
        {
            USART_ApplicationEventCallback(pHandle, USART_ERR_ORE);
        }

        // FE
        flag = ((pHandle->pUSARTx->SR >> USART_SR_FE) & 0x1);
        if (flag)
        {
            USART_ApplicationEventCallback(pHandle, USART_ERR_FE);
        }
    }
}

static void EnableCommonInterrupts(USART_RegDef_t *pUSARTx) {
	pUSARTx->CR3 |= (0x1 << USART_CR3_CTSIE);
	pUSARTx->CR1 |= (0x1 << USART_CR1_TCIE);
	pUSARTx->CR1 |= (0x1 << USART_CR1_IDLEIE);
	pUSARTx->CR1 |= (0x1 << USART_CR2_LBDIE);
}

uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    if (pUSARTHandle->TxState != USART_BUSY_IN_TX)
    {
        pUSARTHandle->TxState = USART_BUSY_IN_TX;
        pUSARTHandle->TxLen = Len;
        pUSARTHandle->pTxBuffer = pTxBuffer;

        // enable interrupts
        EnableCommonInterrupts(pUSARTHandle->pUSARTx);
        pUSARTHandle->pUSARTx->CR1 |= (0x1 << USART_CR1_TXEIE);
    }
    return pUSARTHandle->TxState;
}

uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    if (pUSARTHandle->RxState != USART_BUSY_IN_RX)
    {
        pUSARTHandle->RxState = USART_BUSY_IN_RX;
        pUSARTHandle->RxLen = Len;
        pUSARTHandle->pRxBuffer = pRxBuffer;

        // enable interrupts
        EnableCommonInterrupts(pUSARTHandle->pUSARTx);
        pUSARTHandle->pUSARTx->CR1 |= (0x1 << USART_CR1_RXNEIE);
        // pUSARTHandle->pUSARTx->CR1 |= (0x1 << USART_CR1_PEIE);
    }
    return pUSARTHandle->RxState;
}



__attribute__((weak))void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle, uint8_t ApEv)
{
	return;
}
