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
 * @brief Writes the logic state of the specified GPIO pin.
 * @param GPIOx Pointer to GPIO port
 * @param GPIO_Pin Pin number to be toggled
 *  * @param logicState logic state (high or low)
 */
void GPIO_WRITE_PIN(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t logicState){
	if(logicState == 1){
		GPIO_SET_PIN(GPIOx, GPIO_Pin);
	}
	else{
		GPIO_RESET_PIN(GPIOx, GPIO_Pin);
	}
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

/**
 * @brief  Configures the specified GPIO pin(s) as Output (Push-Pull).
 *         Internal pull-up/pull-down resistors are disabled (floating).
 *         When multiple pin masks are provided, each pin will be configured in turn.
 * @param  GPIOx     Pointer to the target GPIO port (e.g., GPIOA, GPIOB).
 * @param  GPIO_Pin  Pin mask (e.g., GPIO_PIN_5 or GPIO_PIN_5 | GPIO_PIN_6).
 *                   Use STM32 HAL-defined pin macros.
 * @note   The corresponding port clock (RCC) must be enabled before calling this function.
 */
void GPIO_INIT_PIN_OUTPUT(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){

    while (GPIO_Pin){
        uint32_t pos = __builtin_ctz(GPIO_Pin);
        uint32_t two = pos * 2U;

        GPIOx->MODER   = (GPIOx->MODER   & ~(0x3U << two)) | (0x1U << two);
        GPIOx->OTYPER &= ~(1U << pos);
        GPIOx->OSPEEDR = (GPIOx->OSPEEDR & ~(0x3U << two)) | (0x2U << two);
        GPIOx->PUPDR  &= ~(0x3U << two);
        GPIO_Pin &= (GPIO_Pin - 1U);
    }
}

/**
 * @brief  Configures the specified GPIO pin as Input (Floating).
 *         Internal pull-up/pull-down resistors are disabled.
 * @param  GPIOx     Pointer to the target GPIO port (e.g., GPIOA, GPIOB).
 * @param  GPIO_Pin  Single pin mask (e.g., GPIO_PIN_5).
 * @note   This version supports only one pin at a time. For multiple pins,
 *         adapt the function to loop over all set bits in the mask.
 *         The corresponding port clock (RCC) must be enabled before calling.
 */
void GPIO_INIT_PIN_INPUT(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){

    uint32_t pos = __builtin_ctz(GPIO_Pin);
    uint32_t two = pos * 2U;
    GPIOx->MODER &= ~(0x3U << two);
    GPIOx->PUPDR &= ~(0x3U << two);
}
