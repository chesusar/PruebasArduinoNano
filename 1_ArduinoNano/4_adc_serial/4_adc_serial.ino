#include "BBTimer.hpp"

#define POTENCIOMETRO A0
#define PWM 11

BBTimer tim0(BB_TIMER0);
bool timerEvent = false;
int contador100ms = 0;

int contadorADC = 0;
int consignaContadorADC = 0;

int adcValue = 0;
bool enviando = false;

void setup() {
  pinMode(POTENCIOMETRO, INPUT);
  pinMode(PWM, OUTPUT);

  Serial.begin(9600);

  tim0.setupTimer(100000, tim0Callback); // 100 ms
  tim0.timerStart();
}

void loop() {
  String serialBuffer = "";

  if (Serial.available() > 0){
    serialBuffer = Serial.readString();
    serialBuffer.trim();
    if (serialBuffer.startsWith("ADC")){
      if (serialBuffer.length() > 3){ // ADC(x)
        int adc = serialBuffer.substring(4, 5).toInt();
        consignaContadorADC = adc;
        contadorADC = 0;
        if (adc == 0){
          enviando = false;
        }else{
          enviando = true;
        }
        Serial.print("adc enviado: ");
        Serial.println(adc);
      }else{
        Serial.print("ADC: ");
        Serial.println(adcValue);
      }
    }else if (serialBuffer.startsWith("PWM")){
      int pwm = serialBuffer.substring(4, 5).toInt();
      Serial.print("pwm enviado: ");
      Serial.println(pwm);
      analogWrite(PWM, pwm*25.5);
    }
  }

  if (timerEvent){
    adcValue = analogRead(POTENCIOMETRO);
    timerEvent = false;
  }

  if (contadorADC >= consignaContadorADC){
    contadorADC = 0;
    if (enviando){
      Serial.print("ADC: ");
      Serial.println(adcValue);
    }
  }
}

void tim0Callback(){
  timerEvent = true;
  contador100ms++;
  if (contador100ms >= 10){
    contador100ms = 0;
    contadorADC++;
  }
}