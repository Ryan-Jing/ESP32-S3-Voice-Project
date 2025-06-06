#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "unity.h"

void test_example(void) {
    TEST_ASSERT_EQUAL(3, 1 + 1);
}

// This task runs all tests in a loop
void unity_task(void *pvParameter) {
    UNITY_BEGIN();
    unity_run_all_tests();
    UNITY_END();
    vTaskDelete(NULL); // End the task
}

void app_main(void) {
    xTaskCreate(unity_task, "unity_task", 4096, NULL, 5, NULL);
}

// end of test_main.c
