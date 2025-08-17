//Pines de modulo
const uint8_t ENA = 8, IN1 = 9, IN2 = 10, IN3 = 11, IN4 = 12, ENB = 13;
const byte interruptPinR = 2;
const byte interruptPinL = 3;
volatile byte stater = LOW;
volatile byte statel = LOW;

volatile unsigned long lastInterruptTimeR = 0;
volatile unsigned long lastInterruptTimeL = 0;
const unsigned long debounceDelay = 10; // en milisegundos

///////////////////////////////////////////////////////////////////////////////////////////////
//Funciones de interrrupcion
///////////////////////////////////////////////////////////////////////////////////////////////
void MotorStateR() {
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTimeR > debounceDelay) {
    stater = !stater;
    statel = 0;
    lastInterruptTimeR = currentTime;
  }
}

void MotorStateL() {
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTimeL > debounceDelay) {
    statel = !statel;
    stater = 0;
    lastInterruptTimeL = currentTime;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////
//Setup
///////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  //Pines de Modulo
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  //Pines de lectura
  pinMode(interruptPinR, INPUT_PULLUP);
  pinMode(interruptPinL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinR), MotorStateR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPinL), MotorStateL, CHANGE);
}
///////////////////////////////////////////////////////////////////////////////////////////////
//LOOP
///////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  if (stater != statel) {
    if (stater) {
      digitalWrite(ENA, HIGH);
      digitalWrite(ENB, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    else if (statel) {
      digitalWrite(ENA, HIGH);
      digitalWrite(ENB, HIGH);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }else{
      digitalWrite(ENA, LOW);
      digitalWrite(ENB, LOW);
    }
  }
  else{
    Serial.println("Error 404");
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
  }
  delay(2);
}
