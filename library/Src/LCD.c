/* Header Directives Definition */
#include "LCD.h"

/* Structure Object Definition */
LCD_TypeDef_t LCD;

/**
 * @brief Initializes the LCD with the given GPIO ports and pins
 *
 * This function sets up the GPIO connections for the LCD data lines (D4–D7),
 * Enable (EN), and Register Select (RS) pins, then performs the initialization
 * sequence required to start communication in 4-bit mode
 *
 * @param D4_GPIO GPIO port for data line D4
 * @param D4_PIN  Pin number for data line D4
 * @param D5_GPIO GPIO port for data line D5
 * @param D5_PIN  Pin number for data line D5
 * @param D6_GPIO GPIO port for data line D6
 * @param D6_PIN  Pin number for data line D6
 * @param D7_GPIO GPIO port for data line D7
 * @param D7_PIN  Pin number for data line D7
 * @param EN_GPIO GPIO port for Enable (EN) pin
 * @param EN_PIN  Pin number for Enable (EN) pin
 * @param RS_GPIO GPIO port for Register Select (RS) pin
 * @param RS_PIN  Pin number for Register Select (RS) pin
 */
void LCD_InitStruct(volatile GPIO_TypeDef* D4_GPIO, volatile uint16_t D4_PIN,
					volatile GPIO_TypeDef* D5_GPIO, volatile uint16_t D5_PIN,
					volatile GPIO_TypeDef* D6_GPIO, volatile uint16_t D6_PIN,
					volatile GPIO_TypeDef* D7_GPIO, volatile uint16_t D7_PIN,
					volatile GPIO_TypeDef* EN_GPIO, volatile uint16_t EN_PIN,
					volatile GPIO_TypeDef* RS_GPIO, volatile uint16_t RS_PIN){

	LCD.DATA4_GPIOx = D4_GPIO; // saving LCD parameters to base structure
	LCD.DATA4_PINx  = D4_PIN;

	LCD.DATA5_GPIOx = D5_GPIO;
	LCD.DATA5_PINx  = D5_PIN;

	LCD.DATA6_GPIOx = D6_GPIO;
	LCD.DATA6_PINx  = D6_PIN;

	LCD.DATA7_GPIOx = D7_GPIO;
	LCD.DATA7_PINx  = D7_PIN;

	LCD.EN_GPIOx = EN_GPIO;
	LCD.EN_PINx  = EN_PIN;

	LCD.RS_GPIOx = RS_GPIO;
	LCD.RS_PINx  = RS_PIN;

	while(HAL_GetTick() < 50); // according to datasheet of LCD, we have to wait 40-50ms before the initialization
	GPIO_RESET_PIN(LCD.RS_GPIOx, LCD.RS_PINx); // clear RS and EN pin
	GPIO_RESET_PIN(LCD.EN_GPIOx, LCD.EN_PINx);

	LCD_DATA(0x00); // configuration commands
	DELAY_MS(150);
	LCD_CMD(0x03);
	DELAY_MS(5);
	LCD_CMD(0x03);
	DELAY_MS(5);
	LCD_CMD(0x03);
	DELAY_US(150);

	LCD_CMD(0x02);
	LCD_CMD(0x02);
	LCD_CMD(0x08);
	LCD_CMD(0x00);
	LCD_CMD(0x0C);
	LCD_CMD(0x00);
	LCD_CMD(0x06);
	LCD_CMD(0x00);
	LCD_CMD(0x01);
}

/**
 * @brief Sends 4-bit data to the LCD data lines (D4–D7)
 *
 * @param data 4-bit value to send (lower nibble used)
 */
