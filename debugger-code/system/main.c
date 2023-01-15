/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_init.h"
#include "../function/key.h"
#include "../function/motor.h"
#include "retarget.h"
#include "DynamicX.h"

#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
unsigned short x = 0;
unsigned short y = 0;
uint8_t key_Select_flag = 0;
uint8_t key_Verify_flag = 0;
uint8_t key_Enter_flag = 0;
Forms_struct_t forms;


uint8_t usart_data[8] = {0};
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t usart_times = 0;
uint16_t times = 0;
uint16_t twinkles = 0;
extern uint16_t can_id[6];
extern unsigned char lcd_buffer[128 * 160 * 2];

/*定时器中断*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    usart_times++;
    times++;
    twinkles++;
    if (twinkles > 1000) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        twinkles = 0;
    }
}


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_CAN_Init();
    MX_SPI1_Init();
    MX_UART4_Init();
    MX_USART1_UART_Init();

    MX_SPI2_Init();
    MX_SPI3_Init();
    MX_TIM6_Init();
    MX_TIM4_Init();
    MX_TIM1_Init();

    /* USER CODE BEGIN 2 */
    // RetargetInit(&huart1);//初始化打印的函数
    //  RetargetInit(&huart4);
    HAL_TIM_Base_Start_IT(&htim1);//开启定时器的中断
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);//开启PWM输出
    can_init();//can初始化

    gui_config();//lcd屏幕初始化

    /*串口初中断初始化*/
    HAL_UART_Receive_IT(&huart1, usart_data, 8);
    HAL_UART_Receive_IT(&huart4, usart_data, 8);


    main_Form_Init();
    HAL_SPI_Transmit_DMA(&hspi3, (uint8_t *) lcd_buffer, 128 * 160 * 2);
    forms.id = 0;
    uint8_t delay_times = 10;
    /* USER CODE END 2 */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        /*获得触摸屏的数据*/
        while (1) {
            key_Enter_flag = Enter_Key();
            if (xpt2046_readxy(&x, &y) != 0xFF) {

                x = (unsigned short) ((float) x * (0.0363f) - 8.2952f);
                y = (unsigned short) ((float) y * (0.0492f) - 8.5976f);
                printf("%d,%d\n", x, y);
                break;
            }
            if (key_Enter_flag == 2) {
                key_Verify_flag = 1;
                break;
            }
            if (key_Enter_flag == 1) {
                key_Select_flag = (key_Select_flag + 1) % 5;
                break;
            }
            if (times > delay_times) {
                times = 0;
                break;
            }
        }
        printf("key=%d\n", key_Enter_flag);
        while (1) {
            Form_UpdateEvent();

            HAL_SPI_Transmit_DMA(&hspi3, (uint8_t *) lcd_buffer, 128 * 160 * 2);
            HAL_Delay(10);
            if (times > delay_times) {
                times = 0;
                break;
            }
        }


    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
