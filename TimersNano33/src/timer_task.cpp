#include <nrf52840.h>

NRF_TIMER_Type *timer4 = NRF_TIMER4;

void (*timer4Callback)();
uint32_t timer4Time = 0;
uint32_t timer4CurrentTime = 0;

void compareInterrupt();

void startTask(int time, void (*callbackFunc)())
{
    timer4Callback = callbackFunc;
    timer4CurrentTime = 0;
    timer4Time = time;

    // Ensure timer 4 is stopped and cleared before changing settings.
    timer4->TASKS_STOP = 1;
    timer4->TASKS_CLEAR = 1;

    // Timer 4 settings
    timer4->BITMODE = TIMER_BITMODE_BITMODE_16Bit;
    timer4->PRESCALER = 0;
    timer4->CC[0] = 1000UL;
    timer4->INTENSET = TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;
    timer4->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos;

    // CC Interrupt
    NVIC_SetVector(TIMER4_IRQn, (uint32_t)&compareInterrupt);
    NVIC_EnableIRQ(TIMER4_IRQn);

    // Start timer 4
    timer4->TASKS_START = 1;
}

void compareInterrupt()
{
    NVIC_DisableIRQ(TIMER4_IRQn);
    if (timer4->EVENTS_COMPARE[0] == 1)
    {
        timer4CurrentTime++;
        if (timer4CurrentTime >= timer4Time)
        {
            timer4CurrentTime = 0;
            (*timer4Callback)();
        }
        // Clear event
        timer4->EVENTS_COMPARE[0] = 0;
    }
    NVIC_EnableIRQ(TIMER4_IRQn);
}