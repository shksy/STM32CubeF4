/**
  ******************************************************************************
  * @file    USB_Host/HID_RTOS/Src/mouse.c 
  * @author  MCD Application Team
  * @brief   This file implements Functions for mouse menu
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
extern USBH_HandleTypeDef  hUSBHost;

/* Private define ------------------------------------------------------------*/

/* Left Button Report data */
#define HID_MOUSE_BUTTON1               0x01 
/* Right Button Report data */
#define HID_MOUSE_BUTTON2               0x02 
/* Middle Button Report data */
#define HID_MOUSE_BUTTON3               0x04 

/* Mouse directions */
#define MOUSE_TOP_DIR                   0x80
#define MOUSE_BOTTOM_DIR                0x00
#define MOUSE_LEFT_DIR                  0x80
#define MOUSE_RIGHT_DIR                 0x00

#define MOUSE_WINDOW_X                  7
#define MOUSE_WINDOW_Y                  52
#define MOUSE_WINDOW_X_MAX              10
#define MOUSE_WINDOW_Y_MIN              50
#define MOUSE_WINDOW_HEIGHT             40
#define MOUSE_WINDOW_WIDTH              110

#define HID_MOUSE_BUTTON_HEIGHT         10
#define HID_MOUSE_BUTTON_WIDTH          30
#define HID_MOUSE_BUTTON1_XCHORD        8
#define HID_MOUSE_BUTTON2_XCHORD        48
#define HID_MOUSE_BUTTON3_XCHORD        88
#define HID_MOUSE_BUTTON_YCHORD         100

#define MOUSE_LEFT_MOVE                  1
#define MOUSE_RIGHT_MOVE                 2
#define MOUSE_UP_MOVE                    3
#define MOUSE_DOWN_MOVE                  4

#define HID_MOUSE_HEIGHTLSB              2
#define HID_MOUSE_WIDTHLSB               2
#define HID_MOUSE_RES_X                  4  
#define HID_MOUSE_RES_Y                  4

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void USR_MOUSE_Init(void);
static void HID_MOUSE_UpdatePosition(int8_t x, int8_t y);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Manages Mouse Menu Process.  
  * @param  None
  * @retval None
  */
void HID_MouseMenuProcess(void)
{
  if(hid_demo.mouse_state == HID_MOUSE_START)
  {
    LCD_LOG_ClearTextZone();
    BSP_LCD_ClearStringLine(18);
    BSP_LCD_ClearStringLine(19);
    USBH_HID_MouseInit(&hUSBHost);
    USR_MOUSE_Init();
    HID_MOUSE_UpdatePosition(0,0);
  }
}  

/**
  * @brief  Init Mouse window.    
  * @param  None
  * @retval None
  */
static void USR_MOUSE_Init(void)
{
  LCD_LOG_ClearTextZone();
  BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
  BSP_LCD_DisplayStringAtLine(5, (uint8_t *)"USB HID Host Mouse Demo...   ");  
  BSP_LCD_DisplayStringAtLine(18, (uint8_t *)"Reset the board to restart            ");  
  BSP_LCD_SetTextColor(LCD_LOG_DEFAULT_COLOR);
  
  /* Display Mouse Window */
  BSP_LCD_DrawRect(MOUSE_WINDOW_X, MOUSE_WINDOW_Y, MOUSE_WINDOW_WIDTH, MOUSE_WINDOW_HEIGHT);
  
  HID_MOUSE_ButtonReleased(0);
  HID_MOUSE_ButtonReleased(1);
  HID_MOUSE_ButtonReleased(2);
  
  BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  
  HID_MOUSE_UpdatePosition(2,2);
}

/**
  * @brief  Processes Mouse data.
  * @param  data: Mouse data to be displayed
  * @retval None
  */
void USR_MOUSE_ProcessData(HID_MOUSE_Info_TypeDef *data)
{
  if((data->x != 0) && (data->y != 0))
  {
    HID_MOUSE_UpdatePosition(data->x , data->y);
  } 
} 

/**
  * @brief  Handles mouse scroll to update the mouse position on display window.
  * @param  x: USB HID Mouse X co-ordinate
  * @param  y: USB HID Mouse Y co-ordinate
  * @retval None
  */
static void HID_MOUSE_UpdatePosition(int8_t x, int8_t y)
{
  static int16_t  x_loc  = 0, y_loc  = 0; 
  static int16_t  prev_x = 5, prev_y = 1;  
  
  if((x != 0) || (y != 0)) 
  {
    x_loc += x/HID_MOUSE_RES_X;
    y_loc += y/HID_MOUSE_RES_Y;

    if(y_loc > MOUSE_WINDOW_HEIGHT - 12)
    {
      y_loc = MOUSE_WINDOW_HEIGHT - 12;
    }  
    if(x_loc > MOUSE_WINDOW_WIDTH - 10)
    {
      x_loc = MOUSE_WINDOW_WIDTH - 10;
    }  
    
    if(y_loc < 2)
    {
      y_loc = 2;
    }  
    if(x_loc < 2)
    {
      x_loc = 2;
    } 
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayChar(MOUSE_WINDOW_X + prev_x, MOUSE_WINDOW_Y + prev_y, 'x');   
    
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_DisplayChar(MOUSE_WINDOW_X + x_loc, MOUSE_WINDOW_Y + y_loc, 'x');
    
    prev_x = x_loc;
    prev_y = y_loc;
  }
}  

/**
  * @brief  Handles mouse button press.
  * @param  button_idx: Mouse button pressed
  * @retval None
  */
void HID_MOUSE_ButtonPressed(uint8_t button_idx)
{
  /* Set the color for button press status */
  BSP_LCD_SetTextColor(LCD_COLOR_RED);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  
  /* Change the color of button pressed to indicate button press */
  switch(button_idx)
  {
    /* Left Button Pressed */
  case 0:
    BSP_LCD_FillRect(HID_MOUSE_BUTTON1_XCHORD, HID_MOUSE_BUTTON_YCHORD,\
      HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT );
    break;
    
    /* Right Button Pressed */  
  case 1:
    BSP_LCD_FillRect(HID_MOUSE_BUTTON2_XCHORD,HID_MOUSE_BUTTON_YCHORD,\
      HID_MOUSE_BUTTON_WIDTH,HID_MOUSE_BUTTON_HEIGHT);
    break; 
    
    /* Middle button Pressed */  
  case 2:
    BSP_LCD_FillRect(HID_MOUSE_BUTTON3_XCHORD,HID_MOUSE_BUTTON_YCHORD,\
      HID_MOUSE_BUTTON_WIDTH,HID_MOUSE_BUTTON_HEIGHT);
    break;    
  }
}

/**
  * @brief  Handles mouse button release.
  * @param  button_idx: Mouse button released
  * @retval None
  */
void HID_MOUSE_ButtonReleased(uint8_t button_idx)
{
  /* Set the color for release status */
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
  
  /* Change the color of button released to default button color */
  switch(button_idx)
  {
    /* Left Button Released */
  case 0:
    BSP_LCD_FillRect(HID_MOUSE_BUTTON1_XCHORD, HID_MOUSE_BUTTON_YCHORD,\
      HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT);
    break;
    
    /* Right Button Released */  
  case 1:
    BSP_LCD_FillRect(HID_MOUSE_BUTTON2_XCHORD, HID_MOUSE_BUTTON_YCHORD,\
      HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT);
    break;
    
    /* Middle Button Released */  
  case 2:
    BSP_LCD_FillRect(HID_MOUSE_BUTTON3_XCHORD, HID_MOUSE_BUTTON_YCHORD,\
      HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT);
    break;
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
