#include <TMRpcm.h>
#include <Keypad.h>
#include <SD.h>

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

#define MAX_RECORD_LEN 30
struct Record {
  byte key;
  unsigned int dur;
  Record(): key(0), dur(0) {}
} rec[MAX_RECORD_LEN];
byte reclen = 0;

TMRpcm audio;
enum {FREE_PLAY, PLAY, RECORD} mode;


#ifdef debug
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
    for (int i=0; i<numTabs; i++) {
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
#endif

void playPianoKey(byte key) {
  String notename[] = {"", "C5", "C5S", "D5", "D5S", "E5", "F5", "F5S", "G5", "G5S", "A5", "A5S", "B5"};
  String type = "violin";
  String filename = type + "/" + notename[key] + ".wav";
  Serial.println(filename);
  audio.play(filename.c_str());
}

void recordKey(byte key, int dur) {
  if (reclen >= MAX_RECORD_LEN) {
    Serial.println("record limit reached!");
    return;
  }
  rec[reclen].key = key;
  rec[reclen].dur = dur;
  Serial.print("record key: ");
  Serial.print(rec[reclen].key);
  Serial.print(" ");
  Serial.println(rec[reclen].dur);
  reclen++;
}

void writeRecord() {
  File recfile = SD.open("record.txt", FILE_WRITE);
  if (recfile) {
    Serial.println("writing record");
    recfile.write((byte*)rec, sizeof(Record)*reclen);
    recfile.close();
  } else {
    Serial.println("record.txt failed");
  }
}

void onclick(byte key) {
  Serial.print("pressed: ");
  Serial.println(key);
  if (key >= 1 && key <= 12) {
    // piano key
    if (mode == RECORD) {
      unsigned long tm = millis();
      while (keypad.getState() == HOLD);
      recordKey(key, millis()-tm);
    } else if (mode == FREE_PLAY) {
      playPianoKey(key);
      while (keypad.getState() == HOLD);
      audio.pause();
    }
  } else if (key == 13) {
    // play / pause
  } else if (key == 14) {
    // play / record
    if (mode == FREE_PLAY) {
      mode = RECORD;
      Serial.println("record mode");
    } else if (mode == RECORD) {
      mode = FREE_PLAY;
      Serial.println("free play mode");
    }
  } else if (key == 15) {
    // next sound
  } else if (key == 16) {
    // ??
  } else {
    // no key pressed
  }
  Serial.print("released: ");
  Serial.println(key);
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println(F("Initializing SD Card"));
  if (SD.begin(SD_PIN)) {
    Serial.println("Success");
    Serial.println("Files:");
    File root = SD.open("/");
    printDir(root);
  } else {
    Serial.print("SD fail");
  }

  keypad.addEventListener(onclick);
  audio.speakerPin = SPEAKER_PIN;
  pinMode(VOL_PIN, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  audio.setVolume(map(analogRead(VOL_PIN), 0, 1023, 0, 7));
}
