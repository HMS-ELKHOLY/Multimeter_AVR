/*
 * lcd.c
 *
 *  Created on: Sep 7, 2019
 *      Author: modern
 */

#include "lcd.h"
#include "stdlib.h"
#if (EIGHT_BIT_SELECT==1)
void LCD_init(void) {
	DATA_REG = 0xff;
	DATA_PORT = 0;
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_sendCommand(unit8 command) {


	SET_BIT(CONTROL_REG, RS);
	SET_BIT(CONTROL_REG, E);
	SET_BIT(CONTROL_REG, RW);
	CLEAR_BIT(CONTROL_PORT, RS);
	CLEAR_BIT(CONTROL_PORT, RW);
	CLEAR_BIT(CONTROL_PORT, E);
	_delay_ms(2);
	SET_BIT(CONTROL_PORT, E);
	_delay_ms(2);
	DATA_PORT = command;
	_delay_ms(2);
	CLEAR_BIT(CONTROL_PORT, E);
	_delay_ms(1);

}
void LCD_sendChar(unit8 ch) {


	SET_BIT(CONTROL_REG, RS);
	SET_BIT(CONTROL_REG, E);
	SET_BIT(CONTROL_REG, RW);
	SET_BIT(CONTROL_PORT, RS);
	CLEAR_BIT(CONTROL_PORT, RW);
	CLEAR_BIT(CONTROL_PORT, E);
	_delay_ms(2);
	SET_BIT(CONTROL_PORT, E);
	_delay_ms(2);
	DATA_PORT = ch;
	_delay_ms(2);
	CLEAR_BIT(CONTROL_PORT, E);
	_delay_ms(2);

}

#else

void LCD_init(void) {
#if (FOUR_BIT_PINS==YES)
	DATA_REG = (DATA_REG | 0xf0);
	DATA_PORT = (DATA_REG & 0x0f);
#else

	DATA_REG = (DATA_REG | 0x0f);
	DATA_PORT = (DATA_REG & 0xf0);
#endif
	//LCD_sendCommand(ONE_LINE_4_BIT_MODE);

	SET_BIT(CONTROL_REG, RS);
	SET_BIT(CONTROL_REG, E);
	SET_BIT(CONTROL_REG, RW);

	CLEAR_BIT(CONTROL_PORT, RS);
	CLEAR_BIT(CONTROL_PORT, RW);

	CLEAR_BIT(CONTROL_PORT, E);
	SET_BIT(CONTROL_PORT, E);
	_delay_ms(2);
	DATA_PORT = (2 << 4);
	CLEAR_BIT(CONTROL_PORT, E);
	_delay_ms(2);

	LCD_sendCommand(TWO_LINE_4_BIT_MODE);
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_sendCommand(unit8 command) {

	DATA_REG = (DATA_REG | 0xf0);
	DATA_PORT = (DATA_REG & 0x00);
	SET_BIT(CONTROL_REG, RS);
	SET_BIT(CONTROL_REG, E);
	SET_BIT(CONTROL_REG, RW);
	CLEAR_BIT(CONTROL_PORT, RS);
	CLEAR_BIT(CONTROL_PORT, RW);

	CLEAR_BIT(CONTROL_PORT, E);
	_delay_ms(2);
	SET_BIT(CONTROL_PORT, E);
	_delay_ms(2);
	DATA_PORT = (command & 0xf0);
	CLEAR_BIT(CONTROL_PORT, E);
	_delay_ms(2);
	SET_BIT(CONTROL_PORT, E);
	_delay_ms(2);
	DATA_PORT = (command << 4);
	CLEAR_BIT(CONTROL_PORT, E);
	_delay_ms(2);

}
void LCD_sendChar(unit8 ch) {

		DATA_REG = (DATA_REG | 0xf0);
		DATA_PORT = (DATA_REG & 0x00);
		SET_BIT(CONTROL_REG, RS);
		SET_BIT(CONTROL_REG, E);
		SET_BIT(CONTROL_REG, RW);
		SET_BIT(CONTROL_PORT, RS);
		CLEAR_BIT(CONTROL_PORT, RW);

		CLEAR_BIT(CONTROL_PORT, E);
		_delay_ms(2);
		SET_BIT(CONTROL_PORT, E);
		_delay_ms(2);
		DATA_PORT = (ch & 0xf0);
		CLEAR_BIT(CONTROL_PORT, E);
		_delay_ms(2);
		SET_BIT(CONTROL_PORT, E);
		_delay_ms(2);
		DATA_PORT = (ch << 4);
		CLEAR_BIT(CONTROL_PORT, E);
		_delay_ms(2);

}

#endif
void LCD_displayString(const int8 *str) {
	unit8 i = 0;
	while (str[i] != '\0') {
		LCD_sendChar(str[i]);
		//_delay_ms(2);
		i++;
	}
	//_delay_ms(2);
}

void LCD_gotoRowCol(unit8 row, unit8 col) {
	unit8 add = 0;
	switch (row) {
	case 0:
		add = col;
		break;
	case 1:
		add = col + 0x40;
		break;
	case 2:
		add = col + 0x10;
		break;
	case 3:
		add = col + 0x50;
		break;
	}
	LCD_sendCommand(add | 0x80);
}

void LCD_displayStringRowCol(const int8 *str, unit8 row, unit8 col) {
	LCD_gotoRowCol(row, col);
	LCD_displayString(str);
}

void LCD_intToString(unsigned short data) {
	int8 buff[16];
	itoa(data, buff, 10);
	LCD_displayString(buff);
}
void LCD_floatToString(float data, short perc) {
	int8 buff[16];
	//long place=10;
	//short counter=0;

	//	perc;
	float fraction = (float) ((float) data - (int8) data);
	LCD_intToString((short) (data));
	LCD_displayString(".");
	utoa((int16) (fraction*10000.0), buff, 10);
	LCD_displayString(buff);

}
void LCD_charGEN(unsigned char data[8], unit8 posInGCRAM) {
	if (posInGCRAM < 8) {
	   unit8 i = 0;
		LCD_sendCommand(0x40 + posInGCRAM * 8);
		for (; i < 8; i++) {
			LCD_sendChar(data[i]);
		}
	}
}
void invChars(unsigned char data[8]) {
   unit8 i = 0;
	for ( ;i < 8; i++) {
		(data[i] = ~data[i]);
	}
}
