/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//////////////gui///////////////
#include "lcd_init.h"
#include "gui_base.h"
#include "gui_button.h"
#include "gui_label.h"
#include "gui_form.h"

/////////////forms/////////////
#include "main_forms.h"
#include "suscap_debuger_forms.h"
#include "logic_forms.h"
#include "canid_forms.h"
#include "dail_forms.h"
#include "usart_forms.h"
#include "imu_forms.h"
#include "motor_forms.h"
#include "osinfo_forms.h"
#include "all_canid_form.h"

/////////////device/////////////
#include "xpt2046.h"

////////////function////////////
#include "led.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TXD_Pin GPIO_PIN_2
#define TXD_GPIO_Port GPIOA
#define RXD_Pin GPIO_PIN_3
#define RXD_GPIO_Port GPIOA
#define TOUCH_CS_Pin GPIO_PIN_4
#define TOUCH_CS_GPIO_Port GPIOA
#define TOUCH_CLK_Pin GPIO_PIN_5
#define TOUCH_CLK_GPIO_Port GPIOA
#define TOUCH_MISO_Pin GPIO_PIN_6
#define TOUCH_MISO_GPIO_Port GPIOA
#define TOUCH_MOSI_Pin GPIO_PIN_7
#define TOUCH_MOSI_GPIO_Port GPIOA
#define TOUCH_INT_Pin GPIO_PIN_5
#define TOUCH_INT_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_7
#define LED1_GPIO_Port GPIOE
#define LED2_Pin GPIO_PIN_8
#define LED2_GPIO_Port GPIOE
#define MCU_TXD_Pin GPIO_PIN_10
#define MCU_TXD_GPIO_Port GPIOB
#define MCU_RXD_Pin GPIO_PIN_11
#define MCU_RXD_GPIO_Port GPIOB
#define CAN_RX_Pin GPIO_PIN_11
#define CAN_RX_GPIO_Port GPIOA
#define CAN_TX_Pin GPIO_PIN_12
#define CAN_TX_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_15
#define LCD_CS_GPIO_Port GPIOA
#define LCD_CLK_Pin GPIO_PIN_3
#define LCD_CLK_GPIO_Port GPIOB
#define LCD_AO_Pin GPIO_PIN_4
#define LCD_AO_GPIO_Port GPIOB
#define LCD_MOSI_Pin GPIO_PIN_5
#define LCD_MOSI_GPIO_Port GPIOB
#define LCD_RST_Pin GPIO_PIN_6
#define LCD_RST_GPIO_Port GPIOB
#define LCD_LED_Pin GPIO_PIN_7
#define LCD_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
