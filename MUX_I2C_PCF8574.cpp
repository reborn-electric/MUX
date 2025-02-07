#include "MUX_I2C_PCF8574.h"

/// @brief esto hace tal y cual cosa 
/// @param  estas son sus variables 
/// @return puntero a elemento clase weaita grenuina

//-------------------------------//
//-------- [IO-EXPANDER] --------//
//-------------------------------//
PCF8574::PCF8574(void) {}
void PCF8574::set_address(int ADDR) {

  ////debugln("set_address (1)");
  address = ADDR;
  ////debugln("set_address done!");
}

int PCF8574::begin(void) {
  ////debugln("begin parte io exp A/B");
  Wire.beginTransmission(address);
  int error = Wire.endTransmission();
  //debugln(error);
  return error;
}

int PCF8574::write(int myByte) {
 int result =4;
 do{
  ////debugln("<ESTAMOS ADENTRO DEL DO>");
  Wire.beginTransmission(address);
  ////debugln("--> ejecuta: wire.beginTransm");
  ////debugln("--> esto retorna <address>:");
  ////debugln(address);
  Wire.write(myByte);
  ////debugln("--> ejecuta: wire.write(myByte)");
  ////debugln("--> esto retorna <myByte>:");
  ////debugln(myByte);
  ////debugln("--> esto retorna <reg>:");
  ////debugln(reg);
  result = Wire.endTransmission();
  ////debugln("--> esto retorna <result>:");
  ////debugln(result);
 }///


 while(result != 0); ///esto conghela si end transmission es distinto de 0 
  ////debugln("<ESTAMOS ADENTRO DEL WHILE DEL DO>");
  reg = myByte;
  ////debugln("--> ejecuta: reg = myByte");
  ////debugln("--> esto retorna <result>:");
  ////debugln(result);
  ////debugln("--> esto retorna <reg>:");
  ////debugln(reg);
  return result;
}

int PCF8574::read(void) {
  int result = Wire.requestFrom(address, 1);
  if (result == 0) return -1;
  return Wire.read();
}

int PCF8574::combinationToAddress(int A2_A1_A0, bool version_A) {
  if (A2_A1_A0 < 0 || A2_A1_A0 > 7) return -1;
  if (version_A) return 0x38 + A2_A1_A0;
  return 0x20 + A2_A1_A0;
}

int PCF8574::getReg(void) {
  return reg;
}

void PCF8574::pinMode(int pin, bool mode) {
  if (mode != OUTPUT) digitalWrite(pin, HIGH);
}

int PCF8574::digitalWrite(int pin, bool value) {
  int result = write(value ? reg | (1 << pin) : reg & ~(1 << pin));
  return result;
}

int PCF8574::digitalWriteByte(int value) {
  int result = write(value);
  return result;
}

bool PCF8574::digitalRead(int pin) {
  return (read() & (1 << pin)) ? HIGH : LOW;
}

int PCF8574::digitalToggle(int pin) {
  int result = write(reg ^ (1 << pin));
  return result;
}

//-------------------------------//
//--------- [PLACAS MX] ---------//
//-------------------------------//
I2C_MUX_CARD::I2C_MUX_CARD() {}

I2C_MUX_CARD::I2C_MUX_CARD(int ADDR_A, int ADDR_B, int PIN_A, int PIN_B) {
  //debugln("I2C_MUX_CARD ---> creando addr y chan por placa M");
  Wire.begin();
  // //debugln("WIRE online");
  IO_EXPANDER_A.set_address(ADDR_A);
  // //debugln("Address  A setted ");
  IO_EXPANDER_B.set_address(ADDR_B);
  // //debugln("Address  B setted ");

  IO_EXPANDER_A.begin();
  //if (IO_EXPANDER_A.begin() == 0) { 
  //delay(50);
  //debugln("\tEXPANDER A ONLINE ---> lo está reconociendo :)");}
  //  else {
  //   //debugln("\tEXPANDER A OFFLINE");
  // }
  IO_EXPANDER_B.begin();
  //if (IO_EXPANDER_B.begin() == 0){
    //delay(50);
    //debugln("\tEXPANDER B ONLINE ---> lo está reconociendo :)");}
  //  else {
  //   //debugln("\tEXPANDER B OFFLINE");
  // }
  CHAN_A = PIN_A;
  CHAN_B = PIN_B;
  pinMode(CHAN_A, INPUT_PULLUP);
  pinMode(CHAN_B, INPUT_PULLUP);
  Wire.end();
}

void I2C_MUX_CARD::write(int PIN, bool state) {
  IO_EXPANDER_A.digitalWriteByte(PIN);
  pinMode(CHAN_A, OUTPUT);
  digitalWrite(CHAN_A, state);
}

void I2C_MUX_CARD::restore_pin(void) {
  pinMode(CHAN_A, INPUT_PULLUP);
  pinMode(CHAN_B, INPUT_PULLUP);
}

bool I2C_MUX_CARD::read(int PIN) {
  IO_EXPANDER_B.digitalWriteByte(PIN);
  delay(10);
  digitalWrite(CHAN_B,HIGH);
  pinMode(CHAN_B, INPUT);
  //debugln("<estamos en i2c_mux_card::read>");
  //debug("digitalread del CHAN_B AKA PIN ");
  //debugln(CHAN_B);
  //debugln(digitalRead(CHAN_B));
  return (digitalRead(CHAN_B));

}

