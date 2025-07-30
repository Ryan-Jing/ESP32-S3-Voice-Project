#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "unity.h"

static const char test_tag[] = "[dummy_test]";

// TEST_CASE("A 1", test_tag)
// {
//     TEST_ASSERT_EQUAL((1+3), 2);
// }

// MUST HAVE esp_restart() WITHIN SINGLE EXECUTION FREE_RTOS TASK
// This task runs all tests in a loop
void unity_task(void *pvParameters) {
    printf("Hello from QEMU!\n");
    fflush(stdout);
    UNITY_BEGIN();
    unity_run_all_tests();
    UNITY_END();
    esp_restart();
}

void app_main(void) {
    xTaskCreate(unity_task, "unity_task", 4096, NULL, 5, NULL);
}

// end of test_main.c
