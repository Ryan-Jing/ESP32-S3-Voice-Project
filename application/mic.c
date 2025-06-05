/**************************************************************************************************/
/**
 * @file i2s.c
 * @author Ryan Jing (r5jing@uwaterloo.ca)
 * @brief
 *
 * @version 0.1
 * @date 2025-04-12
 *
 * Copyright (c) 2024 Ryan Jing
 *
 */
/**************************************************************************************************/

/*------------------------------------------------------------------------------------------------*/
/* HEADERS                                                                                        */
/*------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include "driver/i2s_std.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "mic.h"
#include "driver/uart.h"
#include "utils.h"

/*------------------------------------------------------------------------------------------------*/
/* MACROS                                                                                         */
/*------------------------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------------------------*/
/* GLOBAL VARIABLES                                                                               */
/*------------------------------------------------------------------------------------------------*/

static const char *TAG = "MIC";

i2s_chan_handle_t rx_handle;

int16_t buffer[I2S_BUFFER_SIZE];

/*------------------------------------------------------------------------------------------------*/
/* FUNCTION PROTOTYPES                                                                            */
/*------------------------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------------------------*/
/* FUNCTION DEFINITIONS                                                                           */
/*------------------------------------------------------------------------------------------------*/

// CHECK NOTES AND ENSURE THIS IS THE CORRECT CONFIGURATION
esp_err_t i2s_config()
{
    esp_err_t return_code;

    // I2S channel configuration
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM, I2S_ROLE_MASTER);

    rx_handle = NULL;

    return_code = i2s_new_channel(&chan_cfg, NULL, &rx_handle);

    // Clock config
    i2s_std_clk_config_t clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(SAMPLE_RATE);

    // Slot config (Philips, mono, 16-bit)
    i2s_std_slot_config_t slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_BITS, I2S_SLOT_MODE_STEREO);

    // GPIO config (change these pins to match your setup)
    i2s_std_gpio_config_t gpio_cfg = {
        .bclk = I2S_SCK_PIN,
        .ws   = I2S_WS_PIN,
        .din  = I2S_SD_PIN,
        .dout = I2S_GPIO_UNUSED
    };

    i2s_std_config_t std_cfg = {
        .clk_cfg = clk_cfg,
        .slot_cfg = slot_cfg,
        .gpio_cfg = gpio_cfg
    };

    return_code = i2s_channel_init_std_mode(rx_handle, &std_cfg);
    return_code = i2s_channel_enable(rx_handle);

    if (return_code != ESP_OK) {
        ESP_LOGE(TAG, "I2S channel initialization failed: %s", esp_err_to_name(return_code));
    } else {
        ESP_LOGI(TAG, "I2S channel initialized successfully");
    }

    return return_code;
}

void i2s_task()
{
    size_t bytes_read = 0;
    esp_err_t ret = i2s_channel_read(rx_handle, buffer, I2S_BUFFER_SIZE, &bytes_read, pdMS_TO_TICKS(100));

    if (ret == ESP_OK && bytes_read > 0) {
        size_t sample_count = bytes_read / sizeof(int16_t);  // Adjust sample count based on 16-bit handling
        for (size_t i = 0; i < sample_count; ++i) {
            printf("%d\n", buffer[i]);  // Output raw audio data
            // uart_write_bytes(UART_NUM_0, (const char*)&buffer[i], sizeof(int16_t));  // Output raw binary audio data
        }
    } else {
        ESP_LOGW(TAG, "Read failed: %s", esp_err_to_name(ret));
    }
}

// end of mic.c
