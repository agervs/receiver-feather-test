// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

int lunchDetected = 0;
int bookDetected = 0;
int waterDetected = 0;
int numberOfTimesLunchDetected = 0;
int numberOfTimesBookDetected = 0;
int numberOfTimesWaterDetected = 0;
int lunchNotDetectedCount = 0;
int bookNotDetectedCount = 0;
int waterNotDetectedCount = 0;
int lunchDetectedThroughThisLoop;
int bookDetectedThroughThisLoop;
int waterDetectedThroughThisLoop;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 1);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
//    Serial.print(c);         // print the character
    if (c == 'l') {
      Serial.println("lunch detected");
    } else if (c == 'b') {
      Serial.println("book detected");  
    } else if (c == 'w') {
      Serial.println("water detected");  
    }
  }
//  Serial.println();
}
