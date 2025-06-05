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
 * @todo [] QEMU EMULATION
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

#include "driver/i2s_std.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "utils.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "mic.h"

/**************************************************************************************************/
// MACROS
/**************************************************************************************************/

#define TAG             "main.c"

#define TASK_STACK_SIZE     2048
#define AUDIO_TASK_SIZE     4096
#define TASK_PRIORITY       5
#define AUDIO_TASK_DELAY    2000 / portTICK_PERIOD_MS

#define LED_GPIO            2

/**************************************************************************************************/
// GLOBAL VARIABLES
/**************************************************************************************************/

esp_err_t return_code;

/**************************************************************************************************/
// FUNCTION PROTOTYPES
/**************************************************************************************************/

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
 * @name
 * @brief
 *
 *
 * @param pvParameters
 *
 */
/**************************************************************************************************/
void ble_task(void *pvParameters);

/**************************************************************************************************/
/**
 * @brief
 *
 * @param[in]   void
 */
/**************************************************************************************************/
void gpio_initialize(void);

/**************************************************************************************************/
/**
 * @name    audio_initialize
 * @brief   Initialize the audio processing task.
 *
 *
 *
 */
/**************************************************************************************************/
void audio_initialize(void);

/**************************************************************************************************/
/**
 * @name
 * @brief
 *
 *
 *
 */
/**************************************************************************************************/
void main_intialize(void);

/**************************************************************************************************/
// FUNCTION DEFINITIONS
/**************************************************************************************************/

void audio_processing_task(void *pvParameters)
{
    while (1)
    {
        // TickType_t start_time = xTaskGetTickCount();
        i2s_task();
        // TickType_t end_time = xTaskGetTickCount();
        // ESP_LOGI(TAG, "i2s_task execution time: %lu ms", (pdTICKS_TO_MS(end_time - start_time)));
        vTaskDelay(AUDIO_TASK_DELAY);
    }
}

void ble_task(void *pvParameters)
{
    while (1)
    {
        // Simulate BLE task
        ESP_LOGI(TAG, "BLE Task Running");
        vTaskDelay(AUDIO_TASK_DELAY);
    }
}

void main_intialize(void)
{
    ESP_LOGI(TAG, "Main Initialize");
    // Initialize UART for logging
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = UART_SCLK_APB,
    };
    const int uart_buffer_size = 1024 * 2;
    uart_param_config(UART_NUM_0, &uart_config);
    uart_set_pin(UART_NUM_0, 43, 44, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_0, uart_buffer_size, uart_buffer_size, 0, NULL, 0);
}

void gpio_initialize(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_GPIO),  // Select GPIO 48
        .mode = GPIO_MODE_OUTPUT,               // Set as output mode
        .pull_up_en = GPIO_PULLUP_DISABLE,      // Disable pull-up
        .pull_down_en = GPIO_PULLDOWN_DISABLE,  // Disable pull-down
        .intr_type = GPIO_INTR_DISABLE          // Disable interrupts
    };
    return_code = gpio_config(&io_conf);

    if (return_code != ESP_OK) {
        ESP_LOGE(TAG, "GPIO configuration failed: %s", esp_err_to_name(return_code));
    } else {
        ESP_LOGI(TAG, "GPIO configured successfully");
    }
}

void audio_initialize(void)
{
    return_code = i2s_config();

    if (return_code != ESP_OK) {
        ESP_LOGE(TAG, "I2S configuration failed: %s", esp_err_to_name(return_code));
    } else {
        ESP_LOGI(TAG, "I2S configured successfully");
    }
}

void app_main()
{
    ESP_LOGI(TAG, "Main App");

    gpio_initialize();
    audio_initialize();

    main_intialize();

    xTaskCreate(
        audio_processing_task, "Audio Processing Task", AUDIO_TASK_SIZE, NULL, TASK_PRIORITY, NULL);

    // This line should never be reached
}

// end of main.c
