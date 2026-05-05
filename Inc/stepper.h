/*
 * stepper.h
 *
 *  Created on: Apr 18, 2026
 *      Author: Morel
 */


#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdint.h>

//A0,A1,A2,A3
#define IN1_AN			(GPIOA -> BSRR = (1U<<0))
#define IN1_AUS			(GPIOA -> BSRR = (1U<<16))
#define IN2_AN			(GPIOA -> BSRR = (1U<<1))
#define IN2_AUS			(GPIOA -> BSRR = (1U<<17))
#define IN3_AN			(GPIOA -> BSRR = (1U<<4))
#define IN3_AUS			(GPIOA -> BSRR = (1U<<20))
#define IN4_AN			(GPIOB -> BSRR = (1U<<0))
#define IN4_AUS			(GPIOB -> BSRR = (1U<<16))

void stepper_init(void);
void stepperStop(void);
void moveForward(uint16_t steps, uint32_t stepDelay_ms);
void moveBackward(uint16_t steps, uint32_t stepDelay_ms);




#endif /* STEPPER_H_ */
