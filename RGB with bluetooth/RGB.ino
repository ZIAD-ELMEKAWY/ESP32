// Includes 
#include "BluetoothSerial.h"

// Bluetooth configuration
String device_name = "ESP32-Z";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;


int greenPin = 15 ;
int redPin   = 2 ;
int bluePin  = 4 ;

void setup() {
  // put your setup code here, to run once:
  pinMode(greenPin , OUTPUT);
  pinMode(redPin , OUTPUT);
  pinMode(bluePin , OUTPUT);

  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

}
void loop() {
  
  while(1)
  {
    if (SerialBT.available()) {
      char cmd = SerialBT.read() ;
      if('g' == cmd)
      {
        // Turn on red
        Serial.println("Green");
        analogWrite(redPin, 255);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 0);
        delay(1000); // Wait for 1 second
      }
      else if ('b' == cmd)
      {
        // Turn on green
        Serial.println("Blue");
        analogWrite(redPin, 0);
        analogWrite(greenPin, 255);
        analogWrite(bluePin, 0);
        delay(1000); // Wait for 1 second
      }
      else if ('r' == cmd)
      {
        // Turn on blue
        Serial.println("Red");
        analogWrite(redPin, 0);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 255);
        delay(1000); // Wait for 1 second
      }
      else if ('c' == cmd)
      {
        // Turn on Cyan (green + blue)
        Serial.println("Yellow");
        analogWrite(redPin, 255);
        analogWrite(greenPin, 255);
        analogWrite(bluePin, 0);
        delay(1000); // Wait for 1 second
      }
      else if ('y' == cmd)
      {
        // Turn on cyan (red + green)
        Serial.println("Yellow");
        analogWrite(redPin, 255);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 255);
        delay(1000); // Wait for 1 second
      }
      else if ('w' == cmd)
      {
        // Turn on white (red + green + blue)
        Serial.println("White");
        analogWrite(redPin, 255);
        analogWrite(greenPin, 255);
        analogWrite(bluePin, 255);
        delay(1000); // Wait for 1 second
      }
      else
      {
        Serial.println("Close");
        analogWrite(redPin, 0);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 0);
      }
    }
  }
  
}


