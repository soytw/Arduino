const String DATA = "111151516161524141313121211241413131212112414131312121121111515161615241413131212112";
const int BPM = 120; // beats per minute
const int LED = 9;
int i;

void setup() {
    pinMode(LED, OUTPUT);
    i = 0;
}

void loop() {
    if (i >= DATA.length()) {
        i = 0;
        delay(2000);
    }
    int pitch = DATA[i] - '0';
    int beats = DATA[i+1] - '0';
    i += 2;
    analogWrite(LED, 255*pitch/8);
    delay(beats*60000/BPM/2);
    analogWrite(LED, 0);
    delay(beats*60000/BPM/2);
}
