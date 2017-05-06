
#include <SoftwareSerial.h>
SoftwareSerial dustport(8,9);

void DUST_setup() {
  dustport.begin(9600);
  
}

//
//void show(String environment, String particle_size){
//  Serial.print(environment + ", PM " + particle_size + " = ");
//  Serial.print(calc_pm());
//  Serial.println(" ug/m3");
//}

byte c;
  
long calc_pm(){ 
  return 256 *( 2 * c);
}


long pm1;

//pm 2.5
long pm25;

//pm 10
long pm10;

// look into difference between atmosphere and the cm values
#define Sep( val ) val + ","

int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

String DUST_loop() {

  int count = 0;

 while (dustport.available()) {
    c = dustport.read();

    Serial.print("Free Ram: ");
    Serial.println(freeRam());
    if((count==0 && c!=0x42) || (count==1 && c!=0x4d)){
      Serial.println(F("check failed"));
    }

    if(count == 11){
      pm1 = calc_pm();
    }
    else if(count == 13){
      pm25 = calc_pm();
    }
    else if(count == 15){
      pm10 = calc_pm();


    }
    if(count > 15){
      Serial.println(F("complete"));

      if(pm1 && pm25 && pm10){
        return Sep(String(pm1)) + Sep(String(pm25)) + String(pm10);
      }
      else{
        return F("null,null,null");
      }

    }

//    check_mem();

   
//    char text[30];
//    sprintf(text, "heap memory: %p\n", heapptr);
//    Serial.println(text);
//    sprintf(text, "stack memory: %p\n", stackptr);
//    Serial.println(text); 

    count++;
  }


  while(dustport.available()) dustport.read();
  Serial.println();
  delay(5000);
}

