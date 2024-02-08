#include <Arduino_LSM9DS1.h>
#include "BBTimer.hpp"

BBTimer tim0(BB_TIMER0);

bool readEvent = false;
bool printEvent = false;

void setup() {
  Serial.begin(9600);
  IMU.begin();
  tim0.setupTimer(200000, tim0Callback);  // 200 ms
}

void loop() {
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

    char buff[128];
    sprintf(buff, "Acel (%.3f, %.3f, %.3f)\nGyro (%.3f, %.3f, %.3f)\nMag (%.3f, %.3f, %.3f)",
            acelX, acelY, acelZ,
            gyroX, gyroY, gyroZ,
            magX, magY, magZ);
    Serial.println(buff);
    Serial.println("----");

    send(buff, 128);
  }
}

void send(char *buff, int size) {
}

void receive() {
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
