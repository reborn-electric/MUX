//-----------------------------------------------------//
//-------[TESTING MASTER - Tester de Ramales V2]-------//
//---Testeo interactivo de Canales en primera etapa---//
//----------------------------------------------------//

//------Librerías------//
#include <Arduino.h>
// #include <Adafruit_PCF8574.h> está en los otros archivos


//------Declaraciones de funciones------//
// (los detalles de cada función estan en los otros archivos)
void testing_automatico();
void testing_manual();

//------Función de testing interactivo------//
// Función propia de este archivo
// Usuario elige desde monitor serial qué testeo ejecutar
void testing_primera_etapa() {
  while (true) {
    Serial.println("TESTING MASTER PRIMERA ETAPA");
    Serial.println("Ingresa (1) para elegir modo Testing automático");
    Serial.println("Ingresa (2) para elegir modo Testing manual");
    Serial.println("Ingresa (0) para salir");

    while (!Serial.available());
    int option = Serial.parseInt();
    
    if (option == 0) {
      Serial.println("Cancelado.");
      return; // Sale de la función
    } 
    else if (option == 1) {
      Serial.println("Ejecutando Testing Automático...");
      testing_automatico();
    } 
    else if (option == 2) {
      Serial.println("Ejecutando Testing Manual...");
      testing_manual();
    } 
    else {
      Serial.println("Opción inválida, intenta nuevamente.");
    }
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  testing_primera_etapa();
}

void loop() {
  // No hace nada, el control está en `testing_primera_etapa`
}
