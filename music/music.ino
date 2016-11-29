// TODO: melody and harmony

#include "music.h"

const int buzzer = 9;
const char musicstr[] = "5-1234 5-1-1- 6-4567 1^-1-1- 4-5432 3-4321 2-3217.1-";
Note music[100];
int musiclen = 0;

void setup() {
    pinMode(buzzer,OUTPUT);
    Serial.begin(9600);
}
void loop() {
    if (Serial.available()) {
        String s = Serial.readString();
        strcpy(musicstr, s.c_str());
    }
    musiclen = fromstr(musicstr, music, 240, 2);
    // int curMillis = millis();
    // int i = (curMillis - prevMillis) * ;
    // prevMillis = curMillis;
    for (int i=0; i<musiclen; i++) {
        tone(buzzer, music[i].freq, music[i].dur);
        delay(music[i].dur*1.3);
        noTone(buzzer);
    }
    delay(1000);
}
