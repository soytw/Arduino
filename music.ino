// TODO: melody and harmony

#include <string.h>
#include <ctype.h>
#include <math.h>

const int buzzer = 9;

struct Note {
    /**
     * the pitch should be described in scientific pitch notation
     * for example, "D5#" of C tone get be described as (2,5,1)
     * PROPERTIES:
     *   pitch: 1-7 note pitch in numeric notation
     *   octave: 0-10
     *   sharp: sharp if positive, flat if negative
     *   notelen: note value
     * METHODS:
     *   freq(): frequency (Hz) in double type
     *   duration(bpm): duration (ms)
     */
    int pitch, octave, sharp, notelen;
    double freq() {
        int mp[] = { 0,60,62,64,65,67,69,71 };
        double p = mp[pitch] + sharp + (octave - 4) * 12;
        return pow(2, (p - 69) / 12) * 440;
    }
    double duration(int bpm) {
        return notelen * 60000.0 / bpm;
    }
};

int bpm = 240;
char musicstr[] = "5-1234 5-1-1- 6-4567 1^-1-1- 4-5432 3-4321 2-3217.1-";
Note music[100];
int musiclen = 0;

int fromstr(char src[], Note res[], int tone) {
    // #: sharp
    // b: flat
    // ^: higher octave
    // .: lower octave
    // -: lengthen
    int srclen = strlen(src);
    int reslen = 0;
    for (int i=0; i<srclen; ) {
        res[reslen].pitch = src[i] - '0';
        res[reslen].octave = 5;
        res[reslen].sharp = tone;
        res[reslen].notelen = 1;
        i++;
        while (!isdigit(src[i]) && i<srclen) {
            if (src[i] == '#')
                res[reslen].sharp++;
            else if (src[i] == 'b')
                res[reslen].sharp--;
            else if (src[i] == '^')
                res[reslen].octave++;
            else if (src[i] == '.')
                res[reslen].octave--;
            else if (src[i] == '-')
                res[reslen].notelen++;
            i++;
        }
        reslen++;
    }
    return reslen;
}
void setup() {
    pinMode(buzzer,OUTPUT);
    Serial.begin(9600);
}
void loop() {
    if (Serial.available()) {
        musicstr = Serial.readString();
    }
    musiclen = fromstr(musicstr, music, 2);
    // int curMillis = millis();
    // int i = (curMillis - prevMillis) * ;
    // prevMillis = curMillis;
    for (int i=0; i<musiclen; i++) {
        tone(buzzer, music[i].freq(), music[i].duration());
        delay(music[i].duration()*1.3);
        noTone(buzzer);
    }
    delay(1000);
}
