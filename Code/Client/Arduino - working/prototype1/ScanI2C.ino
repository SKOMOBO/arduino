


void ScanI2CBus()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning");

  nDevices = 0;
  for (address = 1; address <= 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
//    Serial.println("test: " + String(Wire.requestFrom(address, 1)));
//    Serial.println("attempting " + String(address));
 
   
    Wire.beginTransmission(address);

    //rtclib address
    //Wire.beginTransmission(104);

    //datasheet address for m version
//    Wire.beginTransmission(00h);


    //// timeout if timeout is reached then we assume that there is a issue with the i2c bus

    // use a watchdog timer for this would be good if I can somehow 
    // https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
    /// or use a timed interrupt so that once time is exceeded then it swaps to the error message printer and says hardware issue
    
    error = Wire.endTransmission();
    
//    Serial.println("Error: " + String(error));
    
    if (error == 0)
    {
      Serial.print("I2C device found at ");
      Serial.print(address, DEC); Serial.println(" (decimal)");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at ");
      Serial.println(address, DEC);
    }
//    else{
//      Serial.println("Error was " + String(error));
//    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

}
