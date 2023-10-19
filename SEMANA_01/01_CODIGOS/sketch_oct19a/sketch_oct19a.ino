const int pin25out = 25;
const int pin33out = 33;
const int pin32out = 32;

void setup() {
  // Define os pinos como SAIDA
  pinMode(pin25out, OUTPUT);
  pinMode(pin33out, OUTPUT);
  pinMode(pin32out, OUTPUT);
}

void loop() {
  // Executa um looping de 1 a 7 
  for (int num = 0; num <= 7; num++) {
    // Declara uma outra variável que armazena o número atual para fazer os cálculos
    int num_print = num;

    // Executa um novo looping de 1 a 3 para cada led e seleciona um deles
    for (int i = 0; i < 3; i++) {
      int pino;
      if (i == 0) {
        pino = pin25out;
      } else if (i == 1) {
        pino = pin33out;
      } else {
        pino = pin32out;
      }

      // Após selecionar o led, verifica se o resto da divisão é 1 ou 0 para definir se está ligado ou não
      if (num_print % 2) {
        digitalWrite(pino, HIGH);
      } else {
        digitalWrite(pino, LOW);
      }

      // Divide o número por 2 para continuar a conta e definir o estado dos próximos pinos
      num_print = num_print / 2;
    }
    delay(1000);
  }
}