//-----------------------------------------------------//
//-------[TESTING MASTER - Tester de Ramales V2]-------//
//-------------[(1) FAST CHANNEL TESTING]--------------//
//----------------------------------------------------//

// Testeo de barrido automático Canal a Canal en primera etapa
// Usuario debe ingresar instrucción para comenzar


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

//----------------------------------------------------//
//----------------[Función setChannel]----------------//
//----------------------------------------------------//
// Transforma en binario el canal seleccionado
// Se escribe cada bit en los pines 4,5,6,7 del IO expander
void setChannel(uint8_t channel) {
  for (int i = 0; i < 4; i++) {
    IO_M.digitalWrite(4 + i, (channel >> i) & 0x01);
  }
  Serial.print("Canal configurado: CH");
  Serial.println(channel);
}

//----------------------------------------------------//
//------------[Función selectBoardAndPart]------------//
//----------------------------------------------------//
// Función interactiva con el usuario para iniciar
// el testeo de canales automático
void selectBoardAndPart() {
  while (true) {
    Serial.println("Selecciona la placa M a usar (0-3):");
    while (!Serial.available());
    selectedBoard = Serial.parseInt();
    if (selectedBoard >= 0 && selectedBoard <= 3) break;
    Serial.println("Placa inválida, intenta nuevamente.");
  }

  while (true) {
    Serial.println("Selecciona la parte a revisar:");
    Serial.println("A: Parte A");
    Serial.println("B: Parte B");
    while (!Serial.available());
    selectedPart = toupper(Serial.read());
    if (selectedPart == 'A' || selectedPart == 'B') break;
    Serial.println("Opción inválida, intenta nuevamente.");
  }

  // Asignación de direcciones y CHAN_XX según lo -----//
  // seleccionado por el usuario ----------------------//
  uint8_t address = (selectedPart == 'A') ? I2C_ADDRESSES_A[selectedBoard] : I2C_ADDRESSES_B[selectedBoard];
  common_pin = (selectedPart == 'A') ? COMMON_PINS_A[selectedBoard] : COMMON_PINS_B[selectedBoard];

  if (!IO_M.begin(address, &Wire)) {
    Serial.println("No se pudo encontrar el PCF8574 en la dirección seleccionada");
    while (1);
  }
  
  // Asigna como "salidas" los pines del IO -----------//
  for (int i = 0; i < 8; i++) {
    IO_M.pinMode(i, OUTPUT);
  }
  
  // Asigna como "salidas" los CHAN XX del arduino ----//
  pinMode(common_pin, OUTPUT);
  Serial.print("Placa M");
  Serial.print(selectedBoard);
  Serial.print(" parte ");
  Serial.print(selectedPart);
  Serial.println(" inicializada correctamente");
}


//----------------------------------------------------//
//------------[Función testing_automatico]------------//
//----------------------------------------------------//
void testing_automatico() {
  selectBoardAndPart();
  
  // Paso automático por todos los canales -----------//
  for (uint8_t channel = 0; channel < 16; channel++) {
    setChannel(channel);
    // Efecto ON-OFF para testear el canal con LED ---//
    digitalWrite(common_pin, HIGH);
    delay(500);
    digitalWrite(common_pin, LOW);
    delay(500);
    Serial.println("Cambiando al siguiente canal...");
  }

  while (true) {
    Serial.println("¿Quieres revisar otra placa? (Y/N)");
    while (!Serial.available());
    char response = toupper(Serial.read());
    if (response == 'Y') {
      testing_automatico();
      return;
    }
    if (response == 'N') {
      Serial.println("Finalizando Testing Automático.");
      return;
    }
  }
}
