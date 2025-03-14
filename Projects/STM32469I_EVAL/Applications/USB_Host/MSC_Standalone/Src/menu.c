/**
  ******************************************************************************
  * @file    USB_Host/MSC_Standalone/Src/menu.c
  * @author  MCD Application Team
  * @brief   This file implements Menu Functions
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
MSC_DEMO_StateMachine msc_demo;
uint8_t prev_select = 0;
uint8_t *MSC_main_menu[] =
{
  (uint8_t *)"      1 - File Operations                                                   ",
  (uint8_t *)"      2 - Explorer Disk                                                     ",
  (uint8_t *)"      3 - Re-Enumerate                                                      ",
};

/* Private function prototypes -----------------------------------------------*/
static void MSC_SelectItem(uint8_t **menu, uint8_t item);
static void MSC_DEMO_ProbeKey(JOYState_TypeDef state);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Demo state machine.
  * @param  None
  * @retval None
  */
void Menu_Init(void)
{
  BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  BSP_LCD_DisplayStringAtLine(25, (uint8_t *)"Use [Joystick Left/Right] to scroll up/down");
  BSP_LCD_DisplayStringAtLine(26, (uint8_t *)"Use [Joystick Up/Down] to scroll MSC menu");
  msc_demo.state = MSC_DEMO_IDLE;
  MSC_SelectItem(MSC_main_menu, 0);
}

/**
  * @brief  Manages MSC Menu Process.
  * @param  None
  * @retval None
  */
void MSC_MenuProcess(void)
{
  switch(msc_demo.state)
  {
  case MSC_DEMO_IDLE:
    MSC_SelectItem(MSC_main_menu, 0);
    msc_demo.state = MSC_DEMO_WAIT;
    msc_demo.select = 0;
    break;

  case MSC_DEMO_WAIT:
    if(msc_demo.select != prev_select)
    {
      prev_select = msc_demo.select;
      MSC_SelectItem(MSC_main_menu, msc_demo.select & 0x7F);

      /* Handle select item */
      if(msc_demo.select & 0x80)
      {
        switch(msc_demo.select & 0x7F)
        {
        case 0:
          msc_demo.state = MSC_DEMO_FILE_OPERATIONS;
          break;

        case 1:
          msc_demo.state = MSC_DEMO_EXPLORER;
          break;

        case 2:
          msc_demo.state = MSC_REENUMERATE;
          break;

        default:
          break;
        }
      }
    }
    break;

  case MSC_DEMO_FILE_OPERATIONS:
    /* Read and Write File Here */
    if(Appli_state == APPLICATION_READY)
    {
      MSC_File_Operations();
    }
    msc_demo.state = MSC_DEMO_WAIT;
    break;

  case MSC_DEMO_EXPLORER:
    /* Display disk content */
    if(Appli_state == APPLICATION_READY)
    {
      Explore_Disk("0:/", 1);
    }
    msc_demo.state = MSC_DEMO_WAIT;
    break;

  case MSC_REENUMERATE:
    /* Force MSC Device to re-enumerate */
    USBH_ReEnumerate(&hUSBHost);
    msc_demo.state = MSC_DEMO_WAIT;
    break;

  default:
    break;
  }
  msc_demo.select &= 0x7F;
}

/**
  * @brief  Manages the menu on the screen.
  * @param  menu: Menu table
  * @param  item: Selected item to be highlighted
  * @retval None
  */
static void MSC_SelectItem(uint8_t **menu, uint8_t item)
{
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

  switch(item)
  {
  case 0:
    BSP_LCD_SetBackColor(LCD_COLOR_MAGENTA);
    BSP_LCD_DisplayStringAtLine(27, menu[0]);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_DisplayStringAtLine(28, menu[1]);
    BSP_LCD_DisplayStringAtLine(29, menu[2]);
    break;

  case 1:
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_DisplayStringAtLine(27, menu[0]);
    BSP_LCD_SetBackColor(LCD_COLOR_MAGENTA);
    BSP_LCD_DisplayStringAtLine(28, menu[1]);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_DisplayStringAtLine(29, menu[2]);
    break;

  case 2:
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_DisplayStringAtLine(27, menu[0]);
    BSP_LCD_DisplayStringAtLine(28, menu[1]);
    BSP_LCD_SetBackColor(LCD_COLOR_MAGENTA);
    BSP_LCD_DisplayStringAtLine(29, menu[2]);
    break;
  }
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
}

/**
  * @brief  Probes the MSC joystick state.
  * @param  state: Joystick state
  * @retval None
  */
static void MSC_DEMO_ProbeKey(JOYState_TypeDef state)
{
  /* Handle Menu inputs */
  if((state == JOY_UP) && (msc_demo.select > 0))
  {
    msc_demo.select--;
  }
  else if((state == JOY_DOWN) && (msc_demo.select < 2))
  {
    msc_demo.select++;
  }
  else if(state == JOY_SEL)
  {
    msc_demo.select |= 0x80;
  }
}

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  static JOYState_TypeDef JoyState = JOY_NONE;

  if(GPIO_Pin == MFX_IRQOUT_PIN)
  {
    /* The different functionalities of MFX (TS, Joystick, SD detection, etc. )
    can be configured in exti mode to generate an IRQ on given events.
    The MFX IRQ_OUT pin is unique and common to all functionalities, so if several
    functionalities are configured in exit mode, the MCU has to enquire MFX about
    the IRQ source (see BSP_IO_ITGetStatus). Communication with Mfx is done by I2C.
    Often the sw requires ISRs (irq service routines) to be quick while communication
    with I2C can be considered relatively long (hundreds of usec depending on I2C clk).
    Considering that the features for human interaction like TS, Joystick, SD detection
    don�t need immediate reaction, it is suggested to use POLLING instead of EXTI mode,
    in order to avoid "blocking I2C communication" on interrupt service routines */

    /* Get the Joystick State */
    JoyState = BSP_JOY_GetState();
    HAL_Delay(200);

    MSC_DEMO_ProbeKey(JoyState);

    switch(JoyState)
    {
    case JOY_LEFT:
      LCD_LOG_ScrollBack();
      break;

    case JOY_RIGHT:
      LCD_LOG_ScrollForward();
      break;

    default:
      break;
    }
    /* Clear joystick interrupt pending bits */
    BSP_IO_ITClear();
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
