#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
//
////display address 0x3C
//
SSD1306AsciiWire oled;
//
////bool OLED_connected = false;
//
//// we delay the time until the screen gets cleared so that people can read the data
// might need to use interrupts for this at some point so it doesn't bottleneck
// void delay_clear(){
//   // wait a few milliseconds
//   delay(2000);
//   oled.clear();
// }
//
// bool OLED_connected = false;
//
//// these two functions are exactly the same just with different types, see if theres a way to merge
//void show(const __FlashStringHelper *message){
//
//  if(OLED_connected){
//    delay_clear();
//    oled.print(message);
//  }
//  
//}

// char the_char;

// this function reads a char array from flash memory and displays each character one by one

// consider replacing this whole thing with a macro that wraps strcpy_P and PRGMSTR to save even more space
void flash_show(char data[]){

  delay(2000);
  oled.clear();

  int len = strlen_P(data);
  for(int k = 0; k < len; k++){
      // the_char = pgm_read_byte_near(data + k);
      oled.print((char)pgm_read_byte_near(data + k));
  }
}


// remove flag and replace with calls to flash_show

// put in callbacks to the flash string retriever or get it to stream somehow

void show(char data[]){
    
  // if(OLED_connected){
  delay(2000);
  oled.clear();

  oled.print(data);
}

// my attempt to make my own format function
// void showf(size_t size, char format[], int value){
//   snprintf_P(Buffer, 5, PSTR("%d"), CO2);
//   show(Buffer);
// }
//
//// to make text bigger use oled.set2X();
//// to undo use oled.set1X();

void OLED_setup(){

  // if it returns 0 then the screen exists
  // OLED_connected = Wire.endTransmission() == 0;

  // if(OLED_connected){
  // delay(1000);
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(TimesNewRoman16);

  // show_P("");

  //! Check to see if these can be on screen at same time

  // release the ASCII dragon
  // show_P("     ,.
  //            /,,;';;.  ,;;;..  ,,;.    '
  //          .',''   `::;:' ``;;;;'  `..'
  //          `      ,,/'     ,,//         ");
  show_P("SKOMOBO");
 //? maybe get a better dragon ask Chris?
  // show_P("SKOMOBO\n     ,.\n   /,,;';;.  ,;;;..  ,,;.    '\n .',''   `::;:' ``;;;;'  `..'\n `      ,,/'     ,,//         ");

}
