/**
  ******************************************************************************
  * @file    TIM/TIM_DMA/Src/stm32f4xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
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

/** @defgroup HAL_MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */


/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - DMA configuration for transmission request by peripheral
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef   GPIO_InitStruct;
  static DMA_HandleTypeDef  hdma_tim;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIMx clock enable */
  TIMx_CLK_ENABLE();

  /* Enable GPIO Channel3/3N Clocks */
  TIMx_CHANNEL3_GPIO_CLK_ENABLE();

  /* Enable DMA clock */
  DMAx_CLK_ENABLE();


  /* Configure TIM3_Channel3 in output, push-pull & alternate function mode */
  GPIO_InitStruct.Pin = GPIO_PIN_CHANNEL3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF_TIMx;
  HAL_GPIO_Init(TIMx_GPIO_CHANNEL3_PORT, &GPIO_InitStruct);


  /* Set the parameters to be configured */
  hdma_tim.Init.Channel = DMA_CHANNEL_5;
  hdma_tim.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_tim.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_tim.Init.MemInc = DMA_MINC_ENABLE;
  hdma_tim.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD ;
  hdma_tim.Init.MemDataAlignment = DMA_MDATAALIGN_WORD ;
  hdma_tim.Init.Mode = DMA_CIRCULAR;
  hdma_tim.Init.Priority = DMA_PRIORITY_HIGH;
  hdma_tim.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  hdma_tim.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_tim.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_tim.Init.PeriphBurst = DMA_PBURST_SINGLE;

  /* Set hdma_tim instance */
  hdma_tim.Instance = TIMx_CC3_DMA_INST;

  /* Link hdma_tim to hdma[TIM_DMA_ID_CC3] (channel3) */
  __HAL_LINKDMA(htim, hdma[TIM_DMA_ID_CC3], hdma_tim);

  /* Initialize TIMx DMA handle */
  HAL_DMA_Init(htim->hdma[TIM_DMA_ID_CC3]);

  /*##-2- Configure the NVIC for DMA #########################################*/
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(TIMx_DMA_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIMx_DMA_IRQn);
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
