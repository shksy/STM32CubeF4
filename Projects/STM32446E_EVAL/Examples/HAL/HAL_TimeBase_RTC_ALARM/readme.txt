/**
  @page HAL_TimeBase_RTC_Alarm HAL TimeBase RTC Alarm
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    HAL/HAL_TimeBase_RTC_ALARM/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the HAL TimeBase RTC Alarm example.
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

This example describes how to customize the HAL time base using RTC alarm instead 
of Systick as main source of time base. The EVAL board Key button (connected to EXTI Line13)
will be used to Suspend or Resume tick increment. 
Each time the Key button is pressed; EXTI Line13 interrupt is generated and in the ISR
the uwIncrementState is checked:
  1- If the uwIncrementState = 0: the tick increment is suspended by calling 
     HAL_SuspendTick() API (RTC alarm interrupt is disabled).
  2- If the uwIncrementState = 1: the tick increment is Resumed by calling 
     HAL_ResumeTick() API(RTC alarm interrupt is enabled).

The alarm is configured to assert an interrupt when the RTC reaches 1 ms 

The example brings, in user file, a new implementation of the following HAL weak functions:

HAL_InitTick() 
HAL_SuspendTick()
HAL_ResumeTick()

This implementation will overwrite native implementation in stm32f4xx_hal.c
and so user functions will be invoked instead when called.

The following time base functions are kept as implemented natively:

HAL_IncTick()
HAL_Delay()

In an infinite loop, LED1 and LED3 toggles spaced out over 500ms delay

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in HAL time base ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the HAL time base interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the HAL time base interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application needs to ensure that the HAL time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

System, RTC Alarm, Time base, HAL

@par Directory contents

  - HAL/HAL_TimeBase_RTC_ALARM/Inc/stm32f4xx_hal_conf.h                    HAL configuration file
  - HAL/HAL_TimeBase_RTC_ALARM/Inc/stm32f4xx_it.h                          Interrupt handlers header file
  - HAL/HAL_TimeBase_RTC_ALARM/Src/stm32f4xx_it.c                          Interrupt handlers
  - HAL/HAL_TimeBase_RTC_ALARM/Src/main.c                                  Main program
  - HAL/HAL_TimeBase_RTC_ALARM/Src/stm32f4xx_hal_timebase_rtc_alarm.c      HAL time base functions
  - HAL/HAL_TimeBase_RTC_ALARM/Src/system_stm32f4xx.c                      STM32F4xx system clock configuration file

@par Hardware and Software environment

  - This example runs on STM32F446xx devices
    
  - This example has been tested with STMicroelectronics STM32446E-EVAL board and can be
    easily tailored to any other supported device and development board.      

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
