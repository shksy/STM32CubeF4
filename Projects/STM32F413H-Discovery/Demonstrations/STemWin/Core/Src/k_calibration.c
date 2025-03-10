/**
******************************************************************************
* @file    k_calibration.c
* @author  MCD Application Team
* @brief   This example code shows how to calibrate the touchscreen.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
* @{
*/

/** @addtogroup BSP
* @{
*/

/* Imported variables */
#define CALIB_RES(val,pte1,ptm1,pte2,ptm2) ((((val-ptm2)*(pte1-pte2))/(ptm1-ptm2))+pte2)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Constant related to Flash memory area used to stored the calibration
parameters. These values must be aligned with the scatter file. */
#define CALIBRATION_PARAM_FLASH_BANK         FLASH_BANK_1
#define CALIBRATION_PARAM_FLASH_SECTOR         FLASH_SECTOR_15
#define CALIBRATION_PARAM_FLASH_NB_SECTOR      1


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t ts_calibration_done = 0;
static int16_t aPhysX[2], aPhysY[2], aLogX[2], aLogY[2];

typedef union
{
  struct
  {
    uint32_t     A1 : 15;
    uint32_t     B1 : 16;
    uint32_t     Reserved : 1;
  }b;
  uint32_t d32;
}CALIBRATION_Data1Typedef;

typedef union
{
  struct
  {
    uint32_t      A2 : 15;
    uint32_t      B2 : 16;
    uint32_t      IsCalibrated : 1;
  }b;
  uint32_t d32;
  
}CALIBRATION_Data2Typedef;

CALIBRATION_Data1Typedef data1;
CALIBRATION_Data2Typedef data2;

int16_t  A1, A2, B1, B2, C1, C2, D1, D2;

/* Start calibration_data region definition to map calibration_data[] array:
calibration_data[] stores the calibration parameters in Flash memory */
#if defined(__ICCARM__)
#pragma section =".calibration_data"
#pragma default_variable_attributes = @ ".calibration_data"
uint32_t calibration_data[3*2];
/* Stop placing data in section calibration_data region */
#pragma default_variable_attributes =
#endif

#if defined(__GNUC__)
uint32_t __attribute__((section(".calibration_data"))) calibration_data[3*2];
#endif

#if defined(__CC_ARM)
uint32_t calibration_data[3*2] __attribute__((section(".calibration_data"),zero_init));
#endif

/* Three 64-bit long words used to store 3 32-bit long parameters
calibration_data[0] = 0 / 1 : very first calibration: done no / yes
calibration_data[2] = data1.d32 calibration parameter
calibration_data[4] = data2.d32 calibration parameter */

#if defined(__ICCARM__)
/* Stop placing data in section calibration_data region */
#pragma default_variable_attributes =
#endif
uint32_t Flash_error = 0;

/* Variables used for Flash erase procedure */
static FLASH_EraseInitTypeDef EraseInitStruct;
static uint32_t PAGEError = 0;

/* Flag to indicate user-requested TouchScreen calibration at start-up */
extern uint32_t UserButton_press;

/* Private function prototypes -----------------------------------------------*/
static void TouchscreenCalibration_SetHint(void);
static void TouchScreen_Calibration_GetPhysValues(int16_t LogX, int16_t LogY, int16_t * pPhysX, int16_t * pPhysY) ;
static void TouchScreen_Calibration_WaitForPressedState(uint8_t Pressed, TS_StateTypeDef * TS_State);
/* Private functions ---------------------------------------------------------*/

