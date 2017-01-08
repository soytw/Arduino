// byte btnMap[16][2] = {
//     // analog / digital
//     // row / column
//     {0, 2},
//     {0, 3},
//     {0, 5},
//     {0, 6},
//     {1, 2},
//     {1, 3},
//     {1, 5},
//     {1, 6},
//     {2, 2},
//     {2, 3},
//     {2, 5},
//     {2, 6},
//     {3, 2},
//     {3, 3},
//     {3, 5},
//     {3, 6},
// };

#include <Keypad.h>

byte keys[4][4] = {
    { 1,  2,  3,  4},
    { 5,  6,  7,  8},
    { 9, 10, 11, 12},
    {13, 14, 15, 16},
};
byte rowPin[4] = {2, 3, 5, 6};
byte colPin[4] = {A0, A1, A2, A3};
bool btnState[17];
Keypad keypad = Keypad(makeKeymap(keys), rowPin, colPin, 4, 4);

void setup() {
    Serial.begin(9600);
}

void loop() {
    byte key = keypad.getKey();
    if (key != 0) {
        Serial.println(key);
    }

    // for (int i=0; i<=9; i++) {
    //     Serial.print("  ");
    //     Serial.print(i);
    // }
    // Serial.println(" 10 11 12 13    a0    a1    a2    a3    a4");

    // for (int i=0; i<=13; i++) {
    //     Serial.print("  ");
    //     Serial.print(digitalRead(i));
    // }
    // for (int i=0; i<=5; i++) {
    //     Serial.print("    ");
    //     Serial.print(analogRead(i));
    // }
    // Serial.println();
    // Serial.print(getKey());
    // Serial.println();
    // for (int i=0; i<16; i++) {
    //     Serial.print(btnState[i]);
    //     Serial.print(" ");
    // }
    // Serial.println();
    // delay(1000);

    // if (Serial.available()) {
        // Serial.readString();
        // for (int i=0; i<16; i++) {
        //     btnState[i] = (analogRead(btns[i][0]) >= 1000
        //                 && digitalRead(btns[i][1]) == HIGH);
        //     Serial.print("btn");
        //     Serial.print(i);
        //     Serial.print(" = ");
        //     Serial.println(btnState[i]);
        // }
        // Serial.println();
        // delay(1000);
    // }
}
