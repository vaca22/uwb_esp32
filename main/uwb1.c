#include <stdio.h>
#include <driver/spi_master.h>
#include <string.h>
#include <freertos/task.h>

#define PIN_NUM_MISO 22
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  21
#define PIN_NUM_CS   13
#define LCD_HOST    HSPI_HOST

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
            .clock_speed_hz=10*1000*1000,           //Clock out at 10 MHz
            .mode=0,                                //SPI mode 0
            .spics_io_num=PIN_NUM_CS,               //CS pin
            .queue_size=7,                          //We want to be able to queue 7 transactions at a time
    };
    ret=spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    ret=spi_bus_add_device(LCD_HOST, &devcfg, &spi);

    for(int k=0;k<5;k++){
        uint8_t cmd=0x55;
        spi_transaction_t t;
        memset(&t, 0, sizeof(t));       //Zero out the transaction
        t.length=8;                     //Command is 8 bits
        t.tx_buffer=&cmd;               //The data is the cmd itself
        t.user=(void*)0;                //D/C needs to be set to 0
        ret=spi_device_polling_transmit(spi, &t);
        vTaskDelay(1);
    }

}
