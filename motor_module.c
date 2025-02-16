/*
 * motor_module.c
 *
 *  Created on: 18.06.2024
 *      Author: LennartStuecker
 */

#include <motor_module.h>

void configTimer2A() {

    // configure Timer 0
    SYSCTL_RCGCTIMER_R |= (1 << 2); // TIMER2 = 1
    while (!(SYSCTL_PRTIMER_R & (1 << 2))); // wait for timer 2 clock
    TIMER2_CTL_R &= ~TIMER_CTL_TAEN;   // disable Timer 2 for config
    TIMER2_CFG_R  = TIMER_CFG_32_BIT_TIMER;  // 32-bit mode
    TIMER2_TAMR_R |= 0x0001;             // one shot, count down, match disable
    TIMER2_TAILR_R = 0xFFFFFFFF;   // ILR = 4294967295 (2^32-1) (count interval)
    TIMER2_CTL_R |= TIMER_CTL_TAEN;       // start Timer2

}

// for Direcion
void configPortC(void) {
    SYSCTL_RCGCGPIO_R |= (1 << 2);              // Enable clock for GPIO Port C
    while(!(SYSCTL_PRGPIO_R & (1 << 2)));
    GPIO_PORTC_AHB_DEN_R |= 0x10;           // Enable digital function for PC(4)
    GPIO_PORTC_AHB_DIR_R |= 0x10;
    GPIO_PORTC_AHB_IS_R &= ~0x10;           // Make PC(4) edge-sensitive
    GPIO_PORTC_AHB_IBE_R |= 0x10;          // Trigger on both edges on PC(4)
    //GPIO_PORTC_AHB_IEV_R |= 0x10;           // Trigger on rising edge
    GPIO_PORTC_AHB_ICR_R = 0x10;            // Clear any prior interrupt
    GPIO_PORTC_AHB_IM_R |= 0x10;            // Enable interrupt for PC4

    NVIC_EN0_R = (1 << 2);                 // Enable interrupt in NVIC (interrupt number 2)
}


void configPortL(){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10;  // clock port L
    while (!(SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R10)); // wait for port L clock
    GPIO_PORTL_DEN_R |= 0x30;  //digital Enabling Pl4 and Pl5
    GPIO_PORTL_DIR_R |= 0x00;  // setting Pl4 and PL5 to input

    GPIO_PORTL_IS_R &= ~0x10;  // edge-sensitive
    GPIO_PORTL_IBE_R &= ~0x10;  // NOT both edges
    GPIO_PORTL_IEV_R |= 0x10;  // rising-edge
    GPIO_PORTL_ICR_R |= 0x10;  // clear interrupt portL(5:4)
    GPIO_PORTL_IM_R |= 0x10;  // unmask portL(5:4)
    NVIC_EN1_R = (1 << 21);    // Enable PortL Interrupt
}

/* for speed
void configPortK(void) {
        SYSCTL_RCGCGPIO_R |= (1 << 9);              // Enable clock for GPIO Port K
        while((SYSCTL_PRGPIO_R & (1 << 9) ) == 0);
        GPIO_PORTK_DEN_R |= 0x10;               // Enable digital function for PK4
        GPIO_PORTK_IS_R &= ~0x10;               // Make PK4 edge-sensitive
        GPIO_PORTK_IBE_R &= ~0x10;              // Trigger on one edge
        GPIO_PORTK_IEV_R |= 0x10;               // Trigger on rising edge
        GPIO_PORTK_ICR_R = 0x10;                // Clear any prior interrupt
        GPIO_PORTK_IM_R |= 0x10;                // Enable interrupt for PK4
        NVIC_EN1_R |= (1 << ( 52 - 32 ));         // Enable interrupt for Port K in NVIC (interrupt number 72)
}*/
