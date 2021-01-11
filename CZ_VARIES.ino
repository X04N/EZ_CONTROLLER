///////////////////////////////////////// HOME  /////////////////////////////////

void home()
{
  Menu_Seleccionat = 0;
  alternate_parent_id = false;
  both_parent_id = false;
  menuPosition = 0;
  menu_redraw_required = 1;
  back_id = 252;
  functionToExecute = 0;
}



/*void test(char text[]){
  if(debug){
    Serial.print(F("Debug: "));
    Serial.println(text);
    Serial.print(F(" Value:"));
    Serial.println(value);
  }
}*/

// EEPROM store value and check if it is stored right

void store_value(long address, byte value)
{
  byte counter = 0;
  bool check = false;
  while (check == 0){
    counter++;
    EEPROM.update(address, value);
    byte read_check = 0;
    read_check = EEPROM.read(address);
    if(value == read_check){
      check = 1;
      debug_print("Value stored in EEPROM");
    }
    if (counter == 10) {
      check = true;
      debug_print("Couldn't store value in EEPROM");
    }
  }
}


// SET FACTORY VALUES FOR THE FIRST POWER UP OR WHEN A FACTORY RESET IS CALLED.

void reset_factory(){
  debug_print("Reset factory starting");
  //game mode
  change_puzzle(state);
  // volume
  EEPROM.update(volume_add, 30);
  volume = 10;
  // state solution
  for (byte i = 0; i < input_count; i++) {
      EEPROM.update(state_solution_add[i], true);
      state_solution[i] = true;
  }
  //sequence length
  EEPROM.update(s_lenght_add, 1);
  s_lenght = 1;
  //Morse dash lenght
  EEPROM.update(morse_dash_length_add, 0);
  morse_dash_length = 0;
  //output TYPE
  for (byte i = 0; i < out_count; i++) {
    EEPROM.update(out_type_add[i],0);
    out_type[i] = 0;
  }
  //output DELAY
  for (byte i = 0; i < out_count; i++) {
    EEPROM.update(out_delay_add[i],0);
    out_delay[i] = 0;
  }
  //sequence
  for (byte i = 0; i < 10; i++) {
    for (byte x = 0; x < input_count; x++) {
      EEPROM.update(s_add[i][x], 1);
      s_solution[i][x] = 1;
    }
  }
  // checklist
  for (byte i = 0; i < input_count; i++) {
    EEPROM.update(checklist_add[i],true);
    checklist[i] = true;
  }

  // SIMON
  //Default number of inputs for SIMON game MODE
  EEPROM.update(simon_inputs_used_add,4);
  simon_inputs_used = 4;
  update_simon_sequence();
  //Default BOOL RANDOM for SIMON game MODE
  EEPROM.update(simon_random_add, false);
  simon_random = false;
  //Default BOOL SOUNDS for SIMON game MODE
  EEPROM.update(simon_sounds_add, false);
  simon_sounds = false;
  //Default DIFFICULTY for SIMON game MODE
  EEPROM.update(simon_difficulty_add, 1);
  save_simon_difficulty(1);
  //Default rounds for SIMON game MODE
  EEPROM.update(simon_rounds_add, 5);
  simon_rounds = 5;

  //BURNT bytes list, reset only on first powerup, not on factory resets made
  //from the menu option.
  if (EEPROM_populated != true) {
    for (byte i = 0; i < 30; i++) {
      EEPROM.update(burnt_byte_add[i], false);
    }
  }

  // Set EEPROM_populated to True so this function doesn't run at powerup,
  //only when chosen from the menu
  for (size_t i = 0; i < 2; i++) {
    EEPROM.update(EEPROM_populated_add[i], 22);
    debug_print("EEPROM populated = ", EEPROM.read(EEPROM_populated_add[i]));
  }
  EEPROM_populated = true;

  debug_print("Factory Reset finished");
}

// CHANGE PUZZLE MODE

void change_puzzle(byte id){
      game_mode = id;
      store_value(game_mode_add, game_mode);
      for (byte i = 0; i < number_of_modes; i++)
      {
        if (game_mode == puzzle_modes[i]) {
          MenuList[puzzle_modes[i]][3] = true;
        }else{
          MenuList[puzzle_modes[i]][3] = false;
        }
      }
      for (size_t i = 0; i < input_count; i++) {
        digitalWrite(in_act,LOW);
      }
}

void play(byte audio){
  if (mp3.available()) {
    mp3.stop();
    delay(5);
    mp3.playMp3Folder(audio);
    delay(5);
    mp3.playMp3Folder(audio);
    if (debug) {
      print_mp3_detail(mp3.readType(), mp3.read()); //Print the detail message from DFPlayer to handle different errors and states.
    }
  }
}

void print_mp3_detail(uint8_t type, int value)
{
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
