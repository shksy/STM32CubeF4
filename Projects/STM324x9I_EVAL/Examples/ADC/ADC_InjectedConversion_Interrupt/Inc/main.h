/**
  ******************************************************************************
  * @file    ADC/ADC_InjectedConversion_Interrupt/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm324x9i_eval.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor ADCx instance used and associated 
   resources */
/* Definition for ADCx clock resources */
#define ADCx                                    ADC3
#define ADCx_CLK_ENABLE()                       __HAL_RCC_ADC3_CLK_ENABLE();
#define ADCx_REG_CHANNEL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
#define ADCx_INJ_CHANNEL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
     
#define ADCx_FORCE_RESET()                      __HAL_RCC_ADC_FORCE_RESET()
#define ADCx_RELEASE_RESET()                    __HAL_RCC_ADC_RELEASE_RESET()

/* Definition for ADCx Regular Channel Pin */
#define ADCx_REG_CHANNEL_PIN                    GPIO_PIN_10
#define ADCx_REG_CHANNEL_GPIO_PORT              GPIOF 

/* Definition for ADCx's Regular Channel */
#define ADCx_REG_CHANNEL                        ADC_CHANNEL_8

/* Definition for ADCx Regular Channel Pin */
#define ADCx_INJ_CHANNEL_PIN                    GPIO_PIN_2
#define ADCx_INJ_CHANNEL_GPIO_PORT              GPIOC 

/* Definition for ADCx's Regular Channel */
#define ADCx_INJ_CHANNEL                ADC_CHANNEL_12

/* Definition for ADCx's NVIC */
#define ADCx_IRQn                      ADC_IRQn

/* Exported macro ------------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
