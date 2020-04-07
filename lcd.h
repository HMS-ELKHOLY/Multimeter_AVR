/*
 * lcd.h
 *
 *  Created on: Sep 7, 2019
 *      Author: modern
 */

#ifndef LCD_H_
#define LCD_H_
#include "macro_config.h"
#define NO 0
#define YES 1

#define EIGHT_BIT_SELECT YES

#define FOUR_BIT_PINS  NO
#define RS PD4
#define RW PD6
#define E  PD7
#define CONTROL_PORT PORTD
#define CONTROL_REG  DDRD
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_OFF_BLINK 0x0D
#define CURSOR_ON 0x0E
#define CURSOR_ON_BLINK 0x0F
#define DISP_OFF 0x07

#define SET_CURSOR_LOCATION 0x80
#define CLEAR_COMMAND 0x01
#define TWO_LINE_4_BIT_MODE 0x28
#define ONE_LINE_4_BIT_MODE 0x20
#define RETURN_HOME 0x2

#define DATA_PORT PORTC
#define DATA_REG DDRC
void LCD_sendCommand(unit8 command);
void LCD_sendChar(unit8 ch);

void LCD_init(void);


void LCD_displayString(const int8 * str);
void LCD_gotoRowCol(unit8 row ,unit8 col);

void LCD_displayStringRowCol(const int8 * str,unit8 row,unit8 col);

void LCD_intToString(unsigned  short data);
void LCD_floatToString(float data,short perc);
void LCD_charGEN(unsigned char data [8],unit8 posInGCRAM );
void invChars(unsigned char data[8]);

#endif /* LCD_H_ */
