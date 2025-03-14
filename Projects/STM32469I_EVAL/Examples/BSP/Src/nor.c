/**
  ******************************************************************************
  * @file    BSP/Src/nor.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the NOR Driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define NOR_BUFFER_SIZE     ((uint32_t)1000)
#define NOR_WRITE_READ_ADDR ((uint32_t)0x100000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t nor_aTxBuffer[NOR_BUFFER_SIZE];
uint16_t nor_aRxBuffer[NOR_BUFFER_SIZE];
uint8_t ubIDStatus = 0, ubEraseStatus = 0, ubWriteStatus = 0, ubReadStatus = 0, ubInitStatus = 0;

/* Private function prototypes -----------------------------------------------*/
static void NOR_SetHint(void);
static void Fill_Buffer(uint16_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset);
static uint8_t Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  NOR Demo
  * @param  None
  * @retval None
  */
void NOR_demo (void)
{
  /* NOR IDs structure */
  static NOR_IDTypeDef pNOR_ID;

  NOR_SetHint();
  /* DSI LCD will keep displaying its last frame                     */
  /* need to wait for the display to complete before LCD Display off */
  HAL_Delay(20);

  /*##-1- Configure the NOR device ###########################################*/
  /* NOR device configuration */
  if (BSP_NOR_Init() != NOR_STATUS_OK)
  {
    ubInitStatus++;
  }

  /*##-2- Read & check the NOR device IDs ####################################*/
  /* Initialize the ID structure */
  pNOR_ID.Manufacturer_Code = (uint16_t)0x00;
  pNOR_ID.Device_Code1 = (uint16_t)0x00;
  pNOR_ID.Device_Code2 = (uint16_t)0x00;
  pNOR_ID.Device_Code3 = (uint16_t)0x00;

  /* Read the NOR memory ID */
  if (BSP_NOR_Read_ID(&pNOR_ID) != NOR_STATUS_OK)
    ubIDStatus++;

  /* Test the NOR ID correctness */
  if ((pNOR_ID.Manufacturer_Code != (uint16_t)0x0001) && (pNOR_ID.Manufacturer_Code != (uint16_t)0x0089))
    ubIDStatus++;
  else if (pNOR_ID.Device_Code1 != (uint16_t)0x227E)
    ubIDStatus++;
  else if (pNOR_ID.Device_Code2 != (uint16_t)0x2221)
    ubIDStatus++;
  else if (pNOR_ID.Device_Code3 != (uint16_t)0x2201)
    ubIDStatus++;

  /*##-3- Erase NOR memory ###################################################*/
  /* Return to read mode */
  BSP_NOR_ReturnToReadMode();

  if (BSP_NOR_Erase_Block(NOR_WRITE_READ_ADDR) != NOR_STATUS_OK)
  {
    ubEraseStatus++;
  }

  /*##-4- NOR memory read/write access  ######################################*/
  /* Fill the buffer to write */
  Fill_Buffer(nor_aTxBuffer, NOR_BUFFER_SIZE, 0xC20F);

  /* Write data to the NOR memory */
  if (BSP_NOR_WriteData(NOR_WRITE_READ_ADDR, nor_aTxBuffer, NOR_BUFFER_SIZE) != NOR_STATUS_OK)
  {
    ubWriteStatus++;
  }

  /* Read back data from the NOR memory */
  if (BSP_NOR_ReadData(NOR_WRITE_READ_ADDR, nor_aRxBuffer, NOR_BUFFER_SIZE) != NOR_STATUS_OK)
  {
    ubReadStatus++;
  }

  /*##-5- Checking data integrity ############################################*/
  /* SDRAM initialization */
  BSP_SDRAM_Init();

  if (ubIDStatus != 0)
  {
    BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"NOR Read ID : FAILED.", LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 115, (uint8_t *)"NOR Test Aborted.", LEFT_MODE);
  }
  else
  {
    if (ubInitStatus != 0)
    {
      BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"NOR Initialization : FAILED.", LEFT_MODE);
      BSP_LCD_DisplayStringAt(20, 115, (uint8_t *)"NOR Test Aborted.", LEFT_MODE);
    }
    else
    {
      BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"NOR Initialization : OK.", LEFT_MODE);
    }
    if (ubEraseStatus != 0)
    {
      BSP_LCD_DisplayStringAt(20, 115, (uint8_t *)"NOR ERASE : FAILED.", LEFT_MODE);
      BSP_LCD_DisplayStringAt(20, 130, (uint8_t *)"NOR Test Aborted.", LEFT_MODE);
    }
    else
    {
      BSP_LCD_DisplayStringAt(20, 115, (uint8_t *)"NOR ERASE : OK.   ", LEFT_MODE);
    }
    if (ubWriteStatus != 0)
    {
      BSP_LCD_DisplayStringAt(20, 130, (uint8_t *)"NOR WRITE : FAILED.", LEFT_MODE);
      BSP_LCD_DisplayStringAt(20, 145, (uint8_t *)"NOR Test Aborted.", LEFT_MODE);
    }
    else
    {
      BSP_LCD_DisplayStringAt(20, 130, (uint8_t *)"NOR WRITE : OK.     ", LEFT_MODE);
    }
    if (ubReadStatus != 0)
    {
      BSP_LCD_DisplayStringAt(20, 145, (uint8_t *)"NOR READ : FAILED.", LEFT_MODE);
      BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)"NOR Test Aborted.", LEFT_MODE);
    }
    else
    {
      BSP_LCD_DisplayStringAt(20, 145, (uint8_t *)"NOR READ :  OK.    ", LEFT_MODE);
    }
    if (Buffercmp(nor_aRxBuffer, nor_aTxBuffer, NOR_BUFFER_SIZE) > 0)
    {
      BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)"NOR COMPARE : FAILED.", LEFT_MODE);
      BSP_LCD_DisplayStringAt(20, 175, (uint8_t *)"NOR Test Aborted.", LEFT_MODE);
    }
    else
    {
      BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)"NOR Test : OK.     ", LEFT_MODE);
    }
  }

  while (1)
  {
    if (CheckForUserInput() > 0)
    {
      BSP_NOR_DeInit();
      return;
    }
  }
}

/**
  * @brief  Display NOR Demo Hint
  * @param  None
  * @retval None
  */
static void NOR_SetHint(void)
{
  /* Clear the LCD */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Set LCD Demo description */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 80);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_SetFont(&Font24);
  BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"NOR", CENTER_MODE);
  BSP_LCD_SetFont(&Font12);
  BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)"This example shows how to write", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 45, (uint8_t *)"and read data on NOR", CENTER_MODE);

  /* Set the LCD Text Color */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_DrawRect(10, 90, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize() - 100);
  BSP_LCD_DrawRect(11, 91, BSP_LCD_GetXSize() - 22, BSP_LCD_GetYSize() - 102);

  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"test ongoing...", LEFT_MODE);
}

/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the buffer to fill
  * @param  uwBufferLenght: size of the buffer to fill
  * @param  uwOffset: first value to fill on the buffer
  * @retval None
  */
static void Fill_Buffer(uint16_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset)
{
  uint32_t tmpIndex = 0;

  /* Put in global buffer different values */
  for (tmpIndex = 0; tmpIndex < uwBufferLenght; tmpIndex++ )
  {
    pBuffer[tmpIndex] = tmpIndex + uwOffset;
  }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 1: pBuffer identical to pBuffer1
  *         0: pBuffer differs from pBuffer1
  */
static uint8_t Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}
/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
