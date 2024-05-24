#include <Arduino.h>

QueueHandle_t ledQueue;

void taskLed(void *params);
void taskSample(void *params);

void setup()
{
  Serial.begin(9600);
  delay(1000);
  ledQueue = xQueueCreate(1, sizeof(int));
  if (ledQueue == NULL)
  {
    Serial.println("No se creo LED_QUEUE");
    while (true);
  }
  xTaskCreateUniversal(taskSample, "SAMPLE", 1000, NULL, 2, NULL, 0);
  xTaskCreateUniversal(taskLed, "LED", 1000, NULL, 3, NULL, 0);
}

void loop()
{
  delay(1000);
}

void taskLed(void *params)
{
  for (;;)
  {
    int flag = 0;
    if (xQueueReceive(ledQueue, (void *)&flag, 0) != pdTRUE)
    {
      delay(100);
    }

    if (flag == 1)
    {
      Serial.println("LED ON");
      delay(200);
      Serial.println("LED OFF");
    }
  }
}

void taskSample(void *params)
{
  for (;;)
  {
    int samples[10];
    for (int i = 0; i < 10; i++)
    {
      samples[i] = random(100);
      delay(100);
    }

    Serial.print("Datos ");

    for (int i = 0; i < 10; i++)
    {
      Serial.print(samples[i]);
      Serial.print(", ");
    }

    Serial.println("");
    int flag = 1;
    if (xQueueSend(ledQueue, (void *)&flag, 10) != pdTRUE)
    {
      Serial.println("Error enviar a queue");
    }
  }
}
