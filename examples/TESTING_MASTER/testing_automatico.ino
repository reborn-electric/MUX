//-------[TESTING MASTER - Tester de Ramales V2]-------//
//-------[FAST CHANNEL TESTING]------//
// Testeo de barrido automático Canal a Canal en primera etapa
// Usuario debe ingresar instrucción para comenzar

#include <Arduino.h>
#include <Adafruit_PCF8574.h>

// Objeto para el expansor IO de la parte seleccionada (A o B)
Adafruit_PCF8574 IO_M;

// Direcciones I2C y pines asociados para las partes A y B de cada placa
const uint8_t I2C_ADDRESSES_A[] = {0x20, 0x21, 0x22, 0x23}; // M0A, M1A, M2A, M3A
const uint8_t I2C_ADDRESSES_B[] = {0x24, 0x25, 0x26, 0x27}; // M0B, M1B, M2B, M3B
const uint8_t COMMON_PINS_A[] = {8, 6, 4, 2};               // Pines common_a
const uint8_t COMMON_PINS_B[] = {9, 7, 5, 3};               // Pines common_b

int common_pin; // Pin común para la parte seleccionada

void setup() {
  Serial.begin(9600);
  while (!Serial); // Esperar a que el monitor serie esté listo
  Serial.println("Adafruit PCF8574 LED blink test");

  // Selección interactiva de la placa
  int selectedBoard = -1;
  while (selectedBoard < 0 || selectedBoard > 3) {
    Serial.println("Selecciona la placa M a usar:");
    Serial.println("0: M0");
    Serial.println("1: M1");
    Serial.println("2: M2");
    Serial.println("3: M3");
    while (!Serial.available()); // Esperar entrada del usuario
    selectedBoard = Serial.parseInt();
  }

  // Selección interactiva de la parte (A o B)
  char selectedPart = 'X';
  while (selectedPart != 'A' && selectedPart != 'B') {
    Serial.println("Selecciona la parte a revisar:");
    Serial.println("A: Parte A");
    Serial.println("B: Parte B");
    while (!Serial.available()); // Esperar entrada del usuario
    selectedPart = toupper(Serial.read());
  }

  // Configurar dirección I2C y pin común según la selección
  uint8_t address;
  if (selectedPart == 'A') {
    address = I2C_ADDRESSES_A[selectedBoard];
    common_pin = COMMON_PINS_A[selectedBoard];
  } else {
    address = I2C_ADDRESSES_B[selectedBoard];
    common_pin = COMMON_PINS_B[selectedBoard];
  }

  // Inicializar el expansor IO de la parte seleccionada
  if (!IO_M.begin(address, &Wire)) {
    Serial.println("No se pudo encontrar el PCF8574 en la dirección seleccionada");
    while (1);
  }

  // Establecer como salida los 8 pines del expansor IO
  for (int i = 0; i < 8; i++) {
    IO_M.pinMode(i, OUTPUT);
  }

  pinMode(common_pin, OUTPUT);
  Serial.print("Placa M");
  Serial.print(selectedBoard);
  Serial.print(" parte ");
  Serial.print(selectedPart);
  Serial.println(" inicializada correctamente");
}

void setChannel(uint8_t channel) {
  if (channel > 15) {
    Serial.println("Canal fuera de rango (0-15)");
    return;
  }

  // Configurar pines 4-7 según el canal (en binario)
  for (int i = 0; i < 4; i++) {
    bool bit = (channel >> i) & 0x01;
    IO_M.digitalWrite(4 + i, bit);
  }

  Serial.print("Canal configurado: CH");
  Serial.println(channel);
}

void loop() {
  for (uint8_t channel = 0; channel < 16; channel++) {
    setChannel(channel);

    // Activar y desactivar el pin común
    digitalWrite(common_pin, HIGH);
    delay(500);
    digitalWrite(common_pin, LOW);
    delay(500);

    Serial.println("Cambiando al siguiente canal...");
  }
}
