/*
 Simple SD Audio example, shows the usage of most functions
 via terminal at serial communication port.

 This example shows how to use the SimpleSDAudio library for audio playback.
 You need:
 - An Arduino with ATmega168/ATmega368 or better
 - An SD-Card connected to Arduinos SPI port (many shields will do)
   -> copy some converted audio files on freshly formated SD card into root folder
 - A passive loudspeaker and resistor or better: active speakers (then stereo output will be possible)

 Audio signal output is at the following pin:
 - Arduino with ATmega168/328   (many non-mega Arduinos): Pin 9
 - Arduino with ATmega1280/2560 (many mega Arduinos)    : Pin 44

 Using passive speaker:
    Audio-Pin --- -[100 Ohm resistor]- ---- Speaker ---- GND

 Using amplifier / active speaker / line-in etc.:
    Audio-Pin --||--------------[10k resistor]----+----[1k resistor]---- GND
              100nF capacitor                   to amp

 See SimpleSDAudio.h or our website for more information:
 http://www.hackerspace-ffm.de/wiki/index.php?title...

 created  29 Jun 2012 by Lutz Lisseck
 */

#include <stdio.h>
#include <SimpleSDAudio.h>
#include <Keypad.h>
#include "music.h"


byte keys[4][4] = {
    { 1,  2,  3,  4},
    { 5,  6,  7,  8},
    { 9, 10, 11, 12},
    {13, 14, 15, 16},
};
byte rowPin[4] = {2, 3, 5, 6};
byte colPin[4] = {A0, A1, A2, A3};
Keypad keypad = Keypad(makeKeymap(keys), rowPin, colPin, 4, 4);

#define MAX_MUSICSHEET_LEN 50
char musicsheet[MAX_MUSICSHEET_LEN];
Music::Note notes[MAX_MUSICSHEET_LEN];

// Create static buffer
// bigger than 2*512 is often only possible on Arduino megas!
#define BIGBUFSIZE (2*512)
byte bigbuf[BIGBUFSIZE];


// Callback target, prints output to serial
void DirCallback(char *buf) {
  Serial.println(buf);
}

// helper function to determine free ram at runtime
int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
  Serial.begin(9600);

  Serial.print(F("Free Ram: "));
  Serial.println(freeRam());

  // Setting the buffer manually for more flexibility
  SdPlay.setWorkBuffer(bigbuf, BIGBUFSIZE);

  Serial.print(F("\nInitializing SimpleSDAudio V" SSDA_VERSIONSTRING " ..."));

  // If your SD card CS-Pin is not at Pin 4, enable and adapt the following line:
  //SdPlay.setSDCSPin(10);

  // Select between SSDA_MODE_FULLRATE or SSDA_MODE_HALFRATE (62.5kHz or 31.25kHz)
  // and the output modes SSDA_MODE_MONO_BRIDGE, SSDA_MODE_MONO or SSDA_MODE_STEREO
  if (!SdPlay.init(SSDA_MODE_FULLRATE | SSDA_MODE_MONO)) {
    Serial.println(F("initialization failed. Things to check:"));
    Serial.println(F("* is a card is inserted?"));
    Serial.println(F("* Is your wiring correct?"));
    Serial.println(F("* maybe you need to change the chipSelect pin to match your shield or module?"));
    Serial.print(F("Error code: "));
    Serial.println(SdPlay.getLastError());
    while (1);
  } else {
    Serial.println(F("Wiring is correct and a card is present."));
    Serial.println(F("Files on card:"));
    SdPlay.dir(&DirCallback);
  }
}

