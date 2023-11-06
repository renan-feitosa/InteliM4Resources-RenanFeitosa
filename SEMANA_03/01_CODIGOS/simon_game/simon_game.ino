const int ledAmarelo = 25;     // Pino do LED amarelo
const int ledVermelho = 26;    // Pino do LED vermelho
const int ledAzul = 27;        // Pino do LED azul
const int ledVerde = 14;       // Pino do LED verde

const int buttonAmarelo = 18;  // Pino do botão amarelo
const int buttonVermelho = 5;  // Pino do botão vermelho
const int buttonAzul = 17;     // Pino do botão azul
const int buttonVerde = 16;    // Pino do botão verde
const int buttonReset = 19;    // Pino do botão de reinício

int sequence[100];             // Array para armazenar a sequência gerada aleatoriamente
int playerSequence[100];       // Array para armazenar a sequência inserida pelo jogador
int sequenceLength = 0;        // Comprimento da sequência atual
int playerTurn = false;        // Indica se é a vez do jogador
int score = 0;                 // Pontuação do jogador
int delayTime = 500;           // Tempo de atraso entre as piscadas dos LEDs

void setup() {
  pinMode(buttonAmarelo, INPUT_PULLUP);  // Configura o pino do botão amarelo como entrada com resistor pull-up
  pinMode(buttonVermelho, INPUT_PULLUP); // Configura o pino do botão vermelho como entrada com resistor pull-up
  pinMode(buttonAzul, INPUT_PULLUP);     // Configura o pino do botão azul como entrada com resistor pull-up
  pinMode(buttonVerde, INPUT_PULLUP);    // Configura o pino do botão verde como entrada com resistor pull-up
  pinMode(buttonReset, INPUT_PULLUP);    // Configura o pino do botão de reinício como entrada com resistor pull-up

  pinMode(ledAmarelo, OUTPUT);   // Configura o pino do LED amarelo como saída
  pinMode(ledVermelho, OUTPUT);  // Configura o pino do LED vermelho como saída
  pinMode(ledAzul, OUTPUT);      // Configura o pino do LED azul como saída
  pinMode(ledVerde, OUTPUT);     // Configura o pino do LED verde como saída

  // Inicialize a comunicação serial (opcional, usado para depuração)
  Serial.begin(9600);

  // Inicialize o gerador de números aleatórios
  randomSeed(analogRead(0));

  // Inicialize o jogo
  startGame();
}

void loop() {
  if (playerTurn) {
    checkPlayerInput();
  }

  if (digitalRead(buttonReset) == LOW) {
    // Reinicie o jogo
    startGame();
  }
}

void startGame() {
  turnOnAllLeds();    // Acende todos os LEDs
  delay(500);
  turnOffAllLeds();   // Desliga todos os LEDs
  delay(500);
  sequenceLength = 0;  // Reinicializa o comprimento da sequência
  playerTurn = false;  // É a vez do computador (não do jogador)
  score = 0;           // Zera a pontuação
  addStepToSequence(); // Adiciona um passo à sequência
  playSequence();      // Reproduz a sequência gerada pelo computador
}

void addStepToSequence() {
  sequence[sequenceLength] = random(4);  // Gera um passo aleatório (0 a 3) e adiciona à sequência
  sequenceLength++;  // Aumenta o comprimento da sequência
}

void playSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    int color = sequence[i];
    switch (color) {
      case 0: // Amarelo
        flashLed(ledAmarelo);
        break;
      case 1: // Vermelho
        flashLed(ledVermelho);
        break;
      case 2: // Azul
        flashLed(ledAzul);
        break;
      case 3: // Verde
        flashLed(ledVerde);
        break;
    }
    delay(delayTime);  // Aguarda um período de tempo
    turnOffAllLeds();  // Desliga todos os LEDs
    delay(70);         // Aguarda um curto período de tempo
  }
  playerTurn = true;  // É a vez do jogador após a reprodução da sequência
}

void checkPlayerInput() {
  static int playerStep = 0;  // Acompanha o passo atual do jogador na sequência

  if (digitalRead(buttonAmarelo) == LOW) {
    flashLed(ledAmarelo);  // Acende o LED amarelo

    if (sequence[playerStep] == 0) {
      playerStep++;  // Passo correto, avança para o próximo
    } else {
      startGame();    // Passo errado, reinicia o jogo
    }
  }

  // Repete o mesmo padrão para os outros botões e LEDs
  if (digitalRead(buttonVermelho) == LOW) {
    flashLed(ledVermelho);

    if (sequence[playerStep] == 1) {
      playerStep++;
    } else {
      startGame();
    }
  }

  if (digitalRead(buttonAzul) == LOW) {
    flashLed(ledAzul);

    if (sequence[playerStep] == 2) {
      playerStep++;
    } else {
      startGame();
    }
  }

  if (digitalRead(buttonVerde) == LOW) {
    flashLed(ledVerde);

    if (sequence[playerStep] == 3) {
      playerStep++;
    } else {
      startGame();
    }
  }

  if (playerStep == sequenceLength) {
    playerStep = 0;    // Reinicia o passo do jogador
    delay(500);         // Atraso antes de continuar
    score++;            // Aumenta a pontuação
    addStepToSequence(); // Adiciona um passo à sequência
    playSequence();      // Reproduz a sequência atualizada
  }
}

void flashLed(int led) {
  digitalWrite(led, HIGH);  // Acende o LED
  delay(300);               // Aguarda um período curto
  digitalWrite(led, LOW);   // Desliga o LED
}

void turnOnAllLeds() {
  digitalWrite(ledAmarelo, HIGH);   // Acende o LED amarelo
  digitalWrite(ledVermelho, HIGH);  // Acende o LED vermelho
  digitalWrite(ledAzul, HIGH);      // Acende o LED azul
  digitalWrite(ledVerde, HIGH);     // Acende o LED verde
}

void turnOffAllLeds() {
  digitalWrite(ledAmarelo, LOW);   // Desliga o LED amarelo
  digitalWrite(ledVermelho, LOW);  // Desliga o LED vermelho
  digitalWrite(ledAzul, LOW);      // Desliga o LED azul
  digitalWrite(ledVerde, LOW);     // Desliga o LED verde
}
