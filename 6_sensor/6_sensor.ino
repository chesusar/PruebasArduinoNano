#include <Arduino_LSM9DS1.h>
#include "BBTimer.hpp"

BBTimer tim0(BB_TIMER0);

bool readEvent = false;
bool printEvent = false;

void setup() {
  Serial.begin(9600);
  IMU.begin();
  tim0.setupTimer(100000, tim0Callback);  // 100 ms
  tim0.timerStart();
}

void loop() {
  static float acelX, acelY, acelZ;
  static float gyroX, gyroY, gyroZ;
  static float magX, magY, magZ;

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
    char buff[128];
    sprintf(buff, "Acel (%f, %f, %f)", acelX, acelY, acelZ);
    Serial.println(buff);
    sprintf(buff, "Gyro (%f, %f, %f)", gyroX, gyroY, gyroZ);
    Serial.println(buff);
    sprintf(buff, "Mag (%f, %f, %f)", magX, magY, magZ);
    Serial.println(buff);
    Serial.println("----");
  }
}

void tim0Callback() {
  static int time = 0;
  time += 100;
  readEvent = true;
  if (time >= 1000) {
    time = 0;
    printEvent = true;
  }
}
