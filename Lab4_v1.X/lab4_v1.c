/*
 * File:   lab4_v1.c
 * Author: Peter
 *
 * Created on February 14, 2020, 12:00 PM
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

float pot1 = 0;
float pot2 = 0;
uint16_t temp1 = 0, temp2 = 0;

void setup(void);

void main(void){
    setup();
    oscInit(1);
    spi_msinit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MID, SPI_CLOCK_IDLE_LOW, SPI_ACTIVE_2_IDLE);
    //uart_init();
    //uart_9bit(0,0);
    //txrx_En(1,1);
    //baudRate();
    //uart_interrupts(0,0);
    while(1){
        if (SSPSTATbits.BF == 1 & PIR1bits.SSPIF == 1 & pot2 != 0){
            spi_read(pot1);
            PORTB = pot1;
        }
//        else if (SSPSTATbits.BF == 1 & PIR1bits.SSPIF == 1 & pot1 != 0){
//            spi_read(pot2);
//            PORTB = pot2;
//        }
    }
    return;
}

void setup(void){
    TRISB = 0x00;
    TRISEbits.TRISE0 = 1;
    TRISEbits.TRISE1 = 1;
    ANSELbits.ANS5 = 1;
    ANSELbits.ANS6 = 1;
    PORTB = 0x00;
}