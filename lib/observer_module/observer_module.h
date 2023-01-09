#ifndef D_OBSERVER_H
#define D_OBSERVER_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEBeacon.h>
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
    /**
     * @brief Construct a new Observer Module object
     *
     * @param intervalMSecs
     * @param windowMSecs
     * @param duration
     */
    ObserverModule(uint16_t intervalMSecs, uint16_t windowMSecs, uint32_t duration);
    /**
     * @brief Destroy the Observer Module object
     *
     */
    ~ObserverModule();
    /**
     * @brief
     *
     */
    void begin(void);
    /**
     * @brief
     *
     */
    void poll(void);
};

#endif