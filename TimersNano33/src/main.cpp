#include <Arduino.h>
#include "timer_task.h"

bool ledOn = true;

void setup()
{
    Serial.begin(9600);
    startTask(500);
}

void loop()
{
    if (isTaskEvent())
    {
        Serial.println("Task event");
        ledOn = !ledOn;
        digitalWrite(LEDR, ledOn ? HIGH : LOW);
    }
}
