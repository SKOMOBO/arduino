/*
  WiFiEsp example: Webclient2Repeating

  This sketch connects to a web server and makes an HTTP request
  using an Arduino ESP8266 module.
  It repeats the HTTP call each 10 seconds.

  For more details see: http://yaab-arduino.blogspot.com/p/wifiesp.html
*/

#include "src/WiFiEsp.h"


// make a macro that stores all these strings in flash and then reads out char arrays at runtime?
// make a seperate function that constructs the array using the one that reads out individual chars

char ssid2[] = HOTSPOT;            // your network SSID (name)

int status2 = WL_IDLE_STATUS;     // the Wifi radio's status

unsigned long lastConnectionTime2 = 0;         // last time you connected to the server, in milliseconds
const unsigned long postingInterval2 = 10000L; // delay between updates, in milliseconds

// Initialize the Ethernet client2 object
WiFiEspClient client2;


/// Move the ssid and password out of global spacec use same trick as the http formatting

void TCP_connect(){
  // attempt to connect to WiFi network

  // attept to connect to AP

  show_P("Configuring\nWIFI card");
  // initialize ESP module
  WiFi.init(&Serial);

  show_P("Connecting\n to AP");

  strncpy_P(Buffer, PSTR(PASSWORD), 11);
  status2 = WiFi.begin(ssid2, Buffer);
  
  for(int i=0; i<5; i++){
    if(status2 == WL_CONNECTED){
      show_P("Connected\n to AP");
      break;
    }
    else{
      // Connect to WPA/WPA2 network
      status2 = WiFi.begin(ssid2, Buffer);
    }
  }
  
}

void TCP_setup()
{

  // show_P("Configuring\nWIFI card");
  // // initialize ESP module
  // WiFi.init(&Serial);

  TCP_connect();

  // put in proper retrys here
  // check for the presence of the shield

  show_P("Checking\n WIFI card");
  if (WiFi.status() == WL_NO_SHIELD) {
    show_P("WiFi card\n not present");

    // fix this to be like old code ie reboot after one send etc
  }

}


// merge this function with the http request one g

void TCP_send()
{
 
  // if 10 seconds have passed since your last connection,
  // then connect again and send data
  if (millis() - lastConnectionTime2 > postingInterval2) {

    tcpRequest();
  }
}



// use other code for own at commands etc to see how to send real values

// void reboot_connection()

void send_data2(){
   // if there's a successful connection

  show_P("Sending data\nto server");
  
  // first value in formatting string is to say it is an arduino
  snprintf_P(Buffer, 65, PSTR("0_" BOX_ID "_%d-%d-%d-%d-%d-%d_%d_%d_%d_%d.%d_%d.%d_%d_%c\n"),  year, month, day, hour, minute, second, PM1, PM25, PM10,(int)temperature, (int)(temperature * 100) % 100, (int)humidity, (int)(humidity * 100) % 100, CO2, PIR);
  client2.print(Buffer);

  show_P("Data sent");
  // client2.println();

  // note the time that the connection was made
  lastConnectionTime2 = millis();

}

// this method makes a HTTP connection to the server
void tcpRequest()
{
  // close any connection before send a new request
  // this will free the socket on the WiFi shield

  // move this to bottom for my own protocol
  client2.stop();

  show_P("Connecting\n to server");

  strncpy_P(Buffer, PSTR("54.66.202.130"), 14);
  if (client2.connect(Buffer, 80)) {

    send_data2();

  }else{
    show_P("Server\nconnection\nlost");

    // WiFi.init(&Serial);
    TCP_connect();
  }
  
#ifndef WIFI_CONNECTION_TEST
  delay(6000);
#else
  client2.stop();
  delay(3000);
  strncpy_P(Buffer, PSTR("192.168.0.101"), 14);
  if (client2.connect(Buffer, 10000)) {
    send_data2();
    //snprintf_P(Buffer, 11, PSTR("DAEIN_TEST"));
    //client2.print(Buffer);
    show_P("local Data sent");
  }  
  delay(3000);
#endif

}
