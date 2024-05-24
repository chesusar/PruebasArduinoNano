#include <Arduino_LSM9DS1.h>
#include "BBTimer.hpp"

#define MASTER
// #define PERIPHERAL

BBTimer tim0(BB_TIMER0);

bool readEvent = false;
bool printEvent = false;

void setup() {
  Serial.begin(9600);
#ifdef PERIPHERAL
  Wire.begin(8);
#endif
#ifdef MASTER
  Wire.begin();
#endif
  IMU.begin();
  tim0.setupTimer(200000, tim0Callback);  // 200 ms
}

void loop() {
#ifdef PERIPHERAL
  receive();
  if (printEvent){
    analogWrite(LED_BUILTIN, 0);
  }
#endif

#ifdef MASTER
  static float acelX, acelY, acelZ;
  static float gyroX, gyroY, gyroZ;
  static float magX, magY, magZ;

  if (Serial.available() > 0) {
    String serialBuffer = Serial.readString();
    serialBuffer.trim();
    if (serialBuffer.equals("send") || serialBuffer.equals("SEND")) {
      tim0.timerStart();
      Serial.println("SEND received");
    }
  }

  if (readEvent) {
    readEvent = false;
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(acelX, acelY, acelZ);
    }
    if (IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(gyroX, gyroY, gyroZ);
    }
    IMU.readMagneticField(magX, magY, magZ);
  }

  if (printEvent) {
    printEvent = false;

    tim0.timerStop();

    const int BUFF_SIZE = 128;
    char buff[BUFF_SIZE];

    for (int i = 0; i < BUFF_SIZE; i++){
      buff[i] = ' ';
    }
    buff[BUFF_SIZE - 1] = '\n';

    sprintf(buff, "Acel (%.3f, %.3f, %.3f)\nGyro (%.3f, %.3f, %.3f)\nMag (%.3f, %.3f, %.3f)\n",
            acelX, acelY, acelZ,
            gyroX, gyroY, gyroZ,
            magX, magY, magZ);
    Serial.println(buff);
    Serial.println("----");

    send(buff, 128);
  }
#endif
}

void send(char *buff, int size) {
  for (int i = 0; i < size; i++) {
    Wire.beginTransmission(8);
    Wire.write(buff[i]);
    Wire.endTransmission();
  }
}

void receive() {
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
    analogWrite(LED_BUILTIN, 255);
  }
}

void tim0Callback() {
  static int time = 0;
  time += 200;
  readEvent = true;
  if (time >= 1000) {
    time = 0;
    printEvent = true;
  }
}
