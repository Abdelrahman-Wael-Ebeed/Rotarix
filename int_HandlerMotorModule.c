/*
 * int_HandlerMotorModule.c
 *
 *  Created on: 18.06.2024
 *      Author: LennartStuecker
 */
#include <int_HandlerMotorModule.h>


void IntPortLHandler(void)
{
    TIMER2_CTL_R &= ~TIMER_CTL_TAEN;   // disable Timer 2
    uint32_t ticks = (TIMER_TAR_M - TIMER2_TAR_R);
    float cycleTime = (0xFFFFFFFF - TIMER2_TAR_R) / 16000000.0 ; //cycleTime in seconds
    TIMER2_TAILR_R = TIMER_TAR_M;
    TIMER2_CTL_R |= TIMER_CTL_TAEN;   // disable Timer 2

    GPIO_PORTL_ICR_R |= 0x010; // Clear interrupt source

    if((GPIO_PORTL_DATA_R & 0x10) == GPIO_PORTL_DATA_R) {
        //direction = CLOCKWISE;
        GPIO_PORTC_AHB_DATA_R |= 0x10;  // Rising edge on PC(4) to display C.W
        // interrupt... writes C.w
    }
    else
    {
        //direction = ANTICLOCKWISE;
        GPIO_PORTC_AHB_DATA_R &= ~0x10;  // Falling edge on PC(4) to display A.C.W
        // interrupt.. writes A.C.w
    }


    calculateSpeed(cycleTime);

}

void calculateSpeed(float cycleTime)
{
    float r = 0.0101; // measured motor radius is 1.2cm
    float circ = 2 * M_PI * r; // motor circumference in m
    float dummy = (circ / cycleTime) * 3.6 *ENCODERFACTOR;
    speed = (circ / cycleTime) * 3.6 *ENCODERFACTOR; // motor speed in km/h
}
