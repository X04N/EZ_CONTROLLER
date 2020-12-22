   //SETUP//    //SETUP//    //SETUP//    //SETUP//    //SETUP//    //SETUP//


void setup() {

  Serial.begin(9600);
  debug_print("Entering Setup");
  draw_splash();
  debug_print("debug_mode_ON");
  menu_redraw_required = 1;// force initial redraw

/////////////// SET MP3 PLAYER /////////////////
  Serial1.begin(9600);
  Serial.println();
  Serial.println(F("Initializing MP3 Player ... (May take 3~5 seconds)"));

  delay(1000);

  if (!mp3.begin(Serial1)) {  //Use Serial1 to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    //while(true);
  }else{
    Serial.println(F("MP3 Player working properly"));
    mp3.outputDevice(DFPLAYER_DEVICE_U_DISK);

    mp3.volume(30);  //Set volume value. From 0 to 30

  }




  /////////////// SET SEQUENCE ADDRESSES /////////////////
  int a = 100;
  for(byte i = 0; i < 10; i++)
  {
    for(byte e = 0; e < input_count; e++)
    {
      s_add[i][e] = a;
      a++;
    }
  }

  /////////////// SET DUAL IN MORSE SEQUENCE ADDRESSES /////////////////

  a = 300;
  for(byte i = 0; i < 30; i++)
  {
    for(byte e = 0; e < input_count; e++)
    {
      dual_in_morse_sequence_solution_add[i][e] = a;
      a++;
    }
  }




  /////////////// SET SEQUENCE SOLUTION VARIABLE TO ZERO /////////////////

  for(byte i = 0; i < 10; i++)
  {
    for(byte e = 0; e < input_count; e++)
    {
      s_solution[i][e] = 0;
    }
  }

  /////////////// SET DUAL IN MORSE SEQUENCE SOLUTION /////////////////

  for(byte i = 0; i < 30; i++)
  {
    for(byte e = 0; e < input_count; e++)
    {
      dual_in_morse_sequence_solution[i][e] = 0;
    }
  }



  // omplim tots els espais de l'array amb el valor més alt possible, 255
  for(int i = 0; i < menu_items_count; i++)
  {
    currentMenu[i] = 255;
  }

  /////////////// SET OUTPUT PINS /////////////////

  for(int i = 0; i < sizeof(in_act); i++) // actuadors dels inputs.
  {
    pinMode(in_act[i],OUTPUT);
    digitalWrite(in_act[i], LOW);
  }

  for(int i = 0; i < 2; i++)
  {
    pinMode(out_en[i],OUTPUT);
  }

  pinMode(solve_led,OUTPUT);
  digitalWrite(solve_led, LOW);

  /////////////// SET INTPUT PINS /////////////////

    // Declarem els pins d'entrada asignats als inputs
    for(byte i = 0; i < input_count; i++)
    {
      // Declarem els pins d'entrada asignats als inputs
      pinMode(input_array[i].get_pin(),INPUT_PULLUP);
      //aprofitem el for loop per carregar de la memoria EEPROM
      // la última solució guardada del mode state.
      if(game_mode == 0){
        state_solution[i] = EEPROM.read(state_solution_add[i]);
      }else if(game_mode == 1){
      }
    }

  /////////////// CHECK IF EEPROM IS POPULATED/////////////////
for (byte i = 0; i < 2; i++) {
  if (EEPROM.read(EEPROM_populated_add[i]) != 22) {
    EEPROM_populated = false;
    debug_print("EEPROM populated false = ", i);
  }
}
debug_print("EEPROM_populated= ",EEPROM_populated);
if (EEPROM_populated)
{
  /////////////// LOAD STORED VALUES FROM EEPROM /////////////////
  change_puzzle(EEPROM.read(game_mode_add));
  debug_print("puzzle mode:", game_mode);

  volume = EEPROM.read(volume_add);
  mp3.volume(volume);  //Set volume value. From 0 to 30

  for (byte i = 0; i < out_count; i++) {
    out_delay[i] = EEPROM.read(out_delay_add[i]);
  }

  for (byte i = 0; i < out_count; i++) {
    out_type[i] = EEPROM.read(out_type_add[i]);
  }

  morse_input_count = EEPROM.read(morse_input_count_add);
  set_morse_input_count(morse_input_count);

  morse_dash_length = EEPROM.read(morse_dash_length_add);
  set_morse_dash_length(morse_dash_length);

  s_lenght = EEPROM.read(s_lenght_add);
  debug_print("SEQUENCE LENGHT = ", s_lenght);
  dual_in_morse_sequence_length = EEPROM.read(dual_in_morse_sequence_length_add);

  // load sequence solution
  for(byte i=0; i<10; i++){
    for(byte x=0; x<input_count; x++){
      s_solution[i][x] = EEPROM.read(s_add[i][x]);
    }
  }
  // load state solve array
  for(byte i = 0; i< input_count; i++){
    state_solution[i] = EEPROM.read(state_solution_add[i]);
  }
  if(debug){
    Serial.println("State_Solution: ");
    for(byte i = 0; i< input_count; i++){
      Serial.print(state_solution[i]);
      if(i<input_count-1)
      {
        Serial.print(", ");
      }else
      {
        Serial.println();
      }
    }
  }

  // Load checklist array
  for (byte i = 0; i < input_count; i++) {
    checklist[i] = EEPROM.read(checklist_add[i]);
    if (checklist[i]==true) {
      MenuList[i+51][3] = true;
      checklist_size++;
    }
  }
  if(debug){
    Serial.println("Checklist_Solution: ");
    for(byte i = 0; i< input_count; i++){
      Serial.print(checklist[i]);
      if(i<input_count-1)
      {
        Serial.print(", ");
      }else
      {
        Serial.println();
      }
    }
  }

  //solució dual in morse sequence
  for(byte i=0; i<30; i++){
    for(byte x=0; x<input_count; x++){  //INPUT_COUNT???? IS IT RIGHT?
      dual_in_morse_sequence_solution[i][x] = EEPROM.read(dual_in_morse_sequence_solution_add[i][x]);
      }
  }

  //load number of inputs for SIMON game MODE
  simon_inputs_used = EEPROM.read(simon_inputs_used_add);
  debug_print("simon_input_number = ", simon_inputs_used);
  //load BOOL RANDOM for SIMON game MODE
  simon_random = EEPROM.read(simon_random_add);
  debug_print("simon_random = ",simon_random);
  //load BOOL SOUNDS for SIMON game MODE
  simon_sounds = EEPROM.read(simon_sounds_add);
  debug_print("simon_sounds = ",simon_sounds);
  //load DIFFICULTY for SIMON game MODE
  simon_difficulty = EEPROM.read(simon_difficulty_add);
  debug_print("simon_difficulty = ",simon_difficulty);
  save_simon_difficulty(simon_difficulty);
  //load STEPS for SIMON game MODE
  simon_rounds = EEPROM.read(simon_rounds_add);
  debug_print("simon_rounds = ",simon_rounds);

  /////////////// FINISHED LOADING STORED VALUES FROM EEPROM /////////////////
}else{
  reset_factory();
}

for(int i = 0; i < 2; i++)
{
  if (out_type[i] == 0) {
    digitalWrite(out_en[i], HIGH);
  }else{
    digitalWrite(out_en[i], LOW);
  }
}


  debug_print("Setup Finished");
  for (byte i = 0; i < input_count; i++) {
    debug_print("State solution ",i);
    debug_print(" = ",state_solution[i]);
  }
  play(99);
}//end setup
