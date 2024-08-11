#include <Keypad.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int n = 0;
int digit[4];
int adigit[4] = {1, 2, 3, 4};
int temp = 0;
int temp_new = 0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //R1,R2,R3,R4, connect to the row pinouts of the keypad
byte colPins[COLS] = {9 , 8, 7, 6}; //C1,C2,C3,C4,connect to the column pinouts of the keypad
//R1,R2,R3,R4,C1,C2,C3,C4

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd
  lcd.init();

  Serial.println("  ");
  Serial.println("-----Read data from EEPROM-----");
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password :");

  adigit[0] = EEPROM.read(0);
  adigit[1] = EEPROM.read(1);
  adigit[2] = EEPROM.read(2);
  adigit[3] = EEPROM.read(3);

  Serial.println(EEPROM.read(0));
  Serial.println(EEPROM.read(1));
  Serial.println(EEPROM.read(2));
  Serial.println(EEPROM.read(3));

  Serial.println("  ");
  Serial.println("--------------------------------");
  Serial.println("Enter password to Open Door");
  Serial.println("--------------------------------");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if ((key == 'A') or (key == 'B') or (key == 'A') or (key == 'C') or (key == 'D') or (key == '*') or (key == '#') ) {
      if (key == 'C') {
        digitalWrite(11, 0);
        n = 0;
        digit[0] = 0;
        digit[1] = 0;
        digit[2] = 0;
        digit[3] = 0;
        temp = 0;
        Serial.println("  ");
        Serial.println("--------------------------------");
        Serial.println("Door CLOSED");
        Serial.println("Enter password to Open Door");
        Serial.println("--------------------------------");

        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("                ");
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Door Closed");
        delay(1500);
        lcd.setCursor(0, 0);
        lcd.print("Enter PW to Open");
        lcd.setCursor(0, 1);
      }

      if ((key == 'A') and (temp == 1)) {
        digitalWrite(11, 1);
        Serial.println("  ");
        Serial.println("--------------------------------");
        Serial.println("Door OPEN");
        Serial.println("Press-C for Close Door");
        Serial.println("--------------------------------");

        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("                ");
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Door Opened");
        delay(1000);
        lcd.setCursor(0, 1);
        lcd.print("To close -> C");
      }
      if ((key == 'A') and (temp == 0)) {
        Serial.println("  ");
        Serial.println("--------------------------------");
        Serial.println("Incorrect Password");
        Serial.println("Enter password to Open Door");
        Serial.println("--------------------------------");

        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("                ");
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Incorect");
        delay(1500);
        lcd.setCursor(0, 0);
        lcd.print("Enter again");
        lcd.setCursor(0, 1);
      }



      if ((key == 'B') and (temp == 1)) {
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("                ");
        delay(500);

        lcd.setCursor(0, 0);
        lcd.print("Enter new PW->");

        Serial.println("  ");
        Serial.println("--------------------------------");
        Serial.println("Enter new password");
        Serial.println("--------------------------------");

        
        n = 0;
        temp_new = 1;
      }
      if ((key == 'D') and (digit[0] != 0) and (digit[1] != 0) and (digit[2] != 0) and (digit[3] != 0)) {
        temp_new = 0;
        adigit[0] = digit[0];
        adigit[1] = digit[1];
        adigit[2] = digit[2];
        adigit[3] = digit[3];

        EEPROM.write(0, adigit[0]);
        EEPROM.write(1, adigit[1]);
        EEPROM.write(2, adigit[2]);
        EEPROM.write(3, adigit[3]);

        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 1);
        lcd.print("]");
        delay(500);

        lcd.setCursor(0, 0);
        lcd.print("New PW Saved.");
        delay(1500);

        lcd.setCursor(0, 0);
        lcd.print("Enter PW to Open");
        lcd.setCursor(0, 1);

        Serial.println("  ");
        Serial.println("--------------------------------");
        Serial.println("Saved new password");
        Serial.println("Enter password to Open Door");
        Serial.println("--------------------------------");
      }
      //else {
      //  Serial.println("0000 cant be used as a password");
      //}


    }
    else {
      digit[n] = key - 48;
      Serial.print("n:");
      Serial.print(n);
      Serial.print("  ");
      Serial.println(digit[n]);
      lcd.setCursor(n, 1);
      lcd.print(digit[n]);
      delay(500);
      lcd.setCursor(n, 1);
      lcd.print("*");
      n++;
      if (n > 3) {
        if ((digit[0] == adigit[0]) && (digit[1] == adigit[1]) && (digit[2] == adigit[2]) && (digit[3] == adigit[3])) {
          temp = 1;
          lcd.setCursor(0, 0);
          lcd.print("                ");
          lcd.setCursor(0, 1);
          lcd.print("                ");
          delay(100);
          Serial.println("  ");
          Serial.println("--------------------------------");
          lcd.setCursor(0, 0);
          lcd.print("Open Door -> A");
          lcd.setCursor(0, 1);
          lcd.print("Change PW -> B");

          Serial.println("Press-A for Open Door");
          Serial.println("Press-B for Change password");
          Serial.println("--------------------------------");
        }
        else {
          temp = 0;
          if (temp_new == 1) {
            lcd.setCursor(0, 0);
            lcd.print("                ");
            lcd.setCursor(0, 1);
            lcd.print("                ");
            delay(500);
            Serial.println("Press-D for save password");
            lcd.setCursor(0, 0);
            lcd.print("Save PW -> D");
          }
        }
        n = 0;
        if ((temp_new == 0) and (temp == 0)) {
          lcd.setCursor(0, 0);
          lcd.print("                ");
          lcd.setCursor(0, 1);
          lcd.print("                ");
          delay(500);
          lcd.setCursor(0, 0);
          lcd.print("Open Door -> A");

          Serial.println("  ");
          Serial.println("--------------------------------");
          Serial.println("Press-A for Open Door");
          Serial.println("--------------------------------");
        }
      }
    }
  }
}
