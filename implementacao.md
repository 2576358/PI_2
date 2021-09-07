# **Implementação**

Na etapa de implementação juntamos todas as partes anteriores do projeto, tornamos as até então ideias em algo real. Transformamos o design em um produto, processo ou sistema, incluindo hardware, fabricação, codificação de software, teste e validação.

### **Maquete**

Ainda não terminada.

### **Teste**

Após obtenção dos materiais desejados foi feita uma fase de teste, com o intuito de verificar o bom funcionamento de cada componente. Grande parte destes testes foram realizados com exemplos encontrados na internet ou exemplos do próprio software Arduino. Todos os componentes foram testados, um de cada vez, para averiguar seu comportamento.

### **Código**

Feitos todos os testes vamos para a parte do código, onde juntamos todos estes testes individuáis em um mesmo arquivo tomando as devidas medidas/cuidados para que tudo funcione conforme o esperado sem conflitos ou erros.

Além das funções para cada componente também foi utilizada uma função para multitask, de modo que possamos utilizar multiplos recursos ao mesmo tempo. Para mais informações sobre está função [clique aqui](https://github.com/LPAE/arduino_tutorial/tree/main/tarefas).

#### **Controle Serial:**

Está função serve para controlar alguns componentes pelo teclado, assim que uma tecla for pressionada ela irá executar a ação associada a esta tecla. Essa função serve principalmente como controle para a iluminação mas também está sendo utilizada para obter os dados obtidos pelos sensores de gás e umidade/temperatura além do servo motor utilizado para o portão (criei dois novos "switch case" para as duas ultimas opções pois não consegui fazer funcionar de outra forma, mesma coisa para o servo).

~~~C
void serial() {
  if (Serial.available() > 0) {
    DATA = Serial.read();
    //Serial.print("Entrada recebida: ");
    Serial.println(DATA);
    switch (DATA) {
    
    //controle iluminação---------------------
    
      case 'z':
        digitalWrite(LED1, !digitalRead(LED1));
        Serial.print("Led 1 alterado.\n");
        break;
        
    //controle sensor de gás------------------
        
      case 'q':
        int MQ2_VALUE = analogRead(MQ2);
        Serial.print("Pin A5: ");
        Serial.println(MQ2_VALUE);
        break;
        
    //controle servo--------------------------    
        
      case 'o':
        Serial.print("Abrindo portão!");
        for (pos == 60 ; pos < 150; pos++) {
          s.write(pos);
        }
        break;
      case 'c':
        Serial.print("Fechando portão!");
        for (pos == 150; pos > 60; pos--) {
          s.write(pos);
        }
    }
    
    //controle sensor de temperatura/umidade--
    
    switch (DATA) {
      case 'e':
        float t = dht.readTemperature();
        Serial.print("Temperatura: ");
        Serial.print(t);
        Serial.println(" *C");
        break;
    }
    switch (DATA) {
      case 'w':
        float h = dht.readHumidity();
        Serial.print("Umidade: ");
        Serial.print(h);
        break;
    }
  }
}
~~~

#### **Sensor de movimentos:**

Esta função irá executar quando o sensor de movimento detectar algo (estado lógico do PIR for HIGH), portanto, assim que um movimento for detectado pelo sensor ele irá ascender um led (LED10). Essa função pode ser utilizada em um corredor/garagem para ascender as luzes quando tiver alguém.

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

A função do sensor de gás fica monitorando constantemente o "nível" de gás no ambiente, assim que esse nível passar acima de um limite específico (THRESHOLD) ele irá acionar o BUZZER para alertar o usuário.

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

Acabei desistindo de implementar a matriz led 8x8 pois fiquei desencorajado ao ver exemplos de códigos. Também acabei queimando o adaptador para o arduino, ao liga-lo na tomada ouvi um estouro e aquele cheirinho de queimado, por sorte ele não estava conectado ao arduino no momento do ocorrido.

Isso resume o código atual, para ver o código completo [clique aqui](https://github.com/MarceloPoyer/Projeto_Integrador_2/edit/main/codigo.ino).
