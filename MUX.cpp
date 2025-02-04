#include "MUX.h"
#include "Arduino.h"

MUX::MUX(void)
{
  Serial.println("pasamos por ac jejea");
  IO_A0.begin(IO_A0_ADDR, &Wire);
  Serial.println("A0");
  IO_A1.begin(IO_A1_ADDR, &Wire);
  Serial.println("A1");
  IO_A2.begin(IO_A2_ADDR, &Wire);
  Serial.println("A2");
  IO_A3.begin(IO_A3_ADDR, &Wire);
  Serial.println("A3");
  IO_B0.begin(IO_B0_ADDR, &Wire);
  Serial.println("B0");
  IO_B1.begin(IO_B1_ADDR, &Wire);
  Serial.println("B1");
  IO_B2.begin(IO_B2_ADDR, &Wire);
  Serial.println("B2");
  IO_B3.begin(IO_B3_ADDR, &Wire);
  Serial.println("B3");
}

bool MUX::set_adress_A(uint16_t addr)
{
  uint8_t addr_uint8_t = JAKast(addr);

  if (addr < 0x100) //valor máximo posible 0FF -- indica que estamos en M0
  {
    return (IO_A0.digitalWriteByte(addr_uint8_t));
  }
  else if (addr < 0x200) //valor máximo posible 1FF - indica que estamos en M1
  {
    return (IO_A1.digitalWriteByte(addr_uint8_t));
  }
  else if (addr < 0x300) //valor máximo posible 2FF - indica que estamos en M2
  {
    return (IO_A2.digitalWriteByte(addr_uint8_t));
  }
  else if (addr < 0x400) //valor máximo posible 3FF - indica que estamos en M3
  {
    return (IO_A3.digitalWriteByte(addr_uint8_t));
  }
  else
  {
    Serial.println("adddr out of range FAILURE A");
    return false;
  }
}

bool MUX::set_adress_B(uint16_t addr)
{
  uint8_t addr_uint8_t = JAKast(addr);

  if (addr < 0x100)
  {
    return (IO_B0.digitalWriteByte(addr_uint8_t));
  }
  else if (addr < 0x200)
  {
    return (IO_B1.digitalWriteByte(addr_uint8_t));
  }
  else if (addr < 0x300)
  {
    return (IO_B2.digitalWriteByte(addr_uint8_t));
  }
  else if (addr < 0x400)
  {
    return (IO_B3.digitalWriteByte(addr_uint8_t));
  }
  else
  {
    Serial.println("adddr out of range FAILURE B");
    return false;
  }
}

bool MUX::write_A(uint16_t addr)
{
  HiZ_A();
  if (set_adress_A(addr))
  {
    if (addr < 0x100)
    {
      pinMode(CH_A0, OUTPUT);
      digitalWrite(CH_A0, LOW);
      return true;
    }
    else if (addr < 0x200)
    {
      pinMode(CH_A1, OUTPUT);
      digitalWrite(CH_A1, LOW);
      return true;
    }
    else if (addr < 0x300)
    {
      pinMode(CH_A2, OUTPUT);
      digitalWrite(CH_A2, LOW);
      return true;
    }
    else if (addr < 0x400)
    {
      pinMode(CH_A3, OUTPUT);
      digitalWrite(CH_A3, LOW);
      return true;
    }
  }
  else
  {
    Serial.print("  Unable to set Adress_A   ");
  }
  return false;
}

bool MUX::write_B(uint16_t addr)
{
  HiZ_B();
  if(set_adress_B(addr))
  {
    if (addr < 0x100)
    {
      pinMode(CH_B0, OUTPUT);
      digitalWrite(CH_B0, LOW);
      return true;
    }
    else if (addr < 0x200)
    {
      pinMode(CH_B1, OUTPUT);
      digitalWrite(CH_B1, LOW);
      return true;
    }
    else if (addr < 0x300)
    {
      pinMode(CH_B2, OUTPUT);
      digitalWrite(CH_B2, LOW);
      return true;
    }
    else if (addr < 0x400)
    {
      pinMode(CH_B3, OUTPUT);
      digitalWrite(CH_B3, LOW);
      return true;
    }
  }
  else
  {
    Serial.print("  Unable to set Adress_B   ");
  }
  return false;
}

bool MUX::read_A(uint16_t addr)
{
  HiZ_A();
  if (set_adress_A(addr))
  {
    if (addr < 0x100)
    {
      return !digitalRead(CH_A0);
    }
    else if (addr < 0x200)
    {
      return !digitalRead(CH_A1);
    }
    else if (addr < 0x300)
    {
      return !digitalRead(CH_A2);
    }
    else if (addr < 0x400)
    {
      return !digitalRead(CH_A3);
    }
  }
  else
  {
    Serial.print("  Unable to set Adress_A   ");
  }
  return false;
}

bool MUX::read_B(uint16_t addr)
{
  HiZ_B();
  if (set_adress_B(addr))
  {
    if (addr < 0x100)
    {
      return !digitalRead(CH_B0);
    }
    else if (addr < 0x200)
    {
      return !digitalRead(CH_B1);
    }
    else if (addr < 0x300)
    {
      return !digitalRead(CH_B2);
    }
    else if (addr < 0x400)
    {
      return !digitalRead(CH_B3);
    }
  }
  else
  {
    Serial.print("  Unable to set Adress_B  ");
  }
  return false;
}

uint8_t MUX::JAKast(uint16_t addr)
{
  uint8_t addr_uint8_t = addr & 0x00FF;
}

void MUX::HiZ_A(void)
{
  pinMode(CH_A0, INPUT_PULLUP);
  pinMode(CH_A1, INPUT_PULLUP);
  pinMode(CH_A2, INPUT_PULLUP);
  pinMode(CH_A3, INPUT_PULLUP);
}

void MUX::HiZ_B(void)
{
  pinMode(CH_B0, INPUT_PULLUP);
  pinMode(CH_B1, INPUT_PULLUP);
  pinMode(CH_B2, INPUT_PULLUP);
  pinMode(CH_B3, INPUT_PULLUP);
}

bool MUX::test(uint16_t addr_A, uint16_t addr_B)
{
  HiZ_A();
  HiZ_B();
  write_A(addr_A);
  delay(10);
  return (read_B(addr_B));
}

/*MUX::~MUX()
{
}
*/