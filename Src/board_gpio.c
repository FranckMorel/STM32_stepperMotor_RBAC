/*
 * board_gpio.c
 *
 *  Created on: May 5, 2026
 *      Author: Morel
 */

#include <spi.h>
#include <tft.h>
#include <stepper.h>
#include <encoder.h>

void enable_clocks(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    __DSB();
}

void board_gpio_init(void)
{
    enable_clocks();

    spi_gpio_init();
    tft_gpio_init();
    stepper_gpio_init();
    encoder_gpio_init();
}


