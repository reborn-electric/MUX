//-------[TESTING MASTER - Tester de Ramales V2]-------//
//-------[SLOW CHANNEL TESTING]------//
// Testeo de barrido controlado Canal a Canal en primera etapa
// Usuario debe ingresar instrucción para cambiar de canal 

#include <Arduino.h>
#include <Adafruit_PCF8574.h>

Adafruit_PCF8574 IO_M;
int commonPin;
int selectedBoard;
char selectedPart;

void setup() {
  Serial.begin(115200);
}

void iniciarTest() {
  Serial.println("Slow Channel Testing: selección de placa");
  
  while (true) {
    Serial.println("Selecciona la placa a revisar (0-3):");
    while (!Serial.available()); 
    String input = Serial.readStringUntil('\n'); 
    input.trim(); 

    if (input.length() == 1 && isDigit(input[0])) { 
      selectedBoard = input.toInt();
      if (selectedBoard >= 0 && selectedBoard <= 3) break;
    }
    Serial.println("Placa inválida, intenta nuevamente.");
  }

  while (true) {
    Serial.println("Selecciona la parte a revisar:");
    Serial.println("A: Parte A");
    Serial.println("B: Parte B");
    while (!Serial.available()); 
    String input = Serial.readStringUntil('\n'); 
    input.trim(); 
    input.toUpperCase(); 

    if (input == "A" || input == "B") {
      selectedPart = input[0]; 
      break;
    }
    Serial.println("Opción inválida, intenta nuevamente.");
  }

  const uint8_t boardAddressesA[] = {0x20, 0x21, 0x22, 0x23};
  const uint8_t boardAddressesB[] = {0x24, 0x25, 0x26, 0x27};
  const uint8_t commonPinsA[] = {8, 6, 4, 2};
  const uint8_t commonPinsB[] = {9, 7, 5, 3};

  uint8_t address = (selectedPart == 'A') ? boardAddressesA[selectedBoard] : boardAddressesB[selectedBoard];
  commonPin = (selectedPart == 'A') ? commonPinsA[selectedBoard] : commonPinsB[selectedBoard];

  if (!IO_M.begin(address, &Wire)) {
    Serial.println("No se encontró el PCF8574. Verifique la conexión.");
    while (1);
  }

  for (int i = 0; i < 8; i++) {
    IO_M.pinMode(i, OUTPUT);
  }
  pinMode(commonPin, OUTPUT);

  Serial.println("IO inicializado correctamente");

  for (int channel = 0; channel < 16; channel++) {
    IO_M.digitalWrite(4, channel & 0b0001);
    IO_M.digitalWrite(5, (channel >> 1) & 0b0001);
    IO_M.digitalWrite(6, (channel >> 2) & 0b0001);
    IO_M.digitalWrite(7, (channel >> 3) & 0b0001);

    Serial.print("Revisando Canal ");
    Serial.print(channel);
    Serial.println(" .... ¿Siguiente Canal? (Y)");

    while (true) {
      if (Serial.available()) {
        String input = Serial.readStringUntil('\n'); 
        input.trim();
        input.toUpperCase();
        if (input == "Y") break; 
      }

      digitalWrite(commonPin, HIGH);
      delay(1000);
      digitalWrite(commonPin, LOW);
      delay(500);
    }
    while (Serial.available()) Serial.read(); 
  }

  Serial.print("Revisión canal a canal en placa M");
  Serial.print(selectedBoard);
  Serial.println(" finalizada.");
}

void loop() {
  while (true) {
    iniciarTest();
    Serial.println("¿Quieres revisar otra placa? (Y/N)");
    while (!Serial.available()); 
    String input = Serial.readStringUntil('\n'); 
    input.trim(); 
    input.toUpperCase();
    if (input == "N") {
      Serial.println("Fin de la revisión.");
      while (1); 
    }
  }
}

