/**
  ******************************************************************************
  * @file    USB_Host/MSC_Standalone/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "usbh_core.h"
#include "lcd_log.h"
#include "usbh_msc.h"
#include "ff.h"
#include "ff_gen_drv.h"
#include "usbh_diskio_dma.h"
#include "ts_calibration.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
  MSC_DEMO_IDLE = 0,
  MSC_DEMO_WAIT,  
  MSC_DEMO_FILE_OPERATIONS,
  MSC_DEMO_EXPLORER,
  MSC_REENUMERATE,  
}MSC_Demo_State;

typedef struct _DemoStateMachine {
  __IO MSC_Demo_State state;
  __IO uint8_t        select; 
}MSC_DEMO_StateMachine;

typedef enum {
  APPLICATION_IDLE = 0,  
  APPLICATION_READY,    
  APPLICATION_DISCONNECT,
}MSC_ApplicationTypeDef;

extern USBH_HandleTypeDef hUSBHost;
extern FATFS USBH_fatfs;
extern MSC_ApplicationTypeDef Appli_state;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t  Touchscreen_Calibration (void);
uint16_t TouchScreen_Get_Calibrated_X(uint16_t x);
uint16_t TouchScreen_Get_Calibrated_Y(uint16_t y);
uint8_t  TouchScreen_IsCalibrationDone(void);
FRESULT Explore_Disk(char *path, uint8_t recu_level);
void MSC_File_Operations(void);
void Menu_Init(void);
void MSC_MenuProcess(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
