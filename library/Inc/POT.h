/**
 * @file    POT.h
 * @brief   Potantiometer Functions for STM32
 * @author  Mertcan NANE
 * @date    2025-08-20
 * @version 1.0
 *
 * @contact
 *  https://github.com/mnane34
 *  https://www.youtube.com/@mnane34
 *  https://www.linkedin.com/in/mertcan-nane/
 */

#ifndef INC_POT_H_
#define INC_POT_H_

/* Additional Library Definitions */
#include "main.h"
#include "TIME.h"

typedef struct{
	ADC_HandleTypeDef *hadc;
	uint32_t tempValue;
	uint32_t adcValue;
}POT_TypeDef_t;

/* Function Header Definitions */
uint32_t POT_read(ADC_HandleTypeDef *hadc);
uint32_t POT_map(uint32_t value, long inMin, long inMax, long outMin, long outMax);

#endif
