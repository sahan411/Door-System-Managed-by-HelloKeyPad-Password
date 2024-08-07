/* @file HelloKeypad.pde
  || @version 1.0
  || @author Alexander Brevig
  || @contact alexanderbrevig@gmail.com
  ||
  || @description
  || | Demonstrates the simplest use of the matrix Keypad library.
  || #
*/
#include <Keypad.h>
char a[3];
int x;
int count = 0;

char digit[4];
char adigit[4] = {'1','2','3','4'}; 
int n = 0;
int value;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  /*
    if (key){
    Serial.println(key);
    if(count < 3){
      a[count] = key;
      count++;
    }
    if(count == 3){
      int result = atoi(a);
      Serial.println(result);
      count = 0;
    }
    }
  */

  if (key) {
    if ((key == 'A')or(key == 'B')or(key == 'C')or(key == 'D')or(key == '*')or(key == '#')){
      if(key=='C'){
        digitalWrite(10, 0);
      }
    }
    if(key=='A'){
      if ((digit[0] == adigit[0]) and (digit[1] == adigit[1]) and (digit[2] == adigit[2]) and (digit[3] == adigit[3])) {
          digitalWrite(10, 1);
        }
    }
    if(key=='B'){
      n = 0;
    }
    if(key=='D'){
      digit[0] = '0';
      digit[1] = '0';
      digit[2] = '0';
      digit[3] = '0';
    }
    
    Serial.print("  d0:");
    Serial.print(digit[0]);
    Serial.print("  d1:");
    Serial.print(digit[1]);
    Serial.print("  d2:");
    Serial.print(digit[2]);
    Serial.print("  d3:");
    Serial.print(digit[3]);

  }




}
