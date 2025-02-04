#include <MUX.h>
// Este es un "example" disponible para correr en IDE de Arduino
// Desde Visual Studio marca error en #include <MUX.h> pero en IDE funciona perfecto 

void setup() {
 Serial.begin(9600);

}

void loop() {
MUX myMUX;
  for (uint16_t i = 0x0000; i < 0x0400; i++) 
  {
     //for (uint16_t j = 0; j < 1024; j++) {
        Serial.print("Testing PIN_A: ");
        Serial.print(i,HEX);
        Serial.print("     with PINB:");
        Serial.print(i,HEX);
        Serial.print("     RESULT:   ");
        if(myMUX.test(i,i ))
        {
          Serial.println("Buenolino");
        }
        else{
          Serial.println("Malolino");
        }
      //}      
  }
  while(1);
}
