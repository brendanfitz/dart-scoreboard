#include "ScoreboardLCD.h"

ScoreboardLCD::ScoreboardLCD(LiquidCrystal *myLCD) {
  lcd = myLCD;
  currentLine = 0;
}

void ScoreboardLCD::initalize() {
  (*lcd).begin(16, 2);
  (*lcd).clear();
  for (int i=0; i < 2; i++) {
    (*lcd).setCursor(0, i);
    String msg = "> " + messages[i];
    (*lcd).print(msg);
  }
  (*lcd).cursor();
  (*lcd).setCursor(0, 0  );
}

void ScoreboardLCD::processCommand(String cmd, String *statePtr) {
  if (cmd == "dn") {
    if (currentLine == 2) {
      return;
    }
    currentLine += 1;
    if (currentLine == 2) {
      (*lcd).clear();
      (*lcd).setCursor(0, 0);
      String msg = "> " + messages[currentLine];
      (*lcd).print(msg);
      (*lcd).setCursor(0, 0);
    } else if (currentLine == 1) {
      (*lcd).setCursor(0, 1);
    }
  } else if (cmd == "up") {
    if (currentLine == 0) {
      return;
    }
    currentLine -= 1;
    if (currentLine == 0) {
      (*lcd).setCursor(0, 0);
    } else if (currentLine == 1) {
      for (int i=0; i < 2; i++) {
        (*lcd).setCursor(0, i);
        String msg = "> " + messages[i];
        (*lcd).print(msg);
      }
      (*lcd).setCursor(0, 1);
    }
  } else if (cmd == "ok") {
    String msg = messages[currentLine];
    if (msg == "Set P1 Score") {
      *statePtr = "p1";
      (*lcd).blink();
    } else if (msg == "Set P2 Score") {
      *statePtr = "p2";
      (*lcd).blink();
    } else if (msg == "New Game") {
      *statePtr = "newGame";
    }
  }
}
