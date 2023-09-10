/*
 * stm32f411.h
 *
 *  Created on: Sep 2, 2023
 *      Author: Dell
 */

#ifndef INC_STM32F411_H_
#define INC_STM32F411_H_

#include <stdint.h>
#define __vo volatile


//Base address of Flash and SRAM memories

#define FLASH_BASEADDR			0x08000000U
#define SRAM1_BASEADDR			0x20000000U
#define ROM_BASEADDR			0x1FFF0000U
#define SRAM					SRAM1_BASEADDR

//AHBx and APBx Bus Peripherals base address

#define PERIPH_BASEADDR			0x40000000U
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		0x40010000U
#define AHB1PERIPH_BASEADDR		0x40020000U
#define AHB2PERIPH_BASEADDR		0x50000000U

//Base address of Peripherals hanging on AHB1 bus

#define GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOH_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1C00)

#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x3800)

//Base address of Peripherals hanging on APB1 bus

#define I2C1_BASEADDR			(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR			(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR			(APB1PERIPH_BASEADDR + 0x5C00)
#define SPI2_BASEADDR			(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR			(APB1PERIPH_BASEADDR + 0x3C00)
#define USART2_BASEADDR			(APB1PERIPH_BASEADDR + 0x4400)

//Base address of Peripherals hanging on APB2 bus

#define SPI1_BASEADDR			(APB2PERIPH_BASEADDR + 0x3000)
#define SPI4_BASEADDR			(APB2PERIPH_BASEADDR + 0x3400)
#define SPI5_BASEADDR			(APB2PERIPH_BASEADDR + 0x5000)
#define USART1_BASEADDR			(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR			(APB2PERIPH_BASEADDR + 0x1400)
#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR + 0x3C00)
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR + 0x3800)

//Define struct of GPIO

typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;

//Peripheral definition
#define GPIOA					((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB					((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC					((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD					((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE					((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH					((GPIO_RegDef_t*)GPIOH_BASEADDR)


//Define struct of RCC

typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	uint32_t RESERVED1[2];
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	uint32_t RESERVED2[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	uint32_t RESERVED3[2];
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	uint32_t RESERVED4[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	uint32_t RESERVED5[2];
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	uint32_t RESERVED6[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	uint32_t RESERVED7[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
	uint32_t RESERVED8[2];
	__vo uint32_t DCKCFGR;
}RCC_RegDef_t;
#define RCC						((RCC_RegDef_t*)RCC_BASEADDR)

//Define struct of EXTI
typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;
#define EXTI					((EXTI_RegDef_t *)EXTI_BASEADDR)

//Define struct of SPI
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;
}SPI_RegDef_t;
#define SPI1					((SPI_RegDef_t *)SPI1_BASEADDR)
#define SPI2					((SPI_RegDef_t *)SPI2_BASEADDR)
#define SPI3					((SPI_RegDef_t *)SPI3_BASEADDR)
#define SPI4					((SPI_RegDef_t *)SPI4_BASEADDR)
#define SPI5					((SPI_RegDef_t *)SPI5_BASEADDR)

//Define struct of SYSCFG
typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	uint32_t RESERVED1[2];
	__vo uint32_t CMPCR;
	uint32_t RESERVED2[2];
}SYSCFG_RegDef_t;
#define SYSCFG					((SYSCFG_RegDef_t *)SYSCFG_BASEADDR)

//Define struct of I2C
typedef struct
{
  __vo uint32_t CR1;
  __vo uint32_t CR2;
  __vo uint32_t OAR1;
  __vo uint32_t OAR2;
  __vo uint32_t DR;
  __vo uint32_t SR1;
  __vo uint32_t SR2;
  __vo uint32_t CCR;
  __vo uint32_t TRISE;
  __vo uint32_t FLTR;
}I2C_RegDef_t;
#define I2C1					((I2C_RegDef_t *)SPI1_BASEADDR)
#define I2C2					((I2C_RegDef_t *)SPI2_BASEADDR)
#define I2C3					((I2C_RegDef_t *)SPI3_BASEADDR)

//Define struct of UART
typedef struct
{
  __vo uint32_t SR;
  __vo uint32_t DR;
  __vo uint32_t BRR;
  __vo uint32_t CR1;
  __vo uint32_t CR2;
  __vo uint32_t CR3;
  __vo uint32_t GTPR;
}USART_RegDef_t;
#define USART1					((USART_RegDef_t *)USART1_BASEADDR)
#define USART2					((USART_RegDef_t *)USART2_BASEADDR)
#define USART6					((USART_RegDef_t *)USART6_BASEADDR)




//Clock Enable Macros for GPIOx peripherals
#define GPIOA_PCLK_EN()			(RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()			(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()			(RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()			(RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()			(RCC->AHB1ENR |= (1<<4))
#define GPIOH_PCLK_EN()			(RCC->AHB1ENR |= (1<<7))

//Clock Enable Macros for I2Cx peripherals
#define I2C1_PCLK_EN()			(RCC->APB1LPENR |= (1<<21))
#define I2C2_PCLK_EN()			(RCC->APB1LPENR |= (1<<22))
#define I2C3_PCLK_EN()			(RCC->APB1LPENR |= (1<<23))

//Clock Enable Macros for SPIx peripherals
#define SPI1_PCLK_EN()			(RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()			(RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()			(RCC->APB1ENR |= (1<<15))
#define SPI4_PCLK_EN()			(RCC->APB2ENR |= (1<<13))
#define SPI5_PCLK_EN()			(RCC->APB2ENR |= (1<<20))

//Clock Enable Macros for USARTx peripherals
#define USART1_PCLK_EN()		(RCC->APB2ENR |= (1<<4))
#define USART6_PCLK_EN()		(RCC->APB2ENR |= (1<<5))
#define USART2_PCLK_EN()		(RCC->APB1ENR |= (1<<17))

//Clock Enable Macros for SYSCFG peripherals
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1<<14))

