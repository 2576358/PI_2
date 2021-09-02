/*
INSTITUTO FEDERAL DE SANTA CATARINA
Engenharia Eletrônica
Projeto Integrador II
Marcelo Poyer Radetski
*/
//atribuição pinos----------------------------------------------
#define LED1 22
#define LED2 23
#define LED3 24
#define LED4 25
#define LED5 26
#define LED6 27
#define LED7 28
#define LED8 29
#define LED9 30
#define LED10 31
#define PIR 12
#define MQ2 A5
#define BUZZER 10
#include <Servo.h>

//criação de variáveis------------------------------------------

const unsigned long periodo_tarefa_1 = 1000;
unsigned long tempo_tarefa_1 = millis();
const unsigned long periodo_tarefa_2 = 2000;
unsigned long tempo_tarefa_2 = millis();
char DATA;
int PIR_VALUE;
int THRESHOLD = 400;
int MQ2_VALUE;

//inicialização dos pinos/variáveis-----------------------------

void setup() {

  Serial.begin(9600);
  while (!Serial);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(MQ2, INPUT);
}

//controle do sistema pelo teclado------------------------------

void serial() {
  if (Serial.available() > 0) {
    DATA = Serial.read();
    //Serial.print("Entrada recebida: ");
    Serial.println(DATA);
    switch (DATA) {
      case 'z':
        digitalWrite(LED1, !digitalRead(LED1));
        Serial.print("Led 1 alterado.\n");
        break;
      case 'x':
        digitalWrite(LED2, !digitalRead(LED2));
        Serial.print("Led 2 alterado.\n");
        break;
      case 'c':
        digitalWrite(LED3, !digitalRead(LED3));
        Serial.print("Led 3 alterado.\n");
        break;
      case 'v':
        digitalWrite(LED4, !digitalRead(LED4));
        Serial.print("Led 4 alterado.\n");
        break;
      case 'b':
        digitalWrite(LED5, !digitalRead(LED5));
        Serial.print("Led 5 alterado.\n");
        break;
      case 'n':
        digitalWrite(LED6, !digitalRead(LED6));
        Serial.print("Led 6 alterado.\n");
        break;
      case 'm':
        digitalWrite(LED7, !digitalRead(LED7));
        Serial.print("Led 7 alterado.\n");
        break;
      case 'a':
        digitalWrite(LED8, !digitalRead(LED8));
        Serial.print("Led 8 alterado.\n");
        break;
      case 's':
        digitalWrite(LED9, !digitalRead(LED9));
        Serial.print("Led 9 alterado.\n");
        break;
      case 'q':
        int MQ2_VALUE = analogRead(MQ2);
        Serial.print("Pin A5: ");
        Serial.println(MQ2_VALUE);
        break;
    }
  }
}

//função do sensor de movimento---------------------------------

void pir(unsigned long tempo_atual) {

  if (tempo_atual - tempo_tarefa_1 > periodo_tarefa_1) {

    tempo_tarefa_1 = tempo_atual;
    PIR_VALUE = digitalRead(PIR);
    if (PIR_VALUE == HIGH) {
      digitalWrite(LED10, HIGH);
    }
    else {
      digitalWrite(LED10, LOW);
    }
  }
}

//função do sensor de gás---------------------------------------

void mq2(unsigned long tempo_atual) {

  if (tempo_atual - tempo_tarefa_2 > periodo_tarefa_2) {

    tempo_tarefa_2 = tempo_atual;
    int MQ2_VALUE = analogRead(MQ2);

    if (MQ2_VALUE > THRESHOLD)
      digitalWrite(BUZZER, LOW);
    else
      digitalWrite(BUZZER, HIGH);
  }
}

//função loop---------------------------------------------------

void loop() {
  unsigned long meu_tempo_atual = millis();

  serial();
  pir(meu_tempo_atual);
  mq2(meu_tempo_atual);
}
