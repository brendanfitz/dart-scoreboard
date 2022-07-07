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
  int numLines;
  if ((currentLine == messageCount - 1) && (messageCount % 2 == 1)) {
    numLines = 1;
  } else {
    numLines = 2;
  }
  int startLine = currentLine - (currentLine % 2);
  for (int i=0; i < numLines; i++) {
    (*lcd).setCursor(0, i);
    String msg = (startLine + i == currentLine ? "> " : "  ") + messages[startLine + i];
    (*lcd).print(msg);
  }
  (*lcd).setCursor(0, currentLine % 2);
}

void ScoreboardLCD::printGameOver(int winnerNum) {
  (*lcd).clear();
  (*lcd).setCursor(0, 0);
  (*lcd).print("** Game Over! **");
  (*lcd).setCursor(0, 1);
  (*lcd).print(String(" Player ") + winnerNum + String(" Wins!"));
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
    if (currentLine == messageCount - 1)  {
      return;
    }
    currentLine += 1;
    if (currentLine % 2 == 0) {
      printMenu();
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
    if (currentLine % 2 == 0) {
      (*lcd).setCursor(0, 0);
      (*lcd).print(">");
      (*lcd).setCursor(0, 1);
      (*lcd).print(" ");
    } else {
      printMenu();
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
