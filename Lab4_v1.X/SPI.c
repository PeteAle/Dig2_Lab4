/*
 * File:   SPI.c
 * Author: Peter
 *
 * Created on February 21, 2020, 5:00 PM
 */


#include <xc.h>
#include "SPI.h"

void spi_msinit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge){
  TRISCbits.TRISC5 = 0;
  if(sType & 0b00000100) //If Slave Mode
  {
    SSPSTAT = sTransmitEdge;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
  }
  else //If Master Mode
  {
    SSPSTAT = sDataSample | sTransmitEdge;
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 1;
  }
  SSPCON = sType | sClockIdle;
}

void spi_wait(void){
  while ( !SSPSTATbits.BF ); // Wait for Data Receipt complete
}

void spi_write(char datos){ //Write data to SPI bus
  SSPBUF = datos;
}

void spi_bufReady(unsigned char ready){
    if (SSPSTATbits.BF == 1){
        ready = 1;
    }
    else if (SSPSTATbits.BF == 0){
        ready = 0;
    }
}

void spi_read(char lectura){    // Read the received data
  spi_wait();      // Wait until all bits receive
  lectura = SSPBUF; // Read the received data from the buffer
}