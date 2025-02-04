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

//----------------______________________-----------------
//---------------|NO MODIFICAR LIBRERÍA|-----------------
//-------------------------------------------------------
// Esta es la librería creada por nosotros para hacer nuestros "examples"
// para así hacer los testeos necesarios para validar el hardware

#ifndef MUX_H
#define MUX_H

// address I2C del IO EXPANDER en las placas MX
#define IO_A0_ADDR 0x20 //M0: 000
#define IO_B0_ADDR 0x24 //M0: 100

#define IO_A1_ADDR 0x21 //M1: 001
#define IO_B1_ADDR 0x25 //M1: 101

#define IO_A2_ADDR 0x22 //M2: 010
#define IO_B2_ADDR 0x26 //M2: 110

#define IO_A3_ADDR 0x23 //M3: 011
#define IO_B3_ADDR 0x27 //M3: 111

// pines "DX" del arduino segun canal del MUX 
#define CH_B0 9 // Placa M0
#define CH_A0 8
#define CH_B1 7 // Placa M1
#define CH_A1 6
#define CH_B2 5 // Placa M2
#define CH_A2 4
#define CH_B3 3 // Placa M3
#define CH_A3 2

// librería que permite trabajar con el IO EXPANDER
#include <Adafruit_PCF8574.h>

class MUX //creación de la clase MUX individual. Tenemos varios MUX.
{
private:
    Adafruit_PCF8574 IO_A0; //IO_EXP_A en M0
    Adafruit_PCF8574 IO_B0; //IO_EXP_B en M0
    
    Adafruit_PCF8574 IO_A1; //IO_EXP_A en M1
    Adafruit_PCF8574 IO_B1; //IO_EXP_B en M1
    
    Adafruit_PCF8574 IO_A2; //IO_EXP_A en M2
    Adafruit_PCF8574 IO_B2; //IO_EXP_B en M2

    Adafruit_PCF8574 IO_A3; //IO_EXP_A en M3
    Adafruit_PCF8574 IO_B3; //IO_EXP_B en M3

    
    bool read_A(uint16_t addr);
    bool read_B(uint16_t addr);
    bool write_A(uint16_t addr);
    bool write_B(uint16_t addr);
    //void clear(void);
    uint8_t JAKast(uint16_t addr); //
    void HiZ_A(void); //para ver alta impedancia HIGH (protectivo)
    void HiZ_B(void); //para ver alta impedancia HIGH (protectivo)
    
    
public:
    bool set_adress_A(uint16_t addr);
    bool set_adress_B(uint16_t addr);
    
    MUX(void);
    //~MUX();
    bool test(uint16_t addr_A, uint16_t addr_B); //método "test"
};



  #endif
  