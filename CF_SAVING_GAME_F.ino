

///////////////////////////////////////// SAVING SEQUENCE SOLUTION //////////////////////////////////

void save_secuence()
{

  bool setting = 1;
  byte sequence_cnt = 0;
  bool display_rewrite_required = 1;
  while(setting)
  {
    read_inputs();
    if(display_rewrite_required == 1)
    {
        u8g.firstPage();
        do
        {
          drawHeader(47,46,Menu_Seleccionat);//next, finish, secuence
          u8g_uint_t w, d;
          w = u8g.getWidth();
          //Set Text
          u8g.setFont(u8g_font_6x13);
          u8g.setFontRefHeightText();
          u8g.setFontPosTop();
          strcpy_P(str_buffer, (char*)pgm_read_word(&(string_array[20+sequence_cnt])));
          d = (w-u8g.getStrWidth(str_buffer))/2;
          u8g.drawStr(d, 25, str_buffer);
          strcpy_P(str_buffer, (char*)pgm_read_word(&(string_array[30])));
          d = (w-u8g.getStrWidth(str_buffer))/2;
          u8g.drawStr(d, 40, str_buffer);
         } while( u8g.nextPage() );
         display_rewrite_required = 0;
    }
    //Serial.println(millis());
    if (left_sw.get_State() > 0)
    {
      Serial.println("Left_Switch");
      if(debug)
      {
        display_message(68,false,800,false,active_input_count);
      }
      if(active_input_count)
      {// if at least one input is active
        //store current sequence input state
        for(byte i = 0; i< input_count; i++)
        {
          EEPROM.update(s_add[sequence_cnt][i], input_state[i]);
          s_solution[sequence_cnt][i] = input_state[i];
        }
        //if cnter is smaller than 10 display next
        if(sequence_cnt<9)
        {
          sequence_cnt++;
          u8g.firstPage();
          do
          {
            drawHeader(47,46,Menu_Seleccionat);
            u8g_uint_t w, d;
            w = u8g.getWidth();
            //Set Text
            u8g.setFont(u8g_font_6x13);
            u8g.setFontRefHeightText();
            u8g.setFontPosTop();
            strcpy_P(str_buffer, (char*)pgm_read_word(&(string_array[18])));//SAVED
            d = (w-u8g.getStrWidth(str_buffer))/2;
            u8g.drawStr(d, 25, str_buffer);
           } while( u8g.nextPage() );
           delay(1000);
           display_rewrite_required = 1;
         }else{
          game_mode = secuence;
          Serial.print("game mode: ");Serial.println(game_mode);
          s_lenght = sequence_cnt;
          Serial.print("sequence_lenght: ");Serial.println(s_lenght);
          EEPROM.update(game_mode_add, game_mode);
          EEPROM.update(s_lenght_add, s_lenght);
          setting = false;
          solved = false;
          input_was_active_reset();
          display_message(3,18,3000);// display a message containing strings 3 and 18 for 3 seconds
          home();
         }
       }else{
         display_message(42,43);
         display_rewrite_required = 1;
       }

    }else if (right_sw.get_State() > 0)
    {
      if(sequence_cnt>1){
      Serial.println("Right_SW");
      game_mode = secuence;
      Serial.print("game mode: ");Serial.println(game_mode);
      s_lenght = sequence_cnt;
      Serial.print("sequence_lenght: ");Serial.println(s_lenght);
      EEPROM.update(s_lenght_add, s_lenght);
      EEPROM.update(game_mode_add, game_mode);
      byte write_test = EEPROM.read(s_lenght_add);
      Serial.print("EEPROM Read sequence_lenght: ");Serial.println(write_test);

      setting = false;
      solved = false;
      input_was_active_reset();
      display_message(3,18,3000);// display a message containing strings 3 and 18 for 3 seconds
      home();
    } else {
      display_message(16,62);// SEQUENCE TOO SHORT
      display_rewrite_required = 1;
    }
    }
  }
}



///////////////// SAVING LIST (state and checklist)  ///////////////////////////

void add_remove_from_list(byte input, bool list[])
{
    if (list[input] == true) {
      debug_print("remove_from_list: ", input);
      list[input] = false;
      MenuList[currentMenu[input]][3] = false;
      menu_redraw_required = true;
      checklist_size--;
    }else{
      debug_print("add_to_list: ", input);
      list[input] = true;
      MenuList[currentMenu[input]][3] = true;
      menu_redraw_required = true;
      checklist_size++;
    }
}

void save_list(bool list[], int list_add[], byte mode, byte message, bool checklist = false)
{
  debug_print("saving list");

  if(checklist)
  {
    checklist_size = 0;
  }

  for (byte i = 0; i < input_count; i++) {
    EEPROM.update(list_add[i],list[i]);
    if((list[i] == true) && (checklist == true))
    {
      checklist_size++;
    }
  }

  game_mode = mode;
  EEPROM.update(game_mode_add, mode);
  solved = false;
  display_message(message);
  home();
  if(debug){
    for(byte i = 0; i< input_count; i++)
    {
      Serial.print(list[i]);
      if(i<input_count-1)
      {
        Serial.print(", ");
      }else
      {
        Serial.println();
      }
    }
    for(byte i = 0; i< input_count; i++)
    {
      if(i<input_count-1)
      {
        Serial.print(", ");
      }else
      {
        Serial.println();
      }
    }
  }
}//save_list

