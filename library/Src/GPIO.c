/* Header Directives Definition */
#include "GPIO.h"

/**
 * @brief Sets the specified GPIO pin to HIGH state.
 * @param GPIOx Pointer to GPIO port (e.g., GPIOA, GPIOB)
 * @param GPIO_Pin Pin number to be set (e.g., GPIO_PIN_5)
 */
void GPIO_SET_PIN(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	  assert_param(IS_GPIO_PIN(GPIO_Pin));
	  assert_param(IS_GPIO_PIN_ACTION(HIGH));
	  DELAY_US(1);
	  GPIOx->BSRR = GPIO_Pin;
}

/**
 * @brief Resets the specified GPIO pin to LOW state.
 * @param GPIOx Pointer to GPIO port
 * @param GPIO_Pin Pin number to be reset
 */
void GPIO_RESET_PIN(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	  assert_param(IS_GPIO_PIN(GPIO_Pin));
	  assert_param(IS_GPIO_PIN_ACTION(LOW));
	  DELAY_US(1);
	  GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
}

/**
 * @brief Toggles the state of the specified GPIO pin.
 * @param GPIOx Pointer to GPIO port
 * @param GPIO_Pin Pin number to be toggled
 */
void GPIO_TOGGLE_PIN(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){

	uint32_t currentState;
	assert_param(IS_GPIO_PIN(GPIO_Pin));
	currentState = GPIOx->ODR;
	DELAY_US(1);
	GPIOx->BSRR = ((currentState & GPIO_Pin) << 16U) | (~currentState & GPIO_Pin);
}

/**
 * @brief Reads the state of the specified GPIO pin.
 * @param GPIOx Pointer to GPIO port
 * @param GPIO_Pin Pin number to be read
 * @return HIGH or LOW (GPIO_PinState)
 */
GPIO_pinState_t GPIO_READ_PIN(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){

	GPIO_pinState_t bitStatus;
	assert_param(IS_GPIO_PIN(GPIO_Pin));

	if((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET){
		bitStatus = HIGH;
	}
	else{
		bitStatus = LOW;
	}
	return bitStatus;
}
