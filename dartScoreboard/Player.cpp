extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
}


#include "Player.h"
#include <Arduino.h>
#include <TM1637Display.h>

Player::Player(int gameScore, TM1637Display *inputDisplayPtr,
               TM1637Display *scoreDisplayPtr) {
    score = gameScore;
    scoreDisplay = inputDisplayPtr;
    inputDisplay = scoreDisplayPtr;
    inputNum = 0;
}

void Player::initalizeDisplay() {
  Serial.println("Setting brightness");
  (*inputDisplay).setBrightness(7);
  (*scoreDisplay).setBrightness(7);

  Serial.println("Displaying Score");
  setDisplay("Score");
  setDisplay("Input");
  Serial.println("Setup Done");
}

void Player::updateScore(int amount) {
  if (amount > score) {
    return;
  }
  score = max(0, score - amount);
}

void Player::calcInput(int num) {
  inputNum = inputNum - (inputNum / 100 * 100);
  inputNum = inputNum * 10 + num;
}

void Player::reset() {
  score = 301;
  inputNum = 0;
  initalizeDisplay();
}

int Player::getScore() {
  return score;
}

void Player::setInput(int num) {
  inputNum = num;
}

int Player::getInput() {
  return inputNum;
}

void Player::setDisplay(String displayName) {
  int l;
  int num = (displayName == "Score") ? score : inputNum;
  /* switch to using log10 */
  if (num >= 10000 ) { return; } 
  else if (num >= 1000) { l = 4; } 
  else if (num >= 100) { l = 3; }
  else if (num >= 10) { l = 2; }
  else { l = 1; }
  int pos = l*-1 + 4;
  // Serial.print("l: ");
  // Serial.print(l);
  // Serial.print(", pos: ");
  // Serial.print(pos);
  if (displayName == "Score") {
    // Serial.print(", score: ");
    // Serial.println(score);
    (*scoreDisplay).clear();
    (*scoreDisplay).showNumberDec(score, false, l, pos);
  } else {
    // Serial.print(", inputNum: ");
    // Serial.println(inputNum);
    (*inputDisplay).clear();
    (*inputDisplay).showNumberDec(inputNum, false, l, pos);
  }
}

void Player::processCommand(String cmd, String *statePtr) {
  if (cmd.charAt(0) == '0') {
    calcInput(cmd.toInt());
    Serial.print("Player Score: ");
    Serial.println(getInput());
    setDisplay("Input");
  } else if (cmd == "*") {
    setInput(0);
    setDisplay("Input");
  } else if (cmd == "ok") {
    updateScore(getInput());
    setDisplay("Score");
    setInput(0);
    setDisplay("Input");
  } else if (cmd == "#") {
    *statePtr = "main";
    setInput(0);
  }
  return;
}
