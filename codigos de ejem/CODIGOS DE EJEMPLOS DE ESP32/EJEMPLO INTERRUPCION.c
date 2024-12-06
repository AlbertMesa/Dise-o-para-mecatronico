#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define BUTTON_PIN GPIO_NUM_0  // Pin del botón
#define LED_PIN GPIO_NUM_2     // Pin del LED

static const char *TAG = "BUTTON";

void IRAM_ATTR button_isr_handler(void *arg) {
    gpio_set_level(LED_PIN, !gpio_get_level(LED_PIN)); // Cambia el estado del LED
    ESP_EARLY_LOGI(TAG, "Botón presionado");
}

void app_main() {
    // Configuración del LED
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, 0);

    // Configuración del botón
    gpio_pad_select_gpio(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_NEGEDGE); // Detecta el flanco de bajada (presión)

    // Configura la interrupción
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, button_isr_handler, NULL);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