//Clock Disable Macros for GPIOx peripherals
#define GPIOA_PCLK_DI()			(RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()			(RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()			(RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()			(RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()			(RCC->AHB1ENR &= ~(1<<4))
#define GPIOH_PCLK_DI()			(RCC->AHB1ENR &= ~(1<<7))

//Clock Disable Macros for I2Cx peripherals
#define I2C1_PCLK_DI()			(RCC->APB1LPENR &= ~(1<<21))
#define I2C2_PCLK_DI()			(RCC->APB1LPENR &= ~(1<<22))
#define I2C3_PCLK_DI()			(RCC->APB1LPENR &= ~(1<<23))

//Clock Disable Macros for SPIx peripherals
#define SPI1_PCLK_DI()			(RCC->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI()			(RCC->APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI()			(RCC->APB1ENR &= ~(1<<15))
#define SPI4_PCLK_DI()			(RCC->APB2ENR &= ~(1<<13))
#define SPI5_PCLK_DI()			(RCC->APB2ENR &= ~(1<<20))

//Clock Disable Macros for USARTx peripherals
#define USART1_PCLK_DI()		(RCC->APB2ENR &= ~(1<<4))
#define USART6_PCLK_DI()		(RCC->APB2ENR &= ~(1<<5))
#define USART2_PCLK_DI()		(RCC->APB1ENR &= ~(1<<17))

//Clock Disable Macros for SYSCFG peripherals
#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1<<14))

//Macro reset GPIOx peripherals
#define GPIOA_REG_RESET()		do{RCC->AHB1RSTR |= (1<<0); RCC->AHB1RSTR &= ~(1<<0);}while(0)
#define GPIOB_REG_RESET()		do{RCC->AHB1RSTR |= (1<<1); RCC->AHB1RSTR &= ~(1<<1);}while(0)
#define GPIOC_REG_RESET()		do{RCC->AHB1RSTR |= (1<<2); RCC->AHB1RSTR &= ~(1<<2);}while(0)
#define GPIOD_REG_RESET()		do{RCC->AHB1RSTR |= (1<<3); RCC->AHB1RSTR &= ~(1<<3);}while(0)
#define GPIOE_REG_RESET()		do{RCC->AHB1RSTR |= (1<<4); RCC->AHB1RSTR &= ~(1<<4);}while(0)
#define GPIOH_REG_RESET()		do{RCC->AHB1RSTR |= (1<<7); RCC->AHB1RSTR &= ~(1<<7);}while(0)

