//-------[TESTING MASTER - Tester de Ramales V2]-------//
//------------[SECONDARY CHANNEL TESTING]-------------//
// Testeo controlado Canal a Canal en segunda etapa
// Usuario debe ingresar instrucción para cambiar de canal


//-----------------------------------------------------------//
// EN ESTE CODIGO SE CAMBIAN LAS REFERENCIAS DE MEDICION. 
// MEDIREMOS DESDE TIERRA POR SEGURIDAD  :)
//-----------------------------------------------------------//

#include <Arduino.h>
#include <Adafruit_PCF8574.h>

// pendiente: automatizar esta parte para que quede como los otros códigos
// este código es, por ahora, todo manual.

//creación de cada parte A y B en cada placa M

//Adafruit_PCF8574 IO_M0_A;
//Adafruit_PCF8574 IO_M0_B;

//Adafruit_PCF8574 IO_M1_A;
//Adafruit_PCF8574 IO_M1_B;

//Adafruit_PCF8574 IO_M2_A;
//Adafruit_PCF8574 IO_M2_B;

Adafruit_PCF8574 IO_M3_A;
Adafruit_PCF8574 IO_M3_B;


//-------Creación de los CHAN_XX------//
// los números son los pines del arduino asociados a cada CHAN de cada placa

//int CHAN_0B = 9; 
//int CHAN_0A = 8; 

//int CHAN_1B = 7;
//int CHAN_1A = 6;

//int CHAN_2B = 5;
//int CHAN_2A = 4;

int CHAN_3B = 3;
int CHAN_3A = 2;


void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit PCF8574 LED blink test");
  
  //----------------------[Iniciar el IO B]----------------------//
  if (!IO_M3_B.begin(0x27, &Wire)) 
    {Serial.println("Couldn't find PCF8574"); while (1);} //IO B en M3 está en address 0x27
    
  for (int i = 0; i < 8 ; i ++ )
    {IO_M3_B.pinMode(i, OUTPUT);} //Establecer como salida los 8 pines del IO_B
    
  pinMode(CHAN_3B,OUTPUT); Serial.println("IO B inicializado correctamente"); //Establece como salida el CHAN_3B del Arduino
  

  //----------------------[Iniciar el IO A]----------------------//
  if (!IO_M3_A.begin(0x23, &Wire)) // IO A en M3 está en address 0x23
  {Serial.println("Couldn't find PCF8574"); while (1); } //Establecer como salida los 8 pines del IO_A
  
  for (int i = 0; i < 8 ; i ++ )
    {IO_M3_A.pinMode(i, OUTPUT);} //(no cambiar, sigue siendo output)
  
  pinMode(CHAN_3A,INPUT_PULLUP); //Establece como entrada el CHAN_3A del Arduino
  Serial.print("INICIO --> Lectura por CHAN_3A: "); Serial.println(digitalRead(CHAN_3A));
  Serial.println("IO A inicializado correctamente");
}



void loop() {
  //Parte B
  //------Selector de canal de primera etapa ------// 
  //--[CH15----0010] 
  IO_M3_B.digitalWrite(4, HIGH); //LSB
  IO_M3_B.digitalWrite(5, HIGH); 
  IO_M3_B.digitalWrite(6, HIGH);
  IO_M3_B.digitalWrite(7, HIGH); //MSB
  //------ Cambiar para seleccionar segunda etapa ------//
  //--[CH15 --- 1110]
  IO_M3_B.digitalWrite(0, HIGH);  
  IO_M3_B.digitalWrite(1, HIGH); 
  IO_M3_B.digitalWrite(2, HIGH); 
  IO_M3_B.digitalWrite(3, HIGH);
  

  //Parte A
  //------Selector de canal de primera etapa ------// 
  //--[CH7----0010] 
  IO_M3_A.digitalWrite(4, HIGH); //LSB
  IO_M3_A.digitalWrite(5, HIGH); 
  IO_M3_A.digitalWrite(6, HIGH);
  IO_M3_A.digitalWrite(7, HIGH); //MSB
  //------ Cambiar para seleccionar segunda etapa ------//
  //--[CH15 --- 1110]
  IO_M3_A.digitalWrite(0, HIGH);  
  IO_M3_A.digitalWrite(1, HIGH); 
  IO_M3_A.digitalWrite(2, HIGH); 
  IO_M3_A.digitalWrite(3, HIGH);
  
  
  while(true){

    //revisar los pullup 
    //opcion de señal no es encendido es tierra ???
    //señal low medir dsd tierra 
    //pullup con señal low 
    
    Serial.println("       ");
    Serial.println("|------------INICIO DEL LOOP------------|");
    Serial.println(" --------- <OFF B  x  5seg> --------- "); //(OFF X 5SEG) ---> B high ahora es tierra = no hay led encendido
    digitalWrite(CHAN_3B,HIGH); delay(5000); 
    Serial.print("Estado de B:"); Serial.println(" HIGH EN EL B");
    Serial.print("Lectura por CHAN_3A: "); Serial.print("con el PULLUP = "); Serial.println(digitalRead(CHAN_3A));
    
  
    delay(1000);
    Serial.println("       ");
    Serial.println("------- ESTAMOS AFUERA DEL IF -------");
    Serial.println(" ------- <ON B  x  5seg> ------- "); //(ON X 5SEG) ---> B low esta es la señal de encendido del led 
    digitalWrite(CHAN_3B,LOW); delay(5000);
    Serial.print("Estado de B: "); Serial.println("LOW EN EL B");
    Serial.print("Estado de CHAN_3A: "); Serial.println(digitalRead(CHAN_3A));
    delay(1000);

    delay(50);
    if (!digitalRead(CHAN_3A)) //si: no high (tierra) == si detecta la señal -->  dig read de pin con pullup
    { 
      Serial.println("       ");
      Serial.println("------- ESTAMOS DENTRO DEL IF ------- ");
      Serial.println("Entonces CHAN_3A es tierra");
      Serial.print("Lectura actualizada por CHAN_3A: "); Serial.println(digitalRead(CHAN_3A));
    }


    
    
    
  }
}