#include <xc.h>         /* XC8 General Include File */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <pic.h>

#pragma config IOSCFS = 8MHZ    // Internal Oscillator Frequency Select bit (8 MHz)
#pragma config MCPU = OFF       // Master Clear Pull-up Enable bit (Pull-up disabled)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config CP = OFF         // Code protection bit (Code protection off)
#pragma config MCLRE = OFF      // GP3/MCLR Pin Function Select bit (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)

#define MHz 000000
#define _XTAL_FREQ 8MHz

static void Delay_ms(unsigned int DELAY_CNT) {
    for (unsigned int i = 0; i < DELAY_CNT; i++) {
        __delay_ms(1);
    }
}

static int abs(int t) {
    if(t < 0 ) return -t;
    if(t >= 0) return t;
}

void main(void) {
    
    int width = 0;
    int max_width = 0;
    
    OPTION = 0b11000000;
   
    TRISGPIO = 0b1000; // input GP3 / output GP2,GP1    
    ANS0 = 1;   // GP0 = analog
    ANS1 = 0;   // GP1 = digital
    CHS1 = 0; CHS0 = 0; // select ADC Chanel 00
    ADON = 1;   // turn ADC on
  
    GP2 = 0; GP1 = 0;
    Delay_ms(1000);
     
    while(1) {
        
        if((width > 0)&&(GP3 == 0)) {
            GP2 = 1; GP1 = 1; // Lock
            max_width = width - 110;
            width = 0;
            GO = 1; // start conversion
            while(nDONE);  // wait conversion
        };

        if((width == 0)&&(GP3 == 1)) {
            while(GP3) width++;
        };
                   
        if((35 <= max_width)&&(max_width < 240)) {
            
            if(abs(ADRES - max_width) > 15) {
                
                if(ADRES > max_width) {
                    GP2 = 1; GP1 = 0;
                } else {
                    GP2 = 0; GP1 = 1;
                };
                
            } else {GP2 = 1; GP1 = 1;}; // lock // if(abs(ADRES - max_width) > 15)
            
         } else {GP2 = 0; GP1 = 0;}; // free // if((35 <= max_width)&&(max_width < 240))
        
    };  //  while(1)
}
