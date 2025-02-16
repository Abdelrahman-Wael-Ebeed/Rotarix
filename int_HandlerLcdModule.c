/*
 * int_HandlerLcdModule.c
 *
 *  Created on: 18.06.2024
 *      Author: LennartStuecker
 */

#include <int_HandlerLcdModule.h>

// direction detection
void IntPortCHandler() // IRQ number 2, vector number 18
{
    GPIO_PORTC_AHB_ICR_R = 0x10;
    if((GPIO_PORTC_AHB_DATA_R & 0x10) == 0x10)
    {
        direction = "C.W" ;   //C.W
    }
    else if((GPIO_PORTC_AHB_DATA_R & 0x00) == 0x00)
    {
        direction = "A.C.W" ;  // A.C.W
    }
}

/*
 *  speed detection
void IntPortKHandler(void) // IRQ number 72, vector number 88
{
    GPIO_PORTK_ICR_R = 0x10;  // Clear interrupt flag for PK4

       if((GPIO_PORTK_DATA_R & 0x10) == 0x10)
       {
           if(direction == 1)
           {
               writeToLCD("Team Name", " ", "CLOCKWISE", (char*)speed);
           }
           else
           {
               writeToLCD("Team Name", " ", "ANTICLOCKWISE", (char*)speed);
           }
          GPIO_PORTK_DATA_R = 0x00;
       }
}
*/
