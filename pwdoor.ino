#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <avr/wdt.h>  

const char pwd[6] = {'9','0','3','0','4','8'};
char inpwd[6];
const int pwdlen = 6;
int pwlen = pwdlen;

const int servo_close=70;
const int servo_open=120;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {22,24,26,28}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {30,32,34,36}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(38,40,42,44,46,48);

Servo servo;
//蜂鸣器
void Buzzer();

void setup() {
  //看门狗
  wdt_enable(WDTO_4S);
  servo.attach(3);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  servo.write(servo_close);
  lcd.print("Please input pwd");
  //设置lcd对比度
  pinMode(2,OUTPUT);
  analogWrite(2,135); 
  //蜂鸣器
  pinMode(50,OUTPUT);
  digitalWrite(50,HIGH);
}

void loop() {
  char key = keypad.getKey();
   servo.write(servo_close);
  if(key) {
    Buzzer();
    //看门狗复位
    wdt_reset();
      if(key!='D') {
        if(pwlen==pwdlen)
          lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("inputing pwd:");
        lcd.setCursor((pwdlen-(pwlen--)),1);
        lcd.print('*');
        //判断密码正确与否
        if(pwlen>=0) {
            inpwd[pwdlen-pwlen-1] = key;
          }
      }
      else {
          for(int n=0;n<pwdlen;n++)
            if(inpwd[n]!=pwd[n]) {
                  lcd.clear();
                   lcd.setCursor(0,0);
                   lcd.print("password error!");
                    digitalWrite(50,LOW);
                   delay(6000);
              }
              
               lcd.clear();
                   lcd.setCursor(0,0);
              lcd.print("password pass!");
              

                   //开门
             servo.write(servo_open);
             delay(1500);
             servo.write(servo_close);
                  delay(6000);
        }
  }
}

void Buzzer() {
    digitalWrite(50,LOW);
    delay(100);
    digitalWrite(50,HIGH);
  }














