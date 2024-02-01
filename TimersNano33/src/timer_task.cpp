#include "timer_task.h"
#include <nrf52840.h>
#include <Arduino.h>

NRF_TIMER_Type *timer4 = NRF_TIMER4;

uint32_t timer4Time = 0;
uint32_t timer4CurrentTime = 0;

bool timerEvent = false;
bool led2On = false;

void compareInterrupt();

void startTask(int time)
{
    timer4CurrentTime = 0;
    timer4Time = time;

    // Ensure timer 4 is stopped and cleared before changing settings.
    timer4->TASKS_STOP = 1;
    timer4->TASKS_CLEAR = 1;

    // Timer 4 settings
    timer4->MODE = TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos;
    timer4->BITMODE = TIMER_BITMODE_BITMODE_16Bit;
    timer4->PRESCALER = 7UL; // 1 Mhz
    timer4->CC[0] = 125UL;   // 1 Mhz 10000 1 ms
    timer4->INTENSET = TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;
    timer4->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos;

    // CC Interrupt
    NVIC_SetVector(TIMER4_IRQn, (uint32_t)&compareInterrupt);
    NVIC_EnableIRQ(TIMER4_IRQn);

    // Start timer 4
    timer4->TASKS_START = 1;
}

void stopTask()
{
    NVIC_DisableIRQ(TIMER4_IRQn);
    timer4->TASKS_STOP = 1;
}

void compareInterrupt()
{
    NVIC_DisableIRQ(TIMER4_IRQn);
    if (timer4->EVENTS_COMPARE[0] == 1)
    {
        // Clear event
        timer4->EVENTS_COMPARE[0] = 0;

        timer4CurrentTime++;
        if (timer4CurrentTime >= timer4Time)
        {
            timer4CurrentTime = 0;
            timerEvent = true;
        }
    }
    NVIC_EnableIRQ(TIMER4_IRQn);
}

inline bool isTaskEvent()
{
    if (timerEvent)
    {
        timerEvent = false;
        return true;
    }
    return false;
}