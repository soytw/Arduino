/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */

int led = 13;           // the PWM pin the LED is attached to
float brightness;    // [0,1000] how bright the LED is
float minBrightness = 0;
float maxBrightness = 1000;
float fadeAmount = 0.5; // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  brightness = minBrightness;
}

// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available()) {
    brightness = minBrightness;
    fadeAmount = Serial.parseFloat();
  }

  // set the brightness of pin 9:
  // analogWrite(led, brightness);
  digitalWrite(led, HIGH);
  delayMicroseconds(brightness);
  digitalWrite(led, LOW);
  delayMicroseconds(1000 - brightness);

  // change the brightness for next time through the loop:
  brightness += fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= minBrightness || brightness >= maxBrightness) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  // delay(30);
}
