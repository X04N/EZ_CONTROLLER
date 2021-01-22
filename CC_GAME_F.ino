
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
  for (size_t i = 0; i < 3; i++)
  {
    out_timestamp[i] = solve_timestamp;
  }
  Serial.println(F("================== SOLVED ==================="));
  digitalWrite(solve_led, HIGH);
  play(solve_sound);
  display_message(48,false,0,false);
  //string 48, no second string, no duration delay, no rewrite
}
void solve_outputs()
{
  debug_print("Solve Outputs");
  for (size_t i = 0; i < 3; i++) {
    if ((out_timestamp[i] + (out_delay[i]*1000)) < millis()) {
      debug_print("timestamp Passed for output: ", i);
      if (out_type[i] == 0) {
        digitalWrite(out_en[i], LOW);
      }else{
        digitalWrite(out_en[i], HIGH);
      }
    }
  }
}


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
  debug_print("Simon Delay before creating new sequence: ", simon_delay);
  debug_print("Creating new simon sequence");
  int a_value = analogRead(A5);
  int b_value = millis();
  delay(100);
  randomSeed(a_value + b_value + 12345 - analogRead(A5));
  debug_print("analogRead: ", analogRead(A5));
  debug_print("Simon Delay after randomSeed: ", simon_delay);
  byte random_value = 0;
  for (byte i = 0; i < simon_array_lenght; i++) {
    random_value = random(simon_inputs_used);
    simon_sequence[i] = random_value;
    debug_print("Simon value ", i);
    debug_print("= ", random_value);
    debug_print("Simon Delay: ", simon_delay);
  }
  need_new_random = false;
  debug_print("Simon Delay after creating new sequence: ", simon_delay);
  save_simon_difficulty(simon_difficulty);
  debug_print("Simon Delay after Resaving difficulty: ", simon_delay);
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
  simon_last_display_change = millis();
  simon_pause_timestamp = millis();
}
