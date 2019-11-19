/*
   https://circuits4you.com
   2016 November 25
   Load Cell HX711 Module Interface with Arduino to measure weight in Kgs
  Arduino
  pin
  2 -> HX711 CLK
  3 -> DOUT
  5V -> VCC
  GND -> GND

  Most any pin on the Arduino Uno will be compatible with DOUT/CLK.
  The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
*/

#include "HX711.h"  //You must have this library in your arduino library folder

#define DOUT  33
#define CLK  34
const long LOADCELL_OFFSET =  10682624;
const long LOADCELL_DIVIDER = 5895655;
HX711 scale;

//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
//float calibration_factor = -96650; //-106600 worked for my 40Kg max scale setup

//=============================================================================================
//                         SETUP
//=============================================================================================
void setup() {
  Serial.begin(9600);
  scale.begin(DOUT,CLK);
  scale.set_scale(LOADCELL_DIVIDER);
  scale.set_offset(LOADCELL_OFFSET);
  scale.tare();
  // Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  // Serial.println(zero_factor);
}

//=============================================================================================
//                         LOOP
//=============================================================================================
void loop() {

  Serial.println(max(min(scale.get_units()*3,.2),0) , 6);

}
