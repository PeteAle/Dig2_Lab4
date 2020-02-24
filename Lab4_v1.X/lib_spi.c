/*
 * File:   lib_spi.c
 * Author: Peter
 *
 * Created on February 14, 2020, 2:44 PM
 */


#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "lib_spi.h"

void spi_msinit(unsigned char mode){
    switch(mode){
        case 0:                     // Master mode Fosc/4.
            TRISCbits.TRISC4 = 1;
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 0;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPSTATbits.BF = 0;
            SSPCON = 0b00100000;
            //SSPCONbits.CKP = 0;
            //SSPCONbits.SSPEN = 1;
            break;
        case 1:                     // Master mode Fosc/16
            TRISCbits.TRISC4 = 1;
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 0;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPSTATbits.BF = 0;
            SSPCON = 0b00100001;
            //SSPCONbits.CKP = 0;
            //SSPCONbits.SSPEN = 1;
            break;
        case 2:                     // Master mode Fosc/64
            TRISCbits.TRISC4 = 1;
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 0;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPSTATbits.BF = 0;
            SSPCON = 0b00100010;
            //SSPCONbits.CKP = 0;
            //SSPCONbits.SSPEN = 1;
            break;
        case 3:                     // Slave mode, SS enabled.
            TRISAbits.TRISA5 = 1;   // SS como input.
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 1;
            TRISCbits.TRISC4 = 1;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPSTATbits.BF = 0;
            SSPCON = 0b00100100;
            break;
    }
}

void spi_write(int datos){
    TRISAbits.TRISA5 = 0;
    SSPBUF = datos;
    PIR1bits.SSPIF = 0;
    TRISAbits.TRISA5 = 1;
}

void spi_sWrite(int sData){
    TRISAbits.TRISA5 = 0;
    SSPBUF = sData;
    PIR1bits.SSPIF = 0;
    TRISAbits.TRISA5 = 1;
}

void spi_bufReady(unsigned char ready){
    if (SSPSTATbits.BF == 1){
        ready = 1;
    }
    else if (SSPSTATbits.BF == 0){
        ready = 0;
    }
}

void spi_read(char lectura){
    while (SSPSTATbits.BF == 0){
        lectura = SSPBUF;
    }
}
