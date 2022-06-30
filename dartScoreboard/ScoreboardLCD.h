
#ifndef __SCOREBOARD_LCD__
#define __SCOREBOARD_LCD__

#include <Arduino.h>
#include <LiquidCrystal.h>

class ScoreboardLCD {
  public:
    ScoreboardLCD(LiquidCrystal *myLCD);

    void initalize();

    void processCommand(String cmd, String *statePtr);

    LiquidCrystal *lcd;

  private:
    String messages[3] = {"Set P1 Score", "Set P2 Score" , "New Game"};
    int currentLine;
};

#endif
