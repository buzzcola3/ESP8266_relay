//#include "webserver.h"
#include "timer_check.h"

void chk_rq()
{

if (active_timers != 0){chck_times();}
  
  if (header.indexOf("/RELAY=OFF") != -1)  
  {
    printerOn('f');
     client.print("<HEAD>");
     client.print("<meta http-equiv=\"refresh" content=\"0;url=/\">");
     client.print("</head>");
    return;
  }
  
  if (header.indexOf("/RELAY=ON") != -1)  
  {
    printerOn('t');
     client.print("<HEAD>");
     client.print("<meta http-equiv=\"refresh" content=\"0;url=/\">");
     client.print("</head>");
    return;
  }

    if (header.indexOf("/phoneon") != -1)  
  {
    Serial.println("Phone should be turning on");
    
     client.print("<HEAD>");
     client.print("<meta http-equiv=\"refresh" content=\"0;url=/\">");
     client.print("</head>");
    phonepw('p');
  }
            
  return;

}
