const int button = 4;
double timer;
bool start;

void setup() {
  Serial.begin(9600);
  pinMode(button,INPUT);
  start = false;
  timer = 0;
}

void loop() {
  if (digitalRead(button)==HIGH) {
    if (!start) {
      Serial.print("Timer start.\n");
      start = true;
      timer = millis();
    }
  } else {
    if (start) {
      Serial.print("Timer stop: ");
      Serial.print((millis()-timer)/1000,10);
      Serial.print("\n");
      start = false;
    }
  }
}
