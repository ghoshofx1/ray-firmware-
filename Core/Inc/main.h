/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define FUEL_GAUGE_Pin GPIO_PIN_3
#define FUEL_GAUGE_GPIO_Port GPIOA
#define LSM_INT2_Pin GPIO_PIN_4
#define LSM_INT2_GPIO_Port GPIOC
#define LSM_CS_Pin GPIO_PIN_5
#define LSM_CS_GPIO_Port GPIOC
#define LSM_INT1_Pin GPIO_PIN_0
#define LSM_INT1_GPIO_Port GPIOB
#define PYRO2_CTRL_Pin GPIO_PIN_1
#define PYRO2_CTRL_GPIO_Port GPIOB
#define PYRO1_CTRL_Pin GPIO_PIN_2
#define PYRO1_CTRL_GPIO_Port GPIOB
#define LIS_CS_Pin GPIO_PIN_7
#define LIS_CS_GPIO_Port GPIOE
#define ICM_INT1_Pin GPIO_PIN_9
#define ICM_INT1_GPIO_Port GPIOE
#define ICM_INT2_Pin GPIO_PIN_10
#define ICM_INT2_GPIO_Port GPIOE
#define ADX_INT2_Pin GPIO_PIN_13
#define ADX_INT2_GPIO_Port GPIOE
#define ADX_INT1_Pin GPIO_PIN_14
#define ADX_INT1_GPIO_Port GPIOE
#define ADX_CS_Pin GPIO_PIN_15
#define ADX_CS_GPIO_Port GPIOE
#define MS5_CS_Pin GPIO_PIN_10
#define MS5_CS_GPIO_Port GPIOB
#define ICM_CS_Pin GPIO_PIN_12
#define ICM_CS_GPIO_Port GPIOB
#define GPS_CS_Pin GPIO_PIN_8
#define GPS_CS_GPIO_Port GPIOD
#define GPS_RST_Pin GPIO_PIN_9
#define GPS_RST_GPIO_Port GPIOD
#define GPS_PPS_Pin GPIO_PIN_10
#define GPS_PPS_GPIO_Port GPIOD
#define E22_RST_Pin GPIO_PIN_11
#define E22_RST_GPIO_Port GPIOD
#define E22_DIO1_Pin GPIO_PIN_12
#define E22_DIO1_GPIO_Port GPIOD
#define E22_TXEN_Pin GPIO_PIN_13
#define E22_TXEN_GPIO_Port GPIOD
#define E22_RXEN_Pin GPIO_PIN_14
#define E22_RXEN_GPIO_Port GPIOD
#define E22_BUSY_Pin GPIO_PIN_15
#define E22_BUSY_GPIO_Port GPIOD
#define E22_CS_Pin GPIO_PIN_6
#define E22_CS_GPIO_Port GPIOC
#define SERVO1_PWM_Pin GPIO_PIN_3
#define SERVO1_PWM_GPIO_Port GPIOB
#define SERVO2_PWM_Pin GPIO_PIN_4
#define SERVO2_PWM_GPIO_Port GPIOB
#define LED_B_EN_Pin GPIO_PIN_8
#define LED_B_EN_GPIO_Port GPIOB
#define BUZZ_EN_Pin GPIO_PIN_9
#define BUZZ_EN_GPIO_Port GPIOB
#define LED_G_EN_Pin GPIO_PIN_0
#define LED_G_EN_GPIO_Port GPIOE
#define LED_R_EN_Pin GPIO_PIN_1
#define LED_R_EN_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
