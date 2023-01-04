#ifndef D_OBSERVER_H
#define D_OBSERVER_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <stdint.h>

class ObserverModule
{
private:
    uint16_t _intervalMSecs;
    uint16_t _windowMSecs;
    uint32_t _duration;
    BLEScan *_pBLEScan;
    BLEAdvertisedDeviceCallbacks *_scanResponseCallback;
    BLEScanResults _foundDevices;

public:
    ObserverModule(uint16_t intervalMSecs, uint16_t windowMSecs, uint32_t duration);
    ~ObserverModule();
    void begin(void);
    void poll(void);
};

#endif