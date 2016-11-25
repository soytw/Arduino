// TODO: melody and harmony

#include <string.h>
#include <ctype.h>
#include <math.h>

const int buzz = 9;

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
// #: sharp
// ^: higher octave
// .: lower octave
// -: lengthen

int fromstr(char src[], Note res[], int tone) {
    int len = 0;
    for (int i = 0; i<strlen(src); ) {
        int r = i + 1;
        while (!isdigit(src[r]) && r<strlen(src))
            r++;
        int sharp = tone, octave = 5, notelen = 1;
        for (int j = i; j<r; j++) {
            if (src[j] == '#')
                sharp++;
            else if (src[j] == 'b')
                sharp--;
            else if (src[j] == '^')
                octave++;
            else if (src[j] == '.')
                octave--;
            else if (src[j] == '-')
                notelen++;
        }
        res[len].pitch = src[i] - '0';
        res[len].octave = octave;
        res[len].sharp = sharp;
        res[len].notelen = notelen;
        i = r;
        len++;
    }
    return len;
}
void setup() {
    pinMode(buzz,OUTPUT);
    Serial.begin(9600);
}
void loop() {
    if (Serial.available()) {
        musicstr = Serial.readString();
    }
    musiclen = fromstr(musicstr, music);
    // int curMillis = millis();
    // int i = (curMillis - prevMillis) * ;
    // prevMillis = curMillis;
    for (int i=0; i<musiclen; i++) {
        tone(buzz, music[i].freq(), music[i].duration());
        delay(music[i].duration()*1.3);
        noTone(buzz);
    }
    delay(1000);
}
