/*
 * ADC.h
 *
 *  Created on: Sep 13, 2019
 *      Author: modern
 */

#ifndef ADC_H_
#define ADC_H_
#include "macro_config.h"
#include "types.h"
enum ADC_workingType {
	INTERRUPT, POLLING
};
enum ADC_prescalerVALUE {
	F_CPU__by__2,
	F_CPU__by__2_,
	F_CPU__by__4,
	F_CPU__by__8_,
	F_CPU__by__16_,
	F_CPU__by__32_,
	F_CPU__by__64_,
	F_CPU__by__128_
};

typedef enum ADC_workingType ADC_WT;
typedef enum ADC_prescalerVALUE ADC_P;
typedef struct s {
	ADC_WT WT;
	ADC_P P;
} S;
unint16 getADC();

volatile void ADC_setCALL_BACK(void (*g_ptr)(void));

void ADC_init(enum ADC_prescalerVALUE prescaler);
unint16 ADC_readChanel(unit8 ch_num, enum ADC_workingType type);
#endif /* ADC_H_ */
