/*
 * stepper.h
 *
 *  Created on: Apr 18, 2026
 *      Author: Morel
 */


#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdint.h>

void stepper_init(void);
void stepperStop(void);
void moveForward(uint16_t steps, uint32_t stepDelay_ms);
void moveBackward(uint16_t steps, uint32_t stepDelay_ms);




#endif /* STEPPER_H_ */
