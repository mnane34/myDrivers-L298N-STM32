#include "HCSR-04.h"

/* Structure Object Definition */
HCSR04_TypeDef_t HCSR04;
GPIO_PinState sensorState = SENSOR_ERROR;

/**
 * @brief Initializes the HC-SR04 sensor with TRIG and ECHO pins.
 * @param TRIG_GPIO Pointer to TRIG GPIO port
 * @param TRIG_PIN TRIG pin number
 * @param ECHO_GPIO Pointer to ECHO GPIO port
 * @param ECHO_PIN ECHO pin number
 */
void HCSR04_init( GPIO_TypeDef* TRIG_GPIO,  uint16_t TRIG_PIN,
				  	         GPIO_TypeDef* ECHO_GPIO,  uint16_t ECHO_PIN){

	HCSR04.TRIG_GPIOx = TRIG_GPIO;
	HCSR04.TRIG_PINx = TRIG_PIN;

	HCSR04.ECHO_GPIOx = ECHO_GPIO;
	HCSR04.ECHO_PINx = ECHO_PIN;

	HCSR04.counter = 0;
	HCSR04.duration = 0;
	HCSR04.distance1 = 0;
	HCSR04.distance2 = 0;
}

/**
 * @brief Reads distance measurement from HC-SR04 sensor.
 * @note Returns SENSOR_ERROR if TIMEOUT_US is exceeded.
 * @return SENSOR_SUCCESS or SENSOR_ERROR
 */
SensorState_t HCSR04_readSensor(void){

	uint32_t timeCounter = 0;

	while(GPIO_READ_PIN(HCSR04.ECHO_GPIOx, HCSR04.ECHO_PINx) == HIGH){ // wait for echo pin until low state, previous measurement may be not finished
		if(timeCounter >= TIMEOUT_US){
			return SENSOR_ERROR;
			HCSR04.duration = 0;
		}
		DELAY_US(1);
		timeCounter++;
	}

	GPIO_SET_PIN(HCSR04.TRIG_GPIOx, HCSR04.TRIG_PINx); // trig the sensor for new measurement
	DELAY_US(10);
	GPIO_RESET_PIN(HCSR04.TRIG_GPIOx, HCSR04.TRIG_PINx);

	timeCounter = 0;
	while(GPIO_READ_PIN(HCSR04.ECHO_GPIOx, HCSR04.ECHO_PINx) == LOW){ // wait for echo pin until high state, for controling ultrasonic wave
		if(timeCounter >= TIMEOUT_US){
			return SENSOR_ERROR;
			HCSR04.duration = 0;
		}
		DELAY_US(1);
		timeCounter++;
	}

	HCSR04.counter = 0;

    while (GPIO_READ_PIN(HCSR04.ECHO_GPIOx, HCSR04.ECHO_PINx) == HIGH){ // essential measurement was made at here, the counter is rising step by step per micro-second
        if (HCSR04.counter >= TIMEOUT_US){
        	return SENSOR_ERROR;
        	HCSR04.duration = 0;
        }
        DELAY_US(1);
        HCSR04.counter++;
    }

	HCSR04.duration = HCSR04.counter;
	DELAY_MS(100);

	return SENSOR_SUCCESS;
}

/**
 * @brief Converts the measured pulse duration to distance in centimeters.
 * @param readingState Result of HCSR04_readSensor() (SENSOR_SUCCESS or SENSOR_ERROR)
 * @return Distance in centimeters
 */
float HCSR04_getDistance_cm(SensorState_t readingState){

	SensorState_t currentState = readingState;

	if(currentState == SENSOR_SUCCESS){ // calculate distance as centimeter
		HCSR04.distance1 = HCSR04.duration / 58.0;
	}
	else{
		HCSR04.distance1 = 0;
	}

	return HCSR04.distance1;
}

/**
 * @brief Converts the measured pulse duration to distance in inches.
 * @param readingState Result of HCSR04_readSensor() (SENSOR_SUCCESS or SENSOR_ERROR)
 * @return Distance in inches
 */
float HCSR04_getDistance_inch(SensorState_t readingState){

	SensorState_t currentState = readingState;

	if(currentState == SENSOR_SUCCESS){ // calculate distance as inch
		HCSR04.distance2 = HCSR04.duration / 148.0;
	}
	else{
		HCSR04.distance2 = 0;
	}

	return HCSR04.distance2;
}
