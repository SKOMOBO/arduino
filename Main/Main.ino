#include <Wire.h>

// all our own definitions
#include "definitions.h"

#include <avr/pgmspace.h>



// // this function assumes we are using the global buffer
// void layout(char format[], ...){
//   va_list args;
//   sprintf_P(Buffer, format, args);
// }

void setup(){

  Serial.begin(115200);

  // setup all the modules
  OLED_setup();
  SD_setup();
  PIR_setup();
  CO2_setup();
  Dust_setup();
  Temp_setup();
  Time_setup();

  //  Wifi_setup();
  // WIFI_setup();
  TCP_setup();
}

void loop() {

  // collect the data and store globally
  Time_loop();
  PIR_loop();
  Temp_loop();
  CO2_loop();
  Dust_loop();

  // save the data
  Save_sensors();

}
