#include <DigisparkOLED.h>
#include "auxiliary.hpp"

#define VOLTAGE_FOR_POWER_CALC 12

void DisplayValues(uint16_t value, char* buf);

/* Display initialization and startup text */
void DisplayInitialSetup(void)
{
    oled.begin();
    oled.clear();
    oled.setFont(FONT6X8);
    oled.setCursor(24, 0);
    oled.print("Electric");
    oled.setCursor(24, 1);
    oled.print("Motor");
    oled.setCursor(24, 2);
    oled.print("Power");
    oled.setCursor(24, 3);
    oled.print("Measurement");
}

/* Clear display */
void DisplayClear(void)
{
    oled.clear();
}

void DisplayVoltage(uint16_t voltage, char* buf)
{
    IntegerToChar(voltage, buf);
    oled.setCursor(0, 0);
    oled.print("Voltage: ");
    DisplayValues(voltage, buf);
    oled.setCursor(96, 0);
    oled.print("V");
}

void DisplayCurrent(uint16_t current, char* buf)
{
    IntegerToChar(current, buf);
    oled.setCursor(0, 1);
    oled.print("Current: ");
    DisplayValues(current, buf);
    oled.setCursor(96, 1);
    oled.print("A");
}

void DisplayPower(uint16_t current)
{
    uint16_t power = current * VOLTAGE_FOR_POWER_CALC;
    char bufDisp[BUFSIZE];
    ResetCharBuffer(bufDisp);
    IntegerToChar(power, bufDisp);
    oled.setCursor(0, 2);
    oled.print("Power:   ");
    DisplayValues(power, bufDisp);
    oled.setCursor(96, 2);
    oled.print("W");
}

void DisplayConsumption(uint16_t ah, char* buf)
{
    ResetCharBuffer(buf);
    IntegerToChar(ah, buf);
    oled.setCursor(0, 3);
    oled.print("Cons:    ");
    DisplayValues(ah,buf);
    oled.setCursor(96, 3);
    oled.print("Ah");
}

void DisplayValues(uint16_t value, char* buf)
{
    if(value >= 1000)
    {
        oled.print(buf[0]);
        oled.print(buf[1]);
        oled.print(buf[2]);
        oled.print(",");
        oled.print(buf[3]);
    }
    else if(value >= 100)
    {
        oled.print(0);
        oled.print(buf[0]);
        oled.print(buf[1]);
        oled.print(",");
        oled.print(buf[2]);
    }
    else if(value >= 10)
    {
        oled.print(0);
        oled.print(0);
        oled.print(buf[0]);
        oled.print(",");
        oled.print(buf[1]);
    }
    else
    {
        oled.print(0);
        oled.print(0);
        oled.print(0);
        oled.print(",");
        oled.print(buf[0]);
    }
}

void DisplayReset(void)
{
    oled.clear();
    oled.setCursor(24, 1);
    oled.print("Consumption");
    oled.setCursor(24, 2);
    oled.print("reset");
}

/* Last line empty */