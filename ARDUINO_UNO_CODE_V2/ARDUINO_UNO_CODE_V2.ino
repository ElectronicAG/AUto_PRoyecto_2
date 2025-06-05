// Pines del módulo L298N
const uint8_t ENA = 8, IN1 = 9, IN2 = 10, IN3 = 11, IN4 = 12, ENB = 13;

// Pines de entrada desde el PLC (relés)
const byte interruptPinR = 2; // Derecha
const byte interruptPinL = 3; // Izquierda

void setup() {
  // Configurar pines del motor como salidas
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Entradas desde PLC (con resistencias pull-up internas)
  pinMode(interruptPinR, INPUT_PULLUP);
  pinMode(interruptPinL, INPUT_PULLUP);

  // (Opcional para debug)
  Serial.begin(9600);
}

void loop() {
  // Leer estados de los relés controlados por el PLC
  bool rightSignal = digitalRead(interruptPinR); // 0 = Activado
  bool leftSignal  = digitalRead(interruptPinL); // 0 = Activado

  // Lógica: solo una dirección a la vez, si ambos en 0 => error
  if (!rightSignal && leftSignal) {
    // Girar a la derecha
    moverDerecha();
  }
  else if (!leftSignal && rightSignal) {
    // Girar a la izquierda
    moverIzquierda();
  }
  else {
    // Detener motores (ambos en 1 o ambos en 0)
    detenerMotores();
    if (!rightSignal && !leftSignal) {
      Serial.println("⚠️ ERROR: Ambas señales activas al mismo tiempo.");
    }
  }

  delay(5); // Pequeña espera para estabilidad
}

void moverDerecha() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moverIzquierda() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void detenerMotores() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}
