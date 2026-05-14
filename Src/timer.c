#include <stm32f401xe.h>

/*
	Ohne CLK/PLL Config gilt;
	HSI = 16 MHz
	SYSCLK = 16 MHz
	APB1 = 16 MHz
	APB2 = 16 MHz
*/

static volatile uint32_t tick_ms = 0;

void tim2_init(void)
{
    RCC->APB1ENR |= (1U << 0);   // TIM2EN

    TIM2->PSC = 1600 - 1;        // 16 MHz / 1600 = 10 kHz
    TIM2->ARR = 10 - 1;          // 10 kHz / 10 = 1 kHz = 1 ms

    TIM2->CNT = 0;
    TIM2->SR  = 0;

    TIM2->DIER |= (1U<<0); // Interrupt enable
    NVIC_EnableIRQ(TIM2_IRQn);
    __enable_irq();

    TIM2->CR1 |= (1U << 0);      // Counter enable
}


void TIM2_IRQHandler(void)
{
    if(TIM2->SR & (1U<<0))
    {
        TIM2->SR &= ~(1U<<0);
        tick_ms++;
    }
}

uint32_t timer_ms(void)
{
    return tick_ms;
}

void delay_ms(uint32_t ms)
{
    uint32_t start = timer_ms();

    while((timer_ms() - start) < ms)
    {

    }
}
