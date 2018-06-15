// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

int loopCount = 0;

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

int numberOfTimesLunchDetectedInNumberOfLoops = 0;
int numberOfTimesBookDetectedInNumberOfLoops = 0;
int numberOfTimesWaterDetectedInNumberOfLoops = 0;

int nps_num_of_pixels_in_strip = 6;
int nps_din_pin = 6;
int lunchPixel = 4;
int bookPixel = 3;
int waterPixel = 2;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(nps_num_of_pixels_in_strip, nps_din_pin);

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Wire.setClock(400000);
  Serial.begin(115200);  // start serial for output
  strip.begin();
}

void loop() {
  Wire.requestFrom(8, 1);    // request 6 bytes from slave device #8
  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
//    Serial.print(c);         // print the character
    if (c == 'l') {
      numberOfTimesLunchDetectedInNumberOfLoops = numberOfTimesLunchDetectedInNumberOfLoops + 1;
      lunchDetected = 1;
    } else if (c == 'b') {
      numberOfTimesBookDetectedInNumberOfLoops = numberOfTimesBookDetectedInNumberOfLoops + 1;
      bookDetected = 1;
    } else if (c == 'w') {
      numberOfTimesWaterDetectedInNumberOfLoops = numberOfTimesWaterDetectedInNumberOfLoops + 1;
      waterDetected = 1;
    }
  }


  loopCount = loopCount + 1;
  if (loopCount == 500) {
    if (numberOfTimesLunchDetectedInNumberOfLoops < 1) {
      lunchNotDetectedCount = lunchNotDetectedCount + 1;
      if(lunchNotDetectedCount == 3){
        lunchDetected = 0;
        lunchNotDetectedCount = 0;
      } 
    } else {
        lunchDetected = 1;
        lunchNotDetectedCount = 0;
    }

    if(numberOfTimesBookDetectedInNumberOfLoops < 1) {
      bookNotDetectedCount = bookNotDetectedCount + 1;
      if(bookNotDetectedCount == 3){
        bookDetected = 0;
        bookNotDetectedCount = 0;
      }
    } else {
      bookDetected = 1;
      bookNotDetectedCount = 0;
    }

    if(numberOfTimesWaterDetectedInNumberOfLoops < 1) {
      waterNotDetectedCount = waterNotDetectedCount + 1;
      if(waterNotDetectedCount == 3){
        waterDetected = 0;
        waterNotDetectedCount = 0;
      }
    } else {
      waterDetected = 1;
      waterNotDetectedCount = 0;
    }
//    Serial.print("Lunch: ");
//    Serial.print(numberOfTimesLunchDetectedInNumberOfLoops);
//    Serial.print("Book: ");
//    Serial.print(numberOfTimesBookDetectedInNumberOfLoops);
//    Serial.print("Water: ");
//    Serial.print(numberOfTimesWaterDetectedInNumberOfLoops);
//    Serial.println();
//    Serial.print(loopCount);
//    Serial.println();
    numberOfTimesLunchDetectedInNumberOfLoops = 0;
    numberOfTimesBookDetectedInNumberOfLoops = 0;
    numberOfTimesWaterDetectedInNumberOfLoops = 0;
    loopCount = 0;
  }

  if(lunchDetected == 1){
      set_pixel(lunchPixel, 0, 5, 0);
  } else {
      set_pixel(lunchPixel, 5, 0, 0);
  }

  if(bookDetected == 1){
      set_pixel(bookPixel, 0, 5, 0);
  } else {
      set_pixel(bookPixel, 5, 0, 0);
  }

  if(waterDetected == 1){
      set_pixel(waterPixel, 0, 5, 0);
  } else {
      set_pixel(waterPixel, 5, 0, 0);
  }



} // end of main loop


void set_pixel(int num, int red, int green, int blue) {
    strip.setPixelColor(num, red, green, blue);
    strip.show();
}

