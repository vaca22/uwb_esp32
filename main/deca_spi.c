/*! ----------------------------------------------------------------------------
 * @file	deca_spi.c
 * @brief	SPI access functions
 *
 * @attention
 *
 * Copyright 2013 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */
#include <string.h>
#include <driver/spi_master.h>

#include "deca_spi.h"
#include "deca_sleep.h"
#include "deca_device_api.h"



/*! ------------------------------------------------------------------------------------------------------------------
 * Function: openspi()
 *
 * Low level abstract function to open and initialise access to the SPI device.
 * returns 0 for success, or -1 for error
 */
int openspi(/*SPI_TypeDef* SPIx*/)
{
	// done by port.c, default SPI used is SPI1

	return 0;

} // end openspi()

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: closespi()
 *
 * Low level abstract function to close the the SPI device.
 * returns 0 for success, or -1 for error
 */
int closespi(void)
{
//	while (port_SPIx_busy_sending()); //wait for tx buffer to empty
//
//	port_SPIx_disable();

	return 0;

} // end closespi()

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: writetospi()
 *
 * Low level abstract function to write to the SPI
 * Takes two separate byte buffers for write header and write data
 * returns 0 for success, or -1 for error
 */

extern spi_device_handle_t *mySpi;

int writetospi
(
    uint16       headerLength,
    const uint8 *headerBuffer,
    uint32       bodylength,
    const uint8 *bodyBuffer
)
{
    uint8 an[500];
    memcpy(an,headerBuffer,headerLength);
    memcpy(an+headerLength,bodyBuffer,bodylength);
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length = 8*(bodylength+headerLength);                     //Command is 8 bits
    t.tx_buffer = an;               //The data is the cmd itself
    t.user = (void *) 0;                //D/C needs to be set to 0
    spi_device_polling_transmit(*mySpi, &t);  //Transmit!

    return 0;
}


/*! ------------------------------------------------------------------------------------------------------------------
 * Function: readfromspi()
 *
 * Low level abstract function to read from the SPI
 * Takes two separate byte buffers for write header and read data
 * returns the offset into read buffer where first byte of read data may be found,
 * or returns -1 if there was an error
 */

int readfromspi
(
    uint16       headerLength,
    const uint8 *headerBuffer,
    uint32       readlength,
    uint8       *readBuffer
)
{

    uint8 an[500];
    memcpy(an,headerBuffer,headerLength);
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length = 8*(readlength+headerLength);                     //Command is 8 bits
    t.tx_buffer = an;               //The data is the cmd itself
    t.user = (void *) 0;                //D/C needs to be set to 0
    t.flags = SPI_TRANS_USE_RXDATA;
    spi_device_polling_transmit(*mySpi, &t);  //Transmit!

    memcpy(readBuffer,((uint8_t*)t.rx_data)+headerLength,readlength);

    return 0;
} // end readfromspi()
