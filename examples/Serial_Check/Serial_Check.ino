#include <MUX.h>
// Este es un "example" disponible para correr en IDE de Arduino
// Desde Visual Studio marca error en #include <MUX.h> pero en IDE funciona perfecto 

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  MUX myMux;
  int placa;
  int pin;
  Serial.println("Seleccione placa");
  while (!stringComplete); //espera a que haya un string para hacer alguna wea 
  if (stringComplete) {
    placa =inputString.toInt();     
    inputString = "";
    stringComplete = false;
  }
  Serial.println("Seleccione PIN");
  while (!stringComplete); //espera a que haya un string para hacer alguna wea 
  if (stringComplete) {
    pin =inputString.toInt();    
    inputString = "";
    stringComplete = false;
  }
  myMux.test(placa<<8+pin,placa<<8+pin);
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