#define GPIO_BASEADDR_TO_CODE(x)	((x == GPIOA)? 0: (x == GPIOB)? 1: (x == GPIOC)? 2: (x == GPIOD)? 3: (x == GPIOE)? 4: (x == GPIOH)? 5: 0)

//SPI peripheral reset macro
#define SPI1_REG_RESET()		do{(RCC->APB2RSTR |=(1 << 12)); (RCC->APB2RSTR &= ~(1 << 12));}while(0)
#define SPI2_REG_RESET()		do{(RCC->APB1RSTR |=(1 << 14)); (RCC->APB1RSTR &= ~(1 << 14));}while(0)
#define SPI3_REG_RESET()		do{(RCC->APB1RSTR |=(1 << 15)); (RCC->APB1RSTR &= ~(1 << 15));}while(0)
#define SPI4_REG_RESET()		do{(RCC->APB2RSTR |=(1 << 13)); (RCC->APB2RSTR &= ~(1 << 14));}while(0)
#define SPI5_REG_RESET()		do{(RCC->APB2RSTR |=(1 << 12)); (RCC->APB2RSTR &= ~(1 << 15));}while(0)

//USART peripheral reset macro
#define USART1_REG_RESET()		do { RCC->APB2RSTR |= (1 << 4); RCC->APB2RSTR &= ~(1 << 4); } while(0)
#define USART6_REG_RESET()		do { RCC->APB2RSTR |= (1 << 5); RCC->APB2RSTR &= ~(1 << 5); } while(0)
#define USART2_REG_RESET()		do { RCC->APB1RSTR |= (1 << 17); RCC->APB1RSTR &= ~(1 << 17); } while(0)

//SPI peripheral reset macro
#define I2C1_REG_RESET()		do {(RCC->APB1RSTR |=(1 <<  21)); (RCC->APB1RSTR &= ~(1 << 21));}while(0)
#define I2C2_REG_RESET()		do {(RCC->APB1RSTR |=(1 <<  22)); (RCC->APB1RSTR &= ~(1 << 22));}while(0)
#define I2C3_REG_RESET()		do {(RCC->APB1RSTR |=(1 <<  23)); (RCC->APB1RSTR &= ~(1 << 23));}while(0)


//Some generic Macro
#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET
#define FLAG_RESET	RESET
#define FLAG_SET	SET

// IRQ numbers definition macros
#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40

#define IRQ_NO_SPI1			35
#define IRQ_NO_SPI2			36
#define IRQ_NO_SPI3			51
#define IRQ_NO_SPI4			84
#define IRQ_NO_SPI5			85

#define IRQ_NO_USART1		37
#define IRQ_NO_USART2		38
#define IRQ_NO_USART6		71

#define IRQ_NO_I2C1_EV		31
#define IRQ_NO_I2C1_ER		32
#define IRQ_NO_I2C2_EV		33
#define IRQ_NO_I2C2_ER		34
#define IRQ_NO_I2C3_EV		72
#define IRQ_NO_I2C3_ER		73


//NVIC ISERx core
#define NVIC_ISER0		((__vo uint32_t *)0xE000E100)
#define NVIC_ISER1		((__vo uint32_t *)0xE000E104)
#define NVIC_ISER2		((__vo uint32_t *)0xE000E108)
#define NVIC_ISER3		((__vo uint32_t *)0xE000E10C)

//NVIC ICERx core
#define NVIC_ICER0		((__vo uint32_t *)0XE000E180)
#define NVIC_ICER1		((__vo uint32_t *)0XE000E184)
#define NVIC_ICER2		((__vo uint32_t *)0XE000E188)
#define NVIC_ICER3		((__vo uint32_t *)0XE000E18C)

//NVIC priority core
#define NVIC_PR_BASE_ADDR	((__vo uint32_t *)0xE000E400)

//SPI CR1 bit position definition
#define SPI_CR1_CPHA			0
#define SPI_CR1_CPOL			1
#define SPI_CR1_MSTR			2
#define SPI_CR1_BR				3
#define SPI_CR1_SPE				6
#define SPI_CR1_LSBFIRST		7
#define SPI_CR1_SSI				8
#define SPI_CR1_SSM				9
#define SPI_CR1_RXONLY			10
#define SPI_CR1_DFF				11
#define SPI_CR1_CRCNEXT			12
#define SPI_CR1_CRCEN			13
#define SPI_CR1_BIDIOE			14
#define SPI_CR1_BIDIMODE		15

