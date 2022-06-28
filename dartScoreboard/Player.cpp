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
