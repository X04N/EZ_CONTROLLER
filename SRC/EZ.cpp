#include "Arduino.h"
#include "EZ.h"


extern byte menuPosition = 0;
extern int menu_redraw_required = 0;


// Menu
Menu_item::Menu_item(byte mID, byte parentID, byte functID){
  _mID = mID;
  _parentID = parentID;
  _functID = functID;
}

byte Menu_item::get_mID(){
  return _mID;
}

byte Menu_item::get_parent(){
  return _parentID;
}

byte Menu_item::get_funct(){
  return _functID;
}

//Debounce_Inputs

Input::Input(byte INPin, String INName, bool INNormalState, int debounceDelay, unsigned long INState, bool INLastState, unsigned long INLastDebounceTime, unsigned long activeTime)
{
  _INPin = INPin;
  pinMode(_INPin, INPUT);
  _debounceDelay = debounceDelay;
  _INState = INState;
  _INLastState = INLastState;
  _INLastDebounceTime = INLastDebounceTime;
  _INName = INName;
  _activeTime = activeTime;
}

byte Input::get_pin()
{
  return _INPin;
}
long Input::get_State()
{
    int reading = digitalRead(_INPin);
    // If the switch changed, due to noise or pressing:
    if (reading != _INLastState) {
      // reset the debouncing timer
      _INLastDebounceTime = millis();
    }
       // save the reading.  Next time through the loop,
      // it'll be the inputLastState:
    _INLastState = reading;
    if ((millis() - _INLastDebounceTime) > _debounceDelay)
    {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:
        // only if the button is pushed

        if (reading == 0)
        {
          //Serial.print(_INName);
          //Serial.println (F(" is now active"));
          _activeTime = millis()-_INLastDebounceTime;
          return _activeTime;
        }else
        {
          return 0;
        }
      }

return 0;
}
