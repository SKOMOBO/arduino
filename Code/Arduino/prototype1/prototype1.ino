
#include <SPI.h>

void print(String words){
  Serial.print(words);
}

void println(String words){
  Serial.println(words);
}

#include <Wire.h>
//#include "WSWire.h"
//U#include "I2C.h"

//#include "Startup.h"

void setup() {
 
  Serial.begin(9600);

//    PIR_setup();

//  IR_setup();
//  CO2_setup();
//  DUST_setup();
//  TEMP_setup();

//  SD_setup();

  ScanI2CBus();
   
  //Time_setup();

  //CheckSD();
//  sd();
   
  //I2c.scan();
  
  while (!Serial) {
    //;  wait for serial port to connect. Needed for native USB port only
  }

 
}

void loop() {
//  OLED();
// IR_loop();

//  PIR_loop();

//  DUST_loop();
//  SD_Loop();
//  CO2_loop();

//  Temp_loop();

//  Time_loop();

  // feed all the other loops in here or variables
  //SD_loop();

  delay(1000);
}
