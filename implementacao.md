# **Implementação**

Na etapa de implementação foram integradas todas as partes anteriores do projeto, tornando as ideias em algo real. Transformamos o design em um produto, processo ou sistema, incluindo hardware, fabricação, codificação de software, teste e validação.

### **Maquete**

![IMG_20210915_220247013](https://user-images.githubusercontent.com/84546006/133652158-fba289fc-c930-4155-970c-1a6cb6a95d74.jpg)
![IMG_20210915_220206258](https://user-images.githubusercontent.com/84546006/133652180-ad45171c-d06a-4a7c-ac90-8967cfd79b6f.jpg)
![IMG_20210915_220133964](https://user-images.githubusercontent.com/84546006/133652226-289709e0-e7e8-4322-bf33-338b4fc3c713.jpg)
![IMG_20210915_220224399](https://user-images.githubusercontent.com/84546006/133652212-db5ae4d4-296a-4495-87d1-454b1a2ba80e.jpg)

### **Teste**

Após obtenção dos materiais desejados foi feita uma fase de testes com o intuito de verificar o bom funcionamento de cada componente. Grande parte destes testes foram realizados com exemplos encontrados na internet ou exemplos do próprio software Arduino. Todos os componentes foram testados, um de cada vez, para averiguar seu comportamento e desempenho.

### **Código**

Feitos todos os testes desenvolveu-se o código, onde foram integrados todos estes testes individuáis em um mesmo programa, tomando as devidas medidas/cuidados para que tudo funcione conforme o esperado sem conflitos ou erros.

Além das funções para cada componente também foi utilizada uma função para multitask, de modo que possamos utilizar multiplos recursos ao mesmo tempo. Para mais informações sobre está função [clique aqui](https://github.com/LPAE/arduino_tutorial/tree/main/tarefas).

#### **Controle Serial:**

Esta função serve para controlar alguns componentes pelo teclado. Assim que uma tecla for pressionada ela irá executar a ação associada a esta tecla. Essa função serve principalmente como controle e está sendo utilizada para a iluminação, apresentando os dados obtidos pelos sensores (gás/umidade/temperatura) e para o servo motor utilizado para o portão (tive de utilizar "if" para as quatro ultimas opções pois não consegui fazer funcionar de outra forma).

~~~C
void serial() {
  if (Serial.available() > 0) {
    DATA = Serial.read();
    //Serial.print("Entrada recebida: ");
    Serial.println(DATA);
    switch (DATA) {
    
    //controle iluminação----------------------
    
      case 'z':
        digitalWrite(LED1, !digitalRead(LED1));
        Serial.print("Led 1 alterado.\n");
        break;
        
    //controle sensor de gás-------------------
        
      case 'q':
        int MQ2_VALUE = analogRead(MQ2);
        Serial.print("Pin A5: ");
        Serial.println(MQ2_VALUE);
        break;
    }
    
    //controle sensor de temperatura/umidade---
    
    if (DATA == 'e') {
        float t = dht.readTemperature();
        Serial.print("Temperatura: ");
        Serial.print(t);
        Serial.println(" *C");
    }
    if (DATA == 'w') {
        float h = dht.readHumidity();
        Serial.print("Umidade: ");
        Serial.print(h);
    }
        
    //controle servo---------------------------
        
    if (DATA == 'o'){
      for(pos == 60 ; pos < 150; pos++){
        s.write(pos);
      }
    }
    if (DATA == 'c'){
      for(pos == 150; pos > 60; pos--){
        s.write(pos);
      }
    }
  }
}
~~~

#### **Sensor de movimentos:**

Esta função irá executar quando o sensor de movimento detectar algo (estado lógico do PIR for HIGH), portanto, assim que um movimento for detectado pelo sensor ele irá acender um led (LED10). Essa função pode ser utilizada em um corredor/garagem para acender as luzes quando tiver alguém.

~~~C
void pir(unsigned long tempo_atual) {

  if (tempo_atual - tempo_tarefa_1 > periodo_tarefa_1) {

    tempo_tarefa_1 = tempo_atual;
    PIR_VALUE = digitalRead(PIR);
    if (PIR_VALUE == HIGH) {
      digitalWrite(LED10, HIGH);
      if (PIRSTATE == LOW)
        PIRSTATE = HIGH;
    }
    else {
      digitalWrite(LED10, LOW);
      if (PIRSTATE == HIGH)
        PIRSTATE = LOW;
    }
  }
}
~~~

#### **Sensor de gás:**

A função para o sensor de gás é ficar monitorando constantemente o "nível" de gás no ambiente. Assim que esse nível passar de um limite específico (THRESHOLD) ele irá acionar o BUZZER para alertar o usuário.

~~~C
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
~~~

Algumas considerações:

Não foi implementada a matriz led 8x8, pois os códigos eram demasiadamente laboriosos, sem erequecimento técnico ou conceitual. Houve problemas técnicos (queima do adaptador para o arduino).

Isso resume o código atual. Para ver o código completo [clique aqui](https://github.com/MarceloPoyer/Projeto_Integrador_2/edit/main/codigo.ino).

Vídeo de apresentação da maquete.

[![Watch the video](https://img.youtube.com/vi/Ms0efQEhomI/maxresdefault.jpg)](https://youtu.be/Ms0efQEhomI)