void choose_from_list(byte selected, bool list[], int list_add[]){
  for (byte i = 0; i < sizeof(list)/sizeof(list[0]); i++) {
    // if is the one selected turn to true, otherwise turn to false
  }
}

///////////////// SAVING connect/cut wires  ///////////////////////////


void set_wires()
{
  bool setting = 1;
  unsigned long last_change = millis();
  byte time_spent;
  while(setting == 1)
  {
    debug_print("setting = 1");
    time_spent = round((millis() - last_change)/1000);
    count_down = 10 - time_spent;
    // when counter gets to 0, read inputs and store the state
    if(count_down == 0)
    {// read wires and save them
      debug_print("count_down = 0");
      display_message(64);
      check_for_wires(wire_solve_pairs);
      game_mode = wires;
      EEPROM.update(game_mode_add, game_mode);
      setting = false;
      solved = false;
      functionToExecute = 0;
      display_message(4,18);
      menu_timer = millis();
      home();
      if(debug) // if debug is active, print debug helpers
      {
        debug_print("wires saved");
      }
    }else{//show remaining time
      u8g.firstPage();
      do
      {
        updateCurrentMenu();
        drawHeader(false,false,4,false);
         u8g_uint_t w, d;
         w = u8g.getWidth();
         //Set Text
         u8g.setFont(u8g_font_6x13);
         u8g.setFontRefHeightText();
         u8g.setFontPosTop();
         strcpy_P(str_buffer, (char*)pgm_read_word(&(string_array[63])));// SAVING STATE IN:
         d = (w-u8g.getStrWidth(str_buffer))/2;
         u8g.drawStr(d, 25, str_buffer);
         u8g.setPrintPos(62, 40);
         u8g.print(count_down);
      } while( u8g.nextPage() );
    }
   }
}

///////////////// SAVING SIMON  ///////////////////////////


void set_simon_number_of_inputs()
{
  debug_print("entering set_simon_inputs_used function");
  bool setting = true;
  bool redraw = true;
  int counter = simon_inputs_used;
  while (setting)
  {
    //debug_print("while setting");
    if(redraw){
      u8g.firstPage();
      do  {
      display_message(68,false,false,false,counter, true, 15, 61, 68);
      // NUMBER OF INPUTS no second string - no delay - no rewrite - value counter, no header
      redraw = false;
      } while( u8g.nextPage() );
    }

    if (left_sw.get_State() > 0)
    {
      redraw = true;
      if(counter < input_available){
        counter++;
        debug_print("Increased number of inputs to ", counter);
      }else{
        counter = 2;
      }
    }else if(right_sw.get_State() > 0)
    {
      simon_inputs_used = counter;
      EEPROM.update(simon_inputs_used_add, simon_inputs_used);
      display_message(18);// SAVED!
      setting = false;
      menu_timer = millis();
      back_id = (6);
      menu_back();
    }
  }
}


void save_bool_option(byte menu, byte selected_option)
{
  bool value = false;
  if (selected_option == 70)//true
  {
    value = true;
  }
  switch (menu) {
    case 67://simon_random
      simon_random = value;
      store_value(simon_random_add,simon_random);
      debug_print("simon random = ",simon_random);
    break;
    case 69://simon_sounds
      simon_sounds = value;
      store_value(simon_sounds_add,simon_sounds);
      debug_print("simon_sounds = ", simon_sounds);
    break;
  }
  menu_redraw_required = 1;
}

void save_simon_difficulty(byte difficulty)
{
  simon_difficulty = difficulty;
  debug_print("simon_difficulty: ", simon_difficulty);
  for (byte i = 0; i < 3; i++)
  {
    if(simon_difficulty == i){
      MenuList[73+i][3] = 1;
    }else{
      MenuList[73+i][3] = 0;
    }
  }
  switch (simon_difficulty)
  {
    case 0:
      simon_delay = 2000;
    break;
    case 1:
      simon_delay = 1200;
    break;
    case 2:
      simon_delay = 750;
    break;
    default:
      simon_delay = 2000;
    break;
  }
  store_value(simon_difficulty_add, simon_difficulty);
  menu_redraw_required = true;
}


void save_simon_rounds()
{
  debug_print("entering save_simon_rounds function");
  bool setting = true;
  bool redraw = true;
  int counter = simon_rounds;
  while (setting)
  {
    //debug_print("while setting");
    if(redraw){
      u8g.firstPage();
      do  {
      display_message(76,false,false,false,counter, true, 15, 61, 76);
      // NUMBER OF INPUTS no second string - no delay - no rewrite - value counter, header
      redraw = false;
      } while( u8g.nextPage() );
    }

    if (left_sw.get_State() > 0)
    {
      redraw = true;
      if(counter < (simon_array_lenght-1) )
      {
        counter++;
      }else{
        counter = 2;
      }
      debug_print("Displayed number of rounds: ", counter);
    }else if(right_sw.get_State() > 0)
    {
      simon_rounds = counter;
      EEPROM.update(simon_rounds_add, simon_rounds);
      display_message(18);// SAVED!
      setting = false;
      menu_timer = millis();
      back_id = (6);
      menu_back();
    }
  }
}


// count checklist size
byte size_checklist(){
  checklist_size = 0;
  for (byte i = 0; i < input_count; i++) {
    if (checklist[i]==true) {
      checklist_size++;
    }
  }
}
