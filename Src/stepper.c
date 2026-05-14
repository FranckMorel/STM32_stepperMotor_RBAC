#include <stm32f401xe.h>
#include <stepper.h>


#define IN1_PIN    0
#define IN2_PIN    1
#define IN3_PIN    4
#define IN4_PIN    0


static int stepIndex = 0;
volatile uint32_t stepDelay_ms = 1;


/*
static void speedDelay(void){
	for(int i=0; i<2000; i++){}
}
*/

// Pattern for Half drive Sequence

uint8_t phase[8][4] = {
	  {1, 0, 0, 0},  // Schritt 1
	  {1, 1, 0, 0},  // Schritt 2
	  {0, 1, 0, 0},  // Schritt 3
	  {0, 1, 1, 0},  // Schritt 4
	  {0, 0, 1, 0},  // Schritt 5
	  {0, 0, 1, 1},  // Schritt 6
	  {0, 0, 0, 1},  // Schritt 7
	  {1, 0, 0, 1}   // Schritt 8
};

// Pattern for Full drive sequence
/*
uint8_t phase[4][4] = {
	  {1, 1, 0, 0},  // Schritt 1
	  {0, 1, 1, 0},  // Schritt 2
	  {0, 0, 1, 1},  // Schritt 3
	  {1, 0, 0, 1},  // Schritt 4
};
*/
static void step_Output(int stepIndex){

	    if(phase[stepIndex][0]) IN1_AN;
	    else               		IN1_AUS;

	    if(phase[stepIndex][1]) IN2_AN;
	    else               		IN2_AUS;

	    if(phase[stepIndex][2]) IN3_AN;
	    else               		IN3_AUS;

	    if(phase[stepIndex][3]) IN4_AN;
	    else               		IN4_AUS;

}

void stepper_gpio_init(void){

	GPIOA -> MODER &= ~(3U << (IN1_PIN*2));
	GPIOA -> MODER |=  (1U <<(IN1_PIN*2));

	GPIOA -> MODER &= ~(3U << (IN2_PIN*2));
	GPIOA -> MODER |=  (1U <<(IN2_PIN*2));

	GPIOA -> MODER &= ~(3U << (IN3_PIN*2));
	GPIOA -> MODER |=  (1U <<(IN3_PIN*2));

	GPIOB -> MODER &= ~(3U << (IN4_PIN*2));
	GPIOB -> MODER |=  (1U <<(IN4_PIN*2));

}


void stepper_init(void){

	stepIndex = 0;
	step_Output(stepIndex);

}

void stepperStop(void){

	IN1_AUS; IN2_AUS; IN3_AUS; IN4_AUS;

}

void stepForward(void){
	stepIndex++;
	if(stepIndex >= 8){

		stepIndex = 0;
	}

	step_Output(stepIndex);
	//speedDelay();

}

void stepBackward(void){
	stepIndex--;
	if(stepIndex < 0){

		stepIndex = 7;
	}

	step_Output(stepIndex);
	//speedDelay();

}


void moveForward(uint16_t steps, uint32_t stepDelay_ms){
  for(uint16_t i = 0; i < steps; i++){

	    stepForward();
	    delay_ms(stepDelay_ms);
     }

}

void moveBackward(uint16_t steps, uint32_t stepDelay_ms){
	for(uint16_t i = 0; i < steps; i++){

		stepBackward();
		delay_ms(stepDelay_ms);
	  }
}



