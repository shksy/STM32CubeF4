/**
  ******************************************************************************
  * @file    USB_Host/DualCore_Standalone/Src/explorer.c
  * @author  MCD Application Team
  * @brief   Explore the USB flash disk content
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

/* Includes ----------------------------------------------------------------- */
#include "main.h"

/* Private typedef ---------------------------------------------------------- */
/* Private define ----------------------------------------------------------- */
/* Private macro ------------------------------------------------------------ */
/* Private variables -------------------------------------------------------- */
static int32_t recurseLevel = -1;
/* Private function prototypes ---------------------------------------------- */
/* Private functions -------------------------------------------------------- */

/**
  * @brief  Displays disk content.
  * @param  path: Pointer to root path
  * @param  recu_level: Disk content level
  * @retval Operation result
  */
FRESULT Explore_Disk(char *path, uint8_t recu_level)
{
  FRESULT res = FR_OK;
  FILINFO fno;
  DIR dir;
  char tmp[14];
  uint8_t line_idx = 0;

  recurseLevel++;
  res = f_opendir(&dir, path);
  if (res == FR_OK)
  {
    while (USBH_MSC_IsReady(&hUSBHost_HS))
    {
      res = f_readdir(&dir, &fno);
      if (res != FR_OK || fno.fname[0] == 0)
      {
        break;
      }
      if (fno.fname[0] == '.')
      {
        continue;
      }

      strcpy(tmp, fno.fname);

      line_idx++;
      if (line_idx > YWINDOW_SIZE)
      {
        line_idx = 0;

        LCD_UsrLog("> Press [Tamper] To Continue.\n");

        /* Tamper Button in polling */
        while ((BSP_PB_GetState(BUTTON_TAMPER) != SET) &&
               (Appli_HS_state != APPLICATION_HS_DISCONNECT))
        {
          /* Wait for User Input */
        }
      }

      if (recu_level == 1)
      {
        LCD_DbgLog("   |__");
      }
      else if (recu_level == 2)
      {
        LCD_DbgLog("   |   |__");
      }
      if (fno.fattrib & AM_DIR)
      {
        strcat(tmp, "\n");
        LCD_UsrLog((void *)tmp);
        Explore_Disk(fno.fname, 2);
      }
      else
      {
        strcat(tmp, "\n");
        LCD_DbgLog((void *)tmp);
      }

      if ((fno.fattrib & AM_DIR) && (recu_level == 2))
      {
        Explore_Disk(fno.fname, 2);
      }
    }
    f_closedir(&dir);
  }

  if (--recurseLevel == -1)
  {
    LCD_UsrLog("> Select an operation to Continue.\n");
  }

  return res;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
