/*
 * motor_control.c
 *
 *  Created on: Apr 21, 2026
 *      Author: Morel
 */

#include <motor_control.h>
#include <stepper.h>
#include <timer.h>

static uint32_t lastStepTime = 0;
static uint32_t stepDelay_ms = 1;

static uint32_t targetSteps = 0;
static uint32_t currentSteps = 0;

static uint32_t pauseStartTime = 0;
static uint32_t pauseTime_ms = 1000;
static uint8_t pauseActive = 0;

volatile MotorMode_t currentMode = MODE_NORMAL;
volatile MotorDirection_t currentDirection = DIR_FORWARD;
static MotorState_t currentState = MOTOR_IDLE;

static uint16_t adminSteps = 0;
static uint32_t adminDelayMs = 1;


static const MotorProfile_t userProfiles[] =
{
    [MODE_ECO]    = {1024, 1},
    [MODE_NORMAL] = {2048, 1},
    [MODE_FAST]   = {4096, 1}
};

void MotorControl_init(void){

	stepper_init();
	currentMode = MODE_NORMAL;
	currentDirection = DIR_FORWARD;
}

void MotorControl_Stop(void){
	stepperStop();
	pauseActive = 0;
	currentState = MOTOR_STOPPED;
}


void MotorControl_RunUserMode(void){

	   MotorProfile_t profile = userProfiles[currentMode];

	   stepDelay_ms = profile.stepDelayMs;
	   lastStepTime = timer_ms();

	   targetSteps = profile.steps;
	   currentSteps = 0;

	   currentState = MOTOR_RUNNING;

}

void MotorControl_Task(void)
{
    if(currentState != MOTOR_RUNNING)
        return;
    if(pauseActive){

    	if(timer_ms() - pauseStartTime >= pauseTime_ms){

    		pauseActive = 0;
    		currentSteps = 0;
    		lastStepTime = timer_ms();

    		if(currentDirection == DIR_FORWARD)
    			currentDirection = DIR_BACKWARD;
    		else
    			currentDirection = DIR_FORWARD;
    	}

    	return;
   }

    if((timer_ms() - lastStepTime) >= stepDelay_ms)
    {
        lastStepTime = timer_ms();
        	if(currentDirection == DIR_FORWARD)
                stepForward();
            else
                stepBackward();

        	currentSteps++;

        if(currentSteps >= targetSteps){
        	stepperStop();
        	pauseStartTime = timer_ms();
        	pauseActive = 1;
        	}
    }
}

/*
void MotorControl_RunAdminCustom(void){

	if(adminSteps > 0 &&  adminDelayMs >= 1 ){
		currentState =  MOTOR_RUNNING;

		  if(currentDirection == DIR_FORWARD)
		  {
			  moveForward(adminSteps, adminDelayMs);
		  }
		  else
		  {
			  moveBackward(adminSteps, adminDelayMs);
		  }
		  currentState = MOTOR_IDLE;
  }else

  {
	  currentState = MOTOR_ERROR;
  }

}

*/

void MotorControl_SetMode(MotorMode_t mode){
	if(mode <= MODE_FAST)
		{
		  currentMode = mode;
		}
}

void MotorControl_SetDirection(MotorDirection_t dir){
	if(dir <= DIR_BACKWARD)
	   {
		currentDirection = dir;
	   }

}

void MotorControl_SetAdminSteps(uint16_t steps){
	adminSteps = steps;
}

void MotorControl_SetAdminDelay(uint32_t delayMs){
	adminDelayMs = delayMs;

}

MotorMode_t MotorControl_GetMode(void){
	return currentMode;
}

MotorDirection_t MotorControl_GetDirection(void){
	return currentDirection;
}

MotorState_t MotorControl_GetState(void){
	return currentState;
}

uint16_t MotorControl_GetAdminSteps(void){
	return adminSteps;
}
uint32_t MotorControl_GetAdminDelay(void){
	return adminDelayMs;
}

const char* MotorControl_GetModeString(void){

    switch(MotorControl_GetMode())
    {
        case MODE_ECO:    return "ECO";
        case MODE_NORMAL: return "NORMAL";
        case MODE_FAST:   return "FAST";
        default:          return "UNKNOWN";
    }
}

const char* MotorControl_GetStateString(void){

    switch(MotorControl_GetState())
    {
        case MOTOR_IDLE:    return "IDLE";
        case MOTOR_RUNNING: return "RUNNING";
        case MOTOR_STOPPED: return "STOPPED";
        case MOTOR_ERROR:   return "ERROR";
        default:            return "UNKNOWN";
    }
}

const char* MotorControl_GetDirectionString(void){

    switch(MotorControl_GetDirection())
    {
        case DIR_FORWARD:  return "FORWARD";
        case DIR_BACKWARD: return "BACKWARD";
        default:           return "UNKNOWN";
    }
}
