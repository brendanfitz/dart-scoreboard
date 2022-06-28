#include "ScoredboardRemote.h"

String processCommand(String btnCode) {
  btnCode.toUpperCase();
  String cmd;
  if (btnCode == "BA45FF00")      { cmd = "01"; } 
  else if (btnCode == "B946FF00") { cmd = "02"; } 
  else if (btnCode == "B847FF00") { cmd = "03"; } 
  else if (btnCode == "BB44FF00") { cmd = "04"; } 
  else if (btnCode == "BF40FF00") { cmd = "05"; }
  else if (btnCode == "BC43FF00") { cmd = "06"; }
  else if (btnCode == "F807FF00") { cmd = "07"; } 
  else if (btnCode == "EA15FF00") { cmd = "08"; } 
  else if (btnCode == "F609FF00") { cmd = "09"; }
  else if (btnCode == "E916FF00") { cmd = "*"; } 
  else if (btnCode == "E619FF00") { cmd = "00"; }
  else if (btnCode == "F20DFF00") { cmd = "#"; } 
  else if (btnCode == "E718FF00") { cmd = "up"; } 
  else if (btnCode == "F708FF00") { cmd = "<<"; } 
  else if (btnCode == "E31CFF00") { cmd = "ok"; } 
  else if (btnCode == "A55AFF00") { cmd = ">>"; } 
  else if (btnCode == "AD52FF00") { cmd = "dn"; } 
  else { return btnCode; } 
  return cmd;
}
  /*
  if (btnCode == "BA45FF00")      { cmd = "pwr"; } 
  else if (btnCode == "B946FF00") { cmd = "v+"; } 
  else if (btnCode == "B847FF00") { cmd = "fs"; } 
  else if (btnCode == "BB44FF00") { cmd = "<-"; } 
  else if (btnCode == "BF40FF00") { cmd = "play"; }
  else if (btnCode == "BC43FF00") { cmd = "->"; } 
  else if (btnCode == "F807FF00") { cmd = "dn"; } 
  else if (btnCode == "EA15FF00") { cmd = "v-"; } 
  else if (btnCode == "F609FF00") { cmd = "up"; }
  else if (btnCode == "E916FF00") { cmd = "00"; }
  else if (btnCode == "E619FF00") { cmd = "eq"; } 
  else if (btnCode == "F20DFF00") { cmd = "sr"; } 
  else if (btnCode == "F30CFF00") { cmd = "01"; } 
  else if (btnCode == "E718FF00")   { cmd = "02"; } 
  else if (btnCode == "A15EFF00") { cmd = "03"; } 
  else if (btnCode == "F708FF00") { cmd = "04"; } 
  else if (btnCode == "E31CFF00") { cmd = "05"; }
  else if (btnCode == "A55AFF00") { cmd = "06"; }
  else if (btnCode == "BD42FF00") { cmd = "07"; } 
  else if (btnCode == "AD52FF00") { cmd = "08"; } 
  else if (btnCode == "B54AFF00") { cmd = "09"; }
  */
