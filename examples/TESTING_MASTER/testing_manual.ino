//-----------------------------------------------------//
//-------[TESTING MASTER - Tester de Ramales V2]-------//
//-------------[(2) SLOW CHANNEL TESTING]--------------//
//-----------------------------------------------------//

// Testeo de barrido controlado Canal a Canal en primera etapa
// Usuario debe ingresar instrucción para cambiar de canal 

#include <Adafruit_PCF8574.h>

Adafruit_PCF8574 IO_M;

//Asignación de direcciones IO Expander por partes
const uint8_t I2C_ADDRESSES_A[] = {0x20, 0x21, 0x22, 0x23};
const uint8_t I2C_ADDRESSES_B[] = {0x24, 0x25, 0x26, 0x27};
//Asignación de direcciones pines del arduino 
// *cambiar a "CHAN_XX"
const uint8_t COMMON_PINS_A[] = {8, 6, 4, 2};
const uint8_t COMMON_PINS_B[] = {9, 7, 5, 3};

//Creación de variables
int common_pin;
int selectedBoard;
char selectedPart;

void setChannel(uint8_t channel) {
  for (int i = 0; i < 4; i++) {
    IO_M.digitalWrite(4 + i, (channel >> i) & 0x01);
  }
  Serial.print("Canal configurado: CH");
  Serial.println(channel);
}

void selectBoardAndPart_manual() {
  Serial.println("Selecciona la placa M a usar (0-3):");
  while (!Serial.available());
  selectedBoard = Serial.parseInt();

  Serial.println("Selecciona la parte a revisar (A/B):");
  while (!Serial.available());
  selectedPart = toupper(Serial.read());

  uint8_t address = (selectedPart == 'A') ? I2C_ADDRESSES_A[selectedBoard] : I2C_ADDRESSES_B[selectedBoard];
  common_pin = (selectedPart == 'A') ? COMMON_PINS_A[selectedBoard] : COMMON_PINS_B[selectedBoard];

  if (!IO_M.begin(address, &Wire)) {
    Serial.println("No se pudo encontrar el PCF8574 en la dirección seleccionada");
    while (1);
  }
  
  // setea los pines del IO como salidas
  for (int i = 0; i < 8; i++) {
    IO_M.pinMode(i, OUTPUT);
  }

  // setea los pines del arduino como salidas
  pinMode(common_pin, OUTPUT);
  Serial.println("Placa inicializada correctamente");
}

void testing_manual() {
  selectBoardAndPart_manual();

  while (true) {
    Serial.println("Ingresa un canal (0-15) o (-1) para salir:");
    while (!Serial.available());
    int channel = Serial.parseInt();
    
    if (channel == -1) break;
    if (channel >= 0 && channel <= 15) {
      setChannel(channel);
    } else {
      Serial.println("Canal inválido, intenta nuevamente.");
    }
  }
  Serial.println("Finalizando Testeo Manual...");
}
