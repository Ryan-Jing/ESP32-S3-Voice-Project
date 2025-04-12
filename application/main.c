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

void communication_task(void *pvParameters);
void audio_processing_task(void *pvParameters);

/**************************************************************************************************/
// FUNCTION DEFINITIONS
/**************************************************************************************************/

void app_main()
{
    ESP_LOGI(TAG, "Main App");
}
// end of main.c
