#include "auxiliary.hpp"
#include "consumption.hpp"
#include "display.hpp"

//#define TEST_TIMING_WITH_PB1 //ToDo: to be removed

#define ADC_CURR_MIN 511U
#define ADC_CURR_TRESHOLD 8U

char  buf[BUFSIZE];

void setup() 
{
  pinMode(A2, INPUT); /* Voltage input */
  pinMode(A3, INPUT); /* Current input */
  #ifdef TEST_TIMING_WITH_PB1
  pinMode(PB1,OUTPUT); //ToDo: to be removed
  #else
  pinMode(PB1, INPUT);
  #endif

  DisplayInitialSetup();
  ConsumptionReadFromEeprom();
  _delay_ms(2000);
  DisplayClear();
}

void loop() 
{
  uint16_t test_voltage_in = analogRead(A2);
  uint16_t test_current_in = analogRead(A3);
  uint16_t test_voltage_out = map(test_voltage_in,0,1023,0,250);
  uint16_t test_current_out = 0x00U;
  if((ADC_CURR_MIN + ADC_CURR_TRESHOLD) <= test_current_in)
  {
    test_current_out = map(test_current_in,ADC_CURR_MIN,1023,0,1000);
  }

  DisplayVoltage(test_voltage_out, buf);

  DisplayCurrent(test_current_out, buf);

  DisplayPower(test_current_out);

  uint16_t ah = Consumption(test_current_out);
  DisplayConsumption(ah, buf);    
}

