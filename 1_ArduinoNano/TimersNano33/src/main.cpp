#include <Arduino.h>
#include "timer_task.h"

bool ledOn = true;

void timerCallback();

void setup()
{
    Serial.begin(9600);
    startTask(1000, &timerCallback);
}

void loop()
{
    Serial.println("Loop");
    delay(1000);
    // timerCallback();
}

void timerCallback()
{
    ledOn = !ledOn;
    digitalWrite(LEDR, ledOn? HIGH : LOW);
}
