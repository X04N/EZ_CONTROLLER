
///////////////////////////////////////// GAME FUNCTIONS //////////////////////////////////
void beep()
{
  /*for(int i=0; i<5; i++){
    digitalWrite(12, HIGH);
    delay(50);
    digitalWrite(12, LOW);
    delay(50);
  }*/
  for(int i; i<4; i++){
    digitalWrite(in_act[i], HIGH);
  }
  delay(1000);
  for(int i; i<4; i++){
    digitalWrite(in_act[i], LOW);
  }
}

void solve()
{
  solve_timestamp = millis();
  Serial.println(F("================== SOLVED ==================="));
  digitalWrite(solve_led, HIGH);
  display_message(48,false,0,false);
  //string 48, no second string, no duration delay, no rewrite
  while(1){
    for (size_t i = 0; i < 2; i++) {
      if ((solve_timestamp + out_delay[i]) < millis()) {
        if (out_type[i] == 0) {
          digitalWrite(out_en[i], HIGH);
        }else{
          digitalWrite(out_en[i], LOW);
        }
      }
    }
  }

  /*//delay(output_delay);
  digitalWrite(out_en[0], HIGH);
  digitalWrite(out_en[1], HIGH);
  digitalWrite(out_en[2], HIGH);
  digitalWrite(solve_led, HIGH);
  //beep();
  display_message(48,false,4000);
  delay(3000);
  solved = false;
  menu_redraw_required = true;
  digitalWrite(out_en[0], LOW);
  digitalWrite(out_en[1], LOW);
  digitalWrite(out_en[2], LOW);
  digitalWrite(solve_led, LOW);*/
}


/////////////////////////////////////// STEP COMPARATOR /////////////////////////////////////

/*bool compare_step( byte input[], byte solution[]){

  if(!s_step_solved){
    s_step_active_count = active_count(solution);
    for(byte i = 0; i < input_count; i++)//loop inputs
    {
      if ((input[i]==1 && solution[i]==0) || (input[i]==0 && s_input_was_active[i] == 1) )
      //apreten un que no és a la seqüència o deixen anar un que SI era a la seqüència
      {
        input_was_active_reset();
        return false;
      }else if(input[i]==1 && solution[i]==1)//apreten un que si és a la seqüència
      {
        s_input_was_active[i] = 1;
      }
    }
    if(s_step_active_count == active_count(s_input_was_active)){
      s_step_solved = true;
    }
  }else{
    for(byte i = 0; i < input_count; i++)
    {
      if (input[i]==1 && s_input_was_active[i]==0)//apreten un que no és a la seqüència
      {
        input_was_active_reset();
        return false;
      }
      if(input[i]==0 && s_input_was_active[i]==1)//deixen anar un dels que formaven part del step
      {
        s_release_counter++;
      }
    }
    return(s_step_active_count == s_release_counter);
  }
}*/


/////////////////////////////////////// SEQUENCE FUNCTION /////////////////////////////////////

void check_sequence(byte sequence_lenght, byte step_active_count, byte release_counter, bool step_solved, byte input_was_active[],byte sequence_solution[][10],byte sequence_counter)
{
  //Serial.print(sequence_counter);
      if(sequence_counter < sequence_lenght)
      {
        if(!all_inputs_are_inactive)
        {
          if(!step_solved)
          {
            step_active_count = active_count(sequence_solution[sequence_counter]);
            for(byte i = 0; i < input_count; i++)//loop inputs
            {
              if ((input_state[i]==1 && sequence_solution[sequence_counter][i]==0) || (input_state[i]==0 && input_was_active[i] == 1) )
              //apreten un que no és a la seqüència o deixen anar un que SI era a la seqüència
              {
                input_was_active_reset();
                sequence_counter=0;
              }else if(input_state[i]==1 && sequence_solution[sequence_counter][i]==1)
              //apreten un que si és a la seqüència
              {
                input_was_active[i] = 1;
              }
            }
            if(step_active_count == active_count(input_was_active))
            {
              step_solved = true;
            }
          }else
          {
            for(byte i = 0; i < input_count; i++)
            {
              if (input_state[i]==1 && input_was_active[i]==0)
              //apreten un que no és a la seqüència
              {
                input_was_active_reset();
                sequence_counter=0;
                step_solved = false;
              }
            }
           }
         }else if(all_inputs_are_inactive && step_solved)
         {
            input_was_active_reset();
            sequence_counter++;
            step_solved = false;
         }
       }else
        {
          Serial.println(F("solved"));
          solve();
          sequence_counter=0;
          solved = 1;
          step_solved = false;
        }
  }

  void input_was_active_reset()
  {
    for(byte i=0; i<input_count; i++)
    {
      s_active_inputs[i]=0;
    }
  }

////////////////////////////////////////// COMPARE STATE ////////////////////////////////////////

bool compare_bool(bool a[], bool b[])//compare two bool arrays of lenght input_count
{
  for(byte i = 0; i < input_count; i++)
  {
    if (a[i] != b[i]){
      return false;
    }
  }
  return true;
}


bool compare_byte(byte a[], byte b[])//compare two byte arrays of lenght input_count
{
  for(byte i = 0; i < input_count; i++)
  {
    if (a[i] != b[i]){
      return false;
    }
  }
  return true;
}

byte active_count(byte array[])
{
   byte count = 0;
  for(byte i=0; i<input_count; i++)
  {
    if(array[i] == 1)
    {
      count++;
    }
  }
  return count;
}



////////////////////////////////////////// MORSE CODE ////////////////////////////////////////


void single_input_morse()
{

}


void dual_input_morse()
{

}


////////////////////////////////////////// SIMON ////////////////////////////////////////


void create_random_simon_sequence()
{
  debug_print("Creating new simon sequence");
  randomSeed(analogRead(5));
  byte random_value = 0;
  for (byte i = 0; i < simon_array_lenght; i++) {
    random_value = random(simon_inputs_used);
    random_simon_sequence[i] = random_value;
    debug_print("Simon value ", i);
    debug_print("= ", random_value);
  }
  need_new_random = false;
}

byte last_step_in_round()
{
  return simon_current_round + 1;
}

byte simon_last_round()
{
  return simon_rounds - 1;
}

void pause_simon()
{
  for (size_t i = 0; i < simon_inputs_used; i++)
  { // Loop through imputs in simon game
      digitalWrite(in_act[i], LOW);
  }
  debug_print("Pause simon");
  simon_pause = true;
  display_simon = false;
  simon_startup = false;
  simon_display_counter = 0;
  simon_pause_timestamp = millis();
}
