#include <SoftwareSerial.h>
SoftwareSerial dustport(8,9);

void Dust_setup() {
  //for the arduino mega use serial1 instead of software serial
  //Serial1.begin(9600);
  
  dustport.begin(9600);
  
}

#define receiveDatIndex 24 // Sensor data payload size

//Variable declarations
byte receiveDat[receiveDatIndex]; //receive data from the air detector module
boolean valid_data;
unsigned int checkSum,checkresult;


void readDust(){

  // wait until we receive data!!!!? this is cause of hang probably

  // convert to if statement
  if (dustport.peek()!=66){
    receiveDat[0]=dustport.read();
  }

  dustport.readBytes((char *)receiveDat,receiveDatIndex);
  checkSum = 0;
  for (int i = 0;i < receiveDatIndex;i++){
    checkSum = checkSum + receiveDat[i];
  }
  checkresult = receiveDat[receiveDatIndex-2]*256+receiveDat[receiveDatIndex-1]+receiveDat[receiveDatIndex-2]+receiveDat[receiveDatIndex-1];
  valid_data = (checkSum == checkresult);
}

byte getData(unsigned int index){

// returns 0 if invalid
  if(valid_data){
    return (receiveDat[index]*256)+receiveDat[index + 1];
  }
  else{
    return 0;
  }
}

void Dust_loop(){

  readDust();
  PM1 = (receiveDat[4]*256)+receiveDat[5];
  PM25 = (receiveDat[6]*256)+receiveDat[7];
  PM10 = (receiveDat[8]*256)+receiveDat[9];
//  String message1 = String(PM1) + F(",") + String(PM25) + F(",") + String(PM10);
//  return message1;
  
 }
  

