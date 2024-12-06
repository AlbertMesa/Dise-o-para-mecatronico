#include "driver/spi_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define SPI_MOSI GPIO_NUM_23
#define SPI_CLK GPIO_NUM_18
#define SPI_CS GPIO_NUM_5

void app_main() {
    spi_bus_config_t bus_config = {
        .mosi_io_num = SPI_MOSI,
        .miso_io_num = -1,
        .sclk_io_num = SPI_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };
    spi_bus_initialize(HSPI_HOST, &bus_config, SPI_DMA_CH_AUTO);

    spi_device_interface_config_t dev_config = {
        .clock_speed_hz = 1 * 1000 * 1000,
        .mode = 0,
        .spics_io_num = SPI_CS,
        .queue_size = 1,
    };
    spi_device_handle_t handle;
    spi_bus_add_device(HSPI_HOST, &dev_config, &handle);

    uint8_t data[] = {0xA5, 0x5A};
    spi_transaction_t transaction = {
        .length = 8 * sizeof(data),
        .tx_buffer = data,
    };
    spi_device_transmit(handle, &transaction);
    vTaskDelay(pdMS_TO_TICKS(1000));
}
