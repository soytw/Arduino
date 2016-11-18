// TODO: change tone
//       melody and harmony
// undone
const int buzz = 9;
const int freq[] = {523,587,659,698,784,880,988};
const int sharpfreq[] = {554,622,0,740,831,932,0};
const int highfreq[] = {1047,1175,1319,1397,1568,1760,1976};
const int highsharpfreq[] = {1109,1245,0,1480,1661,1865,0};

struct Note {
    int pitch, value;
};

int bpm = 480;
char melody[] = "6234#^562275671#^2^2256#^54#^34#^5432343#^212";
// #: sharp
// ^: high 8 degree
// +: # and ^
char note[] = "21111222211112222111121111211113";

int fromstr(char melody[], char tempo[], Note res[]) {
    int n = strlen(melody);
    int i = 0;
    int len = 0;
    while (i < n) {
        if (melody[i+1]=='#' && melody[i+2]=='^')
            res[len].pitch = sharpfreq[melody[i]-'1'];
        else if (melody[i+1]=='^')
            res[len].pitch = highfreq[melody[i]-'1'];
        else
            res[len].pitch = freq[melody[i]-'1'];
        res[len].value = tempo[len]-'0';
        len++;
        while (melody[i] < '0' || melody[i] > '9') i++;
    }
}
void setup() {
    pinMode(buzz,OUTPUT);
}
void loop() {
    Note 
        // double dur = (note[len]-'0')*60000.0/bpm;
        // tone(buzz, f, dur);
        // delay(dur*1.3);
        // noTone(buzz);
    delay(1000);
}