/**
* @brief  Performs the TS calibration
* @param  None
* @retval Status (TS_OK = 0/ TS_ERROR = 1 / TS_TIMEOUT = 1 / TS_DEVICE_NOT_FOUND = 3)
*/
uint8_t Touchscreen_Calibration(void)
{
  uint8_t ts_status = TS_OK;
  uint8_t i;
  uint8_t ts_Orientation;
  uint16_t ts_SizeX;
  uint16_t ts_SizeY;
  
  ts_Orientation  = TS_ORIENTATION_LANDSCAPE_ROT180;
  ts_SizeX        = BSP_LCD_GetXSize();
  ts_SizeY        = BSP_LCD_GetYSize();
  
  data1.d32 = k_BkupRestoreParameter(RTC_BKP_DR0);
  data2.d32 = k_BkupRestoreParameter(RTC_BKP_DR1);
  
  /* Start touchscreen internal calibration and configuration + start */
  ts_status = BSP_TS_InitEx(ts_SizeX, ts_SizeY, ts_Orientation);  
  
  if ((calibration_data[0] != 1)  /* Very first start-up and calibration */
      || (UserButton_press == 1))       /* User-requested calibration          */
  {
    TouchscreenCalibration_SetHint();
    
    if (ts_status != TS_OK)
    {
      BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
      BSP_LCD_SetTextColor(LCD_COLOR_RED);
      BSP_LCD_DisplayStringAt(0, 240 - 95, (uint8_t *)"ERROR", CENTER_MODE);
      BSP_LCD_DisplayStringAt(0, 240 - 80, (uint8_t *)"Touchscreen cannot be calibrated", CENTER_MODE);
      if(ts_status == TS_ERROR)
      {
        BSP_LCD_DisplayStringAt(0, 240 - 65, (uint8_t *)"Touchscreen undefined error", CENTER_MODE);
      }
      else if(ts_status == TS_TIMEOUT)
      {
        BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 65, (uint8_t *)"Touchscreen Timeout", CENTER_MODE);
      }
      else
      {
        /* TS_DEVICE_NOT_FOUND */
        BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 65, (uint8_t *)"Touchscreen Not Found", CENTER_MODE);
      }
    }
    else
    {
      /* Get touch points for SW calibration processing */
      aLogX[0] = 20;
      aLogY[0] = 20;
      aLogX[1] = BSP_LCD_GetXSize() - 20;
      aLogY[1] = BSP_LCD_GetYSize() - 20;
      
      for (i = 0; i < 2; i++)
      {
        TouchScreen_Calibration_GetPhysValues(aLogX[i], aLogY[i], &aPhysX[i], &aPhysY[i]);
        if(i == 1)
        {
          if((aPhysX[0] <= (aPhysX[1] + 100)) && (aPhysY[1] <= (aPhysY[0] + 100)))
          {
            i = 0;
          }
        }
      }
      
      data1.b.A1 = aPhysX[0];
      data1.b.B1 = aPhysX[1];
      k_BkupSaveParameter(RTC_BKP_DR0, data1.d32);
      
      data2.b.A2 = aPhysY[0];
      data2.b.B2 = aPhysY[1];
      data2.b.IsCalibrated = 1;
      k_BkupSaveParameter(RTC_BKP_DR1, data2.d32);
      
      /* Save calibration parameters in Flash */
      HAL_FLASH_Unlock();
      
      __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |\
        FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR| FLASH_FLAG_PGSERR);
      
      /* First, erase Flash to be able to write afterwards */
      /* Fill EraseInit structure*/
      EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
      EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
      EraseInitStruct.Banks         = CALIBRATION_PARAM_FLASH_BANK;
      EraseInitStruct.Sector        = CALIBRATION_PARAM_FLASH_SECTOR;
      EraseInitStruct.NbSectors     = CALIBRATION_PARAM_FLASH_NB_SECTOR;
      
      if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
      {
        Flash_error = HAL_FLASH_GetError();
        BSP_LCD_DisplayStringAt(0, 240 - 65, (uint8_t *)"Calibration parameters erasing error", CENTER_MODE);
      }
      
      /* Save calibration 'done' information */
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (uint32_t)&calibration_data, (uint32_t) 1) != HAL_OK)
      {
        Flash_error = HAL_FLASH_GetError();
        BSP_LCD_DisplayStringAt(0, 240 - 65, (uint8_t *)"Calibration parameters saving error", CENTER_MODE);
      }
      /* Save data1.d32 calibration parameter */
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (uint32_t)&calibration_data[2], (uint32_t) (data1.d32)) != HAL_OK)
      {
        Flash_error = HAL_FLASH_GetError();
        BSP_LCD_DisplayStringAt(0, 240 - 65, (uint8_t *)"Calibration parameters saving error", CENTER_MODE);
      }
      /* Save data2.d32 calibration parameter */
      if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (uint32_t)&calibration_data[4], (uint32_t) (data2.d32)) != HAL_OK)
      {
        Flash_error = HAL_FLASH_GetError();
        BSP_LCD_DisplayStringAt(0, 240 - 65, (uint8_t *)"Calibration parameters saving error", CENTER_MODE);
      }
    }
    data1.d32 = calibration_data[2];
    data2.d32 = calibration_data[4];
  }
  else
  {
    /* Retrieve calibration parameters from Flash memory */
    data1.d32 = calibration_data[2];
    data2.d32 = calibration_data[4];
  }
  
  ts_calibration_done = 1;
  
  return (ts_status);
}

/**
* @brief  Display calibration hint
* @param  None
* @retval None
*/
static void TouchscreenCalibration_SetHint(void)
{
  /* Clear the LCD */
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  
  /* Set Touchscreen Demo description */
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  
  BSP_LCD_SetFont(&Font20);
  BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"Touchscreen", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 120, (uint8_t *)"Calibration", CENTER_MODE);
}


