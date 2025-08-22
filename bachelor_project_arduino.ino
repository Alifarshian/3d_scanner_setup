#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38

#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56

#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62

#define ENCODER_PIN 3  

int ENCODER_COUNTER = 0;
int STEP_DELAY;
int STEP_DELAY_rotate = 450;
int STEP_DELAY_cart1 = 20;
int STEP_DELAY_cart2 = 200;

int steps =8;

void oneStep(int step_pin, int dir_pin, int dir, int cart, int enPin) {
    digitalWrite(enPin, LOW);
  if (cart == 1)
    STEP_DELAY = STEP_DELAY_cart1;
  if (cart == 2){
    STEP_DELAY = STEP_DELAY_cart2;
    }
  for (int i = 0; i < steps; i++) {
    digitalWrite(dir_pin, dir);
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(STEP_DELAY);
  }
    digitalWrite(enPin, HIGH); 
}

void Rotate(int step_pin, int dir_pin, int dir , int enPin) {
  digitalWrite(enPin, LOW);
  while (ENCODER_COUNTER<6) {
    digitalWrite(dir_pin, dir);
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(STEP_DELAY_rotate);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(STEP_DELAY_rotate);
  }
  // Rotation complete
 digitalWrite(enPin, HIGH);  
}

void encoderISR() {
  ENCODER_COUNTER+=1;
}

void setup() {
  Serial.begin(9600);

  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);

  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(ENCODER_PIN, INPUT);  
attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), encoderISR, RISING);  
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);
  digitalWrite(Z_ENABLE_PIN, HIGH);
}

void loop() {
  Serial.println(ENCODER_COUNTER);
  if (Serial.available() > 0) {
    char msg = Serial.read();
    if (msg == 'a')
      oneStep(Z_STEP_PIN, Z_DIR_PIN, HIGH, 2 ,Z_ENABLE_PIN );
    if (msg == 'd')
      oneStep(Z_STEP_PIN, Z_DIR_PIN, LOW, 2,Z_ENABLE_PIN);
    if (msg == 's')
      oneStep(Y_STEP_PIN, Y_DIR_PIN, HIGH, 1,Y_ENABLE_PIN);
    if (msg == 'w')
      oneStep(Y_STEP_PIN, Y_DIR_PIN, LOW, 1,Y_ENABLE_PIN);
    if (msg == 'f'){
      Rotate(X_STEP_PIN, X_DIR_PIN, LOW,X_ENABLE_PIN);
      ENCODER_COUNTER = 0;
    }
    if (msg == 'b'){
      Rotate(X_STEP_PIN, X_DIR_PIN, HIGH,X_ENABLE_PIN);
      ENCODER_COUNTER = 0;
    }
  }
}
