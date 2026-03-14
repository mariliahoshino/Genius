

#define MAX_SEQ 50
#define BUZZER 27

int leds[4] = {23, 22, 21, 19};  //variável array
int botoes[4] = {18, 5, 17, 16};
int tons[4] = {523, 659, 784, 1046};

int sequencia[MAX_SEQ];
int rodada = 0;

void setup() {
  Serial.begin(115200);  //velocidade de comunicação serial

  for(int i=0;i<4;i++){
    pinMode(leds[i], OUTPUT);  //define saída LED como saída
    pinMode(botoes[i], INPUT_PULLUP);  //define botoes como entrada e pull up ativado, dispensando resistor de 10K de pull up
  }
  pinMode(BUZZER, OUTPUT);  // define BUZZER como saída

  //randomSeed(analogRead(34));
}

void loop() {

  sequencia[rodada] = random(0,4);  // número aleatório de 0 à 3 e armazena na variável sequencia na posição "rodada"
  rodada++; //é necessário incrementar rodada devido o for utilizar "<" sem o "=" pois o for para uma posição antes

  mostrarSequencia();  // chama a sub rotina

  if(!lerJogador()){  //chama a subrotina e aguarda o retorno
    gameOver();  // se negativo chama game over emitindo som de erro
    rodada = 0;
  }

  delay(1000);
}

void mostrarSequencia(){    // mostra a sequencia de LEDs para memorizar e mostra a última criada para memorizar a mais
  for(int i=0;i<rodada;i++){
    digitalWrite(leds[sequencia[i]], HIGH);
    //tocarSom(sequencia[i]);
    tocarSom(tons[sequencia[i]]);
    //delay(500);
    digitalWrite(leds[sequencia[i]], LOW);
    delay(200);
  }
}

bool lerJogador(){  //monitora se o botão apertado corresponde a posição do LED

  for(int i=0;i<rodada;i++){

    int botao = esperarBotao();

    if(botao != sequencia[i])  //se apertar errado, encerra essa subrotina e retorna false (game over)
      return false;

    digitalWrite(leds[botao], HIGH);
    //tocarSom(botao);
    tocarSom(tons[botao]);
    //delay(300);
    digitalWrite(leds[botao], LOW);
  }

  return true;  //acertando a sequencia saí do for e retorna true repetindo o jogo e incrementando + 1 LED na sequencia
}

int esperarBotao(){  //subrotina aguarda o jogador aperatar o botão
  while(true){
    for(int i=0;i<4;i++)
    {
      if(digitalRead(botoes[i]) == LOW){
        delay(200);
        return i;  //retorna a posição do botão e verifica 
      }
    }
  }
}

void gameOver(){  //subrotina gameover

  for(int i=0;i<4;i++){
    digitalWrite(leds[i], HIGH);  //acende todos os LEDs
  }
  tone(BUZZER, 200); //toca som erro

  delay(1000);  //

  for(int i=0;i<4;i++){  // apaga todos os LEDs
    digitalWrite(leds[i], LOW);
  }
  noTone(BUZZER);  //para som
}

void tocarSom(int freq){

  tone(BUZZER, freq);
  delay(300);
  noTone(BUZZER);

}
