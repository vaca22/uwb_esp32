#include <stdio.h>
#include <driver/spi_master.h>
#include <string.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "deca_device_api.h"
#include "deca_regs.h"

#define PIN_NUM_MISO 1
#define PIN_NUM_MOSI 2
#define PIN_NUM_CLK  3
#define PIN_NUM_CS   19
#define LCD_HOST    SPI2_HOST

spi_device_handle_t *mySpi;
static dwt_config_t config2 = {
        2,               /* Channel number. */
        DWT_PRF_64M,     /* Pulse repetition frequency. */
        DWT_PLEN_1024,   /* Preamble length. Used in TX only. */
        DWT_PAC32,       /* Preamble acquisition chunk size. Used in RX only. */
        9,               /* TX preamble code. Used in TX only. */
        9,               /* RX preamble code. Used in RX only. */
        1,               /* 0 to use standard SFD, 1 to use non-standard SFD. */
        DWT_BR_110K,     /* Data rate. */
        DWT_PHRMODE_STD, /* PHY header mode. */
        (1025 + 64 - 32) /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
};
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
            .queue_size=8,                          //We want to be able to queue 7 transactions at a time
            .cs_ena_pretrans=1,
    };
    ret=spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_DISABLED);
    ESP_ERROR_CHECK(ret);
    ret=spi_bus_add_device(LCD_HOST, &devcfg, &spi);

    mySpi = &spi;

    if(dwt_initialise(DWT_LOADUCODE) == -1)
    {
       ESP_LOGE("fuick","dwm1000 init fail!\r\n");
        vTaskDelay(100);
    }
    ESP_LOGE("fuick","dwm1000 init good!\r\n");
//
//    dwt_configure(&config2);
//
//
//
//    char tx_msg[13]="lgh is a pig~!";
////
//    while(1) {
//
//        dwt_writetxdata(sizeof(tx_msg), (uint8_t*)tx_msg, 0);
//        dwt_writetxfctrl(sizeof(tx_msg), 0);
//
//
//        dwt_starttx(DWT_START_TX_IMMEDIATE);
//
//
//        vTaskDelay(10);
//
//        dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_TXFRS);
//    }
}
