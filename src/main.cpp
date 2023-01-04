/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "observer_module.h"

#define BLE_SCAN_INTERVALMS 100
#define BLE_SCAN_WINDOW 90
#define BLE_SCAN_TIME 5

ObserverModule observerModule = ObserverModule(BLE_SCAN_INTERVALMS,
                                               BLE_SCAN_WINDOW,
                                               BLE_SCAN_TIME);

void setup()
{
  Serial.begin(115200);
  Serial.println("Scanning...");
  observerModule.begin();
}

void loop()
{
  observerModule.poll();
  delay(2000);
}