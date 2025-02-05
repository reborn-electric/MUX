
#include "Arduino.h"
#include <Wire.h>

#define MUX_CHAN_1 23
#define MUX_CHAN_2 25
#define MUX_CHAN_3 27
#define MUX_CHAN_4 29
#define MUX_CHAN_5 31
#define MUX_CHAN_6 33
#define MUX_CHAN_7 35
#define MUX_CHAN_8 37

#define DEBUG 1 

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
  int CHAN_A;
  int CHAN_B;
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
  I2C_MUX_CARD CARD1;
  I2C_MUX_CARD CARD2;
  I2C_MUX_CARD CARD3;
  I2C_MUX_CARD CARD4;
  I2C_MUX_SYSYEM();
  bool read(unsigned int PIN);
  void write(int PIN, bool state);
  void restore_pin(int PIN);
  bool is_conected(int PIN_A, int PIN_B);
  int detect_signal(int PIN, int detection_index);
  bool check_module(void);

};