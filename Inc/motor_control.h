/*
 * control.h
 *
 *  Created on: Apr 20, 2026
 *      Author: Morel
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <stdint.h>

typedef enum
{
    MODE_ECO,
    MODE_NORMAL,
    MODE_FAST
} MotorMode_t;

typedef enum
{
    DIR_FORWARD,
    DIR_BACKWARD
} MotorDirection_t;

typedef enum
{
    MOTOR_IDLE,
    MOTOR_RUNNING,
    MOTOR_STOPPED,
    MOTOR_ERROR
} MotorState_t;

typedef struct
{
    uint16_t steps;
    uint32_t stepDelayMs;
} MotorProfile_t;

void MotorControl_init(void);
void MotorControl_Stop(void);

void MotorControl_SetMode(MotorMode_t mode);
void MotorControl_SetDirection(MotorDirection_t dir);

void MotorControl_SetAdminSteps(uint16_t steps);
void MotorControl_SetAdminDelay(uint32_t delayMs);

void MotorControl_RunUserMode(void);
void MotorControl_RunAdminCustom(void);

void MotorControl_Task(void);


MotorMode_t MotorControl_GetMode(void);
MotorDirection_t MotorControl_GetDirection(void);
MotorState_t MotorControl_GetState(void);

const char* MotorControl_GetDirectionString(void);
const char* MotorControl_GetStateString(void);
const char* MotorControl_GetModeString(void);

uint16_t MotorControl_GetAdminSteps(void);
uint32_t MotorControl_GetAdminDelay(void);


#endif /* MOTOR_CONTROL_H_ */



