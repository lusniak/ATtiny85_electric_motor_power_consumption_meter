
# 12V battery power meter

Device based on Attiny85 which measures voltage, current, calculates power and power consumption in time of 12V battery.
Device shall be connected in series with battery and load e.g. boat trolling motor and battery + ground wire for voltage measurement.
Device is powered from measured battery. It uses non-volatile memory to store calculated power consumption (specified in Ah's) between power cycles.
For current measurement ACS758 module is used and for voltage measurement - voltage divider.
Informations are displayed on OLED 128x64px display controlled over I2C bus.




![](https://github.com/lusniak/attiny85_digispark_resurrection/blob/main/device_ready.PNG)

