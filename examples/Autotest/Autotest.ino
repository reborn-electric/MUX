#include <MUX.h>


void setup() {
 Serial.begin(9600);

}

void loop() {
MUX myMUX;
  for (uint16_t i = 0x000; i < 0x300; i++) 
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
