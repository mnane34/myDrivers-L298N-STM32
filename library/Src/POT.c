/* Header Directives Definition */
#include "POT.h"

/* Structure Object Definition */
POT_TypeDef_t POT;

/**
 * @brief  Read the potentiometer via ADC1 using polling.
 * @param ADCx pointer to channel number
 * @return Latest ADC raw value (e.g., 0..4095 for 12-bit).
 */
uint32_t POT_read(ADC_HandleTypeDef *hADCx){

	POT.hadc = hADCx;

	HAL_ADC_Start(POT.hadc);
	DELAY_US(1);

	if(HAL_ADC_PollForConversion(POT.hadc, 100) == HAL_OK){
		POT.tempValue = HAL_ADC_GetValue(POT.hadc);
	}
	HAL_ADC_Stop(POT.hadc);
	DELAY_US(1);

	return POT.tempValue;
}

/**
 * @brief Maps a value from one range to another.
 * @param value   The input value to be mapped.
 * @param inMin   The lower bound of the input range.
 * @param inMax   The upper bound of the input range.
 * @param outMin  The lower bound of the output range.
 * @param outMax  The upper bound of the output range.
 * @return        The mapped value in the new range.
 */
uint32_t POT_map(uint32_t value, long inMin, long inMax, long outMin, long outMax){

	POT.adcValue = (((value - inMin) * (outMax - outMin)) / (inMax - inMin)) + outMin;

	return POT.adcValue;
}
