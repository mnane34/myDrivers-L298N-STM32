/**
 * @file    GPIO.h
 * @brief   Base Direct Register Access to Control GPIO Pins for STM32
 * @author  Mertcan NANE
 * @date    2025-08-09
 * @version 1.0
 *
 * @contact
 *  https://github.com/mnane34
 *  https://www.youtube.com/@mnane34
 *  https://www.linkedin.com/in/mertcan-nane/
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

/* Header Directives Definitions */
#include "main.h"
#include "TIME.h"

/* GPIO Logic Level Macros Definitions */
#define HIGH 	1
#define LOW 	0

/* GPIO Direct Register Access Functions */
void GPIO_SET_PIN(volatile GPIO_TypeDef* GPIOx, volatile uint16_t GPIO_Pin);
void GPIO_RESET_PIN(volatile GPIO_TypeDef* GPIOx, volatile uint16_t GPIO_Pin);
void GPIO_TOGGLE_PIN(volatile GPIO_TypeDef* GPIOx, volatile uint16_t GPIO_Pin);
GPIO_PinState GPIO_READ_PIN(volatile GPIO_TypeDef* GPIOx, volatile uint16_t GPIO_Pin);

#endif