void loop() {
  byte key = keypad.getKey();
  if (key) Serial.println(key);
  if (key >= 1 && key <= 12) {
    String type="PIA", filename;
    if (key == 1)
      filename = "C5.afm";
    else if (key == 2)
      filename = "C5S.afm";
    else if (key == 3)
      filename = "D5.afm";
    else if (key == 4)
      filename = "D5S.afm";
    else if (key == 5)
      filename = "E5.afm";
    else if (key == 6)
      filename = "F5.afm";
    else if (key == 7)
      filename = "F5S.afm";
    else if (key == 8)
      filename = "G5.afm";
    else if (key == 9)
      filename = "G5S.afm";
    else if (key == 10)
      filename = "A5.afm";
    else if (key == 11)
      filename = "A5S.afm";
    else if (key == 12)
      filename = "B5.afm";

    // SdPlay.SD_L2_SearchFile((byte*)fileName.c_str(), 0UL, 0x00, 0x18, &_fileinfo);
    SdPlay.setFile((type+'-'+filename).c_str());
    Serial.println(type+'-'+filename);
    SdPlay.play();
    unsigned long starttime = millis();
    while (!SdPlay.isStopped()) SdPlay.worker();
  } else if (key == 13) {
    // play / pause
  } else if (key == 14) {
    // mode: record / play
  } else if (key == 15) {
    // next sound
  } else if (key == 16) {
    // ??
  }

  // byte count=0, c, flag;

  // Serial.println(F("Files on card:"));
  // SdPlay.dir(&DirCallback);

// ReEnter:
  // count = 0;
  // Serial.println(F("\r\nEnter music sheet (20 characters at most) (send LF after line):"));
  // do {
  //   while (!Serial.available());
  //   c = Serial.read();
  //   if (c > ' ') musicsheet[count++] = c;
  // } while (c != '\n' && c != '\r' && count < MAX_MUSICSHEET_LEN);
  // musicsheet[count++] = 0;

  // uint8_t len = Music::fromstr(musicsheet,notes,240);
  // byte len = Music::fromstr("55552-0055552-00555554567-5-2-",notes,240); // test

  // Serial.print("You entered: ");
  // Serial.println(musicsheet);

  // each pitch is at most 1.6 seconds long
  // so the minimum BPM = 37.5
  // char notename[] = " CDEFGAB";
  // for (int i=0; i<len; i++) {
  //   if (notes[i].pitch != 0) {
  //     char filename[10];
  //     if (notes[i].sharp)
  //       sprintf(filename, "%c%ds.afm", notename[notes[i].pitch], notes[i].octave);
  //     else
  //       sprintf(filename, "%c%d.afm", notename[notes[i].pitch], notes[i].octave);
  //     bool result = SdPlay.setFile(filename);

  //     // DEBUG
  //     Serial.print("Playing: ");
  //     Serial.println(filename);
  //     if (result)
  //       Serial.println("Found");
  //     else {
  //       Serial.print("Error: ");
  //       Serial.println(SdPlay.getLastError());
  //     }
  //     // END DEBUG

  //     SdPlay.play();
  //   }
  //   unsigned long starttime = millis();
  //   while (millis()-starttime <= notes[i].dur) {
  //     SdPlay.worker();
  //   }
  // }

  // delay(1000);

  // Serial.print(F("Looking for file... "));
  // if(!SdPlay.setFile("default.afm")) {
  //   Serial.println(F(" not found on card! Error code: "));
  //   Serial.println(SdPlay.getLastError());
  //   goto ReEnter;
  // } else {
  //  Serial.println(F("found."));
  // }

  // Serial.println(F("s: stop"));
  // Serial.println(F("p: play"));
  // Serial.println(F("h: pause"));
  // Serial.println(F("f: reenter sheet"));
  // Serial.println(F("d: unmount SD"));
  // Serial.println(F("v: view status"));
  // flag = 1;

  // while(flag) {
  //   SdPlay.worker();
  //   if(Serial.available()) {
  //     c = Serial.read();
  //     switch(c) {
  //        case 's':
  //          SdPlay.stop();
  //          Serial.println(F("Stopped."));
  //          break;

  //        case 'p':
  //          SdPlay.play();
  //          Serial.println(F("Play."));
  //          break;

  //        case 'h':
  //          SdPlay.pause();
  //          Serial.println(F("Pause."));
  //          break;

  //        case 'd':
  //          SdPlay.deInit();
  //          Serial.println(F("SdPlay deinitialized. You can now safely remove card. System halted."));
  //          while(1) ;
  //          break;

  //        case 'f':
  //          flag = 0;
  //          break;

  //        case 'v':
  //          Serial.print(F("Status: isStopped="));
  //          Serial.print(SdPlay.isStopped());
  //          Serial.print(F(", isPlaying="));
  //          Serial.print(SdPlay.isPlaying());
  //          Serial.print(F(", isPaused="));
  //          Serial.print(SdPlay.isPaused());
  //          Serial.print(F(", isUnderrunOccured="));
  //          Serial.print(SdPlay.isUnderrunOccured());
  //          Serial.print(F(", getLastError="));
  //          Serial.println(SdPlay.getLastError());
  //          Serial.print(F("Free RAM: "));
  //          Serial.println(freeRam());
  //          break;
  //     }
  //   }
  // }
}
