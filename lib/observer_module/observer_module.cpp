#include "observer_module.h"

#define OBSERVER_NAME "GATEWAY"

class ScanResponseCallback : public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
    }
};

ObserverModule::ObserverModule(uint16_t intervalMSecs, uint16_t windowMSecs, uint32_t duration)
    : _intervalMSecs(intervalMSecs),
      _windowMSecs(windowMSecs),
      _duration(duration),
      _pBLEScan(nullptr),
      _scanResponseCallback(nullptr)
{
}

ObserverModule::~ObserverModule()
{
    delete _scanResponseCallback;
}

void ObserverModule::begin()
{
    BLEDevice::init(OBSERVER_NAME);
    _scanResponseCallback = new ScanResponseCallback();
    _pBLEScan = BLEDevice::getScan();
    _pBLEScan->setActiveScan(true); // active scan uses more power, but get results faster
    _pBLEScan->setInterval(_intervalMSecs);
    _pBLEScan->setWindow(_windowMSecs); // less or equal setInterval value
    _pBLEScan->setAdvertisedDeviceCallbacks(_scanResponseCallback);
}

void ObserverModule::poll(void)
{

    _foundDevices = _pBLEScan->start(_duration, false);
#ifdef DEBUG_LOG
    for (auto i{0}; i < _foundDevices.getCount(); i++)
    {
        BLEAdvertisedDevice tempDevice = _foundDevices.getDevice(i);
        Serial.print("Address: ");
        Serial.println(tempDevice.getAddress().toString().c_str());
        Serial.print("RSSI: ");
        Serial.println(tempDevice.getRSSI());
    }
#endif
    _pBLEScan->clearResults();
}