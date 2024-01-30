// #include "BBTimer.hpp"
#include "jtimer.h"

#define IN_POT A0

// Utilizar Timer4, resto en uso por Arduino
// BBTimer timerPot(BB_TIMER4);


void timCallback(){
  Serial.println("Hola");
}


void timerPotCallback() {
  int medidaPot = analogRead(IN_POT);
  Serial.println(medidaPot);
}


void setup() {
  pinMode(IN_POT, OUTPUT);
  Serial.begin(9600);
  startTimer(100, &timCallback);
  
  // timerPot.setupTimer(10000, timerPotCallback);
  // timerPot.timerStart();
}


void loop() {

}
