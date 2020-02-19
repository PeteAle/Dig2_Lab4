/*
 * File:   lib_spi.c
 * Author: Peter
 *
 * Created on February 14, 2020, 2:44 PM
 */


#include <xc.h>
#include "lib_spi.h"
#include <stdio.h>
#include <stdint.h>

void spi_msinit(uint8_t mode){
    switch(mode){
        case 0:                     // Master mode Fosc/4.
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 0;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPCON = 0b00100000;
            //SSPCONbits.CKP = 0;
            //SSPCONbits.SSPEN = 1;
            break;
        case 1:                     // Master mode Fosc/16
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 0;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPCON = 0b00100001;
            //SSPCONbits.CKP = 0;
            //SSPCONbits.SSPEN = 1;
            break;
        case 2:                     // Master mode Fosc/64
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 0;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPCON = 0b00100010;
            //SSPCONbits.CKP = 0;
            //SSPCONbits.SSPEN = 1;
            break;
        case 3:                     // Slave mode, SS enabled.
            TRISCbits.TRISC5 = 0;
            TRISCbits.TRISC3 = 1;
            TRISCbits.TRISC4 = 1;
            SSPSTATbits.SMP = 0;
            SSPSTATbits.CKE = 0;
            SSPCON = 0b00100100;
            break;
    }
}
