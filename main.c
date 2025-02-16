#include "inc/tm4c1294ncpdt.h"
#include <stdio.h>
#include <stdint.h>

#include "lcd_module.h"
#include "motor_module.h"
#include "int_HandlerMotorModule.h"
#include "int_HandlerLcdModule.h"

// handled by the NVIC

volatile unsigned char* direction = "x";
volatile unsigned short speed = 0;


//volatile unsigned int remainingTimeEvent;

int main(void)
{

    configTimer2A(); // Speed calc timer
    configPortC(); // intHandler for direction
    configPortD(); // for UART
    configPortL(); // for motor S(1,2)
    //configPortK(); //intHandler for speed

    configTimer1A(); //LCD writing timer
    configUART2(); //UART2 for serial comm


    while(1)
    {
        if((TIMER1_RIS_R & (1<<0)) == 0x01){

            if ((GPIO_PORTL_DATA_R & 0x01) == 0x01)
            {
                GPIO_PORTL_DATA_R &= ~0x01;
            }
            else
            {
                GPIO_PORTL_DATA_R |= 0x01;
            }
            TIMER1_ICR_R |= (1<<0);
            UART2_SendCommand(CLEAR_DISPLAY, 0x01);

            //char str[10];
            //char buffer1[20] = "";
            char buffer2[20] = "";
            sprintf(buffer2, "%d", speed);
            writeToLCD("Team Name: Got iT! ", " " , (char*) direction , buffer2);
           }

    }
	return 0;
}
