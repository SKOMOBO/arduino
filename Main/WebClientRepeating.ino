/*
  WiFiEsp example: WebClientRepeating

  This sketch connects to a web server and makes an HTTP request
  using an Arduino ESP8266 module.
  It repeats the HTTP call each 10 seconds.

  For more details see: http://yaab-arduino.blogspot.com/p/wifiesp.html
*/

#include "src/WiFiEsp.h"


// make a macro that stores all these strings in flash and then reads out char arrays at runtime?
// make a seperate function that constructs the array using the one that reads out individual chars

char ssid[] = HOTSPOT;            // your network SSID (name)

int status = WL_IDLE_STATUS;     // the Wifi radio's status

unsigned long lastConnectionTime = 0;         // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10000L; // delay between updates, in milliseconds

// Initialize the Ethernet client object
WiFiEspClient client;


/// Move the ssid and password out of global spacec use same trick as the http formatting

void WIFI_connect(){
  // attempt to connect to WiFi network

  // attept to connect to AP

  show_P("Configuring\nWIFI card");
  // initialize ESP module
  WiFi.init(&Serial);

  show_P("Connecting\n to AP");

  strncpy_P(Buffer, PSTR(PASSWORD), 11);
  status = WiFi.begin(ssid, Buffer);
  
  for(int i=0; i<5; i++){
    if(status == WL_CONNECTED){
      show_P("Connected\n to AP");
      break;
    }
    else{
      // Connect to WPA/WPA2 network
      status = WiFi.begin(ssid, Buffer);
    }
  }
  
}

void WIFI_setup()
{

  // show_P("Configuring\nWIFI card");
  // // initialize ESP module
  // WiFi.init(&Serial);

  WIFI_connect();

  // put in proper retrys here
  // check for the presence of the shield

  show_P("Checking\n WIFI card");
  if (WiFi.status() == WL_NO_SHIELD) {
    show_P("WiFi card\n not present");

    // fix this to be like old code ie reboot after one send etc
  }

}


// merge this function with the http request one g

void WIFI_send()
{
 
  // if 10 seconds have passed since your last connection,
  // then connect again and send data
  if (millis() - lastConnectionTime > postingInterval) {

    httpRequest();
  }
}



// // use other code for own at commands etc to see how to send real values

// // void reboot_connection()


// // int port = 80;
// // char protocol[5] = "\0";

// void store_config(){
//   if(SD_available){
//     myFile = SD.open(F("config.txt"), FILE_WRITE);

//     // store data in buffer
//     sprintf_P(Buffer, PSTR("PORT %d\nSERVER %s\nPROTOCOL %s"), port,  Buffer, protocol);

//     // write the variables into the config file
//     Save(Buffer);
//   }
// }


// void update_config(){
//   // connect to massey
//   strncpy_P(Buffer, PSTR("seat-skomobo.massey.ac.nz"), 26);

//   if (client.connect(Buffer, 80)) {

//     strncpy_P(Buffer, PSTR("GET /config HTTP/1.1\n"), 23);
//     client.print(Buffer);
//     strncpy_P(Buffer, PSTR("Host: seat-skomobo.massey.ac.nz\r\n"), 34);
//     client.print(Buffer);
//     strncpy_P(Buffer, PSTR("Connection: close\r\n\r\n"), 22);
//     client.print(Buffer);

//     // debugging for now
//     Serial.println(client.read());

//     show_P("Updating config");

//     // variables get reassigned here

//     // server gets stored in buffer

//     // if there is no reply we check the config file
    
//     //if(reply){
//     store_config();
//     //}
//     //else{
//     // read_config();
//     // if(data_in_config){
//       // assign config values
//     //}
//     // else{
// //      reassign default values
//     //}
//     //}


//   }else{
//     show_P("No update");
//   }


// }


// void tcp_send_data(){
//   // if there's a successful connection

//  show_P("Sending data\nto server");
 
//  // First variable is the tcp 'route'

//  snprintf_P(Buffer, 70, PSTR("0_" BOX_ID "_%d-%d-%d-%d-%d-%d_%d_%d_%d_%d.%d_%d.%d_%d_%c\n"),  year, month, day, hour, minute, second, PM1, PM25, PM10,(int)temperature, (int)(temperature * 100) % 100, (int)humidity, (int)(humidity * 100) % 100, CO2, PIR);
//  client.print(Buffer);

//  show_P("Data sent");
//  // note the time that the connection was made
//  lastConnectionTime = millis();

// }

void http_send_data(){
 
  show_P("Sending data\nto server");
  
  snprintf_P(Buffer, 70, PSTR("GET /" BOX_ID "_%d-%d-%d-%d-%d-%d_%d_%d_%d_%d.%d_%d.%d_%d_%c HTTP/1.1\n"),  year, month, day, hour, minute, second, PM1, PM25, PM10,(int)temperature, (int)(temperature * 100) % 100, (int)humidity, (int)(humidity * 100) % 100, CO2, PIR);
  client.print(Buffer);
  strncpy_P(Buffer, PSTR("Host: seat-skomobo.massey.ac.nz\r\n"), 34);
  client.print(Buffer);
  strncpy_P(Buffer, PSTR("Connection: close\r\n\r\n"), 22);
  client.print(Buffer);

  show_P("Data sent");

  // note the time that the connection was made
  lastConnectionTime = millis();

}

// this method makes a HTTP connection to the server
void httpRequest()
{
  // close any connection before send a new request
  // this will free the socket on the WiFi shield

  // move this to bottom for my own protocol
  client.stop();

  // show_P("Updating config");
  // update_config();

  show_P("Connecting\n to server");

  strncpy_P(Buffer, PSTR("seat-skomobo.massey.ac.nz"), 26);
    
  //update config puts domain received from massey in buffer
  // if (client.connect(Buffer, port)) {

  if (client.connect(Buffer, 80)) {
    
    http_send_data();
    
    // if(strcmp_P(protocol,PSTR("TCP"))){
    //     tcp_send_data();
    // }
    // else if(strcmp_P(protocol,PSTR("blue"))){
    //     blue_send();
    // }
    // else{

    //     // here if it is HTTP or an invalid protocol we just assume to use HTTP, better than
    //     // it not sending anything because the protocol is wrong :)
    //     http_send_data();
    // }

  }else{
    show_P("Server\nconnection\nlost");

    // WiFi.init(&Serial);
    WIFI_connect();
  }

  delay(6000);

}