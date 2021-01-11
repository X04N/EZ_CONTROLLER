

///////////////  SAVING STATE SOLVE //////////////

void print_debug_state_saved()
{
  Serial.print("Debug:");
  Serial.println("State stored.");
  Serial.print("Game_Mode: ");
  Serial.println(game_mode);
  Serial.print("Stored solve STATE: ");
  for(byte i = 0; i< input_count; i++)
  {
    Serial.print(input_state[i]);
    if(i<input_count-1)
    {
      Serial.print(", ");
    }else
    {
      Serial.println();
    }
  }
  Serial.print(F("Solve STATE read from EEPROM: "));
  for(byte i = 0; i< input_count; i++)
  {
    Serial.print(EEPROM.read(state_solution_add[i]));
    if(i<input_count-1)
    {
      Serial.print(", ");
    }else
    {
      Serial.println();
    }
   }
}



void debug_print_active_input_count(byte active_input_count)
{
  if(debug)
  {
    Serial.print("debug active_input_count: ");
    Serial.println(active_input_count);
  }
}

void print_simon_sequence(){
  for (byte i = 0; i < simon_array_lenght; i++) {
    debug_print("Simon value ", i);
    debug_print("= ", default_simon_sequence[simon_inputs_used][i]);
  }
}
