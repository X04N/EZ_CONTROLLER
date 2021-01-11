 /*
  Universal 8bit Graphics Library, https://github.com/olikraus/u8glib/

  Copyright (c) 2012, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
bool debug = false;
void debug_print(char * text, long variable=2147483647)
{
  if(debug)
  {
    Serial.print("Debug: ");
    Serial.print(text);
    if(variable != 2147483647)
    {
      Serial.println(variable);
    }else{
      Serial.println();
    }
  }
}

//////////////////////////////   INCLUDES  //////////////////////////////////////
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include "U8glib.h"
#include "SRC/EZ.h"
//#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"



void test(char value[] = 'no value');


//////////////////////////////   DECLARE MP3  //////////////////////////////////////
DFRobotDFPlayerMini mp3;
void printDetail(uint8_t type, int value);

//////////////////////////////   DISPLAY CONFIG  //////////////////////////////////////

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI -- per display 1.3 inches
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI -- per display 0.9 inches
#define u8g_logo_width 50
#define u8g_logo_height 50
const unsigned char u8g_logo_bits[] PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFB, 0x0F, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xE0, 0x3F, 0x00, 0x00, 0x00, 0xC0, 0x7F, 0x84, 0x7F, 0x00, 0x00, 0x00, 0xF0, 0x1F, 0x1F, 0xFF, 0x01, 0x00, 0x00, 0xFC, 0xC7, 0x7F, 0xFC, 0x07, 0x00, 0x00, 0xFE, 0xE1, 0xFF, 0xF1, 0x1F, 0x00, 0x80, 0xFF, 0xF8, 0xFF, 0xC1, 0x3F, 0x00, 0xC0, 0x3F, 0xFE, 0x7F, 0x80, 0x7F, 0x00, 0xC0, 0x8F, 0xFF, 0x1F, 0x00, 0x7E, 0x00, 0xC0, 0xCF, 0xFF, 0x0F, 0x00, 0x7C, 0x00, 0xC0, 0xF7, 0xFF, 0x03, 0x00, 0x78, 0x00, 0xC0, 0xF3, 0xFF, 0x00, 0x00, 0x78, 0x00, 0x00, 0xF0, 0x7F, 0xC0, 0x03, 0x78, 0x00, 0x20, 0xF0, 0x1F, 0xF0, 0x07, 0x78, 0x00, 0x30, 0xF0, 0x07, 0xFC, 0x07, 0x78, 0x00, 0x38, 0xF0, 0x03, 0xFE, 0x07, 0x78, 0x00, 0x38, 0xF0, 0x83, 0xFF, 0x07, 0x78, 0x00, 0x38, 0xF0, 0xE3, 0xFF, 0x07, 0x78, 0x00, 0x38, 0xF0, 0xFB, 0xFF, 0x03, 0x78, 0x00, 0x38, 0xF0, 0xFF, 0xFF, 0x80, 0x79, 0x00, 0x38, 0xF0, 0xFF, 0x3F, 0xE0, 0x79, 0x00, 0x38, 0xF0, 0xFF, 0x0F, 0xF0, 0x79, 0x00, 0x38, 0xF0, 0xFF, 0x07, 0xFC, 0x79, 0x00, 0x38, 0xF0, 0xFF, 0x01, 0xFF, 0x79, 0x00, 0x38, 0xF0, 0x7F, 0xC0, 0xFF, 0x79, 0x00, 0x38, 0xF0, 0xFF, 0xE1, 0xFF, 0x79, 0x00, 0x38, 0xE0, 0xFF, 0xFB, 0xFF, 0x7D, 0x00, 0x38, 0xE0, 0xFF, 0xFF, 0x7F, 0x7C, 0x00, 0x38, 0x80, 0xFF, 0xFF, 0x3F, 0x7E, 0x00, 0x38, 0x00, 0xFE, 0xFF, 0x8F, 0x7F, 0x00, 0x78, 0x00, 0xF8, 0xFF, 0xC3, 0x3F, 0x00, 0xF8, 0x01, 0xE0, 0xFF, 0xF1, 0x1F, 0x00, 0xF8, 0x03, 0xC0, 0x7F, 0xFC, 0x07, 0x00, 0xE0, 0x0F, 0x00, 0x1F, 0xFF, 0x01, 0x00, 0x80, 0x3F, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0xFE, 0x00, 0xEE, 0x3F, 0x00, 0x00, 0x00, 0xFC, 0x01, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0xC7, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xC0, 0xCF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

// Create Menu

const byte menu_items_count = 81;
byte screen = 0;
byte Menu_Seleccionat = 0;
byte currentMenu[menu_items_count];
bool active_menu = true;
unsigned long menu_timer = 0;
int menu_timeout = 20000;
byte alternate_parent_id = false;
bool both_parent_id = false;
byte back_id = 252;
// comptador que indica quants items hi ha en el menú actual
byte countCurrentMenu = 0;
// funció a executar quan es selecciona un item del menú
byte functionToExecute = 0;
bool display_rewrite_required = 0;


// variable que enmagatzema la string retrieved de la EEPROM per pasar-la
//a la pantalla
char str_buffer[20];
// string per splash sota logo
const char *website="ESCAPEBLOCKS.COM";



////////////////////////   DECLARACIÓ INPUTS  //////////////////////////////////

// Create input objects
Input left_sw(4, "LEFT");
Input right_sw(26, "RIGHT");

const byte input_count = 10;
byte input_available = 10;
Input input_array[input_count]{
  Input(49, "IN1"),
  Input(47, "IN2"),
  Input(45, "IN3"),
  Input(43, "IN4"),
  Input(38, "IN5"),
  Input(40, "IN6"),
  Input(2, "IN7"),
  Input(7, "IN8"),
  Input(36, "IN9"),
  Input(34, "IN10")
};

bool input_state[input_count]
{false,false,false,false,false,false,false,false,false,false};
byte active_input_count = 0;
bool all_inputs_are_inactive = 1;

unsigned long active_time_next = 0;
unsigned long active_time_select = 0;
unsigned long next_count = 0;
unsigned long select_count = 0;



////////////////////////////////   ACTUADORS  //////////////////////////////////
byte in_act[input_count]
{
  48,46,44,42,41,37,3,6,35,33
};

///////////////////////////////   OUTPUTS  /////////////////////////////////////
const byte out_count = 3;
int out_delay[out_count]{
  0,0,0
};
int out_delay_add[out_count]{
  30,31,32
};

long solve_timestamp = 0;
long out_timestamp[out_count]{
  0,0,0
};

byte out_en[out_count]//out enable pins
{
  22,23,24
};
byte out_type[out_count]
{//0 = normally open (disabled), 1 = normally closed (enabled)
  0,0,0
};
int out_type_add[out_count]
{
  17,18,19
};
byte input_en = 25;
byte buzz_en = 27;

byte selected_output = 0;

//////////////////   ADRECES ALTERNATIVES   ////////////////////////////////////
bool EEPROM_populated = true;
int EEPROM_populated_add [2] = {1022,1023};

bool burnt_byte[30]{
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
int burnt_byte_add[30]{
  941,942,943,944,945,946,947,948,949,950,951,952,953,954,955,956,957,958,959,960,961,962,963,964,965,966,967,967,968,969
};

int alternate_byte[30]{
  970,971,972,973,974,975,976,977,978,979,980,981,982,983,984,985,986,987,988,989,990,991,992,993,994,995,996,997,998,999
};

////////////////////   GAME MODE I SETTINGS VARIS ///////////////////////////////

byte game_mode =  0;
byte game_mode_add = 1;
bool solved = false;
byte solve_led = 30;
byte volume = 10;
byte volume_add = 47;

 /////////////////////   VARIABLES DEL MODO STATE  /////////////////////////////

bool state_solution[input_count]{true,true,true,true,true,true,true,true,true,true};
byte count_down = 10;
int state_solution_add[input_count]{2,3,4,5,6,7,8,9,10,11};


/////////////////////   VARIABLES DEL MODO SEQUENCE  ///////////////////////////
byte s_lenght = 0;
int s_lenght_add = 12;

byte s_step_active = 0;

byte s_release_counter = 0;

bool s_step_solved = false;

byte s_active_inputs[input_count]
{
  0,0,0,0
};

int s_add [10][input_count];
byte s_solution[10][input_count];


byte s_counter = 0;

//////////////////////   VARIABLES DEL MODO MORSE  //////////////////////////

byte dual_in_morse_sequence_length = 0;
int dual_in_morse_sequence_length_add = 0;

byte dual_in_morse_step_active_count = 0;

byte dual_in_morse_release_counter = 0;

bool dual_in_morse_step_solved = false;

byte dual_in_morse_input_was_active[input_count]
{
  0,0,0,0
};


byte morse_input_count = 34;
int morse_input_count_add = 15;

byte morse_dash_length = 38;
int morse_dash_length_add = 16;

byte dual_in_morse_sequence_solution[30][input_count];
int dual_in_morse_sequence_solution_add[30][input_count];

byte dual_in_morse_sequence_counter = 0;



/////////////////////   VARIABLES DEL MODO CHECKLIST  ////////////////////////

bool checklist[input_count]{true,true,true,true,true,true,true,true,true,true};

byte checklist_size = 0;
byte checklist_counter = 0;

int checklist_add[input_count]{20,21,22,23,24,25,26,27,28,29};

byte triggered_inputs[input_count]{false,false,false,false,false,false,false,false,false,false};



/////////////////////   VARIABLES DEL MODO WIRES  ////////////////////////

byte wire_solve_pairs[input_count]// in_act_input
{
  0,1,2,3,4,5,6,7,8,9
};

byte wire_current_pairs[input_count]
{
  255,255,255,255,255,255,255,255,255,255
};

long wire_solve_pairs_add[input_count]
{
  33,34,35,36,37,38,39,40,41,42
};


/////////////////////   VARIABLES DEL MODO TRIP WIRE  ////////////////////////

bool started = false;
long last_time_flash = 0;
bool flash_state = 0;

/////////////////////   VARIABLES DEL MODO SIMON  ////////////////////////

bool simon_startup = false;
byte simon_inputs_used = 10;
const long simon_inputs_used_add = 13;

bool simon_random = false;
const long simon_random_add = 14;
bool need_new_random = true;

bool simon_sounds = false;
const long simon_sounds_add = 43;

byte simon_difficulty = 0;
const long simon_difficulty_add = 44;
long simon_delay = 1000;

byte simon_rounds = 2;
const long simon_rounds_add = 45;
bool simon_round_solved = false;

byte simon_display_counter = 0;
bool display_simon = true;

byte simon_current_step = 0;
bool simon_step_solved = false;
byte simon_current_round = 0;

long simon_last_display_change = 0;
int simon_repeat_delay = 4000;
const long simon_repeat_delay_add = 46;
bool simon_repeat = true;
bool display_finished = false;
long simon_repeat_timestamp = 0;

long simon_pause_timestamp = 0;
bool simon_pause = false;
int simon_pause_duration = 1200;

const byte simon_array_lenght =22;
const byte default_simon_sequence[11][simon_array_lenght]
{
  {0,1,2,3,4,5,6,7,8,9,3,5,1,0,4,2,7,9,6,8,5,3},// never should be used
  {0,1,2,3,4,5,6,7,8,9,3,5,1,0,4,2,7,9,6,8,5,3},// never should be used
  {0,1,1,0,1,0,1,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1},  // 2 inputs
  {0,1,2,0,0,2,1,0,1,1,2,0,2,2,2,0,0,1,1,0,2,1}, // 3 inputs
  {0,1,2,3,3,1,0,2,1,3,0,2,1,3,0,3,0,2,1,2,2,1}, // 4 inputs
  {0,1,2,3,4,3,1,0,4,2,1,4,3,0,2,1,3,0,2,1,2,4}, // 5 inputs
  {0,1,2,3,4,5,3,5,1,0,4,2,1,4,3,0,2,1,3,0,5,4}, // 6 inputs
  {0,1,2,3,4,5,6,3,5,1,0,4,2,6,1,4,3,0,2,1,6,5}, // 7 inputs
  {0,1,2,3,4,5,6,7,3,5,1,0,4,2,7,6,1,4,7,3,0,5}, // 8 inputs
  {0,1,2,3,4,5,6,7,8,3,5,1,0,4,2,7,6,8,1,4,5,3}, // 9 inputs
  {0,1,2,3,4,5,6,7,8,9,3,5,1,0,4,2,7,9,6,8,5,3} // 10 inputs
};

byte simon_sequence[20]
{
  255,255,255,255,255,255,255,255,255,255,255,225,255,255,255,255,255,255,255,255
};



/////////////////////   MP3 HANDLES  ////////////////////////

byte success_sound = 99;

byte trig_in[10]{
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10
};

byte rel_in[10]{
  11,
  12,
  13,
  14,
  15,
  16,
  17,
  18,
  19,
  20
};

byte solve_sound = 100;
byte error_sound = 101;
