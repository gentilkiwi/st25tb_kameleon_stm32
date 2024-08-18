/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define TRF_IO2_Pin GPIO_PIN_0
#define TRF_IO2_GPIO_Port GPIOC
#define TRF_IO4_SPI2_CS_Pin GPIO_PIN_1
#define TRF_IO4_SPI2_CS_GPIO_Port GPIOC
#define TRF_IO6_SPI2_MISO_Pin GPIO_PIN_2
#define TRF_IO6_SPI2_MISO_GPIO_Port GPIOC
#define TRF_IO7_SPI2_MOSI_Pin GPIO_PIN_3
#define TRF_IO7_SPI2_MOSI_GPIO_Port GPIOC
#define UBTN_Pin GPIO_PIN_0
#define UBTN_GPIO_Port GPIOA
#define UBTN_EXTI_IRQn EXTI0_IRQn
#define TRF_IRQ_Pin GPIO_PIN_1
#define TRF_IRQ_GPIO_Port GPIOA
#define TRF_IRQ_EXTI_IRQn EXTI1_IRQn
#define TRF_IO1_Pin GPIO_PIN_2
#define TRF_IO1_GPIO_Port GPIOA
#define TRF_IO0_Pin GPIO_PIN_3
#define TRF_IO0_GPIO_Port GPIOA
#define ULED1_Pin GPIO_PIN_4
#define ULED1_GPIO_Port GPIOA
#define TRF_SYS_CLK_SPI1_SCK_Pin GPIO_PIN_5
#define TRF_SYS_CLK_SPI1_SCK_GPIO_Port GPIOA
#define TRF_MOD_SPI1_MOSI_Pin GPIO_PIN_7
#define TRF_MOD_SPI1_MOSI_GPIO_Port GPIOA
#define TRF_IO5_Pin GPIO_PIN_4
#define TRF_IO5_GPIO_Port GPIOC
#define TRF_IO3_Pin GPIO_PIN_5
#define TRF_IO3_GPIO_Port GPIOC
#define D2_Pin GPIO_PIN_0
#define D2_GPIO_Port GPIOB
#define TRF_ASK_OOK_Pin GPIO_PIN_1
#define TRF_ASK_OOK_GPIO_Port GPIOB
#define TRF_DATA_CLK_SPI2_SCK_Pin GPIO_PIN_10
#define TRF_DATA_CLK_SPI2_SCK_GPIO_Port GPIOB
#define TRF_EN_Pin GPIO_PIN_11
#define TRF_EN_GPIO_Port GPIOB
#define D3_Pin GPIO_PIN_3
#define D3_GPIO_Port GPIOB
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOB
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOB
#define K2_Pin GPIO_PIN_6
#define K2_GPIO_Port GPIOB
#define K2_EXTI_IRQn EXTI9_5_IRQn
#define K1_Pin GPIO_PIN_7
#define K1_GPIO_Port GPIOB
#define K1_EXTI_IRQn EXTI9_5_IRQn
#define K3_Pin GPIO_PIN_8
#define K3_GPIO_Port GPIOB
#define K3_EXTI_IRQn EXTI9_5_IRQn
#define K4_Pin GPIO_PIN_9
#define K4_GPIO_Port GPIOB
#define K4_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
