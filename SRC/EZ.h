/*
  SparkS.h - Library for Spark_S Escape Room Controler.
  Created by Joan Casas Vidal, June 2019.
*/
#ifndef SparkS_h
#define SparkS_h

#include "Arduino.h"

extern byte menuPosition;
extern int menu_redraw_required;

class Menu_item
{
  public:

  //menu
  Menu_item(byte mID, byte parentID = false, byte functID = false);//constructor

  byte get_mID();
  byte get_parent();
  byte get_funct();
  byte get_childrenId();

  private:

  //menu
  byte _mID;
  byte _parentID;
  byte _functID;
};


class Input
{
  public:
  //debounce_Inputs
  Input(byte INPin, String INName = "input", bool INNormalState = 1, int debounceDelay = 40, unsigned long INState = 0, bool INLastState = false, unsigned long INLastDebounceTime = 0, unsigned long activeTime = 0);//constructor

  long get_State();
  void rst_State();
  byte get_pin();

  private:
  //debounce_Inputs
  byte _INPin;
  long _INState;
  bool _INLastState;
  int _debounceDelay;
  unsigned long _INLastDebounceTime;
  unsigned long _INReturn;
  String _INName;
  unsigned long _activeTime;
};


void drawHeader(byte left, byte right, byte middle, bool limit = true);
void save_list(bool list[], int list_add[], byte mode, byte message, bool checklist = false);





#endif
