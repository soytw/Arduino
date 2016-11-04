const int buzz = 9;
const int freq[] = {523,587,659,698,784,880,988};
const int sharpfreq[] = {554,622,0,740,831,932,0};
const int highfreq[] = {1047,1175,1319,1397,1568,1760,1976};
const int highsharpfreq[] = {1109,1245,0,1480,1661,1865,0};

int bpm = 480;
char melody[] = "6234+562275671+^2^2256+54+34+5432+343+212";
// #: sharp
// ^: high 8 degree
// +: # and ^
char note[] =   "21111222211112222111121111211113";

void setup() {
  pinMode(buzz,OUTPUT);
}
void loop() {
  int n = strlen(melody);
  for (int i=0; i<n; i++) {
    double dur = (note[i]-'0')*60000.0/bpm;
    int f;
    if (melody[i+1]=='+') f=sharpfreq[melody[i]-'1'], i++;
    else if (melody[i+1]=='^') f=1175;
    else f=freq[melody[i]-'1'];
    tone(buzz, f, dur);
    delay(dur*1.3);
    noTone(buzz);
  }
  delay(1000);
}
