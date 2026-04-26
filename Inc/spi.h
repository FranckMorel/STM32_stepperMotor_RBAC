/*
 * spi.h
 *
 *  Created on: Apr 17, 2026
 *      Author: MOREL
 */

#ifndef SPI_H_
#define SPI_H_

#include <stm32f401xe.h>
#include <stdint.h>


void spi_gpio_Init(void);
void spi1_config(void);
void spi1_transmit(uint8_t *data, uint32_t size);
void spi1_recieve(uint8_t *data, uint32_t size);
void cs_enable(void);
void cs_disable(void);



#endif /* SPI_H_ */
