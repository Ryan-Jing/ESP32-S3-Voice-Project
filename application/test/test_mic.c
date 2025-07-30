#include <stdio.h>
#include "unity.h"
#include "mic.h"
#include "esp_err.h"

TEST_CASE("i2s_config returns ESP_OK on successful init", "[mic]")
{
    esp_err_t ret = i2s_config();
    TEST_ASSERT_EQUAL_HEX32(ESP_OK, ret);
}

// TEST_CASE("mic buffer is zero-initialized", "[mic]")
// {
//     extern int16_t buffer[]; // buffer is defined in mic.c
//     for (size_t i = 0; i < I2S_BUFFER_SIZE; ++i) {
//         TEST_ASSERT_EQUAL_INT16(0, buffer[i]);
//     }
// }

// end of test_mic.c
