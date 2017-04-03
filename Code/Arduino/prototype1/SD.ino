#include <SD.h>

File myFile;

void Save(String text){
  myFile = SD.open("data.txt", FILE_WRITE);

  //if the file opened okay, write to it
  if (myFile) {
    
    print("Writing to data.txt...");
    myFile.println(text);
    
    //close the file
    myFile.close();
    println("done.");
  
  } 
  
  else {
    
    //if the file didn't open, print an error
    println("error opening test.txt");
    
  }
}

void SD_setup(){
  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    return;
  }
  
  println("initialization done.");

  // print the headings for our data in the txt file

  // improvement: check if the headings already are in the file if they are then dont print
  Save("Time Movement Temperature Humidty CO2 IR 1 2 3 4 5 6 7 Dust 1.0 2.5 10");
}

String Concat(datetime current_time, bool movement, float * values){
  
  String result = String(current_time) + " " + String(movement);
  for( int i = 0; i < size(values); i++){
    result = result + " " + String(values[i]);
  }

  return result;
}


void SD_loop(datetime current_time, bool movement, float * values){
  String text = Concat(current_time, movement, values);
  Save(text);
}


void SD_test(){

  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    return;
  }
  
  println("initialization done.");

  //open the file. note that only one file can be open at a time, so you have to close this one before opening another. 
  //myFile = SD.open(test.txt, FILE_WRITE);

  //if the file opened okay, write to it
  if (myFile) {
    
    print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    
    //close the file
    myFile.close();
    println("done.");
  
  } 
  
  else {
    
    //if the file didn't open, print an error
    println("error opening test.txt");
    
  }

  //re-open the file for reading
  myFile = SD.open("TEST.TXT");

  if (myFile) {
    println("test.txt");

    //read from the file until there's nothing else in it
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    
    //close the file
    myFile.close();
  } 
  
  else {
    //if the file didn't open, print an error
    println("error opening test.txt");
  }
}

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

#include <SPI.h>

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// MKRZero SD: SDCARD_SS_PIN
const int chipSelect = 10;

void CheckSD() {
  // Open serial communications and wait for port to open:
  //Serial.begin(9600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }


  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    Serial.end();
    return;
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.print("\nCard type: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }


  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                            // SD card blocks are always 512 bytes
  Serial.print("Volume size (bytes): ");
  Serial.println(volumesize);
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);


  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
}
