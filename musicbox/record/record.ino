#include <Keypad.h>
#include <FileIO.h>
byte keys[4][4] = {
    { 1,  2,  3,  4},
    { 5,  6,  7,  8},
    { 9, 10, 11, 12},
    {13, 14, 15, 16},
};
byte rowPin[4] = {2, 3, 5, 6};
byte colPin[4] = {A0, A1, A2, A3};
Keypad keypad = Keypad(makeKeymap(keys), rowPin, colPin, 4, 4);

int btnofrec = 9;

struct record {
  byte key = 0;
  double dur = 0;
  String type = "violin";
} REC[105];
int pt = 0;
bool on = false;
bool Write = false;
String Data;

void setup() {
  Serial.begin(9600);
  pinMode(btnofrec,INPUT);
  FileSystem.begin();
  while ( !Serial );
}

void loop() {
    if ( digitalRead(btnofrec) ) {
      Serial.println("Record Mode On");
      delay(100);
      on = true;
      while ( on ) {
        REC[pt].key = keypad.getKey();
  //      if ( REC[pt].key )  
          Serial.println(REC[pt].key);
        if ( REC[pt].key >= 1 && REC[pt].key <= 12 ) {
          if ( pt ) 
            REC[pt-1].dur = millis() - REC[pt-1].dur;
          REC[pt++].dur = millis();
        }
        if ( digitalRead(btnofrec) ) {
          Serial.println("Record More Off");
          Write = true;
          break;
        }
      }
  if ( Write ) {
    //  store into string
    Data = "";
    for ( int i=0; i<pt; i++ ) {
      Data += REC[i].key;
      Data += " ";
      Data += REC[i].dur;
      Data += "\n";
      }
    }
    //  write in SD
    const char filenamepath[] = "/mnt/sda1/record.txt";
    int mode = FileSystem.exists(filenamepath) ? FILE_APPEND : FILE_WRITE;
    File file = FileSystem.open("/mnt/sda1/record.txt",mode); 
  
    if ( file ) {
      file.println(Data);
      file.close();
    }
    Write = false;
  }
}
