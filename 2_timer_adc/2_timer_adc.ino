#include "BBTimer.hpp"

#define POTENCIOMETRO A0

BBTimer tim0(BB_TIMER0);
bool timerEvent = false;

void setup() {
  pinMode(POTENCIOMETRO, INPUT);
  Serial.begin(9600);
  tim0.setupTimer(10000000, tim0Callback);
  tim0.timerStart();
}

void loop() {
  if (timerEvent)
  {
    timerEvent = false;
    Serial.println(analogRead(POTENCIOMETRO)*3.3/1024);
  }
}

void tim0Callback(){
  timerEvent = true;
}