bool I2C_MUX_CARD::is_conected(int PIN_A, int PIN_B) {
  write(PIN_A, LOW);
  bool buff = read(PIN_B);
  restore_pin();
  return (!buff);
}

int I2C_MUX_CARD::check_signal(int PIN) {
bool detected = 0;
bool correcto = 0;

  //debug("Checking PIN 0x");
  //debugHEX(PIN);
  for (int i = 0; i < 256; i++) {

    if (i != PIN && is_conected(PIN, i)) {
        
        //debug(" detected at PIN 0x");
        //debugHEX(i);
        //debugln("");
         return (i);
      
    }
  }
  if (! detected){
    //debug("Checking PIN 0x");
    //debugHEX(PIN);
    //debugln(" not detected");
    }
  //
  return (-1);
 
}

bool I2C_MUX_CARD::check_card(void) {
  //debugln("check_card");
  bool state = true;
  for (int i = 0; i < 256; i++) {
    if (check_signal(i) != i) {
      state = false;
      
    }
  }
  return (state);
}


//--------------------------------------//
//--------- [SISTEMA COMPLETO] ---------//
//--------------------------------------//

I2C_MUX_SYSYEM::I2C_MUX_SYSYEM() {

  // MUX_CHAN_0A ---> CHAN_0A
  //debugln("               ");
  //debugln("LOADING CARD_M0");
  CARD_M0 = I2C_MUX_CARD(MUX_addr_0A, MUX_addr_0B, MUX_CHAN_0A, MUX_CHAN_0B);
  //debugln("LOADING CARD_M1");
  CARD_M1 = I2C_MUX_CARD(MUX_addr_1A, MUX_addr_1B, MUX_CHAN_1A, MUX_CHAN_1B);
  // delay(2000);
  //debugln("LOADING CARD_M2");
  CARD_M2 = I2C_MUX_CARD(MUX_addr_2A, MUX_addr_2B, MUX_CHAN_2A, MUX_CHAN_2B);
  //debugln("LOADING CARD_M3");
  CARD_M3 = I2C_MUX_CARD(MUX_addr_3A, MUX_addr_3B, MUX_CHAN_3A, MUX_CHAN_3B);
  //debugln("SYSTEM LOADED");
}

bool I2C_MUX_SYSYEM::read(unsigned int PIN) {
  if (PIN <= 255) { return (CARD_M0.read(PIN)); }
  PIN -= 256;
  if (PIN <= 255) { return (CARD_M1.read(PIN)); }
  PIN -= 256;
  if (PIN <= 255) { return (CARD_M2.read(PIN)); }
  PIN -= 256;
  if (PIN <= 255) { return (CARD_M3.read(PIN)); }
  //debugln("no funco tamos hasta loly");
}

void I2C_MUX_SYSYEM::write(int PIN, bool state) {
  if (PIN <= 255) { return (CARD_M0.write(PIN, state)); }
  PIN -= 256;
  if (PIN <= 255) { return (CARD_M1.write(PIN, state)); }
  PIN -= 256;
  if (PIN <= 255) { return (CARD_M2.write(PIN, state)); }
  PIN -= 256;
  if (PIN <= 255) { return (CARD_M3.write(PIN, state)); }
}

void I2C_MUX_SYSYEM::restore_pin(int PIN) {
  if (PIN <= 255) { return (CARD_M0.restore_pin()); }
  PIN -= 256;
  if (PIN <= 255) { return (CARD_M1.restore_pin()); }
  PIN -= 256;
  if (PIN <= 255) { return (CARD_M2.restore_pin()); }
  PIN -= 256;
  if (PIN <= 255) { return (CARD_M3.restore_pin()); }
}

bool I2C_MUX_SYSYEM::is_conected(int PIN_A, int PIN_B) {
  ////debugln("<Estamos en i2c_mux_system::isconected>");
  write(PIN_A, LOW);
  ////debugln("numero de PIN_A:");
  ////debugln(PIN_A);
  delay(50);
  bool buff = read(PIN_B);
  ////debugln("valor de PIN_B:");
  ////debugln(buff);
  restore_pin(PIN_A);
  restore_pin(PIN_B);
  return (!buff);
}

int I2C_MUX_SYSYEM::detect_signal(int PIN, int detection_index) {
  int count = 1;
  for (int i = 0; i < 1024; i++) {
    if (PIN == i) { continue; }
    if (is_conected(PIN, i)) { count++; }
    if (count == detection_index) { return (i); }
  }
  return (-1);
}

//bool I2C_MUX_SYSYEM::check_module(void) {
  //debugln("check_module");
  //  //debugln("Revisando la Tarjeta 1");
  // Wire.begin();
  // if (!CARD1.check_card()) {
  //   //debugln("MALA");
  //  }
  // //debugln("Revisando la Tarjeta 2");
  // if (!CARD_M1.check_card()) {
  //   //debugln("MALA");
  // }
  //debugln("Revisando la tarjeta 3");
  //if (!CARD_M2.check_card()) {
    //debugln("MALA");
  
  // //debugln("Revisando la tarjeta 4");
  // if (!CARD_M3.check_card()) {
  //   //debugln("MALA");
  // }
  //return (true);
  //Wire.end();
//}
