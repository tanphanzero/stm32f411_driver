# stm32f411_driver
Drivers for the STM32F411VET6

## Project file structure
**Src** : The Src folder contains the main application file ( main.c ). The user might change the contents of the file if needed. The folder contains example code each example with its own source file.

**Drivers** : folder contains further sub folder **Src** and **Inc**.

- **Src** : Src folder contains driver source (.c) file which has all the driver apis the application file uses
- **Inc** : Inc folder contains the driver header (.h) file which has all the function prototypes and configuration macros.

## Communication protocols have been implemented and Driver Apis Usage
- **GPIO** : include **Driver/Inc/stm32f411_gpio_driver.h** (driver header) and **Driver/Src/stm32f411disc_gpio_driver.c** (driver source). Examples include **Src/001_Toggle_Led.c** , **Src/002_Button_Led.c** , **Src/003_Button_Led_IRQ.c**

- **SPI** : include **Driver/Inc/stm32f411_spi_driver.h** (driver header) and **Driver/Src/stm32f411disc_spi_driver.c** (driver source). Examples include **Src/004_SPI_Send.c**

- **USART** : include **Driver/Inc/stm32f411_uart_driver.h** (driver header) and **Driver/Src/stm32f411disc_uart_driver.c** (driver source). Examples include **Src/005.USART_Send.c** , **Src/006.USART_Receive.c** , **Src/007.USART_Send_Receive_IRQ.c**

- **I2C** : include **Driver/Inc/stm32f411_i2c_driver.h** (driver header) and **Driver/Src/stm32f411disc_i2c_driver.c** (driver source). No examples
