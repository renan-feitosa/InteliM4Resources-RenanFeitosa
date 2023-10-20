const int pin11out = 11;
const int pin10out = 10;
const int pin09out = 9;
int delayled = 0;
int i = 0;

void setup() {
  // Define os pinos como SAIDA
  pinMode(pin11out, OUTPUT);
  pinMode(pin10out, OUTPUT);
  pinMode(pin09out, OUTPUT);
}

void loop() {
	if (i%2){
    	delayled = 250;
    } else {
    	delayled = 500;
    }
    digitalWrite(pin11out, HIGH);
    digitalWrite(pin09out, LOW);
  
    delay(delayled);
  
    digitalWrite(pin10out, HIGH);
    digitalWrite(pin11out, LOW);
    
  
    delay(delayled);
  
    digitalWrite(pin09out, HIGH);
    digitalWrite(pin10out, LOW);
  
    delay(delayled);
	i++;
}
