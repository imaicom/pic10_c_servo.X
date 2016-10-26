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

void main(void) {
    
    unsigned char t = 0;
    unsigned char width = 0;
    unsigned char max_width = 0;
    unsigned char data;
    unsigned char i = 40;
    
    OPTION = 0b11000000;
   
    TRISGPIO = 0b1000; // input GP3 / output GP2,GP1    
    ANS0 = 1;   // GP0 = analog
    ANS1 = 0;   // GP1 = digital
    CHS1 = 0; CHS0 = 0; // select ADC Chanel 00
    ADON = 1;   // turn ADC on
  
 
    Delay_ms(500); GP2 = 1; GP1 = 0;
    Delay_ms(500); GP2 = 0; GP1 = 1;
    Delay_ms(500); GP2 = 1; GP1 = 0;
    Delay_ms(500); GP2 = 0; GP1 = 1;
 /*
    Delay_ms(500); GP2 = 1; GP1 = 0;
    Delay_ms(500); GP2 = 0; GP1 = 1;
    Delay_ms(500); GP2 = 1; GP1 = 0;
    Delay_ms(500); GP2 = 0; GP1 = 1;
*/
    t = GP3;
    
    GO = 1; // start conversion

    while (1) {
 //       while (nDONE);  // wait conversion
 
        if(!nDONE) {
            data = ADRES;
            GO = 1; // start conversion
        };
       
        if(GP3 == 1) {
            width++;
        } else {
            if(t != GP3) {
                max_width = width;
            };
            width = 0;
        };
        
        t = GP3;
        
        i++; if(i > 140) i = 40;
        if (i > max_width) {GP1 = 0;}else{GP1 = 1;};

/*            
        if (width > 120) { // MAX 130 ?
            GP1 = 0;
        } else {
            GP1 = 1;
        };

        if (width >  60) { // MIN 50 ?
            GP2 = 0;
        } else {
            GP2 = 1;
        };
 */

 /*
        if(GP3 == 1) GP2 = 0;
        if(GP3 == 0) GP2 = 1;

        if((t != GP3)&&(GP3 == 0)) {
            width++;
        };
        if(width <= 1000) {GP2 = 0; GP1 = 1;}
        if(width > 1000)  {GP2 = 1; GP1 = 0;}
        if(width > 2000)  {width = 0;}
        
        t = GP3;

        if((t != GP3)&&(GP3 == 0)) {
            max_width = width;
            width = 0;
        };

        if(GP3 == 1) width++;

        t = GP3;

        if(max_width > 50){
            GP2 = 1; GP1 = 0;
        } else {
            GP2 = 0; GP1 = 1;
        }
*/        
//        if(GP3 == 1) GP2 = 1;
//        if(GP3 == 0) GP2 = 0;
        
        /*
        if(ADRES > 100){
            GP2 = 1; GP1 = 0;
        } else {
            GP2 = 0; GP1 = 1;
        }
        */
    }
}
