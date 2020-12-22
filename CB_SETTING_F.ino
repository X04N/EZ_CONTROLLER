///////////////////////////////////////// SETTINGS FUNCTIONS //////////////////////////////////


  //////////// OUTPUT ////////////

void set_output_type(byte id){
  switch (id)
  {
    case 10:
    case  0:
        out_type[selected_output] = 0;
        store_value(out_type_add[selected_output], out_type[selected_output]);
        MenuList[10][3] = 1;
        MenuList[11][3] = 0;
        menu_redraw_required = 1;
        digitalWrite(out_en[selected_output], HIGH);
     break;
    case 11:
    case  1:
        out_type[selected_output] = 1;
        store_value(out_type_add[selected_output], out_type[selected_output]);
        MenuList[10][3] = 0;
        MenuList[11][3] = 1;
        menu_redraw_required = 1;
        digitalWrite(out_en[selected_output], LOW);
     break;
    default:
      // statements
      break;
  }
}

void set_output_delay()
{
  debug_print("set_output_delay_function");
  bool setting = true;
  bool redraw = true;
  int counter = out_delay[selected_output];
  while (setting)
  {
    debug_print("while setting");

    if(redraw){
      u8g.firstPage();
      do  {
      display_message(14,false,false,false,counter, true, 15, 61, (33 + selected_output));// SECONDS no second string - no delay - no rewrite - value
      redraw = false;
      } while( u8g.nextPage() );
    }

    if (left_sw.get_State() > 0)
    {
      redraw = true;
      if(counter < 5){
        debug_print("increase delay by one");
        counter++;
      }else if(counter >= 5 && counter < 30){
        debug_print("increase delay by 5");
        counter += 5;
      }else if(counter >= 30 && counter < 120){
        debug_print("increase delay by 10");
        counter += 10;
      }else if(counter >= 120 && counter < 300){
        debug_print("increase delay by 30");
        counter += 30;
      }else if(counter >= 300 && counter < 900){
        debug_print("increase delay by 60");
        counter += 60;
      }else if(counter >= 900){
        counter = 0;
      }
    }else if(right_sw.get_State() > 0)
    {
      out_delay[selected_output] = counter*1000;
      EEPROM.update(out_delay_add[selected_output],out_delay[selected_output]);
      display_message(18);// SAVED!
      back_id = (33 + selected_output);
      setting = false;
      menu_back();
    }
  }
}

  //////////// MORSE ////////////


void set_morse_input_count(byte n)
{
  byte first_item_id = 34;
  byte last_item_id = 35;

  morse_input_count = n;
  EEPROM.update(morse_input_count_add, morse_input_count);
  for(byte i = first_item_id; i <= last_item_id; i++){
    if(i == n){
      MenuList[i][3] = 1;
    }else{
      MenuList[i][3] = 0;
    }
  }
  menu_redraw_required = 1;
}

void set_morse_dash_length(byte l)
{
  byte first_item_id = 36;
  byte last_item_id = 41;

  morse_dash_length = l;
  EEPROM.update(morse_dash_length_add, morse_dash_length);
  for(byte i = first_item_id; i <= last_item_id; i++){
    if(i == l){
      MenuList[i][3] = 1;
    }else{
      MenuList[i][3] = 0;
    }
  }
  menu_redraw_required = 1;
}

//////////////////////////////////// VOLUME ///////////////////////////////////

void set_volume()
{
  debug_print("entering VOLUME function");
  bool setting = true;
  bool redraw = true;
  int counter = volume;
  while (setting)
  {
    //debug_print("while setting");
    if(redraw){
      u8g.firstPage();
      do  {
      display_message(79,false,false,false,counter, true, 15, 61, 78);
      // NUMBER OF INPUTS no second string - no delay - no rewrite - value counter, header
      redraw = false;
      } while( u8g.nextPage() );
    }

    if (left_sw.get_State() > 0)
    {
      redraw = true;
      if( counter < 30 )
      {
        counter++;
        mp3.volume(counter);  //Set volume value. From 0 to 30
        mp3.playMp3Folder(success_sound);
      }else{
        counter = 0;
      }
      debug_print("Displayed number of rounds: ", counter);
    }else if(right_sw.get_State() > 0)
    {
      volume = counter;
      EEPROM.update(volume_add, volume);
      display_message(18);// SAVED!
      setting = false;
      menu_timer = millis();
      back_id = (77);
      menu_back();
    }
  }
}
