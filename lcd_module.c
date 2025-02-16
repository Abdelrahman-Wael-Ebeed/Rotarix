#include <lcd_module.h>


// Configuring PortD
void configPortD(void) {
    SYSCTL_RCGCGPIO_R |= (1 << 3);  // clock port D
    while (!(SYSCTL_PRGPIO_R & (1 << 3))); // wait for port D clock
    GPIO_PORTD_AHB_DEN_R |= 0x20;           // Enable PD(5) for TX
    GPIO_PORTD_AHB_AFSEL_R |= 0x20;
    GPIO_PORTD_AHB_PCTL_R |= 0x00100000;
}

// Configure Timer 1A to avoid too many messages when writing data to the LCD Display
//ToDO Revisit the pre-scalre part, Goal: achieve time-out of 1 Sec
void configTimer1A(void) {
    // configure Timer 0
    SYSCTL_RCGCTIMER_R |= (1 << 1);         // TIMER1 = 1
    while (!(SYSCTL_PRTIMER_R & (1 << 1))); // wait for timer 1 clock
    TIMER1_CTL_R &= ~TIMER_CTL_TAEN;                  // disable Timer 1 for config
    TIMER1_CFG_R  = TIMER_CFG_32_BIT_TIMER;                   // 32-bit mode
    TIMER1_TAMR_R |= 0x02;                  // periodic, count down, match disable
    TIMER1_TAILR_R = 16000000;
    //TIMER1_TAPR_R = 267-1;                  // Pre-scaler of 267 to achieve time-out of 1 sec
    TIMER1_CTL_R |= TIMER_CTL_TAEN;                   // start Timer2
}

// Configuring UART2
void configUART2() {
    SYSCTL_RCGCUART_R |= 0x4;               // Switch on clock for UART2
    while(!(SYSCTL_PRUART_R & 0x4));
    UART2_CTL_R &= ~0x0001;                 // Disable UART2 for configuration
    UART2_IBRD_R = 104;                     // set DIVINT of BRD (bit-rate 9600 bit/s)
    UART2_FBRD_R = 11;                      // set DIVFRAC of BRD
    UART2_LCRH_R = 0x00000060;              // serial format 8N1
    UART2_CTL_R = 0x101;                    // Enable UART2 (EN, TX)
}


void UART2_SendString(char *str) {
    while(*str != '\0') {                  // Continue until the end of the string
        UART2_SendChar(*str);               // Send each character
          str++;
      }
}

void UART2_SendChar(char data) {
    while(UART2_FR_R & 0x20);            // Wait until TXFF is 0 (Transmit FIFO not full)
    UART2_DR_R = data;
}

void UART2_SendCommand(int cmd, int value) {
    UART2_SendChar(cmd);                // Command must be transmitted first followed by the desired value
    UART2_SendChar(value);
}

// Print the rows to the LCD
void writeToLCD(char* row1, char* row2, char* row3, char* row4) {
   //timerWait(50000);
   UART2_SendString(row1);                   // Send the first row string
   UART2_SendChar(CARRIAGE_RETURN);
   UART2_SendString(row2);                   // Send the second row string
   UART2_SendChar(CARRIAGE_RETURN);
   UART2_SendString(row3);                   // Send the second row string
   UART2_SendChar(CARRIAGE_RETURN);
   UART2_SendString(row4);                   // Send the second row string
   UART2_SendChar(CARRIAGE_RETURN);
}

