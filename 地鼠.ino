unsigned long time;
unsigned long timebefore; 

const int buttonPin1 = 2;   //button
const int buttonPin2 = 3;  
const int buttonPin3 = 4;  
const int ledPin1 =  13;    //LED
const int ledPin2 =  12;  
const int ledPin3 =  11;  
const int scorePin =  10; 
const int speedpin =  5; //可變電阻
int buttonState1 = 0;       
int buttonState2 = 0;   
int buttonState3 = 0;    
int ledPin1State = 0;
int switch_led;
int randNumber;
int speed;
void setup() {
  randomSeed(analogRead(0));
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(speedpin, INPUT);
  pinMode(scorePin, OUTPUT);
}

void loop() {
  speed = analogRead(speedpin);
  speed/=100;
  randNumber = random(1,4);
  time = millis();
  timebefore=time;
  switch_led=random(1,4);

  switch(switch_led){
  case 1:digitalWrite(ledPin1, HIGH);
      break;
  case 2:
         digitalWrite(ledPin2, HIGH);
         break;
  case 3:
        digitalWrite(ledPin3, HIGH);
        break;
  }
 for(;;){
    time = millis();
    if(time-timebefore>997*speed)break;
    buttonState1 = digitalRead(buttonPin1);   
    buttonState2 = digitalRead(buttonPin2); 
    buttonState3 = digitalRead(buttonPin3); 
  
  if(switch_led==1){
        if (buttonState1==HIGH) {
        digitalWrite(scorePin, LOW);
     }
      else{
        digitalWrite(scorePin,HIGH);
        delay(100);
        break;
     }
  }
  if(switch_led==2){
        if (buttonState2==HIGH) {
        digitalWrite(scorePin, LOW);
     }
      else{
        digitalWrite(scorePin,HIGH);
        delay(100);
        break;
     }
  }
   if(switch_led==3){
        if (buttonState3==HIGH) {
        digitalWrite(scorePin, LOW);
     }
      else{
        digitalWrite(scorePin,HIGH);
        delay(100);
        break;
     }
  }

}
  digitalWrite(scorePin, LOW);
  switch(switch_led){
  case 1:digitalWrite(ledPin1, LOW);
      break;
  case 2:
         digitalWrite(ledPin2, LOW);
         break;
  case 3:
        digitalWrite(ledPin3,LOW);
        break;
  }
  delay(1000);
}
