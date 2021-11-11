//#include "webserver.h"
#include "timer_check.h"

void chk_rq()
{

if (active_timers != 0){chck_times();}
  
  if (header.indexOf("/RELAY=OFF") != -1)  
  {
    debugI("* chk_request/ OFF button pressed"); //debug
    printerOn('f');
    
    return;
  }
  
  if (header.indexOf("/RELAY=ON") != -1)  
  {
    debugI("* chk_request/ ON button pressed"); //debug
    printerOn('t');
    
    return;
  }

    if (header.indexOf("/phoneon") != -1)  
  {
    Serial.println("Phone should be turning on");
    debugI("* chk_request/ Phone power button pressed"); //debug
    
    phonepw('p');
  }
   Debug.handle(); //debug
  return;

}
