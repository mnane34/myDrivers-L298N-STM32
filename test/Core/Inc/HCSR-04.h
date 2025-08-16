/**
 * @file    HCSR-04.h
 * @brief 	HCSR-04 Ultrasonic Sensor Driver  for STM32
 * @author  Mertcan NANE
 * @date    2025-08-09
 * @version 1.0
 *
 * @contact
 *  https://github.com/mnane34
 *  https://www.youtube.com/@mnane34
 *  https://www.linkedin.com/in/mertcan-nane/
 */

#ifndef INC_HCSR_04_H_
#define INC_HCSR_04_H_

/* Header Directives Definitions */
#include "main.h"
#include "TIME.h"
#include "GPIO.h"

/* HCSR-04 Sensor Thresholding Definitions */
#define TIMEOUT_US 30000U

/* HCSR-04 Sensor State Definitions */
typedef enum {
    SENSOR_ERROR = 0,
    SENSOR_SUCCESS = 1
}SensorState_t;

/* HCSR-04 Base Pin Definitions */
typedef struct{

	volatile GPIO_TypeDef* TRIG_GPIOx;
	volatile uint16_t TRIG_PINx;

	volatile GPIO_TypeDef* ECHO_GPIOx;
	volatile uint16_t ECHO_PINx;

	uint32_t counter;
	uint32_t duration;
	float distance1;
	float distance2;

}HCSR04_TypeDef_t;

/* HCSR-04 Function Header Definitions */
void HCSR04_init(volatile GPIO_TypeDef* TRIG_GPIO, volatile uint16_t TRIG_PIN,
				 	 	 	 volatile GPIO_TypeDef* ECHO_GPIO, volatile uint16_t ECHO_PIN);
SensorState_t HCSR04_readSensor(void);
float HCSR04_getDistance_cm(SensorState_t readingState);
float HCSR04_getDistance_inch(SensorState_t readingState);


#endif
