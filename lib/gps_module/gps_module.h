#ifndef D_GPS_MODULE_H
#define D_GPS_MODULE_H

#include <Arduino.h>
#include <TinyGPSPlus.h>
#include "SoftwareSerial.h"

class GpsModule
{
private:
    unsigned long _baudrate;
    int8_t _rx;
    int8_t _tx;
    SoftwareSerial serial;
    TinyGPSPlus _nmea_decoder;

public:
    GpsModule(int8_t rx, int8_t tx);
    ~GpsModule();
    void begin(uint32_t baudrate);
    void poll(void);
};

#endif