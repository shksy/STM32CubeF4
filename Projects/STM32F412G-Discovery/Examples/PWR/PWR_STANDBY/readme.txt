/**
  @page PWR_STANDBY PWR standby example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    PWR/PWR_STANDBY/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the PWR STANDBY example.
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
 
How to enter the Standby mode and wake up from this mode by using an external 
reset or the WKUP pin.

In the associated software, the system clock is set to 100 MHz.
The SysTick is programmed to generate an interrupt each 1 ms.

After a reset (or wake-up from STANDBY mode), LED1 is ON and MCU is in RUN mode.
The system enters STANDBY mode after 5s, LED1 is OFF.
A rising edge on wakeup pin WKUP2 PC.00 will wake-up the system from STANDBY.
Alternatively, an external RESET of the board will lead to a system wake-up as well.
The LED1 Blinks once in order to indicate the system was resumed from Standby mode.
These steps are repeated in an infinite loop.

@note This example can not be used in DEBUG mode due to the fact 
      that the Cortex-M4 core is no longer clocked during low power mode 
      so debugging features are disabled.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Power, PWR, Standby mode, Interrupt, EXTI, Wakeup, Low Power, RTC, External reset, LSI

@par Directory contents 

  - PWR/PWR_STANDBY/Inc/stm32f4xx_conf.h         HAL Configuration file
  - PWR/PWR_STANDBY/Inc/stm32f4xx_it.h           Header for stm32f4xx_it.c
  - PWR/PWR_STANDBY/Inc/main.h                   Header file for main.c
  - PWR/PWR_STANDBY/Src/system_stm32f4xx.c       STM32F4xx system clock configuration file
  - PWR/PWR_STANDBY/Src/stm32f4xx_it.c           Interrupt handlers
  - PWR/PWR_STANDBY/Src/main.c                   Main program
  - PWR/PWR_STANDBY/Src/stm32f4xx_hal_msp.c      HAL MSP module

@par Hardware and Software environment

  - This example runs on STM32F412xG devices

  - This example has been tested with STMicroelectronics STM32412G-DISCOVERY
    board and can be easily tailored to any other supported device 
    and development board.

  - STM32412G-DISCOVERY Set-up
    - LED1 connected to PE.00 pin.
    - Put a Jumper between PC.00 and 5V to generate a rising edge on PWR_WAKEUP_PIN2.
    - Connect an ampere-meter to JP7 to measure the IDD current.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Wake-up will be done in putting 3.3V to PC.00 pin (present on pin8 of P1).
      Wired should be put between PC.00 and GND before running test. Connect to 3V3 to awake board.
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
