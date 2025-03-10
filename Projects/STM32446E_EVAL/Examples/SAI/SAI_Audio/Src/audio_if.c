/**
  ******************************************************************************
  * @file    SAI/SAI_Audio/Src/audio_if.c 
  * @author  MCD Application Team
  * @brief   This file provides the Audio Out (playback) interface API
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
#include "audio_if.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup SAI_Audio
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static AUDIO_BufferTypeDef  buffer_ctl;
static AUDIO_PLAYBACK_StateTypeDef  audio_state;

/* Private function prototypes -----------------------------------------------*/
static uint32_t GetData(void *pdata, uint32_t offset, uint8_t *pbuf, uint32_t NbrOfData);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes Audio Interface.
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_Init(void)
{
  audio_state = AUDIO_STATE_IDLE;
  
  if(BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_AUTO, AUDIO_DEFAULT_VOLUME, SAI_AUDIO_FREQUENCY_48K) == 0)
  {
    audio_state = AUDIO_STATE_INIT;
    return AUDIO_ERROR_NONE;
  }
  return AUDIO_ERROR_IO;
}

/**
  * @brief  Starts Audio streaming.    
  * @param  None
  * @retval Audio error
  */ 
AUDIO_ErrorTypeDef AUDIO_Start(void)
{
  uint32_t bytesread;
  
  buffer_ctl.state = BUFFER_OFFSET_NONE;
  bytesread = GetData( (void *)AUDIO_FILE_ADDRESS,
                      0,
                      &buffer_ctl.buff[0],
                      AUDIO_BUFFER_SIZE);
  if(bytesread > 0)
  {
    BSP_AUDIO_OUT_Play((uint16_t*)&buffer_ctl.buff[0], AUDIO_BUFFER_SIZE);
    audio_state = AUDIO_STATE_PLAYING;      
    buffer_ctl.fptr = bytesread;
    return AUDIO_ERROR_NONE;
  }
  return AUDIO_ERROR_IO;
}

/**
  * @brief  Manages Audio process. 
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_Process(void)
{
  uint32_t bytesread;
  AUDIO_ErrorTypeDef error_state = AUDIO_ERROR_NONE;  
  
  switch(audio_state)
  {
  case AUDIO_STATE_PLAYING:
    
    if(buffer_ctl.fptr >= AUDIO_FILE_SIZE)
    {
      /* Play audio sample again ... */
      buffer_ctl.fptr = 0; 
      error_state = AUDIO_ERROR_EOF;
    }

    /* 1st half buffer played; so fill it and continue playing from bottom*/
    if(buffer_ctl.state == BUFFER_OFFSET_HALF)
    {
      bytesread = GetData((void *)AUDIO_FILE_ADDRESS,
                          buffer_ctl.fptr,
                          &buffer_ctl.buff[0],
                          AUDIO_BUFFER_SIZE /2);
      
      if( bytesread >0)
      { 
        buffer_ctl.state = BUFFER_OFFSET_NONE;
        buffer_ctl.fptr += bytesread; 
      }
    }
    
    /* 2nd half buffer played; so fill it and continue playing from top */    
    if(buffer_ctl.state == BUFFER_OFFSET_FULL)
    {
      bytesread = GetData((void *)AUDIO_FILE_ADDRESS,
                          buffer_ctl.fptr, 
                          &buffer_ctl.buff[AUDIO_BUFFER_SIZE /2],
                          AUDIO_BUFFER_SIZE /2);
      if( bytesread > 0)
      {
        buffer_ctl.state = BUFFER_OFFSET_NONE;
        buffer_ctl.fptr += bytesread;
      }
    }
    break;
    
  default:
    error_state = AUDIO_ERROR_NOTREADY;
    break;
  }
  
  return error_state;
}

/**
  * @brief  Gets Data from storage unit.
  * @param  None
  * @retval None
  */
static uint32_t GetData(void *pdata, uint32_t offset, uint8_t *pbuf, uint32_t NbrOfData)
{
  uint8_t *lptr = pdata;
  uint32_t ReadDataNbr;
  
  ReadDataNbr = 0;
  while(((offset + ReadDataNbr) < AUDIO_FILE_SIZE) && (ReadDataNbr < NbrOfData))
  {
    pbuf[ReadDataNbr]= lptr [offset + ReadDataNbr];
    ReadDataNbr++;
  }
  return ReadDataNbr;
}

/*------------------------------------------------------------------------------
       Callbacks implementation:
           the callbacks API are defined __weak in the stm324x9i_eval_audio.c file
           and their implementation should be done the user code if they are needed.
           Below some examples of callback implementations.
  ----------------------------------------------------------------------------*/

/**
  * @brief  Calculates the remaining file size and new position of the pointer.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
  if(audio_state == AUDIO_STATE_PLAYING)
  {
    /* BSP_AUDIO sets SAI DMA in circular mode => no need to invoke SAI_Transmit each time */
    /* allows AUDIO_Process() to refill 2nd part of the buffer  */
    buffer_ctl.state = BUFFER_OFFSET_FULL;
  }
}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{ 
  if(audio_state == AUDIO_STATE_PLAYING)
  {
    /* allows AUDIO_Process() to refill 1st part of the buffer  */
    buffer_ctl.state = BUFFER_OFFSET_HALF;
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
