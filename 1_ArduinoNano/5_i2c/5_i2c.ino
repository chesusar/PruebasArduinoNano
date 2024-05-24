#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // String serialBuffer = "";

  // if (Serial.available() > 0){
  //   serialBuffer = Serial.readString();
  //   serialBuffer.trim();
  //   sendI2C(0x00);
  // }
  sendI2C('0');
  delay(500);
  sendI2C('1');
  delay(500);
}

void sendI2C(unsigned char val) {
  Wire.beginTransmission(8);
  Wire.write(val);
  Wire.endTransmission();
}