#ifndef HEADER_DISPLAY
#define HEADER_DISPLAY

#include <DigisparkOLED.h>

void DisplayInitialSetup(void);
void DisplayClear(void);
void DisplayVoltage(uint16_t voltage, char* buf);
void DisplayCurrent(uint16_t current, char* buf);
void DisplayPower(uint16_t current);
void DisplayConsumption(uint16_t ah, char* buf);
void DisplayReset(void);

#endif /* HEADER_DISPLAY */
/* Last line empty */