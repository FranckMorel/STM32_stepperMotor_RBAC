/*
 * timer.h
 *
 *  Created on: Apr 20, 2026
 *      Author: Morel
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

void tim2_init(void);
uint32_t timer_ms(void);
void delay_ms(uint32_t ms);


#endif /* TIMER_H_ */
