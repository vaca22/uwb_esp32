#include <stdio.h>
#include <driver/spi_master.h>
#include <string.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "deca_device_api.h"

#define PIN_NUM_MISO 25
#define PIN_NUM_MOSI 22
#define PIN_NUM_CLK  23
#define PIN_NUM_CS   19
#define LCD_HOST    HSPI_HOST

spi_device_handle_t *mySpi;

void app_main(void)
{
    esp_err_t ret;
    spi_device_handle_t spi;
    spi_bus_config_t buscfg={
            .miso_io_num=PIN_NUM_MISO,
            .mosi_io_num=PIN_NUM_MOSI,
            .sclk_io_num=PIN_NUM_CLK,
            .quadwp_io_num=-1,
            .quadhd_io_num=-1,
            .max_transfer_sz=20*320*2+8
    };
    spi_device_interface_config_t devcfg={
            .clock_speed_hz=2*1000*1000,           //Clock out at 10 MHz
            .mode=0,                                //SPI mode 0
            .spics_io_num=PIN_NUM_CS,               //CS pin
            .queue_size=7,                          //We want to be able to queue 7 transactions at a time
    };
    ret=spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    ret=spi_bus_add_device(LCD_HOST, &devcfg, &spi);

    mySpi = &spi;

    if(dwt_initialise(DWT_LOADUCODE) == -1)
    {
       ESP_LOGE("fuick","dwm1000 init fail!\r\n");
        vTaskDelay(100);
    }
}
