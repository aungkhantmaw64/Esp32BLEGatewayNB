/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/
#include <Arduino.h>
#include "YACL.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#include "observer_module.h"
#include "gps_module.h"

#define BLE_SCAN_INTERVALMS 100
#define BLE_SCAN_WINDOW 90
#define BLE_SCAN_TIME 5

#define BLE_TASK_BLOCKED_PERIOD_MS 1000
#define BLE_TASK_STACK_SIZE 2000

#define GPS_TASK_BLOCKED_PERIOD_MS 1000
#define GPS_TASK_STACK_SIZE 2000
#define GPS_RX 18
#define GPS_TX 19
#define GPS_BAUDRATE 9600

static ObserverModule observerModule(BLE_SCAN_INTERVALMS,
                                     BLE_SCAN_WINDOW,
                                     BLE_SCAN_TIME);

static GpsModule gpsModule(GPS_RX, GPS_TX);

static TaskHandle_t xBeaconTaskHandle = NULL;
static TaskHandle_t xGpsTaskHandle = NULL;

static void vBeaconScanTask(void *pvParameters)
{
  while (1)
  {
    observerModule.poll();
    vTaskDelay(BLE_TASK_BLOCKED_PERIOD_MS / portTICK_RATE_MS);
  }
  vTaskDelete(NULL);
}

static void vGPSReadTask(void *pvParameters)
{
  while (1)
  {
    gpsModule.poll();
    vTaskDelay(GPS_TASK_BLOCKED_PERIOD_MS / portTICK_RATE_MS);
  }
  vTaskDelete(NULL);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Scanning...");
  observerModule.begin();
  gpsModule.begin(GPS_BAUDRATE);

  xTaskCreate(vBeaconScanTask,
              "BeaconScan",
              BLE_TASK_STACK_SIZE,
              NULL,
              0,
              &xBeaconTaskHandle);

  xTaskCreate(vGPSReadTask,
              "GpsRead",
              GPS_TASK_STACK_SIZE,
              NULL,
              0,
              &xGpsTaskHandle);
}

void loop()
{
}