//SPI CR2 bit position definition
#define SPI_CR2_RXDMAEN			0
#define SPI_CR2_TXDMAEN			1
#define SPI_CR2_SSOE			2
#define SPI_CR2_FRF				4
#define SPI_CR2_ERRIE			5
#define SPI_CR2_RXNEIE			6
#define SPI_CR2_TXEIE			7

//SPI SR bit position definition
#define SPI_SR_RXNE				0
#define SPI_SR_TXE				1
#define SPI_SR_CHSIDE			2
#define SPI_SR_UDR				3
#define SPI_SR_CRCERR			4
#define SPI_SR_MODF				5
#define SPI_SR_OVR				6
#define SPI_SR_BSY				7
#define SPI_SR_FRE				8

//USART SR
#define USART_SR_PE				0
#define USART_SR_FE				1
#define USART_SR_NE				2
#define USART_SR_ORE			3
#define USART_SR_IDLE			4
#define USART_SR_RXNE			5
#define USART_SR_TC				6
#define USART_SR_TXE			7
#define USART_SR_LBD			8
#define USART_SR_CTS			9

//USART CR1
#define USART_CR1_SBK			0
#define USART_CR1_RWU			1
#define USART_CR1_RE			2
#define USART_CR1_TE			3
#define USART_CR1_IDLEIE		4
#define USART_CR1_RXNEIE		5
#define USART_CR1_TCIE			6
#define USART_CR1_TXEIE			7
#define USART_CR1_PEIE			8
#define USART_CR1_PS			9
#define USART_CR1_PCE			10
#define USART_CR1_WAKE			11
#define USART_CR1_M				12
#define USART_CR1_UE			13
#define USART_CR1_OVER8			15

//USART CR2
#define USART_CR2_ADD			0
#define USART_CR2_LBDL			5
#define USART_CR2_LBDIE			6
#define USART_CR2_LBCL			8
#define USART_CR2_CPHA			9
#define USART_CR2_CPOL			10
#define USART_CR2_STOP			12
#define USART_CR2_LINEN			14

//USART CR3
#define USART_CR3_EIE			0
#define USART_CR3_IREN			1
#define USART_CR3_IRLP			2
#define USART_CR3_HDSEL			3
#define USART_CR3_NACK			4
#define USART_CR3_SCEN			5
#define USART_CR3_DMAR			6
#define USART_CR3_DMAT			7
#define USART_CR3_RTSE			8
#define USART_CR3_CTSE			9
#define USART_CR3_CTSIE			10
#define USART_CR3_ONEBIT		11

//I2C CR1
#define I2C_CR1_PE				0
#define I2C_CR1_NOSTRETCH  		7
#define I2C_CR1_START 			8
#define I2C_CR1_STOP  			9
#define I2C_CR1_ACK 			10
#define I2C_CR1_SWRST  			15

//I2C CR2
#define I2C_CR2_FREQ			0
#define I2C_CR2_ITERREN			8
#define I2C_CR2_ITEVTEN			9
#define I2C_CR2_ITBUFEN 		10

//I2C OAR1
#define I2C_OAR1_ADD0    		0
#define I2C_OAR1_ADD71 			1
#define I2C_OAR1_ADD98  		8
#define I2C_OAR1_ADDMODE   		15

//I2C SR1
#define I2C_SR1_SB 				0
#define I2C_SR1_ADDR 			1
#define I2C_SR1_BTF 			2
#define I2C_SR1_ADD10 			3
#define I2C_SR1_STOPF 			4
#define I2C_SR1_RXNE 			6
#define I2C_SR1_TXE 			7
#define I2C_SR1_BERR 			8
#define I2C_SR1_ARLO 			9
#define I2C_SR1_AF 				10
#define I2C_SR1_OVR 			11
#define I2C_SR1_TIMEOUT 		14

//I2C SR2
#define I2C_SR2_MSL				0
#define I2C_SR2_BUSY 			1
#define I2C_SR2_TRA 			2
#define I2C_SR2_GENCALL 		4
#define I2C_SR2_DUALF 			7

//I2C CCR
#define I2C_CCR_CCR 			0
#define I2C_CCR_DUTY 			14
#define I2C_CCR_FS  			15


#endif /* INC_STM32F411_H_ */