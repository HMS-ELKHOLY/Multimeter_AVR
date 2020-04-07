#include "lcd.h"

#include "ADC.h"
#define VOLT_AMP PB0
#define DC_AC PB1
char *sig_msg[2] = { "DC", "AC" };
char *type_msg[2] = { "VOLT", "AMP" };
volatile char *sig;
volatile char *type;
volatile float value = 0;
volatile float RMS = 0;
int ac_counter=0;
float root(float in ){
	float result=0;
	while(result<in/2){
		result+=.1;
		if (result*result>=in)
			break;
	}
	return result;
}
void timer1_init_ctc(unsigned short top) {
	cli();/**stop interrupt first**/
	TCNT1 = 0;//count from zero
	OCR1A = top;//use top value
	TCCR1A = 0;
	SET_BIT(TCCR1A, FOC1A);/*non -pwm*/
	SET_BIT(TCCR1B, WGM12);/*compare mode*/
	/*64 pre-scaler */
	SET_BIT(TCCR1B, CS11);
	SET_BIT(TCCR1B, CS10);
	/*enable interrupt on compare match*/
	SET_BIT(TIMSK, OCIE1A);/**enable interrupt at last**/
	DDRA=0xff;

	sei();
}
ISR (TIMER1_COMPA_vect) {
	cli();
	ac_counter++;
	volt_mes();
	RMS+=value*value;
	if(ac_counter>1000){
		value=root(RMS/1000);
	}
	}

void volt_mes() {
	for (int counter = 0; counter < 3; counter++) {
		PORTA = (0x2 << 2) >> counter;

		value = ((float) ADC_readChanel(0, POLLING) / (float) 1023.0
				* (float) 5.0);

		if (counter == 0) {
			value = value * 4 - 0.57 * 4; //offset from op amp
			if (value > 10)
				break;
		}
		if (counter == 1) {
			value = value * 2 - 0.26 * 2; //offset from op amp
			if (value > 5)
				break;
		}

	}

}

int main() {
	DDRB &= ~(0x7);
	PORTB |= (0x7);
	DDRA = 0xE;
	PORTA = 0x2 << 2;
	LCD_init();
	LCD_sendCommand(CURSOR_ON);

	ADC_init(F_CPU__by__16_);

	//timer1_init_ctc(155); doesn't work i dont know why
	while (1) {
		volt_mes();
		if (BIT_IS_SET(PINB, DC_AC)) {
			_delay_ms(30);
			if (BIT_IS_SET(PINB, DC_AC)) {
				sig = sig_msg[0];


			}

		} else{
			sig = sig_msg[1];
			RMS=0;
			for(int i =0 ; i< 3000 ;i++){
				volt_mes();
				RMS+=value*value;
				_delay_us(100);
			}
			value=root(RMS/3000);
		}
		if (BIT_IS_CLEAR(PINB, VOLT_AMP)) {
			_delay_ms(30);
			if (BIT_IS_CLEAR(PINB, VOLT_AMP)) {
				value = value / 100.0;
				type = type_msg[1];
			}
		} else {
			type = type_msg[0];
		}

		LCD_sendCommand(CLEAR_COMMAND);
		LCD_gotoRowCol(0, 0);
		LCD_displayString(sig);
		LCD_floatToString((float) value, 1);
		LCD_displayString(type);
		//TOGGLE_BIT(PORTD,0);

		_delay_ms(20);

	}
}

