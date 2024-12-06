#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/freeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define led1 33
#define led2 25
#define led3 26
#define STACK_SIZE 1024*2

#define delay1 2000
#define delay2 4000
#define delay3 8000

const char *tag = "Main";

esp_err_t init_led(void);
esp_err_t create_task(void);
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);

void app_main(void)
{
    init_led();
    while (1)
    {
        init_led();
        create_task();
        
    }
}

esp_err_t init_led()
{
    gpio_reset_pin(led1);
    gpio_set_direction(led1, GPIO_MODE_OUTPUT);
    gpio_reset_pin(led2);
    gpio_set_direction(led2, GPIO_MODE_OUTPUT);
    gpio_reset_pin(led3);
    gpio_set_direction(led3, GPIO_MODE_OUTPUT);
    return ESP_OK;
}

esp_err_t create_task(void)
{
    static uint8_t ucParameterToPass;
    TaskHandle_t xHandle = NULL;

    xTaskCreate(vTask1,
                "vTask1",
                STACK_SIZE,
                &ucParameterToPass,
                1,
                &xHandle);

    xTaskCreate(vTask2,
                "vTask2",
                STACK_SIZE,
                &ucParameterToPass,
                1,
                &xHandle);
    xTaskCreate(vTask3,
                "vTask3",
                STACK_SIZE,
                &ucParameterToPass,
                1,
                &xHandle);
    return ESP_OK;
}

void vTask1(void *pvParameters)
{
    while (1)
    {
        ESP_LOGI(tag, "Led G");
        vTaskDelay(pdMS_TO_TICKS(delay1));
        gpio_set_level(led1, 1);
        vTaskDelay(pdMS_TO_TICKS(delay1));
        gpio_set_level(led1, 0);
    }
}

void vTask2(void *pvParameters)
{
    while (1)
    {
        ESP_LOGE(tag, "Led B");
        vTaskDelay(pdMS_TO_TICKS(delay2));
        gpio_set_level(led2, 1);
        vTaskDelay(pdMS_TO_TICKS(delay2));
        gpio_set_level(led2, 0);
    }
}

void vTask3(void *pvParameters)
{
    while (1)
    {
        ESP_LOGW(tag, "Led Y");
        vTaskDelay(pdMS_TO_TICKS(delay3));
        gpio_set_level(led3, 1);
        vTaskDelay(pdMS_TO_TICKS(delay3));
        gpio_set_level(led3, 0);
    }
}
