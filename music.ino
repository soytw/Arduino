// TODO: change tone
//       melody and harmony

const int buzz = 9;
const int freq[] = {523,587,659,698,784,880,988};
const int sharpfreq[] = {554,622,0,740,831,932,0};
const int highfreq[] = {1047,1175,1319,1397,1568,1760,1976};
const int highsharpfreq[] = {1109,1245,0,1480,1661,1865,0};

struct Note {
    int pitch, value;
};

int bpm = 240;
// String musicstr = "6-234#^56-2-2-7-5671#^2^-2-2-5-6#^54#^34#^-54323-43#^212";
String musicstr = "5-12345-1-1-6-45671^-1-1-4-54323-43211";
Note music[100];
int musiclen = 0;
// #: sharp
// ^: high 8 degree
// -: lengthen

int fromstr(String src, Note res[]) {
    int len = 0;
    for (int i=0; i<src.length(); ) {
        int r=i+1, tm=1;
        while ((src[r] < '0' || src[r] > '9') && r<src.length()) r++;
        bool sharp=false, high=false;
        for (int j=i; j<r; j++) {
            if (src[j]=='#')
                sharp = true;
            else if (src[j]=='^')
                high = true;
            else if (src[j]=='-')
                tm++;
        }
        if (sharp && high)
            res[len].pitch = highsharpfreq[src[i]-'1'];
        else if (sharp)
            res[len].pitch = sharpfreq[src[i]-'1'];
        else if (high)
            res[len].pitch = highfreq[src[i]-'1'];
        else
            res[len].pitch = freq[src[i]-'1'];
        res[len].value = tm;

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
        double dur = music[i].value*60000.0/bpm;
        tone(buzz, music[i].pitch, dur);
        delay(dur*1.3);
        noTone(buzz);
    }
    delay(1000);
}
