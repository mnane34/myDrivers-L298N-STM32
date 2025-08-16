/**
 * @file    TIME.h
 * @brief   Delay Functions (uS and mS) for STM32
 * @author  Mertcan NANE
 * @date    2025-08-09
 * @version 1.0
 *
 * @contact
 *  https://github.com/mnane34
 *  https://www.youtube.com/@mnane34
 *  https://www.linkedin.com/in/mertcan-nane/
 */

#ifndef INC_TIME_H_
#define INC_TIME_H_

/* Header Directives Definitions */
#include "main.h"

/* SysTick Timer Delay Macros */
#define SYSTICK_LOAD 								(SystemCoreClock / 1000000U)
#define SYSTICK_DELAY_CALIB 						(SYSTICK_LOAD >> 1)

#define DELAY_US(us)								do{																\
													   uint32_t start = SysTick->VAL;								\
													   uint32_t ticks = (us * SYSTICK_LOAD) - SYSTICK_DELAY_CALIB;	\
													   while((start - SysTick->VAL) < ticks);						\
													   }while(0)

#define DELAY_MS(ms)								do{																\
														for(uint32_t i=0; i<ms; ++i){ DELAY_US(1000); } 			\
													   }while(0)

#endif
