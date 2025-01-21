/*!
 *  @file MUX.h
 *
 * 	I2C Driver for PCF8574 based I2C MUX 
 *
 * 	This is a library CUstom PCB assembly "exodia"
 *
 *
 *	Propperty of Reborn Electric. All Rights Reserved
 *
 *
 * 
 * 
 */


#ifndef MUX_H
#define MUX_H

#define IO_A0_ADDR 0x20
#define IO_A1_ADDR 0x21
#define IO_A2_ADDR 0x22
#define IO_A3_ADDR 0x23

#define IO_B0_ADDR 0x24
#define IO_B1_ADDR 0x25
#define IO_B2_ADDR 0x26
#define IO_B3_ADDR 0x27

// pines del arduino segun canal del MUX 
#define CH_B0 9
#define CH_B1 7
#define CH_B2 5
#define CH_B3 3

#define CH_A0 8
#define CH_A1 6
#define CH_A2 4
#define CH_A3 2




#include <Adafruit_PCF8574.h>

class MUX
{
private:
    Adafruit_PCF8574 IO_A0;
    Adafruit_PCF8574 IO_A1;
    Adafruit_PCF8574 IO_A2; 
    Adafruit_PCF8574 IO_A3; 
    Adafruit_PCF8574 IO_B0; 
    Adafruit_PCF8574 IO_B1;
    Adafruit_PCF8574 IO_B2;
    Adafruit_PCF8574 IO_B3;

    bool set_adress_A(uint16_t addr);
    bool set_adress_B(uint16_t addr);
    bool read_A(uint16_t addr);
    bool read_B(uint16_t addr);
    bool write_A(uint16_t addr);
    bool write_B(uint16_t addr);
    //void clear(void);
    uint8_t JAKast(uint16_t addr);
    void HiZ_A(void);
    void HiZ_B(void);
    
    
public:
    MUX(void);
    //~MUX();
    bool test(uint16_t addr_A, uint16_t addr_B);
};



  #endif
  