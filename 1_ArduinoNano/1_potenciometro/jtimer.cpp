#include "jtimer.h"

void (*callback)();

void tickTimer();


void startTimer(int time, void (*callbackFunction)()) {
  callback = callbackFunction;
  tickTimer();
}

void stopTimer() {

}

void tickTimer() {
  (*callback)();
}