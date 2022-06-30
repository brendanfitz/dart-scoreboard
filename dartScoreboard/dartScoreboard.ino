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
#define P1_CLK 22
#define P1_DIO 24
#define P1_INPUT_CLK 26
#define P1_INPUT_DIO 28
#define P2_CLK 30
#define P2_DIO 32
#define P2_INPUT_CLK 34
#define P2_INPUT_DIO 36

String cmd;

LiquidCrystal myLCD(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
ScoreboardLCD lcd(&myLCD);

TM1637Display scoreDisplayP1(P1_CLK, P1_DIO);
TM1637Display inputDisplayP1(P1_INPUT_CLK, P1_INPUT_DIO);
TM1637Display scoreDisplayP2(P2_CLK, P2_DIO);
TM1637Display inputDisplayP2(P2_INPUT_CLK, P2_INPUT_DIO);

int gameScore = 301;
Player player1(gameScore, &scoreDisplayP1, &inputDisplayP1);
Player player2(gameScore, &scoreDisplayP2, &inputDisplayP2);


String state = "main";

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IRpin, ENABLE_LED_FEEDBACK);
  lcd.initalize();
   
  delay(1000);
  player1.initalizeDisplay();
  player2.initalizeDisplay();
}

void loop() {
  if (IrReceiver.decode()) {
    cmd = processCommand(String(IrReceiver.decodedIRData.decodedRawData, HEX));
    Serial.print("You pressed ");
    Serial.println(cmd);
    if (state == "main") {
      lcd.processCommand(cmd, &state);

      if (state == "newGame") {
        player1.reset();
        player2.reset();
        state = "main";
      }
    } else if (state == "p1") {
      player1.processCommand(cmd, &state);
      if (state == "main") {
        lcd.printMenu();
      }
    } else if (state == "p2") {
      player2.processCommand(cmd, &state);
      if (state == "main") {
        lcd.printMenu();
      }
    }
    Serial.print("Current State: ");
    Serial.println(state);
    delay(250);
    IrReceiver.resume();
  }
}
