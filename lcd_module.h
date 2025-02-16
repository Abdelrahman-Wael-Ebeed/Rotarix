/*
 * lcd_module.h
 *
 *  Created on: 18.06.2024
 *      Author: LennartStuecker
 */

#ifndef LCD_MODULE_H_
#define LCD_MODULE_H_

#include "inc/tm4c1294ncpdt.h"
#include <stdio.h>
#include <stdint.h>


// LCD special commands
#define CLEAR_DISPLAY 0xFE          // 0x01
#define CARRIAGE_RETURN 0x0D        //to set the cursor to the start of the new line
#define LINE_FEED 0x0A              //the string to print



void UART2_SendString(char *str);
void UART2_SendChar(char data);
void UART2_SendCommand(int cmd, int value);

void configUART2();
void configPortD();
void configTimer1A();

void writeToLCD(char* row1, char* row2, char* row3, char* row4);
void timerWait(unsigned short delay);

#endif /* LCD_MODULE_H_ */
