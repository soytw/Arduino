#include <TMRpcm.h>
#include <Keypad.h>

#define debug

#define VOL_PIN A4
#define SD_PIN 4
#define SPEAKER_PIN 9

byte keys[4][4] = {
    { 1,  2,  3,  4},
    { 5,  6,  7,  8},
    { 9, 10, 11, 12},
    {13, 14, 15, 16},
};
byte rowPin[4] = {2, 3, 5, 6};
byte colPin[4] = {A0, A1, A2, A3};
Keypad keypad = Keypad(makeKeymap(keys), rowPin, colPin, 4, 4);

// #define MAX_MUSICSHEET_LEN 50
// char musicsheet[MAX_MUSICSHEET_LEN];
// Music::Note notes[MAX_MUSICSHEET_LEN];

TMRpcm audio;
File sd;


int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void printDir(File dir, int numTabs=0) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    for (uint8_t i=0; i<numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDir(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.print(F("Free Ram: "));
  Serial.println(freeRam());

  Serial.println(F("Initializing SD Card"));
  if (SD.begin(SD_PIN)) {
    Serial.println("Success");
    Serial.println("Files:");
    sd = SD.open("/");
    printDir(sd);
    audio.speakerPin = SPEAKER_PIN;
  } else {
    Serial.print("SD fail");
  }

  pinMode(VOL_PIN, INPUT);
}

void loop() {
  // Serial.println("0 1 2 3 4 5 6 7 8 9 0 1 2 3");
  // for (int i=0; i<=13; i++) {
  //   Serial.print(' ');
  //   Serial.print(digitalRead(i));
  // }
  // Serial.println();

  audio.setVolume(map(analogRead(VOL_PIN), 0, 1023, 0, 7));

  byte key = keypad.getKey();
  if (key) Serial.println(key);

  if (key >= 1 && key <= 12) {
    // piano key
    String notename[] = {"", "C5", "C5S", "D5", "D5S", "E5", "F5", "F5S", "G5", "G5S", "A5", "A5S", "B5"};
    String type = "violin";
    String filename = type + "/" + notename[key] + ".wav";
    Serial.println(filename);
    audio.play(filename.c_str());
    unsigned long tm = millis();
    while (millis() - tm <= 800) audio.loop(1);
    audio.pause();
  } else if (key == 13) {
    // play / pause
  } else if (key == 14) {
    // mode: record / play
  } else if (key == 15) {
    // next sound
  } else if (key == 16) {
    // ??
  } else {
    // no key pressed
    // Serial.println("pause");
    // audio.pause();
  }
}
