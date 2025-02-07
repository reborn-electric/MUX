
#include "Arduino.h"
#include <Wire.h>


#define MUX_CHAN_0A 8  //CHAN_0A
#define MUX_CHAN_0B 9  //CHAN_0B
#define MUX_CHAN_1A 6  //CHAN_1A
#define MUX_CHAN_1B 7  //CHAN_1B
#define MUX_CHAN_2A 4  //CHAN_2A
#define MUX_CHAN_2B 5  //CHAN_2B
#define MUX_CHAN_3A 2  //CHAN_3A
#define MUX_CHAN_3B 3  //CHAN_3B

// cambiar a IO_PX para 0-7
#define MUX_addr_0A 0x20 
#define MUX_addr_0B 0X24
#define MUX_addr_1A 0X21
#define MUX_addr_1B 0X25
#define MUX_addr_2A 0X22
#define MUX_addr_2B 0X26
#define MUX_addr_3A 0X23
#define MUX_addr_3B 0X27


#define DEBUG 0 
#if DEBUG==1
#define debug(x) Serial.print(x)
#define debugHEX(x) Serial.print(x,HEX)
#define debugln(x) Serial.println(x)


#define DEBUG_COM Serial.begin(115500)
#else
#define debug(x)
#define debugln(x)
#define DEBUG_COM
#endif

#define PCF8574_CLOCK 100000
class PCF8574 {
  // private:
  //   int write(int reg);
  //   int read(void);
  //   int getReg(void);    
  //   int address, reg = 255;
	
	public:
 
    int write(int);
    int read(void);
    int getReg(void);    
    int address, reg = 255;
    PCF8574(void);
    int begin(void);
    void set_address( int ADDR);
    static int combinationToAddress(int A2_A1_A0, bool version_A);
    void pinMode(int, bool);
    int  digitalWrite(int, bool);
    int digitalWriteByte(int value);
    bool  digitalRead(int);
    int  digitalToggle(int);

  };


class I2C_MUX_CARD{
  private:

  // bool ONLINE_A;
  // bool ONLINE_B;
  // bool OPERATIVE;
  // PCF8574 IO_EXPANDER_A;
  // PCF8574 IO_EXPANDER_B;
  // int CHAN_A;
  // int CHAN_B;

  public:
  bool ONLINE_A;
  bool ONLINE_B;
  bool OPERATIVE;
  PCF8574 IO_EXPANDER_A;
  PCF8574 IO_EXPANDER_B;
  unsigned int CHAN_A;
  unsigned int CHAN_B;
  I2C_MUX_CARD();
  I2C_MUX_CARD(int ADDR_A, int ADDR_B, int PIN_A, int PIN_B);
  void write(int PIN, bool state);
  bool read(int PIN);
  void restore_pin(void);
  bool is_conected(int PIN_A, int PIN_B);
  int check_signal(int PIN);
  bool check_card(void);

};

class I2C_MUX_SYSYEM {
  // private:

  public:
  I2C_MUX_CARD CARD_M0; //M0
  I2C_MUX_CARD CARD_M1; //M1
  I2C_MUX_CARD CARD_M2; //M2
  I2C_MUX_CARD CARD_M3; //M3

  I2C_MUX_SYSYEM();
  bool read(unsigned int PIN);
  void write(int PIN, bool state);
  void restore_pin(int PIN);
  bool is_conected(int PIN_A, int PIN_B);
  int detect_signal(int PIN, int detection_index);
  bool check_module(void);

};