/**
* @brief  Get Physical position
* @param  LogX : logical X position
* @param  LogY : logical Y position
* @param  pPhysX : Physical X position
* @param  pPhysY : Physical Y position
* @retval None
*/
static void TouchScreen_Calibration_GetPhysValues(int16_t LogX, int16_t LogY, int16_t * pPhysX, int16_t * pPhysY)
{
  TS_StateTypeDef TS_State = {0};
  
  /* Draw the ring */
  
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_FillCircle(LogX, LogY, 20);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_FillCircle(LogX, LogY, 10);
  
  /* Wait until pressed state on the touch panel */
  TouchScreen_Calibration_WaitForPressedState(1, &TS_State);
  
  /* Return as physical touch values the positions of first touch, even if double touched occurred */
  *pPhysX = TS_State.touchX[0];
  *pPhysY = TS_State.touchY[0];
  
  /* Wait until touch is released on touch panel */
  TouchScreen_Calibration_WaitForPressedState(0, &TS_State);
  
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_FillCircle(LogX, LogY, 20);
}

/**
* @brief  TouchScreen_Calibration_WaitForPressedState : wait until a particular press/depress action
*         The function is managing anti-rebound : that is the awaited state when detected
*         needs to be stable for a sufficient time (timeout time), otherwise a new sense to search
*         for awaited state is performed. When awaited state is found and state is stable for timeout
*         duration, the function is exited.
* @param  uint8_t Pressed :  Awaited pressed state
*         - Await touch (single/multiple) detection if Pressed == 1
*         - Await no touch detection if Pressed == 0
* @retval None
*/
static void TouchScreen_Calibration_WaitForPressedState(uint8_t Pressed, TS_StateTypeDef * TS_State)
{
  uint16_t TimeStart = 0;
  uint8_t  status = TS_OK;
  uint32_t exitFirstLevelWhileLoopReq = 0;  /* By default no exit request from first level while loop  */
  uint32_t exitSecondLevelWhileLoopReq = 0; /* By default no exit request from second level while loop */
  
  /* First level while loop entry */
  do
  {
    /* reset exit second level while loop in case it was set */
    exitSecondLevelWhileLoopReq = 0;
    
    /* Sense of touch state from touch IC until get the awaited state in parameter 'Pressed' */
    status = BSP_TS_GetState(TS_State);
    if(status == TS_OK)
    {
      if (((Pressed == 0) && (TS_State->touchDetected == 0)) ||
          ((Pressed == 1) && ((TS_State->touchDetected == 1) || (TS_State->touchDetected == 2))))
      {
        /* Got awaited press state */
        /* Record in 'TimeStart' the time of awaited touch event for anti-rebound calculation */
        /* The state should persist for a minimum sufficient time */
        TimeStart = HAL_GetTick();
        
        /* Is state of the touch changing ? */
        /* Second level while loop entry */
        do
        {
          /* New sense of touch state from touch IC : to evaluate if state was stable */
          status = BSP_TS_GetState(TS_State);
          if(status == TS_OK)
          {
            /* Is there a state change compared since having found the awaited state ? */
            if (((Pressed == 0) && ((TS_State->touchDetected == 1) || (TS_State->touchDetected == 2))) ||
                ((Pressed == 1) && ((TS_State->touchDetected == 0))))
            {
              /* Too rapid state change => anti-rebound management : restart first touch search */
              exitSecondLevelWhileLoopReq = 1; /* exit request from second level while loop */
            }
            else if ((HAL_GetTick() - 100) > TimeStart)
            {
              /* State have not changed for the timeout duration (stable touch for 100 ms) */
              /* This means the touch state is stable : can exit function */
              
              /* found valid touch, exit both while levels */
              exitSecondLevelWhileLoopReq = 1;
              exitFirstLevelWhileLoopReq  = 1;
            }
            
            /* Wait 10 ms before next sense of touch at next loop iteration */
            HAL_Delay(100);
            
          } /* of if(status == TS_OK) */
        }
        while (!exitSecondLevelWhileLoopReq);
        
      } /* of if (((Pressed == 0) && .... */
      
    } /* of if(status == TS_OK) */
    
    if(!exitFirstLevelWhileLoopReq)
    {
      /* Wait some time before next sense of touch at next loop iteration */
      HAL_Delay(100);
    }
  }
  while (!exitSecondLevelWhileLoopReq);
}

/**
* @brief  Calibrate x position (to obtain X = calibrated(x))
* @param  x : X position
* @retval calibrated x
*/
uint16_t TouchScreen_Get_Calibrated_X(uint16_t x)
{
  int32_t ret=(CALIB_RES(x,20,data1.b.A1,220,data1.b.B1));
  if (ret<0) ret=0;
  else if  (ret>240) ret=239;
  return ret;
}

/**
* @brief  Calibrate Y position
* @param  y : Y position
* @retval calibrated y
*/
uint16_t TouchScreen_Get_Calibrated_Y(uint16_t y)
{
  int32_t ret=(CALIB_RES(y,20,data2.b.A2,220,data2.b.B2));
  if (ret<0) ret=0;
  else if  (ret>240) ret=239;
  return ret;
}

/**check if the TS is calibrated
* @param  None
* @retval calibration state (1 : calibrated / 0: no)
*/
uint8_t TouchScreen_IsCalibrationDone(void)
{
  return (ts_calibration_done);
}

/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
