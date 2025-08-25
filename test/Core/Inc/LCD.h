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
#include "TIME.h"
#include "GPIO.h"

/* LCD Base Pin Definitions */
typedef struct{

	GPIO_TypeDef*  DATA4_GPIOx;
	uint16_t  DATA4_PINx;

	GPIO_TypeDef*  DATA5_GPIOx;
	uint16_t  DATA5_PINx;

	GPIO_TypeDef*  DATA6_GPIOx;
	uint16_t  DATA6_PINx;

	GPIO_TypeDef*  DATA7_GPIOx;
	uint16_t  DATA7_PINx;

	GPIO_TypeDef*  EN_GPIOx;
	uint16_t  EN_PINx;

	GPIO_TypeDef*  RS_GPIOx;
	uint16_t  RS_PINx;

}LCD_TypeDef_t;

/* Function Header Definitions */
void LCD_shiftRight(void);
void LCD_shiftLeft(void);
void LCD_writeString(const char *str);
void LCD_writeChar(char data);
void LCD_setCursor(unsigned char row, unsigned char column);
void LCD_clear(void);
void LCD_cmd(unsigned char cmd);
void LCD_data(unsigned char data);
void LCD_init( GPIO_TypeDef*  D4_GPIO, uint16_t  D4_PIN,
					  GPIO_TypeDef*  D5_GPIO, uint16_t  D5_PIN,
					  GPIO_TypeDef*  D6_GPIO, uint16_t  D6_PIN,
					  GPIO_TypeDef*  D7_GPIO, uint16_t  D7_PIN,
					  GPIO_TypeDef*  EN_GPIO, uint16_t  EN_PIN,
					  GPIO_TypeDef*  RS_GPIO, uint16_t  RS_PIN);

#endif
