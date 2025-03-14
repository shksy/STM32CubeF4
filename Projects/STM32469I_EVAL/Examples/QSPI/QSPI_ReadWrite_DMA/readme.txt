/**
  @page QSPI_ReadWrite_DMA QSPI Read/Write in DMA mode example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    QSPI/QSPI_ReadWrite_DMA/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the QSPI Read/Write in DMA mode example.
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

How to use a QSPI memory in DMA mode.

This example describes how to erase part of a QSPI memory, write data in DMA mode, read data in DMA mode 
and compare the result in an infinite loop.

LED1 toggles each time a new comparison is good
LED3 is on as soon as a comparison error occurs
LED3 is on as soon as an error is returned by HAL API

In this example, HCLK is configured at 180 MHz.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@note The connection of the LCD reset pin to a dedicated GPIO PK7 instead of the STM32F469 NRST pin may cause residual display on LCD with applications/examples that do not require display.
	  The LCD clear can be ensured by hardware through the board's power off/power on or by software calling the BSP_LCD_Reset() function.

@par Keywords

Memory, QSPI, Erase, Read, Write, DMA

@par Directory contents 

  - QSPI/QSPI_ReadWrite_DMA/Inc/stm32f4xx_hal_conf.h HAL configuration file
  - QSPI/QSPI_ReadWrite_DMA/Inc/stm32f4xx_it.h       Interrupt handlers header file
  - QSPI/QSPI_ReadWrite_DMA/Inc/main.h               Header for main.c module  
  - QSPI/QSPI_ReadWrite_DMA/Src/stm32f4xx_it.c       Interrupt handlers
  - QSPI/QSPI_ReadWrite_DMA/Src/main.c               Main program
  - QSPI/QSPI_ReadWrite_DMA/Src/system_stm32f4xx.c   STM32F4xx system source file
  - QSPI/QSPI_ReadWrite_DMA/Src/stm32f4xx_hal_msp.c  HAL MSP file    


@par Hardware and Software environment

  - This example runs on STM32F469xx/STM32F479xx devices.

  - This example has been tested and validated with STMicroelectronics STM32469I-EVAL RevC board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
