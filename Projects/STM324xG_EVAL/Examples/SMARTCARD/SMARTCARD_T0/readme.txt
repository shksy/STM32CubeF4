/**
  @page SMARTCARD_T0 Smart Card T0 protocol example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    SMARTCARD/T0/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the Smart Card T0 protocol example.
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


This example describes a firmware Smartcard Interface based on the USART
peripheral. The main purpose of this firmware example is to provide resources 
facilitating the development of an application using the USART peripheral in 
smartcard mode.


The firmware interface is composed of library source files developed in order to
support ISO7816-3/4 specification, an application example is also provided.

This example is based on the AN2598 "Smartcard interface with the STM32F101xx 
and STM32F103xx" application note. For more details, please refer to AN2598 
available on www.st.com


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Connectivity, SMARTCARD, USART 

@par Directory contents 

  - SMARTCARD/SMARTCARD_T0/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - SMARTCARD/SMARTCARD_T0/Inc/stm32f4xx_it.h          Interrupt handlers header file
  - SMARTCARD/SMARTCARD_T0/Inc/main.h                  Main program header file
  - SMARTCARD/SMARTCARD_T0/Inc/smartcard.h             Header for smartcard.c module
  - SMARTCARD/SMARTCARD_T0/Src/stm32f4xx_it.c          Interrupt handlers
  - SMARTCARD/SMARTCARD_T0/Src/main.c                  Main program
  - SMARTCARD/SMARTCARD_T0/Inc/smartcard.c             smartcard module
  - SMARTCARD/SMARTCARD_T0/Src/stm32f4xx_hal_msp.c     HAL MSP module
  - SMARTCARD/SMARTCARD_T0/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file


@par Hardware and Software environment

  - This example runs on STM32F407xx/417xx devices.
  
  - This example has been tested with STMicroelectronics STM324xG-EVAL RevC 
    evaluation boards and can be easily tailored to any other supported device 
    and development board. 
      
  - STM324xG-EVAL RevC Set-up
    - Use LED1, LED2, LED3 and LED4 connected respectively to PG.06, PG.08, PI.09
      and PC.07 pins.
    - Please ensure that jumper JP21 is fitted.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
