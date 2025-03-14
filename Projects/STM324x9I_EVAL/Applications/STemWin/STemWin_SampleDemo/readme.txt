/**
  @page STemWin_SampleDemo Readme file
 
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    STemWin/STemWin_SampleDemo/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of STemWin Sample Demo application.  
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                               www.st.com/SLA0044
  *
  ******************************************************************************
   @endverbatim

@par Application Description

This application shows how to implement a sample demonstration example allowing 
to show some of the STemWin Library capabilities.

The list of modules to be used is configured into the file Demo/GUIDEMO.h

At the first run, after power OFF/ON, a touch screen calibration is needed: in
order to this, user is just requested to follow the displayed instructions.
Then all the demo modules are run sequentially. Throughout the demonstration, a
control frame window is displayed at the bottom right of the touch screen: it
includes a progress bar and two control buttons (Next + Halt) allowing to skip
or pause the currently running module.

LEDs 1 to 4 are continuously toggling to indicate that the Demo runs properly.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@note Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select the RTC clock source; in this 
      case the Backup domain will be reset in order to modify the RTC Clock source, as consequence RTC  
      registers (including the backup registers) and RCC_BDCR register are set to their reset values.
	   
@par Keywords

Display, STemWin, HelloWorld, LCD, GUI, Demonstration, Touch screen
     
@par Directory contents 

  - STemWin/STemWin_SampleDemo/STemWin/Target/GUIConf.h                        Header for GUIConf.c
  - STemWin/STemWin_SampleDemo/STemWin/Target/LCDConf.h                        Header for LCDConf*.c
  - STemWin/STemWin_SampleDemo/Core/Inc/rtc.h                                  Header for rtc.c
  - STemWin/STemWin_SampleDemo/Core/Inc/calibration.h                          Header for calibration.c
  - STemWin/STemWin_SampleDemo/Core/Inc/main.h                                 Main program header file
  - STemWin/STemWin_SampleDemo/Core/Inc/stm32f4xx_hal_conf.h                   Library Configuration file
  - STemWin/STemWin_SampleDemo/Core/Inc/stm32f4xx_it.h                         Interrupt handlers header file
  - STemWin/STemWin_SampleDemo/Core/Src/rtc.c                                  Main file to configure RTC clock
  - STemWin/STemWin_SampleDemo/Core/Src/calibration.c                          Main file to calibrate TS
  - STemWin/STemWin_SampleDemo/STemWin/Target/GUIConf.c                        Display controller initialization file
  - STemWin/STemWin_SampleDemo/STemWin/Target/LCDConf_stm324x9i_eval_MB1046.c  Configuration file for the GUI library (MB1046 LCD)
  - STemWin/STemWin_SampleDemo/STemWin/Target/LCDConf_stm324x9i_eval_MB1063.c  Configuration file for the GUI library (MB1063 LCD)
  - STemWin/STemWin_SampleDemo/Core/Src/main.c                                 Main program file
  - STemWin/STemWin_SampleDemo/Core/Src/stm32f4xx_it.c                         STM32F4xx Interrupt handlers
  - STemWin/STemWin_SampleDemo/Core/Src/system_stm32f4xx.c                     STM32F4xx system file
  - STemWin/STemWin_SampleDemo/STemWin/App/GUIDEMO_*.c                         All the sources files provided for SEGGER DEMO
  - STemWin/STemWin_SampleDemo/STemWin/App/GUIDEMO.h                           DEMO modules configuration file


@par Hardware and Software environment 

  - This application runs on STM32F429xx/439xx devices.
    
  - This application has been tested with STMicroelectronics STM324x9I-EVAL RevB
    (STM32F429xx/STM32F439xx Devices) evaluation boards and can be easily 
    tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the application
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
