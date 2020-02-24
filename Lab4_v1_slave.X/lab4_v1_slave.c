/*
 * File:   lab4_v1_slave.c
 * Author: Peter
 *
 * Created on February 21, 2020, 11:45 AM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "lib_adc.h"
#include "lib_osccon.h"
//#include "lib_spi.h"
#include "SPI.h"
#include "UART.h"

#define _XTAL_FREQ 4000000

void setup(void);
void intEnable(void);

uint8_t temporal = 0;
uint8_t pot1 = 0;
int pot2 = 0;
uint16_t temp1 = 0, temp2 = 0;
uint16_t centenas1 = 0, decenas1 = 0, unidades1 = 0;
uint16_t centenas2 = 0, decenas2 = 0, unidades2 = 0;


void __interrupt() isr(){
    di();
    
    }
//    else if (PIR1bits.ADIF == 1 && ADCON0bits.CHS3 == 0 && ADCON0bits.CHS2 == 1 && ADCON0bits.CHS1 == 1 && ADCON0bits.CHS0 == 1){
//        pot2 = ADRESH;
//        PIR1bits.ADIF = 0;
//    }
//    if (ADCON0bits.CHS3 == 0 && ADCON0bits.CHS2 == 1 && ADCON0bits.CHS1 == 1 && ADCON0bits.CHS0 == 0){
//        ADCON0bits.CHS3 = 0;
//        ADCON0bits.CHS2 = 1;
//        ADCON0bits.CHS1 = 1;
//        ADCON0bits.CHS0 = 1;
//    }
//    else if (ADCON0bits.CHS3 == 0 && ADCON0bits.CHS2 == 1 && ADCON0bits.CHS1 == 1 && ADCON0bits.CHS0 == 1){
//        ADCON0bits.CHS3 = 0;
//        ADCON0bits.CHS2 = 1;
//        ADCON0bits.CHS1 = 1;
//        ADCON0bits.CHS0 = 0;
//    }
//    ei();
//}

void main(void) {
    setup();
    oscInit(1);
    adcSetup();
    analogInSel(6);
    adcFoscSel(1);
    spi_msinit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MID, SPI_CLOCK_IDLE_LOW, SPI_ACTIVE_2_IDLE);
    //intEnable();
    while(1){
        if (ADCON0bits.GO_DONE == 0){
            ADCON0bits.GO_DONE = 1;
        }
        if (SSPSTATbits.BF == 1){
            spi_read(temporal);
            spi_write(pot1);
        }
        if (PIR1bits.ADIF == 1 && ADCON0bits.CHS3 == 0 && ADCON0bits.CHS2 == 1 && ADCON0bits.CHS1 == 1 && ADCON0bits.CHS0 == 0){
            pot1 = ADRESH;
            PIR1bits.ADIF = 0;
        }
//        temp1 = ((pot1*5.0)/255.0)*100;
//        centenas1 = temp1/100;
//        temp1 = temp1 - (centenas1*100);
//        decenas1 = temp1/10;
//        unidades1 = temp1 - (decenas1*10);
//        spi_write(centenas1);
//        __delay_ms(100);
//        spi_write(decenas1);
//        __delay_ms(100);
//        spi_write(unidades1);
    }
    return;
}

void setup(void){
    TRISEbits.TRISE1 = 1;
    TRISEbits.TRISE2 = 1;
    ANSELbits.ANS6 = 1;
    ANSELbits.ANS7 = 1;
    PORTE = 0;
}

void intEnable(void){
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.ADIE = 1;
    //PIE1bits.TXIE = 0;
    //PIE1bits.RCIE = 1;
}