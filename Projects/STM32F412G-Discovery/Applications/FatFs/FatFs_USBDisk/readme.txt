/**
  @page FatFs_USBDisk   FatFs with USB disk drive application
 
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    FatFs/FatFs_USBDisk/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the FatFs with USB disk drive application
  ******************************************************************************
  * @attention
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

How to use STM32Cube firmware with FatFs middleware component as a generic FAT
file system module and STM32 USB On-The-Go (OTG) host library, in both Full
Speed (FS) and High Speed (HS) modes. This example develops an application
exploiting FatFs features with USB disk drive configuration.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick. 
The user is provided with the SystemClock_Config() function to configure the system 
clock (SYSCLK) to run at 100 MHz. The Full Speed (FS) USB module uses internally 
a 48-MHz clock which is coming from the PLL I2S.
           
The application is based on writing a text file to a drive, and it's performed 
using FatFs APIs to access the FAT volume as described in the following steps: 

 - Link the USB Host disk I/O driver;
 - Register the file system object (mount) to the FatFs module for the USB drive;
 - Create and Open new text file object with write access;
 - Write data to the text file;
 - Close the open text file;
 - Unlink the USB Host disk I/O driver.
 
Notice that the application manages possible errors that might occur during the 
access to FAT volume, when using FatFs APIs. In addition, user can check if the
written text file is available on the USB disk.

It is possible to fine tune needed FatFs features by modifying defines values 
in FatFs configuration file �ffconf.h� available under the project includes 
directory, in a way to fit the application requirements. 

STM32F412G-Discovery board's LEDs can be used to monitor the application status:
  - LED4 is ON when the application runs successfully.
  - LED2 is ON when any error occurs. 

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about FatFs implementation on STM32Cube, please refer to UM1721 "Developing Applications 
on STM32Cube with FatFs".

@par Keywords

Connectivity, FatFS, USB_Host, FAT, File system 

@par Directory contents
 
  - FatFs/FatFs_USBDisk/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - FatFs/FatFs_USBDisk/Inc/stm32f4xx_it.h          Interrupt handlers header file
  - FatFs/FatFs_USBDisk/Inc/main.h                  Main program header file
  - FatFs/FatFs_USBDisk/Inc/usbh_diskio_dma.h       FatFS usbh diskio driver header file
  - FatFs/FatFs_USBDisk/Inc/ffconf.h                FAT file system module configuration file   
  - FatFs/FatFs_USBDisk/Inc/usbh_conf.h             USB Host low level configuration
  - FatFs/FatFs_USBDisk/Src/stm32f4xx_it.c          Interrupt handlers
  - FatFs/FatFs_USBDisk/Src/main.c                  Main program
  - FatFs/FatFs_USBDisk/Src/usbh_diskio_dma.c       FatFS usbh diskio driver implementation
  - FatFs/FatFs_USBDisk/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file
  - FatFs/FatFs_USBDisk/Src/usbh_conf.c             USB Host configuration functions
         
 
@par Hardware and Software environment

  - This application runs on STM32F412xG devices.
    
  - This application has been tested with STMicroelectronics STM32F412G-Discovery boards 
    and can be easily tailored to any other supported device and board.

  - STM32F412G-Discovery Set-up
    - Plug the USB key into the STM32F412G-Discovery board through 'USB micro A-Male 
      to A-Female' cable (CN3)

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the application

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
