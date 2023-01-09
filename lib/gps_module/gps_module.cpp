#include "gps_module.h"

GpsModule::GpsModule(int8_t rx, int8_t tx)
    : _rx(rx), _tx(tx), _nmea_decoder(TinyGPSPlus())
{
}

GpsModule::~GpsModule()
{
}

void GpsModule::begin(uint32_t baudrate)
{
    serial.begin(baudrate,
                 SWSERIAL_8N1,
                 _rx,
                 _tx,
                 false,
                 256);
    serial.enableIntTx(false);
}

void GpsModule::poll(void)
{
    while (serial.available())
    {
        char byte = (char)serial.read();
        Serial.print(byte);
        if (_nmea_decoder.encode(byte))
        {
            if (_nmea_decoder.location.isValid())
            {
#ifdef DEBUG_LOG
                Serial.print(F("Location: "));
                Serial.print(_nmea_decoder.location.lat(), 6);
                Serial.print(F(","));
                Serial.print(_nmea_decoder.location.lng(), 6);
#endif
            }
        }
    }
}