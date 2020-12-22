///////////////////////////////////////// READ BUTTONS MENU //////////////////////////////////

void read_buttons_menu()
{
  ///read SELECT
  if (right_sw.get_State() > 0 && select_count == 0)
  {
    if(active_menu == 0)
    {
      active_menu = 1;
      return;
    }
    menu_timer = millis();
    select_count++;
    functionToExecute = MenuList[currentMenu[menuPosition]][2];
  }else if(right_sw.get_State() == 0){
    select_count = 0;
  }
  ///read NEXT
  if (left_sw.get_State() > 0)
  {
    if(active_menu == 0)
    {
      active_menu = 1;
      return;
    }
    menu_timer = millis();
    if(left_sw.get_State()/next_count > 500)
    {
      next_count++;
      if(menuPosition<(countCurrentMenu-1)){
        //Serial.print("menu seleccionat = ");Serial.println(Menu_Seleccionat);
        //Serial.print("countCurrentMenu = ");Serial.println(countCurrentMenu);Serial.print("menuPosition = ");Serial.println(menuPosition);
        menuPosition++;
        //Serial.print("new_menuPosition = ");Serial.println(menuPosition);
      }else{
        //Serial.print("countCurrentMenu = ");Serial.println(countCurrentMenu);Serial.print("menuPosition = ");Serial.println(menuPosition);
        menuPosition = 0;
        //Serial.print("new_menuPosition = ");Serial.println(menuPosition);
      }
    }
    menu_redraw_required = true;
  }else{
    next_count = 0;
  }
}

///////////////////////////////////////// READ BUTTONS SEQUENCE //////////////////////////////////

void read_buttons_sequence()
{
  ////////////read SELECT //////////////
  if (left_sw.get_State() > 0)
  {

  }
  ////////////read NEXT //////////////
  if (right_sw.get_State() > 0)
  {
    if(active_menu == 0){
      active_menu = 1;
      return;
    }
    active_menu = 1;
    menu_timer = millis();
    if(right_sw.get_State()/next_count > 500)
    {
      next_count++;
      if(menuPosition<(countCurrentMenu-1)){
        menuPosition++;
      }else{
        menuPosition = 0;
      }
    }
    menu_redraw_required=1;
  }else{
    next_count = 0;
  }
}

///////////////////////////////////////// READ INPUTS //////////////////////////////////

bool read_inputs()
 {
   active_input_count = 0;
   all_inputs_are_inactive = true;
   bool has_changed = false;
    for(byte i = 0; i < input_count; i++)
    {
      if(input_array[i].get_State() > 0){
        all_inputs_are_inactive = false;
        active_input_count++;
      }
      if (input_array[i].get_State() > 0 && input_state[i]!= 1)
      {
          input_state[i] = 1;
          debug_print("active_input_count: ", active_input_count);
          has_changed = true;
          mp3.playMp3Folder(i+1);
          debug_print("input turned on: ", i);
      }else if(input_array[i].get_State() == 0 && input_state[i]!= 0){
          input_state[i] = 0;
          has_changed = true;
          debug_print("active_input_count: ", active_input_count);
          debug_print("input turned off: ", i);
      }
    }
    return has_changed;
 }

//////////////////////////////// CHECK FOR WIRES ///////////////////////////////

void check_for_wires(byte array[])
{
  for (byte i = 0; i < input_count; i++)
  {
      //debug_print("checking connection i = ", i );
      digitalWrite(in_act[i], HIGH);
      array[i] = 255;
      for (byte x = 0; x < input_count; x++)
      {
          //debug_print("with x = ", x);
          if (input_array[x].get_State() > 0)
          {
              array[i] = x;
              break;
          }
      }
  }
}
