/*
 * ADC.c
 *
 *  Created on: Sep 13, 2019
 *      Author: modern
 */

#include "ADC.h"
#include "lcd.h"
#include <stdlib.h>
volatile short val = 0;

static volatile void (*g_FUNC_pointer)(void) =NULL;

ISR(ADC_vect) {
//	val = ADC;
	CLEAR_BIT(SREG,7);
	if (g_FUNC_pointer != NULL )
		g_FUNC_pointer();
}
void ADC_init(enum ADC_prescalerVALUE prescaler) {
	ADMUX = 0;
	ADCSRA = 0;
	SET_BIT(ADCSRA, ADEN);
	ADCSRA |= prescaler;
}

unint16 ADC_readChanel(unit8 ch_num, enum ADC_workingType type) {
	CLEAR_BIT(DDRD,ch_num);
	ADMUX = (ADMUX & 0x0E) | (ch_num & 0x07);
	SET_BIT(ADCSRA, ADSC);
	if (type == POLLING) {
		while (!(ADCSRA & (1 << ADIF)))
			;
		SET_BIT(ADCSRA, ADIF);
		CLEAR_BIT(ADCSRA, ADIE);
		return ADC;
	} else {

		SET_BIT(ADCSRA, ADIE);
		SET_BIT(SREG, 7);
		return 0xff;
	}

}
unint16 getADC(){
	return ADC;
}
void ADC_setCALL_BACK(volatile void (*g_ptr)(void)) {
	cli();
	g_FUNC_pointer = g_ptr;
	sei();
}

