/**
  @page LTDC_Paint LTDC Paint application
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Display/LTDC_Paint/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the LTDC Paint application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
   @endverbatim

@par Application Description

 This application describes how to configure LCD touch screen and attribute 
 an action related to configured touch zone and how to save BMP picture in USB Disk.
 
 At the beginning of the main program the HAL_Init() function is called to reset 
 all the peripherals, initialize the Flash interface and the systick.
 Then the SystemClock_Config() function is used to configure the system
 clock (SYSCLK) to run at 168 MHz.  

 After LCD and touch screen initialization, touchscreen calibration is requested
 for better accuracy, then, menu is displayed on the screen. 
 
 The menu contains palette of colors, clear icon, save icon, different kind 
 of draw size, the current selected size, selected color and working rectangle. 

 Select one of proposed colors and select the size of brush to draw 
 inside the working rectangle.
 
 Clear the working window by pressing the clear icon or/and save the picture 
 in USB Mass Stroage by pressing the save icon.
palette f
                                          LCD Menu
               ____________________________________________________________
          /   |______|---------------------------------------------------- |
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
palette   |   |______||               Working Rectangle                   ||
   of   __|   |______||                                                   ||
 Colors   |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||___________________________________________________|| 
          \   |______|__________________ _________        __               | 
              |clear |  choose the brush|   Save  |      |__|         O    | 
              |______|________size______|_USBDisk_|__selected color__size__|


  - LED1 is on to indicate the end of saving operation and a message is displayed 
    on LCD to indicate the beginning and the end of the saving operation.
  - LED3 is ON when any error occurs.

Note: After save operation, the touch positions are not cleared from STMPE811 FIFO 
      and the next touch in any positions of the LCD screen leads second save 
      operation.
      This limitation is only with ampire 480x272 LCD device.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Graphic, Display, LTDC, Pictures, USB, BMP, Background, Foreground, Layers, Touchscreen, Calibration

@par Directory contents

    - Display/LTDC_Paint/Inc/main.h                 Main configuration file
    - Display/LTDC_Paint/Inc/usbh_diskio_dma.h      FatFS usbh diskio driver header file
    - Display/LTDC_Paint/Inc/stm32f4xx_it.h         Interrupt handlers header file
    - Display/LTDC_Paint/Inc/stm32f4xx_hal_conf.h   HAL Configuration file 
    - Display/LTDC_Paint/Inc/ffconf.h               FAT file system module configuration file
    - Display/LTDC_Paint/Inc/usbh_conf.h            Configuration file for USB module
    - Display/LTDC_Paint/Inc/color.h                Image used for LTDC Validation
    - Display/LTDC_Paint/Inc/color2.h               Image used to display colored pens
    - Display/LTDC_Paint/Inc/save.h                 Image used to display save icon
    - Display/LTDC_Paint/Src/main.c                 Main program 
    - Display/LTDC_Paint/Src/usbh_diskio_dma.c      FatFS usbh diskio driver implementation
    - Display/LTDC_Paint/Src/stm32f4xx_it.c         Interrupt handlers
    - Display/LTDC_Paint/Src/usbh_conf.c            Main function to configure USB
    - Display/LTDC_Paint/Src/ts_calibration.c       Main function used to calibrate TS
    - Display/LTDC_Paint/Src/system_stm32f4xx.c     STM32F4xx system clock configuration file


@par Hardware and Software environment

  - This application runs on STM32F427x/STM32F437x/STM32F429x/STM32F439x Devices.

  - This application has been tested with STM324x9I-EVAL RevB evaluation board 
    and can be easily tailored to any other supported device and development board.

  - STM324x9I-EVAL Set-up
    - Plug the USB key into the STM324x9I-EVAL board through 'USB micro A-Male 
      to A-Female' cable (HS mode: connector CN9).


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the application

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
                                   