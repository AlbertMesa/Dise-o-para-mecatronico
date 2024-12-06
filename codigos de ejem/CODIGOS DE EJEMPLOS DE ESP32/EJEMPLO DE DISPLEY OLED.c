#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ssd1306.h"

#define SDA_PIN GPIO_NUM_21
#define SCL_PIN GPIO_NUM_22

void app_main() {
    ssd1306_i2c_init(SDA_PIN, SCL_PIN);
    ssd1306_clear_screen();
    ssd1306_draw_string(0, 0, "Hola, ESP32!", 12);
    ssd1306_refresh_gram();
    vTaskDelay(pdMS_TO_TICKS(2000));

    while (1) {
        ssd1306_clear_screen();
        ssd1306_draw_string(0, 0, "Actualizar Texto", 12);
        ssd1306_refresh_gram();
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
