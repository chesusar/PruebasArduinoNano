#include "BBTimer.hpp"

#define POTENCIOMETRO A0
#define PWM 11

BBTimer tim0(BB_TIMER0);
bool timerEvent = false;
int contador = 0;
int consigna = 0;

void setup() {
  pinMode(POTENCIOMETRO, INPUT);
  pinMode(PWM, OUTPUT);

  Serial.begin(9600);

  tim0.setupTimer(100000, tim0Callback);
  tim0.timerStart();
}

void loop() {
  if (timerEvent){
    consigna = analogRead(POTENCIOMETRO)/1024.0*255;
    timerEvent = false;
  }
  analogWrite(PWM, consigna);
}

void tim0Callback(){
  timerEvent = true;
}