/**************************************************************************************************/
/**
 * @file main.c
 * @author Ryan Jing (r5jing@uwaterloo.ca)
 *
 * @brief This project aims to test sound processing algorithms on the ESP32 platform.
 *
 *        The goal is to implement a simple sound processing algorithm that can be run on the ESP32,
 *        and to limit test the performance of the ESP32 platform for sound processing tasks.
 *
 *       The project will use the ESP-IDF framework and the ESP32's I2S interface to read and write
 *       audio data. The project will also use FreeRTOS to manage tasks and scheduling.
 *
 * @version 0.1
 * @date 2025-04-09  
 *
 * Copyright (c) 2024 Ryan Jing
 *
 */
/**************************************************************************************************/

/**************************************************************************************************/
// HEADERS
/**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "driver/i2s.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "utils.h"

/**************************************************************************************************/
// MACROS
/**************************************************************************************************/

#define TAG             "main.c"

#define TASK_STACK_SIZE 2048
#define TASK_PRIORITY   5
#define TASK_DELAY      1000 / portTICK_PERIOD_MS

/**************************************************************************************************/
// GLOBAL VARIABLES
/**************************************************************************************************/

/**************************************************************************************************/
// FUNCTION PROTOTYPES
/**************************************************************************************************/

/**************************************************************************************************/
/**
 * @brief
 *
 *
 * @param[out] pvParameters
 */
/**************************************************************************************************/
void communication_task(void *pvParameters);

/**************************************************************************************************/
/**
 *
 * @brief   This function is the main task for audio processing.
 *
 *
 * @param[out] pvParameters
 */
/**************************************************************************************************/
void audio_processing_task(void *pvParameters);

/**************************************************************************************************/
/**
 * @brief
 *
 * @param[in]   void
 */
/**************************************************************************************************/
void main_initialize(void);

/**************************************************************************************************/
// FUNCTION DEFINITIONS
/**************************************************************************************************/

void communication_task(void *pvParameters)
{
    while (1)
    {
        // Simulate communication task
        ESP_LOGI(TAG, "Communication Task Running");
        vTaskDelay(TASK_DELAY);
    }
}

void audio_processing_task(void *pvParameters)
{
    while (1)
    {
        // Simulate audio processing task
        ESP_LOGI(TAG, "Audio Processing Task Running");
        vTaskDelay(TASK_DELAY);
        ESP_LOGI(TAG, "Audio Buffer: %d", audio_buffer[0]);  // Testing
    }
}

void main_initialize(void)
{
    // Create tasks
}

void app_main()
{
    ESP_LOGI(TAG, "Main App");
    main_initialize();

    xTaskCreate(
        communication_task, "Communication Task", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(
        audio_processing_task, "Audio Processing Task", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
}

// end of main.c
