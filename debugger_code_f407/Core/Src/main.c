/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_init.h"
#include "key.h"
#include "motor.h"
#include "retarget.h"
#include "DynamicX.h"
#include "can_communication.h"
#include "BMI1088_show.h"
#include "test1.h"
#include "test2.h"
#include "test3.h"
#include "fifo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t usart_data[8] = {0};

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
#define UART_TYPEC huart3
#define UART_GH huart2
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
///////////IMU////////////
extern float accel[3];
extern float gyro[3];
extern float mag[3];

extern float INS_quat[4];
extern float INS_angle[3];
uint8_t IMU_updata = 0;
extern uint8_t can_BMI_accel_data[8];
extern uint8_t can_BMI_gyro_data[8];

unsigned short x = 0;
unsigned short y = 0;
uint8_t key_Select_flag = 0;
uint8_t key_Verify_flag = 0;
uint8_t key_Enter_flag = 0;

Forms_struct_t forms;
uint16_t usart_times = 0;
uint16_t can_times = 0;
uint16_t times = 0;
uint16_t twinkles = 0;
extern uint16_t can_id[6];
extern unsigned char lcd_buffer[130 * 162 * 2];

/*��ʱ���ж�*/





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
    MX_CAN1_Init();
    MX_SPI1_Init();
    MX_SPI2_Init();
    MX_SPI3_Init();
    MX_USART2_UART_Init();
    MX_USART3_UART_Init();
    MX_TIM7_Init();
    /* USER CODE BEGIN 2 */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
    /* USER CODE END 2 */

    /* Call init function for freertos objects (in freertos.c) */
//    MX_FREERTOS_Init();
//
//    /* Start scheduler */
//    osKernelStart();
    /* We should never get here as control is now taken by the scheduler */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    RetargetInit(&huart3);//��ʼ����ӡ�ĺ���
    HAL_TIM_Base_Start_IT(&htim7);//������ʱ�����ж�

    can_init();//can��ʼ��
    can_fifo_init();

    /*���ڳ��жϳ�ʼ��*/
    HAL_UART_Receive_IT(&huart2, usart_data, 8);
    HAL_UART_Receive_IT(&huart3, usart_data, 8);

    gui_config();//lcd��Ļ��ʼ��

    HAL_Delay(5);
    main_Form_Init();
    HAL_SPI_Transmit_DMA(&hspi3, (uint8_t *) lcd_buffer, 128 * 160 * 2);
    HAL_Delay(5);

    uint8_t delay_times = 10;
    int count = 0;



    //HAL_UART_Transmit(&huart3, "test=", 5, HAL_MAX_DELAY);




    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */

        while (1) {

            key_Enter_flag = Enter_Key();
//            if (xpt2046_readxy(&x, &y) != 0xFF) {
//
//                x = (unsigned short) ((float) x * (0.0363f) - 8.2952f);
//                y = (unsigned short) ((float) y * (0.0492f) - 8.5976f);
//                printf("%d,%d\n", x, y);
//                break;
//            }
            if (key_Enter_flag == 2) {
                key_Verify_flag = 1;
                HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_7);
                break;
            }
            if (key_Enter_flag == 1) {
                key_Select_flag = (key_Select_flag + 1) % 5;
                HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);

                break;
            }
            if (times > 10) {
                times = 0;
                break;
            }

        }
        // printf("key=%d\n", key_Enter_flag);
        while (1) {

            Form_UpdateEvent();
            HAL_Delay(5);

            HAL_SPI_Transmit_DMA(&hspi3, (uint8_t *) lcd_buffer, 128 * 160 * 2);
            HAL_Delay(10);

            if (times > 10) {
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

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 224;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    /* USER CODE BEGIN Callback 0 */

    /* USER CODE END Callback 0 */
    if (htim->Instance == TIM6) {
        HAL_IncTick();
    }
    /* USER CODE BEGIN Callback 1 */
    can_times++;
    usart_times++;
    times++;
    twinkles++;
    AHRS_update(INS_quat, 1.0f / 1000.0f, gyro, accel, mag);
    get_angle(INS_quat, &INS_angle[0], &INS_angle[1], &INS_angle[2]);
    /* USER CODE END Callback 1 */
}

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
