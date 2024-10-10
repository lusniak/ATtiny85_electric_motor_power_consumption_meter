#include <Arduino.h>
#include "auxiliary.hpp"

/* Return char array with digits from provided int variable */
char* IntegerToChar(int i, char *p)
{
    if (i / 10 == 0) 
    {
        // No more digits.
        *p++ = i + '0';
        *p = '\0';
        return p;
    }

    p = IntegerToChar(i / 10, p);
    *p++ = i % 10 + '0';
    *p = '\0';

    return p;
}

/* Resets char array with 0 values */
void ResetCharBuffer(char* buffer)
{
  for(uint8_t i=0; i<=BUFSIZE-1; i++)
  {
    buffer[i] = '0';
  }
}
/* Last line empty */