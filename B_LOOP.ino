   //LOOP//    //LOOP//    //LOOP//    //LOOP//    //LOOP//    //LOOP//    //LOOP//    //LOOP//    //LOOP//    //LOOP//    //LOOP//    //LOOP//    //LOOP//

void loop()
{
  //myDFPlayer.playMp3Folder(1);
  //delay(2000);
  //debug_print("loop");

  ///////////////////////////////////////// READ AND STORE INPUT VALUES //////////////////////////////////
  read_buttons_menu();
  read_inputs();

   /////////////////////////////// MENU FUNCTIONS /////////////////////////////
  if(functionToExecute != 0)
  {
    //hack per a canviar funcions en el menú de seleccionar mode
    if(Menu_Seleccionat == 1)
    {
      functionToExecute = 16;
      if (currentMenu[menuPosition] == menu_items_count-1) {
        //If the back option is clicked
        functionToExecute = 2;
      }
    }
    switch (functionToExecute)
    {
      //UPDATE MENU
      case 1:
       update_menu();
       debug_print("Menu Seleccionat = ", Menu_Seleccionat);
       debug_print("back_id = ", back_id);

       functionToExecute = 0;
      break;
      //BACK MENU
      case 2:
        menu_back();
        functionToExecute = 0;
      break;
      //SAVE NEW SEQUENCE SOLVE
      case 3:
        save_secuence();
        functionToExecute = 0;
      break;
      //SET OUTPUT TYPE
      case 4:
        set_output_type(currentMenu[menuPosition]);
        functionToExecute = 0;
      break;
      //SET OUTPUT DELAY
      case 5:
        set_output_delay();
        functionToExecute = 0;
      break;
      // SET WIRES
      case 6:
        set_wires();
      break;
      //SET NEW MORSE CODE
      case 7:
        /*setting_dual_input_morse();
        delay(1000);*/
        functionToExecute = 0;
      break;
      //SET MORSE CODE INPUT COUNT
      case 8:
        game_mode = trip_wire;
        store_value(game_mode_add, game_mode);
        home();
      break;
      //SET MORSE DASH LENGHT
      case 9:
        set_morse_dash_length(currentMenu[menuPosition]);
        functionToExecute = 0;
      break;
      //SAVE NEW LIST
      case 10:
        if (Menu_Seleccionat == 49) { //checklist
          add_remove_from_list(menuPosition, checklist, checklist_add);
          size_checklist();
        }else if(Menu_Seleccionat == 2){ //state
          add_remove_from_list(menuPosition, state_solution, state_solution_add);
        }
        functionToExecute = 0;
      break;
      //
      case 11:
      if (Menu_Seleccionat == 49)//checklist
      {
        save_list(checklist, checklist_add, checklist_mode, 50, true);
      }else if(Menu_Seleccionat == 2)//state
      {
        save_list(state_solution, state_solution_add, state, 18);
      }
        functionToExecute = 0;
      break;
      //
      case 12:
        //SET NUMBER OF INPUTS FOR SIMON GAME
        set_simon_number_of_inputs();
        functionToExecute = 0;
      break;
      //
      case 13:
        //SAVE BOOLEAN OPTION
        debug_print("Menu_Seleccionat: ", Menu_Seleccionat);
        debug_print("CurrentMenu[menuPosition]: ", currentMenu[menuPosition]);
        save_bool_option(Menu_Seleccionat, currentMenu[menuPosition]);
        functionToExecute = 0;
      break;
      //
      case 14:
        //SAVE DIFFICULTY OPTION
        save_simon_difficulty(menuPosition);
        functionToExecute = 0;
      break;
      case 15:
        //SAVE SIMON ROUNDS
        save_simon_rounds();
        functionToExecute = 0;
      break;
      case 16:
        //CHANGE SELECTED PUZZLE
        debug_print("changing puzzle to: ", MenuList[currentMenu[menuPosition]][0]);
        change_puzzle(MenuList[currentMenu[menuPosition]][0]);
        //menu_back();
        menu_redraw_required = true;
        functionToExecute = 0;
      break;
      case 17:
        //JUMP TO CURRENT PUZZLE SETTINGS
        functionToExecute = MenuList[game_mode][2];
        if (MenuList[game_mode][2] == 1) {
          Menu_Seleccionat = game_mode;
          menu_redraw_required = 1;
          menuPosition = 0;
          back_id = 0;
          functionToExecute = 0;
        }else{
          functionToExecute = MenuList[game_mode][2];
        }
      break;
      case 18:
        //adjust volume
        set_volume();
        functionToExecute = 0;
      break;
      case 19:
        //Display soft version
        display_message(menu_items_count-3,menu_items_count-2,4000,true,2147483647,true,false,false,menu_items_count-4);
        menu_timer = millis();
        home();
        //string1,string2,duration,rewrite,value,header
      break;
      // DEFAULT
      default:
        // statements
        break;
    }//functionToExecute switch end
  }//if functionToExecute end
  ///////////////////////////////// SPLASH TIMER ///////////////////////////////

  if(millis() - menu_timer > menu_timeout)
  {
    draw_splash();
    home();
    menu_timer = millis();
    active_menu = false;
  }

///////////////////////////////////// REDRAW MENU //////////////////////////////

  if(active_menu && menu_redraw_required != 0)
  {
      debug_print("Redrawing Menu");
      debug_print("Menu Seleccionat = ", Menu_Seleccionat );
      alternate_parent_id = false;
      both_parent_id = false;

      switch (Menu_Seleccionat)
      {
        case 1:
        //state game mode
          alternate_parent_id = 7;
        break;

        case 2:
        //state game settings
          alternate_parent_id = 49;
          debug_print("redoing list tics for state puzzle");
          redo_list_tics(state_solution, 51);
          back_id = 0;
        break;

        case 3:
        //sequence puzzle settings
          back_id = 0;
        break;

        case 4:
        //wires puzzle settings
          back_id = 0;
        break;

        case 5:
        //morse puzzle settings
          back_id = 0;
        break;

        case 6:
        //simon puzzle settings
          back_id = 0;
        break;

        case 8:
        //oputput type
          redo_out_tics();
        break;

        case 33:
        //Output 1
          selected_output = 0;
          redo_out_tics();
        break;

        case 34:
        //Output 2
          selected_output = 1;
          alternate_parent_id = 33;
          redo_out_tics();
        break;

        case 35:
        //Output 3
          selected_output = 2;
          alternate_parent_id = 33;
          redo_out_tics();
        break;

        case 49:
        //checklist
          debug_print("redoing list tics for checklist puzzle");
          redo_list_tics(checklist, 51);
          back_id = 0;
        break;

        case 66:
        //trip wire puzzle settings
          back_id = 0;
        break;

        case 67:
          redo_yes_no_ticks(simon_random);
        break;

        case 69:
          alternate_parent_id = 67;
          redo_yes_no_ticks(simon_sounds);
        break;

        case 80:
          alternate_parent_id = 67;
          redo_yes_no_ticks(remote);
        break;

        case 999:
        break;

        default:
        break;
      }//end switch (Menu_Seleccionat)

      u8g.firstPage();
      do
      {
        drawMenu();
        drawHeader(47,13,Menu_Seleccionat);
      } while( u8g.nextPage() );

        menu_redraw_required = 0;

  }//end active menu && menu redraw required



////////////////////////////// EXECUTE CURRENT GAME MODE ///////////////////////

  //debug_print("solved = ", solved);
  if(solved == false)
  {
      switch (game_mode)
      {
        debug_print("Puzzle_Mode: ", game_mode);
/*-----------STATE-----------*/
           case state:

                  if(compare_bool(input_state, state_solution))
                  {
                      debug_print("state SOLVED");
                      solved = true;
                  }

            break;

/*-----------SECUENCE-----------*/
            case secuence:

            //Serial.print(s_sequence_counter);Serial.print("  --  ");Serial.print(s_sequence_lenght);Serial.print(" -- step_solved= ");Serial.println(s_step_solved);
            if(s_counter < s_lenght)
            {
              if(!all_inputs_are_inactive)
              {
                if(!s_step_solved)
                {
                  s_step_active = active_count(s_solution[s_counter]);
                  for(byte i = 0; i < input_count; i++)//loop inputs
                  {
                    if ((input_state[i]==1 && s_solution[s_counter][i]==0) || (input_state[i]==0 && s_active_inputs[i] == 1) )
                    //apreten un que no és a la seqüència o deixen anar un que SI era a la seqüència
                    {
                      input_was_active_reset();
                      s_counter=0;
                    }else if(input_state[i]==1 && s_solution[s_counter][i]==1)//apreten un que si és a la seqüència
                    {
                      s_active_inputs[i] = 1;
                    }
                  }
                  if(s_step_active == active_count(s_active_inputs)){
                    s_step_solved = true;
                  }
                }else{
                  for(byte i = 0; i < input_count; i++)
                  {
                    if (input_state[i]==1 && s_active_inputs[i]==0)//apreten un que no és a la seqüència
                    {
                      input_was_active_reset();
                      s_counter=0;
                      s_step_solved = false;
                    }
                  }
                 }
               }else if(all_inputs_are_inactive && s_step_solved)
               {
                  input_was_active_reset();
                  s_counter++;
                  s_step_solved = false;
               }
             }else
              {
                Serial.println(F("solved"));
                solved = true;
                s_counter=0;
                s_step_solved = false;
              }

            break;

/*-----------MORSE-----------*/
            case morse:

                  if(morse_input_count == 34)// SINGLE INPUT MORSE
                  {
                    (
                      dual_in_morse_sequence_length,
                      dual_in_morse_step_active_count,
                      dual_in_morse_release_counter,
                      dual_in_morse_step_solved,
                      dual_in_morse_input_was_active,
                      dual_in_morse_sequence_solution,
                      dual_in_morse_sequence_counter
                    );
                  }

            break;

/*----------- CHECKLIST -----------*/
            case checklist_mode:

                  // if an item in input_state is true, make it also true in triggered_inputs
                  //and increase the counter
                  for (byte i = 0; i < input_count; i++)
                  {
                    if(input_state[i] == true && triggered_inputs[i] == false)
                    {
                      triggered_inputs[i] = true;
                      checklist_counter++;
                      debug_print("Checklist counter= ", checklist_counter);
                      debug_print("Checklist_size+ ", checklist_size);
                    }
                  }
                  // compare checklist_size and counter, if equal, solve()
                  if (checklist_size == checklist_counter)
                  {
                      solved = true;
                  }

            break;

/*----------- WIRES -----------*//////////
            case wires:

                  check_for_wires(wire_current_pairs);

                  if (compare_byte(wire_solve_pairs, wire_current_pairs))
                  {
                      solved = true;
                  }

            break;

/*----------- TRIP WIRE -----------*/
            case trip_wire:
                  //EXECUTE TRIP WIRE MODE
                  //flip flash state
                  if(millis()-last_time_flash > 1000)
                  {
                    flash_state = !flash_state;
                    last_time_flash = millis();
                  }

                  if (!started)
                  {
                    //flash_button
                    digitalWrite(in_act[0], flash_state);
                    //read button and switch started value if pushed
                    if (input_state[0] == true) {
                      started = true;
                      digitalWrite(in_act[0], LOW);
                      last_time_flash = millis();
                      flash_state = true;
                    }
                  }else
                  {
                    digitalWrite(in_act[1], flash_state);
                    //read trip wires, if triggered, require start button to be pushed again
                    for (byte i = 2; i < input_available; i++) {
                      if(input_state[i] == true)
                      {
                        started = false;
                        digitalWrite(in_act[1], LOW);
                        last_time_flash = millis();
                        flash_state = true;
                        play(error_sound);
                      }
                    }
                    //read finish button, if it is pushed, solve.
                    if (input_state[1] == true) {
                      solved = true;
                      started = false;
                    }
                  }
            break;

/*----------- EXECUTE SIMON -----------*/
            case simon:

             ////////  RANDOM? //////////

            if (simon_random && need_new_random)
            {
              create_random_simon_sequence();
            }

            /////// DISPLAY MANAGEMENT ///////

            if(display_simon)
            {
              if(!simon_startup)
              {
                //delay(2000);
                debug_print("Starting Sequence Display");
                debug_print("Simon Delay: ",simon_delay);
                simon_startup = true;
                simon_last_display_change = millis();
                if(simon_sounds)
                {
                  mp3.playMp3Folder(simon_sequence[simon_display_counter]+1);
                  //debug_print("Play: ", simon_sequence[simon_input_number][simon_display_counter]+1);
                }
                debug_print("Displayed step: ", simon_display_counter);
              }
              if (simon_startup && millis() > simon_last_display_change + ( (simon_delay/4) *3 ) )
              //If the input has been displayed for 3/4 of the simon_delay, turn it of
              {
                for (size_t i = 0; i < 10; i++)
                { // Loop through imputs in simon game
                    digitalWrite(in_act[i], LOW);
                }
              }else if(simon_startup && millis() <= simon_last_display_change + ( (simon_delay/4) *3 ) )
              {
                for (size_t i = 0; i < simon_inputs_used; i++)
                { // Loop through imputs in simon game
                  if(simon_sequence[simon_display_counter] == i)
                  { // if the input is the one in the current display step
                    digitalWrite(in_act[i], HIGH);
                    // light it up
                  }else{ // else turn it off
                    digitalWrite(in_act[i], LOW);
                  }
                }
              }
            }
            if( display_simon && ((simon_last_display_change + simon_delay) <= millis()) )
            {
              if(simon_display_counter < last_step_in_round() )
              {
                simon_display_counter++;
                simon_last_display_change = millis();
                if(simon_sounds){
                  play(trig_in[simon_sequence[simon_display_counter]]);
                  //mp3.playMp3Folder(simon_sequence[simon_input_number][simon_display_counter]+1);
                  //debug_print("play: ", simon_sequence[simon_input_number][simon_display_counter]+1);
                }
                debug_print("Displayed step: ", simon_display_counter);
              }else{
                simon_display_counter = 0;
                display_simon = false;
                simon_startup = false;
                for (size_t i = 0; i < simon_inputs_used; i++)
                {
                  digitalWrite(in_act[i], LOW);
                }
                if(simon_repeat){
                  simon_repeat_timestamp = millis();
                }
              }
            } else if(!display_simon && simon_repeat && !simon_pause)
            {
              if ( (simon_repeat_timestamp + simon_repeat_delay) <= millis())
              {
                display_simon = true;
              }
            }
            if (simon_pause && (simon_pause_timestamp + simon_pause_duration) < millis())
            /// if pase time has passed
            {
              debug_print("Pause ended");
              simon_pause = false;
              display_simon = true;
            }

            ///// INPUT MANAGEMENT //////

            if (!all_inputs_are_inactive)
            {
              pause_simon();
              for (size_t i = 0; i < 10; i++)
              {
                if (input_state[i] == true)
                //if an input is triggered
                {
                  if (i == simon_sequence[simon_current_step])
                  {
                    //if it is the right one
                    //debug_print("i: ",i);
                    debug_print("Right input triggered!");
                    //debug_print("Simon input number: ", simon_input_number);
                    //debug_print("Simon current step :", simon_current_step);
                    if ( simon_current_step < last_step_in_round() )
                    {
                      simon_step_solved = true;
                    }else
                    {
                      simon_round_solved = true;
                    }
                  }else
                  {
                    /////ERROR///
                    debug_print("Simon Delay when finding ERROR: ", simon_delay);
                    simon_current_round = 0;
                    simon_current_step = 0;
                    //debug_print("i: ",i);
                    debug_print("Wrong input triggered!");
                    //debug_print("Simon input number: ", simon_input_number);
                    debug_print("Simon current step :", simon_current_step);
                    debug_print( "Simon current round ", simon_current_round );
                    need_new_random = true;
                    display_simon = false;
                    simon_startup = false;
                    simon_display_counter = 0;
                    simon_repeat_timestamp = millis();
                    play(error_sound);
                  }
                }
              }
            }else
            {
              if (simon_step_solved)
              {
                debug_print( "Solved step ", simon_current_step );
                simon_step_solved = false;
                simon_current_step++;
                debug_print( "Increased step to: ", simon_current_step );
                display_simon = false;
                pause_simon();
              }else if (simon_round_solved)
              {
                simon_round_solved = false;
                if (simon_current_round < simon_last_round() )
                {
                  debug_print( "Solved step ", simon_current_step );
                  debug_print( "Solved round ", simon_current_round );
                  simon_current_round++;
                  debug_print( "Simon current round ", simon_current_round );
                  delay(1200);
                  simon_current_step = 0;
                  pause_simon();
                  play(success_sound);
                }else
                {
                  solved = true;
                }
              }
            }
            break;
            default:
              // statements
              break;

      }
  }else{// if solved != false

    if (solve_timestamp == 0) {
      solve();
    }

    solve_outputs();
  }

  if (remote && input_state[9] == true) {
    solved = true;
  }

}//loop end
