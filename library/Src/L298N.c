/* Header Directives Definition */
#include "L298N.h"

/* Structure Object Definition */
L298N_TypeDef_t MOTOR;
L298N_Direction_t motorDirection = NO_DIRECTION;

/**
 * @brief  Initialize L298N driver by starting PWM on the ENA pin.
 * @note   Expects TIM2 and GPIOs to be already configured for PWM/AF.
 * @pre    MX_TIM2_Init() has been called; ENA is wired to TIM2 CH1.
 */
void L298N_init(TIM_HandleTypeDef * hTIMx){
	MOTOR.htim = hTIMx;
	HAL_TIM_PWM_Start(MOTOR.htim, TIM_CHANNEL_1);
}

/**
 * @brief  Set motor rotation direction via IN1/IN2 lines.
 * @param  direction  Motor direction: LEFT or RIGHT.
 * @note   Uses PB13 (IN1) and PB14 (IN2). Adjust pins if your hardware differs.
 * @note   Adds a tiny delay between toggles to avoid shoot-through.
 */
void L298N_setDirection(L298N_Direction_t direction){
	if(direction == LEFT){
		GPIO_SET_PIN(GPIOB, GPIO_PIN_14);
		DELAY_US(1);
		GPIO_RESET_PIN(GPIOB, GPIO_PIN_13);
		DELAY_US(1);
	}
	else if (direction == RIGHT){
		GPIO_SET_PIN(GPIOB, GPIO_PIN_13);
		DELAY_US(1);
		GPIO_RESET_PIN(GPIOB, GPIO_PIN_14);
		DELAY_US(1);
	}
}

/**
 * @brief  Set motor speed by applying PWM to ENA.
 * @param TIMx pointer to channel number
 * @param  xChannel  TIM channel used for ENA (e.g., TIM_CHANNEL_1).
 * @param  xDuty     Duty in percent [0..100].
 * @note   Duty is scaled as (xDuty * 20) → assumes ARR ≈ 1999 (i.e., 2000 ticks).
 *         If your ARR is different, adjust the scale accordingly.
 * @warning No clamping is performed here; pass 0..100 to avoid CCR > ARR.
 */
void L298N_setPWM(TIM_HandleTypeDef * hTIMx, uint32_t xChannel, uint16_t xDuty){
	MOTOR.htim = hTIMx;
	MOTOR.channel = xChannel;
	MOTOR.duty =  xDuty;
	__HAL_TIM_SET_COMPARE(MOTOR.htim, MOTOR.channel, MOTOR.duty * 20);
}