void LCD_DATA(unsigned char data){

	if(data & 1){
		GPIO_SET_PIN(LCD.DATA4_GPIOx,   LCD.DATA4_PINx);
	}
	else{
		GPIO_RESET_PIN(LCD.DATA4_GPIOx, LCD.DATA4_PINx);
	}

	if(data & 2){
		GPIO_SET_PIN(LCD.DATA5_GPIOx,   LCD.DATA5_PINx);
	}
	else{
		GPIO_RESET_PIN(LCD.DATA5_GPIOx, LCD.DATA5_PINx);
	}

	if(data & 4){
		GPIO_SET_PIN(LCD.DATA6_GPIOx,   LCD.DATA6_PINx);
	}
	else{
		GPIO_RESET_PIN(LCD.DATA6_GPIOx, LCD.DATA6_PINx);
	}

	if(data & 8){
		GPIO_SET_PIN(LCD.DATA7_GPIOx,   LCD.DATA7_PINx);
	}
	else{
		GPIO_RESET_PIN(LCD.DATA7_GPIOx, LCD.DATA7_PINx);
	}
}

/**
 * @brief Sends a command to the LCD in command mode
 *
 * Typically used for instructions like clearing the display,
 * setting cursor position, etc
 *
 * @param cmd 4-bit command to send
 */
void LCD_CMD(unsigned char cmd){

	GPIO_RESET_PIN(LCD.RS_GPIOx, LCD.RS_PINx); // sending a gpio pulse for trigging the data commands
	LCD_DATA(cmd);
	GPIO_RESET_PIN(LCD.EN_GPIOx, LCD.EN_PINx);
	DELAY_US(5);
	GPIO_SET_PIN(LCD.EN_GPIOx,   LCD.EN_PINx);
	DELAY_US(5);
	GPIO_RESET_PIN(LCD.EN_GPIOx, LCD.EN_PINx);
	DELAY_US(100);
}

/**
 * @brief Clears the LCD screen and resets cursor position
 */
void LCD_clear(){

	LCD_CMD(0);
	LCD_CMD(1);
	DELAY_MS(2);
}

/**
 * @brief Sets the LCD cursor to a specific row and column
 *
 * @param row Row number (1 or 2)
 * @param column Column number (starting from 1)
 */
void LCD_setCursor(unsigned char row, unsigned char column){

	unsigned char temp, low4, high4;

	if(row == 1){
		temp = 0x80 + column - 1; // according to datasheet of LCD, we determine the row (1 or 2)

	}
	else if(row == 2){
		temp = 0xC0 + column - 1;
	}

	high4 = temp >> 4; // conversion to 4-bit type
	low4 = temp & 0x0F;
	LCD_CMD(high4);
	LCD_CMD(low4);
}

/**
 * @brief Writes a single character to the LCD
 *
 * Sends the character data to the LCD for display at the current cursor position
 *
 * @param data Character to display
 */
void LCD_writeChar(char data){

	char low4, high4;
	low4  = data & 0x0F; // read data with bitwise masking
	high4 = data & 0xF0;

	GPIO_SET_PIN(LCD.RS_GPIOx, LCD.RS_PINx);

	LCD_DATA(high4 >> 4);
	GPIO_RESET_PIN(LCD.EN_GPIOx, LCD.EN_PINx);
	DELAY_US(5);
	GPIO_SET_PIN(LCD.EN_GPIOx, LCD.EN_PINx);
	DELAY_US(5);
	GPIO_RESET_PIN(LCD.EN_GPIOx, LCD.EN_PINx);
	DELAY_US(100);

	LCD_DATA(low4);
	GPIO_RESET_PIN(LCD.EN_GPIOx, LCD.EN_PINx);
	DELAY_US(5);
	GPIO_SET_PIN(LCD.EN_GPIOx, LCD.EN_PINx);
	DELAY_US(5);
	GPIO_RESET_PIN(LCD.EN_GPIOx, LCD.EN_PINx);
	DELAY_US(100);
}

/**
 * @brief Writes a null-terminated string to the LCD
 *
 * Displays the string starting at the current cursor position
 *
 * @param str Pointer to the null-terminated string
 */
void LCD_writeString(char *str){

	int i;

	for(i=0; str[i]!='\0'; i++){
		LCD_writeChar(str[i]);
	}
}

/**
 * @brief Shifts the entire LCD display to the left
 */
void LCD_shiftLeft(){

	LCD_CMD(0x01);
	LCD_CMD(0x08);
}

/**
 * @brief Shifts the entire LCD display to the right
 */
void LCD_shiftRight(){

	LCD_CMD(0x01);
	LCD_CMD(0x0C);
}
