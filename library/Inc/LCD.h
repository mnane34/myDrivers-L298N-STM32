/**
 * @file    LCD.h
 * @brief   16x2 Liquid Crystal Display Driver for STM32
 * @author  Mertcan NANE
 * @date    2025-08-09
 * @version 1.0
 *
 * @contact
 *  https://github.com/mnane34
 *  https://www.youtube.com/@mnane34
 *  https://www.linkedin.com/in/mertcan-nane/
 */

#ifndef LCD_H_
#define LCD_H_

/* Header Directives Definitions */
#include "main.h"
#include "stdint.h"
#include "main.h"
#include "TIME.h"
#include "GPIO.h"

/* LCD Base Pin Definitions */
typedef struct{

	volatile GPIO_TypeDef* DATA4_GPIOx;
	volatile uint16_t DATA4_PINx;

	volatile GPIO_TypeDef* DATA5_GPIOx;
	volatile uint16_t DATA5_PINx;

	volatile GPIO_TypeDef* DATA6_GPIOx;
	volatile uint16_t DATA6_PINx;

	volatile GPIO_TypeDef* DATA7_GPIOx;
	volatile uint16_t DATA7_PINx;

	volatile GPIO_TypeDef* EN_GPIOx;
	volatile uint16_t EN_PINx;

	volatile GPIO_TypeDef* RS_GPIOx;
	volatile uint16_t RS_PINx;

}LCD_TypeDef_t;

extern LCD_TypeDef_t LCD;

/* Function Header Definitions */
void LCD_shiftRight();
void LCD_shiftLeft();
void LCD_writeString(char *str);
void LCD_writeChar(char data);
void LCD_setCursor(unsigned char row, unsigned char column);
void LCD_clear();
void LCD_CMD(unsigned char cmd);
void LCD_DATA(unsigned char data);
void LCD_InitStruct(volatile GPIO_TypeDef* D4_GPIO, volatile uint16_t D4_PIN,
					volatile GPIO_TypeDef* D5_GPIO, volatile uint16_t D5_PIN,
					volatile GPIO_TypeDef* D6_GPIO, volatile uint16_t D6_PIN,
					volatile GPIO_TypeDef* D7_GPIO, volatile uint16_t D7_PIN,
					volatile GPIO_TypeDef* EN_GPIO, volatile uint16_t EN_PIN,
					volatile GPIO_TypeDef* RS_GPIO, volatile uint16_t RS_PIN);

#endif
