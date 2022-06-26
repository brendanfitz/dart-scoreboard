#include <IRremote.h>
#include <Dictionary.h>
#include <TM1637Display.h>
#include "remote.h"
#define CLK 2
#define DIO 3
#define IRpin 9

String myKey;
String cmd;

TM1637Display display = TM1637Display(CLK, DIO);
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};

Dictionary &myDict = *(new Dictionary());

void initializeDict() {
  myDict("BA45FF00", "pwr");
  myDict("B946FF00", "v+");
  myDict("B847FF00", "fs");

  myDict("BB44FF00", "<-");
  myDict("BF40FF00", "play");
  myDict("BC43FF00", "->");

  myDict("F807FF00", "dn");
  myDict("EA15FF00", "v-");
  myDict("F609FF00", "up");
  
  myDict("E916FF00", "00");
  myDict("E619FF00", "eq");
  myDict("F20DFF00", "sr");
  
  myDict("F30CFF00", "01");
  myDict("E718FF00", "02");
  myDict("A15EFF00", "03");

  myDict("F708FF00", "04");
  myDict("E31CFF00", "05");
  myDict("A55AFF00", "06");

  myDict("BD42FF00", "07");
  myDict("AD52FF00", "08");
  myDict("B54AFF00", "09");
}

String processCommand() {
  myKey = String(IrReceiver.decodedIRData.decodedRawData, HEX);
  myKey.toUpperCase();
  String cmd = myDict[myKey];
  Serial.print("You pressed ");
  Serial.println(cmd);
  return cmd;
}

int pos = 3;
int displayVal = 0;

void setDisplay(int i) {
  if (pos == 3) {
    display.clear();
    displayVal = 0;
  }
  
  int valMagnitude = -1*pos + 3;
  displayVal += int(pow(double(10), double(valMagnitude))) * i;
  Serial.print("Display Value: ");
  Serial.println(displayVal);
  display.showNumberDec(i, false, 1, pos);
  
  if (pos == 0) {
    pos = 3;
  } else {
    pos--;
  }
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IRpin, ENABLE_LED_FEEDBACK);
  initializeDict();

  display.clear();
  delay(1000);
  display.setBrightness(7);
}

void loop() {
  if (IrReceiver.decode()) {
    cmd = processCommand();
    if (cmd.charAt(0) == '0') {
      setDisplay(cmd.toInt());
    }
    delay(250);
    IrReceiver.resume();
  }
}
