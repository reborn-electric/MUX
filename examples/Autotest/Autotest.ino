//---------------------------------------------------//
//---------[Autotest - Tester de Ramales V2]---------//
//--------Testeo entre pines de segunda etapa--------//
//---------------------------------------------------//

// Testeo automático del pin de un canal consigo mismo 
// y el resto de pines de ese canal.
// Para todos los canales de todas las placas de
// primera etapa.

#include <MUX_I2C_PCF8574.h>
#include <Wire.h>


void setup() {
  Serial.begin(115200);
}

void loop() {
  I2C_MUX_SYSYEM MyMegaMux;
  Wire.begin();
  Serial.println(">>>>>>>>>>>>>>>>>>>> BEGIN AUTOTEST <<<<<<<<<<<<<<<<<<<<<");
  Serial.println("           ");

    for (int i = 0; i < 4; i++) //--------Outer loop largo 4
    { 
      Serial.print("M");
      Serial.println(i); 
      Serial.println();
       
      for (int j = 0; j < 16; j++) //-----Middle loop largo 16
      {    
        for (int k = 0; k < 16; k++) //---Inner loop largo 16
        { 
          Serial.print(MyMegaMux.is_conected((i<<8)|(j<<4)|k,(i<<8)|(j<<4)|k));
          //delay(5);
        }
        Serial.println();        
      }
      Serial.println();  
    }
  Serial.println(">>>>>>>>>>>>>>>>>>>> END AUTOTEST <<<<<<<<<<<<<<<<<<<<<");
  Serial.println("           ");
  while(2); //para detener el proceso
}

 




