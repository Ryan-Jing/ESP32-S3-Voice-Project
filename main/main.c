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
 * @version 0.1
 * @date 2025-04-09  
 *
 * Copyright (c) 2024 Ryan Jing
 *
 */
/**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "driver/i2s.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#define TAG "main.c"

void app_main()
{
    ESP_LOGI(TAG, "Main App");
}