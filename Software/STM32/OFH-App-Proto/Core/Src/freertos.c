/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app.h"
#include "tusb.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for fanDriverTask */
osThreadId_t fanDriverTaskHandle;
uint32_t fanDriverTaskBuffer[ 128 ];
osStaticThreadDef_t fanDriverTaskControlBlock;
const osThreadAttr_t fanDriverTask_attributes = {
  .name = "fanDriverTask",
  .cb_mem = &fanDriverTaskControlBlock,
  .cb_size = sizeof(fanDriverTaskControlBlock),
  .stack_mem = &fanDriverTaskBuffer[0],
  .stack_size = sizeof(fanDriverTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for tUsbTask */
osThreadId_t tUsbTaskHandle;
uint32_t tUsbTaskBuffer[ 512 ];
osStaticThreadDef_t tUsbTaskControlBlock;
const osThreadAttr_t tUsbTask_attributes = {
  .name = "tUsbTask",
  .cb_mem = &tUsbTaskControlBlock,
  .cb_size = sizeof(tUsbTaskControlBlock),
  .stack_mem = &tUsbTaskBuffer[0],
  .stack_size = sizeof(tUsbTaskBuffer),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for cdcTask */
osThreadId_t cdcTaskHandle;
uint32_t cdcTaskBuffer[ 128 ];
osStaticThreadDef_t cdcTaskControlBlock;
const osThreadAttr_t cdcTask_attributes = {
  .name = "cdcTask",
  .cb_mem = &cdcTaskControlBlock,
  .cb_size = sizeof(cdcTaskControlBlock),
  .stack_mem = &cdcTaskBuffer[0],
  .stack_size = sizeof(cdcTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ledTask */
osThreadId_t ledTaskHandle;
uint32_t ledTaskBuffer[ 128 ];
osStaticThreadDef_t ledTaskControlBlock;
const osThreadAttr_t ledTask_attributes = {
  .name = "ledTask",
  .cb_mem = &ledTaskControlBlock,
  .cb_size = sizeof(ledTaskControlBlock),
  .stack_mem = &ledTaskBuffer[0],
  .stack_size = sizeof(ledTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartFanDriverTask(void *argument);
void StartTUsbTask(void *argument);
void StartCdcTask(void *argument);
void StartLedTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of fanDriverTask */
  fanDriverTaskHandle = osThreadNew(StartFanDriverTask, NULL, &fanDriverTask_attributes);

  /* creation of tUsbTask */
  tUsbTaskHandle = osThreadNew(StartTUsbTask, NULL, &tUsbTask_attributes);

  /* creation of cdcTask */
  cdcTaskHandle = osThreadNew(StartCdcTask, NULL, &cdcTask_attributes);

  /* creation of ledTask */
  ledTaskHandle = osThreadNew(StartLedTask, NULL, &ledTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartFanDriverTask */
/**
  * @brief  Function implementing the fanDriverTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartFanDriverTask */
void StartFanDriverTask(void *argument)
{
  /* USER CODE BEGIN StartFanDriverTask */
  (void) argument;
  /* Infinite loop */
  for(;;)
  {
    fanDriverLoop();
  }
  /* USER CODE END StartFanDriverTask */
}

/* USER CODE BEGIN Header_StartTUsbTask */
/**
* @brief Function implementing the tUsbTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTUsbTask */
void StartTUsbTask(void *argument)
{
  /* USER CODE BEGIN StartTUsbTask */
  (void) argument;
  tud_init(BOARD_TUD_RHPORT);
  /* Infinite loop */
  for(;;)
  {
    tUsbLoop();
  }
  /* USER CODE END StartTUsbTask */
}

/* USER CODE BEGIN Header_StartCdcTask */
/**
* @brief Function implementing the cdcTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCdcTask */
void StartCdcTask(void *argument)
{
  /* USER CODE BEGIN StartCdcTask */
  (void) argument;
  /* Infinite loop */
  for(;;)
  {
    cdcLoop();
  }
  /* USER CODE END StartCdcTask */
}

/* USER CODE BEGIN Header_StartLedTask */
/**
* @brief Function implementing the ledTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLedTask */
void StartLedTask(void *argument)
{
  /* USER CODE BEGIN StartLedTask */
  (void) argument;
  /* Infinite loop */
  for(;;)
  {
    ledLoop();
  }
  /* USER CODE END StartLedTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

