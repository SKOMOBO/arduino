void setup(){
  Serial.begin(115200);
  pinMode(3, INPUT);
}


// for using the arduino mega (or another board) as a voltemeter
void CheckVoltage(){

  // Print the value received on analog pin 1 after converting it to volts
  Serial.print(analogRead(A10) * (5.0/1023.0));
  Serial.println(F("V"));
  delay(1000);
}

void continuity(){
  Serial.println(digitalRead(3) == 1);
}


void loop(){
//  CheckVoltage();
  continuity();
  delay(1000);
}

