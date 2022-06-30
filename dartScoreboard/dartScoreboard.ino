#include <IRremote.h>
#include <LiquidCrystal.h>
#include "Player.h"
#include "ScoredboardRemote.h"
#include "ScoreboardLCD.h"
#define LCD_RS 2
#define LCD_EN 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define IRpin 13
#define CLK 22
#define DIO 24
#define INPUT_CLK 26
#define INPUT_DIO 28

String cmd;

LiquidCrystal myLCD(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
ScoreboardLCD lcd(&myLCD);

TM1637Display scoreDisplayP1(CLK, DIO);
TM1637Display inputDisplayP1(INPUT_CLK, INPUT_DIO);

Player player1(301, &scoreDisplayP1, &inputDisplayP1);

String state = "main";

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IRpin, ENABLE_LED_FEEDBACK);
  lcd.initalize();
   
  delay(1000);
  player1.initalizeDisplay();
}

void loop() {
  if (IrReceiver.decode()) {
    cmd = processCommand(String(IrReceiver.decodedIRData.decodedRawData, HEX));
    Serial.print("You pressed ");
    Serial.println(cmd);
    if (state == "main") {
      lcd.processCommand(cmd, &state);

      if (state == "newGame") {
        // TODO: reset function for p1 and p2
      }
    } else if (state == "p1") {
      player1.processCommand(cmd, &state);
    }
    Serial.print("Current State: ");
    Serial.println(state);
    delay(250);
    IrReceiver.resume();
  }
}
