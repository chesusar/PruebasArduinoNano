#ifndef JTIMER_H
#define JTIMER_H

#include <nrf_timer.h>

void startTimer(int, void(*)());
void stopTimer();

#endif

