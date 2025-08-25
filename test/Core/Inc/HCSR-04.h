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

	GPIO_TypeDef* TRIG_GPIOx;
	uint16_t TRIG_PINx;

	GPIO_TypeDef* ECHO_GPIOx;
	uint16_t ECHO_PINx;

	uint32_t counter;
	uint32_t duration;
	float distance1;
	float distance2;

}HCSR04_TypeDef_t;

/* HCSR-04 Function Header Definitions */
void HCSR04_init(GPIO_TypeDef* TRIG_GPIO,  uint16_t TRIG_PIN,
				  	  	  	GPIO_TypeDef* ECHO_GPIO, uint16_t ECHO_PIN);
SensorState_t HCSR04_readSensor(void);
float HCSR04_getDistance_cm(SensorState_t readingState);
float HCSR04_getDistance_inch(SensorState_t readingState);

#endif
