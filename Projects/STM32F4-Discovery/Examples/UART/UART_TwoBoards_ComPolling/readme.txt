/**
  @page UART_TwoBoards_ComPolling UART TwoBoards Communication Polling example

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    UART/UART_TwoBoards_ComPolling/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the UART TwoBoards Communication Polling example.
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
   @endverbatim

@par Example Description 

This example describes an UART transmission (transmit/receive) in polling mode
between two boards.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 168 MHz.

Then 1st board is waiting for user button key to be pressed. Once done, data 
are transmitted through UART2 in polling mode. 2nd board has configured UART2 
to receive data in polling mode. Once data received is completed, 2nd board also 
transmit same characters on UART2 which will be received by 1st board.
Both boards compare transmitted data to received ones. If they are same, green 
LED is turn on, else red one is turn On

Warning: As both boards do not behave same way, "TRANSMITTER_BOARD" switch 
compilation exists to determine either software is for 1st transmitter board or 
2nd receiver (then transmitter) board. In other words, 1st board has to be 
flashed with software compiled with switch enable, 2nd board has to be flashed 
with software compiled with switch disable.

STM32 discovery board's LEDs can be used to monitor the transfer status:
 - LED6 (Blue) is ON when the transmission process is complete.
 - LED4 (Green) is ON when the reception process is complete.
 - LED3 (Orange) is ON when there's UART error callback, otherwise the Led is blinking
   waiting for button press to start transmission. 
 - LED5 (Red) is ON when there is an error in transmission/reception process.   

The UART is configured as follows:
    - BaudRate = 9600 baud  
    - Word Length = 8 Bits (7 data bit + 1 parity bit)
    - One Stop Bit
    - None parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Reception and transmission are enabled in the time

@note USARTx/UARTx instance used and associated resources can be updated in "main.h"
file depending hardware configuration used.

@par Keywords

Connectivity, UART, Baud rate, RS-232, Full-duplex, Polling, Parity, Stop bit, Transmission, Reception,

@note When the parity is enabled, the computed parity is inserted at the MSB
position of the transmitted data.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - UART/UART_TwoBoards_ComPolling/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - UART/UART_TwoBoards_ComPolling/Inc/stm32f4xx_it.h          interrupt handlers header file
  - UART/UART_TwoBoards_ComPolling/Inc/main.h                  Main program header file  
  - UART/UART_TwoBoards_ComPolling/Src/stm32f4xx_it.c          interrupt handlers
  - UART/UART_TwoBoards_ComPolling/Src/main.c                  Main program
  - UART/UART_TwoBoards_ComPolling/Src/stm32f4xx_hal_msp.c     HAL MSP module
  - UART/UART_TwoBoards_ComPolling/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file


@par Hardware and Software environment 

  - This example runs on STM32F407xx devices.    
  - This example has been tested with STMicroelectronics STM32F4-Discovery RevB & RevC 
    boards and can be easily tailored to any other supported device 
    and development board.
    
  - STM32F4-Discovery RevB & RevC set-up
    - Connect a wire between 1st board PA2 pin (UART Tx) to 2nd board PA3 pin (UART Rx)
    - Connect a wire between 1st board PA3 pin (UART Rx) to 2nd board PA2 pin (UART Tx)
    - Connect 1st board GND to 2nd Board GND  
  
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
