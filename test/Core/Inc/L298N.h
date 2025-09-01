/**
 * @file    L298N.h
 * @brief   L298N Motor Driver Development for STM32
 * @author  Mertcan NANE
 * @date    2025-08-20
 * @version 1.0
 *
 * @contact
 *  https://github.com/mnane34
 *  https://www.youtube.com/@mnane34
 *  https://www.linkedin.com/in/mertcan-nane/
 */
#ifndef INC_L298N_H_
#define INC_L298N_H_

/* Additional Library Definitions */
#include "main.h"
#include "TIME.h"
#include "GPIO.h"

typedef struct{
	TIM_HandleTypeDef *htim;
	uint32_t channel;
	uint16_t duty;
}L298N_TypeDef_t;

/* Motor Direction State Definitions */
typedef enum{
	NO_DIRECTION = 0,
	RIGHT = 1,
	LEFT = 2
}L298N_Direction_t;

/* Function Header Definitions */
void L298N_init(TIM_HandleTypeDef * hTIMx);
void L298N_setPWM(TIM_HandleTypeDef * hTIMx, uint32_t xChannel, uint16_t xDuty);
void L298N_setDirection(L298N_Direction_t direction);
#endif
