/*

 NOTES*

 alternate funtion mapping -> Data sheet stm32f401re

 PA7 -> MOSI , AF
 PA5 -> SCK , AF

 */

#include "stm32f401xe.h"

#define SPI1EN 			(1U<<12)
#define GPIOAEN			(1U<<0)
#define SPI_CPHA		(1U<<0)
#define SPI_CPOL		(1U<<1)
#define FUll_DuplexEN	(1U<<10)
#define LSBFirst		(1U<<7)
#define MSTR			(1U<<2)
#define DFF 			(1U<<11)
#define SSM 			(1U<<9)
#define SSI				(1U<<8)
#define SPIEN			(1U<<6)

#define SR_TXE			(1U<<1)
#define SR_BSY			(1U<<7)
#define SR_RXNE			(1U<<0)



void spi_gpio_init(void){

	// set PA5 and PA7 to alternate function Mode
	GPIOA->MODER &= ~(3U << (5*2));
	GPIOA->MODER |= (2U << (5*2));

	GPIOA->MODER &= ~(3U << (7*2));
	GPIOA->MODER |= (2U << (7*2));

	/* set alternate function type to SPI1
	  Pins 0 to 7 -> alternate function LOW Register
	  Pins 8 to 15 -> alternate function HIGH Register
	 */

	//PA5 to AF5 , 20 - 23 ( 0101 )
	GPIOA->AFR[0] &= ~(15U << (5*4));
	GPIOA->AFR[0] |= (5U << (5*4));

	//PA7 to AF5 , 28 - 31 ( 0101 )
	GPIOA->AFR[0] &= ~(15U << (7*4));
	GPIOA->AFR[0] |= (5U << (7*4));

}

void spi1_config(void){
	RCC -> APB2ENR |= SPI1EN;

	/*	Set clock to fpclk/2
	 	BR zu 010 -> 84MHz/8 , SCL max beim ST7735S 15MHz
	 */
	SPI1->CR1 &= ~(7U << 3);
	SPI1->CR1 |= (2U << 3);

	// CPOL und CPHA auf MODE0 -> 0,0 laut Datenblatt ST7735S
	SPI1 -> CR1 &= ~(SPI_CPOL);
	SPI1 -> CR1 &= ~(SPI_CPHA);

	// Enable Full duplex
	SPI1 -> CR1 &= ~(FUll_DuplexEN);

	// Enable MSB Fisrt, spezifisch für ST7735S
	SPI1 -> CR1 &= ~(LSBFirst);

	// Set Master Mode
	SPI1 -> CR1 |= (MSTR);

	// Set 8-Bit Data Mode
	SPI1 -> CR1 &= ~(DFF);

	// Enable Software slave management
	SPI1 -> CR1 |= (SSM);
	SPI1 -> CR1 |= (SSI);

	// Enable SPI periph
	SPI1 -> CR1 |= (SPIEN);

}


void spi1_transmit(uint8_t *data, uint32_t size){
	uint32_t i = 0;
	uint8_t temp;

	while(i<size)
	{
	  // Wait until TXE ist set -> SPI_SR
		while(!(SPI1 -> SR & (SR_TXE))){}

	  // Write the data to data Buffer
		SPI1 -> DR = data[i];
		i++;
	}

	// Wait until TX Buffer empty
	while(!(SPI1 -> SR & (SR_TXE))){}

	// Wait for BSY flag to reset
	while(SPI1 -> SR & SR_BSY){}

	// Clear the OVR flag -> Reference Manual(Error flags)
	temp = SPI1 -> DR;
	temp = SPI1 -> SR;

}


void spi1_receive(uint8_t *data, uint32_t size){

	while(size){
		SPI1 ->DR = 0;

		while(!(SPI1 -> SR & SR_RXNE)){}

		*data++ = (SPI1 -> DR);
		 size--;
	}
}



