
#define relaypin 0
#define phonepin 3
int active_timers; //if >0, timers are checked in chck_times()

char printerOn(char On)
{
  if (On == '?')
   {
    if (digitalRead(relaypin) == HIGH){return 'f';}
    else {return 't';}
   }

  if (On == 'f') {debugI("* fx_handlers/ relay triggered OFF");} //debug
  if (On == 't') {debugI("* fx_handlers/ relay triggered ON");} //debug
  
  if (On == 'f') {Serial.println("Printer Off"); digitalWrite(relaypin, HIGH); return 'f';}
  if (On == 't') {Serial.println("Printer On"); digitalWrite(relaypin, LOW); return 't';}
}

boolean power;
unsigned long powerbutton_timer;
char phonepw(char On)
{
  if (On == '?'){if (power == true){return 't';} else {return 'f';};}
  if (On == 'r'){power = false; return 'k';}
  if (digitalRead(relaypin) == HIGH){return 'E';}

  if (On == 'p')
  {
  powerbutton_timer = millis();
  digitalWrite(phonepin, HIGH);

  active_timers++;
  power = true;
  return 't';
  }
}
