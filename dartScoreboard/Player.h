#ifndef __PLAYER__
#define __PLAYER__

#include <Arduino.h>
#include <TM1637Display.h>

class Player {
public:
    Player(int gameScore, TM1637Display *inputDisplayPtr,
           TM1637Display *scoreDisplayPtr);

    void initalizeDisplay();

    void reset();

    void updateScore(int amount);

    int getScore();

    void setDisplay(String displayName);

    void setInput(int num);

    int getInput();
    
    void calcInput(int num);

    void processCommand(String cmd, String *statePtr);
    
    TM1637Display *scoreDisplay;
    TM1637Display *inputDisplay;
private:
    int score;
    int inputNum;
};
#endif
