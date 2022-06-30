#include "ScoreboardLCD.h"

ScoreboardLCD::ScoreboardLCD(LiquidCrystal *myLCD) {
  lcd = myLCD;
  currentLine = 0;
}

void ScoreboardLCD::initalize() {
  (*lcd).begin(16, 2);
  printMenu();
}

void ScoreboardLCD::printMenu() {
  (*lcd).clear();
  for (int i=0; i < 2; i++) {
    (*lcd).setCursor(0, i);
    String msg = (i == currentLine ? "> " : "  ") + messages[i];
    (*lcd).print(msg);
  }
  (*lcd).setCursor(0, currentLine);
}

void ScoreboardLCD::printPlayerMenu(int playerNum) {
  (*lcd).clear();
  (*lcd).setCursor(0, 0);
  (*lcd).print(String("*Enter P") + playerNum + String(" Score*"));
  (*lcd).setCursor(0, 1);
  (*lcd).print("      # for menu");
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
      (*lcd).setCursor(0, 0);
      (*lcd).print(" ");
      (*lcd).setCursor(0, 1);
      (*lcd).print(">");
    }
  } else if (cmd == "up") {
    if (currentLine == 0) {
      return;
    }
    currentLine -= 1;
    if (currentLine == 0) {
      (*lcd).setCursor(0, 1);
      (*lcd).print(" ");
      (*lcd).setCursor(0, 0);
      (*lcd).print(">");
    } else if (currentLine == 1) {
      for (int i=0; i < 2; i++) {
        (*lcd).setCursor(0, i);
        String msg = (i == 1 ? "> " : "  ") + messages[i];
        (*lcd).print(msg);
      }
      (*lcd).setCursor(0, 1);
    }
  } else if (cmd == "ok") {
    String msg = messages[currentLine];
    if (msg == "Set P1 Score") {
      *statePtr = "p1";
      printPlayerMenu(1);
    } else if (msg == "Set P2 Score") {
      *statePtr = "p2";
      printPlayerMenu(2);
    } else if (msg == "New Game") {
      *statePtr = "newGame";
    }
  }
}
