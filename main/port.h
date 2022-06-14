/*! ----------------------------------------------------------------------------
 * @file	port.h
 * @brief	HW specific definitions and functions for portability
 *
 * @attention
 *
 * Copyright 2013 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */


#ifndef PORT_H_
#define PORT_H_

#include <stdint-gcc.h>

#ifdef __cplusplus
extern "C" {
#endif



/* Define our wanted value of CLOCKS_PER_SEC so that we have a millisecond
 * tick timer. */
#undef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000

//void printf2(const char *format, ...);

extern int writetospi_serial(uint16_t headerLength,
                             const uint8_t *headerBuffer,
                             uint32_t bodylength,
                             const uint8_t *bodyBuffer);

extern int readfromspi_serial(uint16_t	headerLength,
                              const uint8_t *headerBuffer,
                              uint32_t readlength,
                              uint8_t *readBuffer );

#define writetospi  writetospi_serial
#define readfromspi readfromspi_serial

typedef enum
{
    LED_PC6,
    LED_PC7,
    LED_PC8,
    LED_PC9,
    LED_ALL,
    LEDn
} led_t;

#define SPIy_PRESCALER				SPI_BaudRatePrescaler_128

#define SPIy						SPI2
#define SPIy_GPIO					GPIOB
#define SPIy_CS						GPIO_Pin_12
#define SPIy_CS_GPIO				GPIOB
#define SPIy_SCK					GPIO_Pin_13
#define SPIy_MISO					GPIO_Pin_14
#define SPIy_MOSI					GPIO_Pin_15

#define LCD_RW						GPIO_Pin_10
#define LCD_RS						GPIO_Pin_11

#define SPIx_PRESCALER				SPI_BaudRatePrescaler_8



#define TA_BOOT1                 	GPIO_Pin_2
#define TA_BOOT1_GPIO            	GPIOB

//PC0����ESP8266_CHPD
#define TA_RESP_DLY                 GPIO_Pin_0
#define TA_RESP_DLY_GPIO            GPIOC

//PC7,PC8,PC10,PC11,PC12
#define TA_SW1_3					GPIO_Pin_7
#define TA_SW1_4					GPIO_Pin_8
#define TA_SW1_6					GPIO_Pin_10
#define TA_SW1_7					GPIO_Pin_11
#define TA_SW1_8					GPIO_Pin_12
#define TA_SW1_GPIOC                 GPIOC

//PA15
#define TA_SW1_5					GPIO_Pin_15
#define TA_SW1_GPIOA                 GPIOA

#define S1_SWITCH_ON  (1)
#define S1_SWITCH_OFF (0)
//when switch (S1) is 'on' the pin is low
int is_switch_on(uint16_t GPIOpin);

#define port_IS_TAG_pressed()		is_switch_on(TA_SW1_4)
#define port_IS_LONGDLY_pressed()	is_dlybutton_low()



void led_on(led_t led);
void led_off(led_t led);
#define gpio_set(x)				0
#define gpio_reset(x)				0
#define is_gpio_out_low(x)			0
#define is_gpio_out_high(x)			0
			
/*! ------------------------------------------------------------------------------------------------------------------
 * @fn peripherals_init()
 *
 * @brief Initialise all peripherals.
 *
 * @param none
 *
 * @return none
 */
void peripherals_init (void);

void SPI_ChangeRate(uint16_t scalingfactor);
void SPI_ConfigFastRate(uint16_t scalingfactor);

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn spi_set_rate_low()
 *
 * @brief Set SPI rate to less than 3 MHz to properly perform DW1000 initialisation.
 *
 * @param none
 *
 * @return none
 */
void spi_set_rate_low (void);

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn spi_set_rate_high()
 *
 * @brief Set SPI rate as close to 20 MHz as possible for optimum performances.
 *
 * @param none
 *
 * @return none
 */
void spi_set_rate_high (void);

unsigned long portGetTickCnt(void);

#define portGetTickCount() 			portGetTickCnt()

void reset_DW1000(void);
void setup_DW1000RSTnIRQ(int enable);
void USART_putc(char c);

#ifdef __cplusplus
}
#endif

#endif /* PORT_H_ */
