// TODO: change tone
//       melody and harmony
// done
const int buzz = 9;
const int freq[] = {523,587,659,698,784,880,988};
const int sharpfreq[] = {554,622,0,740,831,932,0};
const int highfreq[] = {1047,1175,1319,1397,1568,1760,1976};
const int highsharpfreq[] = {1109,1245,0,1480,1661,1865,0};
struct Note {
    int pitch, value;
} nt[100];
double bpm = 240, sum = 0;
String musicin = "";
// #: sharp
// ^: high 8 degree
// -: lengthen
int fromstr(String melody, Note res[]) {
    int len = 0;
    for (int i=0; i<melody.length(); ) {
        int r = i+1, tm = 1;
        while ((melody[r] < '0' || melody[r] > '9') && r<melody.length()) r++;
        bool sharp = false, high = false;
        for (int j=i; j<r; j++) {
            if (melody[j]=='#')
                sharp = true;
            else if (melody[j]=='^')
                high = true;
            else if (melody[j]=='-')
                tm++;
        }
        res[len].value = tm;
        res[len].pitch = freq[melody[i]-'1'];
        i = r;
        len++;
    }
    return len;
}
void printdata() {
    Serial.print("BPM : ");
    Serial.println(bpm, 2);
    Serial.print("duration : ");
    Serial.println(duration/1000, 2);
    bool no = 0;
    for ( int i=0; i<musicin.length(); i++ ) {
        if ( no && musicin[i] >= '0' && musicin[i] <= '9' )
            Serial.print(" ");
        else if ( musicin[i] >= '0' && musicin[i] <= '9' )
            no = 1;
        Serial.print(musicin[i]);
    }
    Serial.print("\n");
}
void setup() {
    pinMode(buzz,OUTPUT);
    Serial.begin(9600);
}
void loop() {
    if ( Serial.available() > 0 )
        musicin += Serial.readString();
    delay(200);
    if ( musicin.length() ) {
        delay(100);
        int n=fromstr(musicin, nt);
        for (int i=0; i<n; i++) {
            double dur = nt[i].value*60000.0/bpm;
            tone(buzz, nt[i].pitch, dur);
            delay(dur*1.3);
            noTone(buzz);
            duration += dur;
        }
        printdata();
        delay(1000);
        musicin = "";
    }
    delay(500);
}
