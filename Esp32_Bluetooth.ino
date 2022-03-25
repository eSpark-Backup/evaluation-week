//#include <dummy.h>
//
//
//#include "BluetoothSerial.h"
//
///* Check if Bluetooth configurations are enabled in the SDK */
///* If not, then you have to recompile the SDK */
//#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
//#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
//#endif
//
//BluetoothSerial SerialBT;
//
//void setup() {
//  Serial.begin(115200);
//  /* If no name is given, default 'ESP32' is applied */
//  /* If you want to give your own name to ESP32 Bluetooth device, then */
//  /* specify the name as an argument SerialBT.begin("myESP32Bluetooth"); */
//  SerialBT.begin();
//  Serial.println("Bluetooth Started! Ready to pair...");
//}
//
//void loop() {
//  if (Serial.available())
//  {
//    SerialBT.write(Serial.read());
//  }
//  if (SerialBT.available())
//  {
//    Serial.write(SerialBT.read());
//  }
//  delay(20);
//}

/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleWrite.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"


const int dirPin = 16;
const int stepPin = 17;
const int stepsPerRevolution = 500;
int stepDelay=2000;


class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value: ");
        
        for (int i = 0; i < value.length(); i++)
          { 
             Serial.print(value[i]);
          }
        
        Serial.print(value[0]);
        
        //Motor spiining in clockwise
        if (value[0] == 'A')
        digitalWrite(dirPin, HIGH);

        else
        {
          stepDelay = (int)((value[3]<<1) || (value[2]<<2) || (value[1]<<1) | (value[3]<<0));
          Serial.print(stepDelay);
        }
     
        if (value[0] == 'B')
        digitalWrite(dirPin, LOW);

        else
        {
          stepDelay = (int)((value[3]<<1) || (value[2]<<2) || (value[1]<<1) | (value[3]<<1));
          Serial.print(stepDelay);
        }
        
        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {
  
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  Serial.begin(115200);

  Serial.println("1- Download and install an BLE scanner app in your phone");
  Serial.println("2- Scan for BLE devices in the app");
  Serial.println("3- Connect to MyESP32");
  Serial.println("4- Go to CUSTOM CHARACTERISTIC in CUSTOM SERVICE and write something");
  Serial.println("5- See the magic =)");

  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  //Motor spiining in clockwise
  //if (main_value != 'A')
  //digitalWrite(dirPin, HIGH);
  
  // Motor Spinning Loop
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
  
  delay(2000); // Wait 2 seconds
  
  //counterclockwise
  //if (main_value == 'A')
  //digitalWrite(dirPin, LOW);
  
  // Motor Spinning Loop
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }

  delay(2000); // Wait 2 seconds
  Serial.println(stepDelay);
}
