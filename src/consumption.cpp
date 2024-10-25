#include <Arduino.h>
#include <EEPROM.h>
#include "display.hpp"

#define CONSUMPTION_PERIOD_MS 1000
#define AS_IN_AH 3600
#define AS_AH_RATIO 3600
#define AS_STORAGE_TRESHOLD 1000
#define EEPROM_ADDR_AS_STORAGE 0
#define EEPROM_ADDR_VIRGIN_FLAG 9
#define BUTTON_TRESHOLD 3
#define TRUE 0x01U
#define FALSE 0x00U

//#define TEST_TIMING_WITH_PB1 //ToDo: to be removed
//#define DISABLE_EEPROM_WHILE_TESTING

uint32_t ms_old = 0x00U; /* Previous miliseconds */
uint32_t As = 0x00U; /* AmperSeconds (in fact: real As * 10) */
uint32_t As_stored = 0x00U; /* AmperSeconds previously stored */
uint8_t button = 0x00U;

static void ConsumptionReset(void);
static void StoreConsumptionInEeprom(void);
static uint32_t EEPROMRead(uint32_t address);
static void EEPROMWrite(uint32_t address, uint32_t value);

/* Return AmperHours, store AmperSeconds in Eeprom */
uint16_t Consumption(uint16_t current)
{
  uint32_t ms = millis();
  uint16_t Ah = 0x00U;

  if(ms - ms_old >= CONSUMPTION_PERIOD_MS)
  {   
    #ifndef TEST_TIMING_WITH_PB1
    if(HIGH == digitalRead(PB1))
    {
      button++;
    }
    else
    {
      button = 0x00U;
    }
    #else
    digitalWrite(PB1, HIGH); //ToDo: to be removed
    #endif
    As += current;
    ms_old = ms;
    #ifdef TEST_TIMING_WITH_PB1
    digitalWrite(PB1, LOW); //ToDo: to be removed
    #endif
  }
  #ifndef TEST_TIMING_WITH_PB1
  if(button >= BUTTON_TRESHOLD)
  {
    DisplayReset();
    ConsumptionReset();
    button = 0x00U;
    delay(1000);
    DisplayClear();
  }
  #endif
  Ah = As/AS_AH_RATIO;
  StoreConsumptionInEeprom();

  return Ah;
}

/* Reset stored AmperSeconds after request (button) from user */
void ConsumptionReset(void)
{
  As = 0x00U;
  EEPROMWrite(EEPROM_ADDR_AS_STORAGE,As);
}

/* Read stored AmperSeconds from Eeprom at the start of program */
void ConsumptionReadFromEeprom(void)
{
  #ifdef TEST_TIMING_WITH_PB1
  digitalWrite(PB1, HIGH);//ToDo: to be removed
  #endif
  boolean isMemoryVirgin = EEPROM.read(EEPROM_ADDR_VIRGIN_FLAG);
  if(FALSE != isMemoryVirgin)
  {
    As = 0x00U;
  }
  else
  {
    As = EEPROMRead(0);
  }
  #ifdef TEST_TIMING_WITH_PB1
  digitalWrite(PB1, LOW); //ToDo: to be removed
  #endif
}

/* Function will store As in Eeprom if conditions are fulfilled */
static void StoreConsumptionInEeprom(void)
{
  if((As > 0x00U) && /* Consumption have to be larger than 0 */
    (As % (AS_IN_AH*10U) <= AS_STORAGE_TRESHOLD) && /* Consumption shall be updated every 1Ah with couple % treshold */
    (As_stored != As) && /* Consumption to be stored shall be different than previously stored value */
    (As - As_stored > ((AS_IN_AH*10U) - AS_STORAGE_TRESHOLD))) /* Consumption interval after previous storage shall be near 1Ah to prevent several writes with similar values */
  {
    /* With every incremented Ah store As in EEPROM */
    #ifdef TEST_TIMING_WITH_PB1
    digitalWrite(PB1, HIGH); //ToDo: to be removed
    #endif
    #ifndef DISABLE_EEPROM_WHILE_TESTING
    EEPROM.update(EEPROM_ADDR_VIRGIN_FLAG,0x00U);
    EEPROMWrite(EEPROM_ADDR_AS_STORAGE,As);
    #endif
    As_stored = As;
    #ifdef TEST_TIMING_WITH_PB1
    digitalWrite(PB1, LOW); //ToDo: to be removed
    #endif
  }
}

/* Read four byte variable */
static uint32_t EEPROMRead(uint32_t address) 
{
  uint32_t four = EEPROM.read(address);
  uint32_t three = EEPROM.read(address + 1);
  uint32_t two = EEPROM.read(address + 2);
  uint32_t one = EEPROM.read(address + 3);
  
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

/* Write four byte variable */
static void EEPROMWrite(uint32_t address, uint32_t value) 
{
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}
/* Last line empty */