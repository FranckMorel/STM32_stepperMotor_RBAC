/*
 * r_encoder.c
 *
 *  Created on: May 5, 2026
 *      Author: Morel
 */

/*
CLK -> PB3
DT -> PA10
SW -> PB5
 */
#include <stm32f401xe.h>
#include <ui.h>
#include <timer.h>

#define ENC_DT_PORT   GPIOA
#define ENC_DT_PIN    10

#define ENC_CLK_PORT  GPIOB
#define ENC_CLK_PIN   3

#define ENC_SW_PORT   GPIOB
#define ENC_SW_PIN    5



static uint8_t last_clk = 1;
static uint8_t last_sw  = 1;


static uint8_t read_pin(GPIO_TypeDef *port, uint8_t pin){

    return (port->IDR >> pin) & 1U;
}

void encoder_gpio_init(void){
	// DT , SW und CLK als input Pins mit PULL-Up Widerstand

	//DT
	GPIOA -> MODER &= ~(3U<<(ENC_DT_PIN*2));
	GPIOA -> PUPDR &= ~(3U<<(ENC_DT_PIN*2));
	GPIOA -> PUPDR |=  (1U<<(ENC_DT_PIN*2));

	//CLK
	GPIOB -> MODER &= ~(3U<<(ENC_CLK_PIN*2));
	GPIOB -> PUPDR &= ~(3U<<(ENC_CLK_PIN*2));
	GPIOB -> PUPDR |=  (1U<<(ENC_CLK_PIN*2));

	//SW
	GPIOB -> MODER &= ~(3U<<(ENC_SW_PIN*2));
	GPIOB -> PUPDR &= ~(3U<<(ENC_SW_PIN*2));
	GPIOB -> PUPDR |=  (1U<<(ENC_SW_PIN*2));

}

void encoder_init(void){

    last_clk = read_pin(ENC_CLK_PORT, ENC_CLK_PIN);
    last_sw  = read_pin(ENC_SW_PORT, ENC_SW_PIN);
}


void encoder_task(void)
{
	  static uint8_t clk_last = 1;

	    uint8_t clk_now = (GPIOB->IDR >> 3) & 1U;    // CLK = PB3
	    uint8_t dt      = (GPIOA->IDR >> 10) & 1U;   // DT  = PA10

	    if ((clk_last == 1) && (clk_now == 0))
	    {
	        if (dt == 1)
	            UI_NextItem();
	        else
	            UI_PrevItem();
	        UI_DrawMenu();
	    }

	   // UI_DrawMenu();

	    clk_last = clk_now;
}

void encoder_button_task(void)
{
    static uint8_t sw_last = 1;
    static uint32_t last_press_time = 0;

    uint8_t sw_now = (GPIOB->IDR >> 5) & 1U;

    if ((sw_last == 1) && (sw_now == 0))
    {
        if ((timer_ms() - last_press_time) > 200)
        {
            last_press_time = timer_ms();
            UI_SelectItem();
        }
    }

    sw_last = sw_now;
}




