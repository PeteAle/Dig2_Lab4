/*
 * File:   lab4_v1.c
 * Author: Peter
 *
 * Created on February 14, 2020, 12:00 PM
 */


#include <xc.h>
#include "lib_adc.h"
#include "lib_osccon.h"

void main(void) {
    return;
}

void setup(void){
    TRISB = 0x00;
    ANSELbits.ANS5 = 1;
    ANSELbits.ANS6 = 1;
    PORTB = 0;
    
}

void spi_initModeSel(char mode){
    switch(mode){
        case 1:
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 0
            SSPSTATbits.SMP = 1;
            SSPSTATbits.CKE = 0;
            SSPSTATbits.BF = 0;
            
    }
}
