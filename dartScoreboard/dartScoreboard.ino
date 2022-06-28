#include <IRremote.h>
#include <LiquidCrystal.h>
#include "Player.h"
#include "ScoredboardRemote.h"
#define CLK 2
#define DIO 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_RS 8
#define LCD_EN 9
#define INPUT_CLK 10
#define INPUT_DIO 11
#define IRpin 13

String cmd;

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
const char *message = "Hello, world!";
String messages[] = {
  "Set P1 Score",
  "Set P2 Score"  
};
int lineNum = 0;  

TM1637Display scoreDisplayP1(CLK, DIO);
TM1637Display inputDisplayP1(INPUT_CLK, INPUT_DIO);

Player player1(501, &scoreDisplayP1, &inputDisplayP1);

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IRpin, ENABLE_LED_FEEDBACK);
  lcd.begin(16, 2);
  for (int i=0; i < 2; i++) {
    lcd.setCursor(0, i);
    String msg = messages[i];
    lcd.print(msg);
  }
  lcd.setCursor(0, 0);
  lcd.cursor();
   
  delay(1000);
  Serial.println("Setting brightness");
  (*player1.inputDisplay).setBrightness(7);
  (*player1.scoreDisplay).setBrightness(7);

  Serial.println("Displaying Score");
  player1.setDisplay("Score");
  player1.setDisplay("Input");
  Serial.println("Setup Done");
}

void loop() {
  if (IrReceiver.decode()) {
    cmd = processCommand(String(IrReceiver.decodedIRData.decodedRawData, HEX));
    Serial.print("You pressed ");
    // String btnCode = String(IrReceiver.decodedIRData.decodedRawData, HEX);
    // btnCode.toUpperCase();
    Serial.println(cmd);
    if (cmd.charAt(0) == '0') {
      player1.calcInput(cmd.toInt());
      Serial.print("Player 1 Score: ");
      Serial.println(player1.getInput());
      player1.setDisplay("Input");
    } else if (cmd == "*") {
      player1.setInput(0);
      player1.setDisplay("Input");
    } else if (cmd == "ok") {
      player1.updateScore(player1.getInput());
      player1.setDisplay("Score");
      player1.setInput(0);
      player1.setDisplay("Input");
    }
    delay(250);
    IrReceiver.resume();
  }
}
