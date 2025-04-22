// Written by: Zach Winters
// Last Edited: 4/22/2025
// TEC 284 Magic 8 Ball

//Arduino references can be found at: https://www.arduino.cc/reference/en/

//Necessary library files for the OLED and Accelerometer. Do not edit or delete!

#include <Arduino.h>
#include <U8x8lib.h>
#include "LIS3DHTR.h"

#ifdef SOFTWAREWIRE
#include <SoftwareWire.h>
SoftwareWire myWire(3, 2);
LIS3DHTR<SoftwareWire> LIS;  //Software I2C
#define WIRE myWire
#else
#include <Wire.h>
LIS3DHTR<TwoWire> LIS;  //Hardware I2C
#define WIRE Wire
#endif

//Defining a structure named "Data" to store variables 
struct Data {
  int resultNum;
  String outcomes;
  String mood;
};

//Creating an array contained by my previously defined Structure "Data"
Data outcomes[10]{

  { 1, "For Sure!", "Positive" },
  { 2, "Yes", "Positive" },
  { 3, "Definitely!", "Positive" },
  { 4, "Maybe", "Neutral" },
  { 5, "Not Sure..", "Neutral" },
  { 6, "Ask Later", "Neutral" },
  { 7, "I'm Tired", "Neutral" },
  { 8, "No Way!", "Negative" },
  { 9, "No", "Negative" },
  { 10, "Nope", "Negative" },
};

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/U8X8_PIN_NONE);  //do not delete

//Setup loop to ensure the OLED and other processes actually start
void setup() {

  LIS.begin(WIRE, 0x19);  //I2C init -- do not delete

  //debug below
  Serial.begin(9600);
  u8x8.begin();
  u8x8.setFlipMode(1);
  u8x8.clear();
}
//Loop to randomize the outcomes from the arrays as well as enabling a 2 second delay, ensuring that processes run more than once
void loop() {

  u8x8.setFont(u8x8_font_chroma48medium8_r);  //do not edit or delete
  u8x8.setCursor(0, 0);
  if (LIS.getAccelerationZ() > 2) {  //If the Grove board is shaken

    u8x8.clear();
    int randomOutcome = random(1, 10);
    u8x8.println(outcomes[randomOutcome].outcomes);
    u8x8.println(outcomes[randomOutcome].mood);
    u8x8.println(outcomes[randomOutcome].resultNum);
    delay(2000);
  } else {
    u8x8.clear();
  }
}
