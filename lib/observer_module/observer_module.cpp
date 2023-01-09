#include "observer_module.h"

#define OBSERVER_NAME "GATEWAY"

#define ENDIAN_CHANGE_U16(x) ((((x)&0xFF00) >> 8) + (((x)&0xFF) << 8))

class ScanResponseCallback : public BLEAdvertisedDeviceCallbacks
{
    bool isIbeacon(std::string strManufacturerData)
    {
        uint8_t cManufacturerData[100];
        strManufacturerData.copy((char *)cManufacturerData, strManufacturerData.length(), 0);
        return (strManufacturerData.length() == 25 && cManufacturerData[0] == 0x4C && cManufacturerData[1] == 0x00);
    }

    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
        std::string strManufacturerData = advertisedDevice.getManufacturerData();
        if (isIbeacon(strManufacturerData))
        {
            BLEBeacon oBeacon = BLEBeacon();
            oBeacon.setData(strManufacturerData);
#ifdef DEBUG_LOG
            Serial.printf("ID: %04X\n", oBeacon.getManufacturerId());
            Serial.printf("Major: %d\n", ENDIAN_CHANGE_U16(oBeacon.getMajor()));
            Serial.printf("Minor: %d\n", ENDIAN_CHANGE_U16(oBeacon.getMinor()));
            Serial.printf("UUID: %s\n", oBeacon.getProximityUUID().toString().c_str());
            Serial.printf("RSSI: %d\n", oBeacon.getSignalPower());
#endif
        }
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