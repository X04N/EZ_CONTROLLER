   // FUNCIONS//  // FUNCIONS//  // FUNCIONS//  // FUNCIONS//  // FUNCIONS//  // FUNCIONS//  // FUNCIONS//  // FUNCIONS//  // FUNCIONS//


///////////////////////////////////////// SPLASH //////////////////////////////////

 void draw_splash()
{
    u8g.firstPage();
  do {
    u8g.drawXBMP( 39, 0, u8g_logo_width, u8g_logo_height, u8g_logo_bits);
    uint8_t i, h;
    u8g_uint_t w, d;
    u8g.setFont(u8g_font_6x13);
    u8g.setFontRefHeightText();
    u8g.setFontPosTop();
    h = 13;
    w = u8g.getWidth();
    d = (w-u8g.getStrWidth(website))/2;//center text (screen width - string width)/2
    u8g.setDefaultForegroundColor();
    u8g.drawStr(d, 52, website);
    u8g.setColorIndex(1);
  } while( u8g.nextPage() );
}

///////////////////////////////////////// MENU FUNCTIONS //////////////////////////////////

void updateCurrentMenu(/*byte alternate_parent_id = 0, bool both_parent_id = 0 // NO NEED TO PASS, they are now global variables*/)
{

  byte count = 0;
  for(byte i = 0; i < menu_items_count; i++)
  {
    if(Menu_Seleccionat == 0)// when home page don't add BACK button
    {
          if(MenuList[i][1] == Menu_Seleccionat)
          {
            currentMenu[count] = i;
            count++;
          }
    }else if(alternate_parent_id != 0 && both_parent_id == 0)
    //when defined exclusive alternate id
    {
      if(MenuList[i][1] == alternate_parent_id || MenuList[i][1] == 253 )
      {
        currentMenu[count] = i;
        count++;
      }
    }else if(alternate_parent_id != 0 && both_parent_id == 1)
    // when both alternate id and regular current id need to be in the menu
    {
      if(MenuList[i][1] == alternate_parent_id || MenuList[i][1] == Menu_Seleccionat || MenuList[i][1] == 253 )
      {
        currentMenu[count] = i;
        count++;
      }
    }else// regular menu with BACK button
    {
      if(MenuList[i][1] == Menu_Seleccionat || MenuList[i][1] == 253 )
      {
        currentMenu[count] = i;
        count++;
      }
    }
  }
  countCurrentMenu = count;
  for(byte i = count; i < menu_items_count; i++)
  {
    currentMenu[i] = 255;
  }
}


void update_menu(){
  Menu_Seleccionat = currentMenu[menuPosition];
  menu_redraw_required = 1;
  menuPosition = 0;
}

void menu_back(){
  if (back_id != 252) {
    Menu_Seleccionat = back_id;
  }else if(back_id == 7){//si intenta llistar tots els puzzle settings anar a Home.
    back_id = 0;
  }else{
    Menu_Seleccionat = MenuList[Menu_Seleccionat][1];//parent
  }
  debug_print("back_id = ", back_id);
  debug_print("Menu_Seleccionat = ", Menu_Seleccionat);
  menu_redraw_required = 1;
  menuPosition = 0;
  back_id = 252;
}
/////////////////////////////////////////   MENU   //////////////////////////////////

void drawMenu()
{
  //debug_print("Drawing Menu");
  updateCurrentMenu();
  uint8_t i, h;
  u8g_uint_t w, d;
  int starting_position = 0;
  u8g.setFont(u8g_font_6x13);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  h = 13;
  w = u8g.getWidth();
  if (menuPosition > 3){
    starting_position = (menuPosition-3);

  }
  for(byte i = starting_position; i <  menu_items_count; i++ ) {
    if(currentMenu[i]==255){
      return;
    }else
    {
      strcpy_P(str_buffer, (char*)pgm_read_word(&(string_array[currentMenu[i]])));
      if(MenuList[currentMenu[i]][3] == 1)
      {
        d = (w-u8g.getStrWidth(str_buffer))/2;//center text (screen width - string width)/2
        u8g.setDefaultForegroundColor();
        int x = i-starting_position;
        //if the current menu is the selected one, draw a box around it
        if ( i == menuPosition ) {
             u8g.drawBox(0, x*h+14, w, h-2);
             u8g.setDefaultBackgroundColor();
         }
         u8g.drawTriangle(d-7,x*h+14, d-2,x*h+19, d-7,x*h+24);
         int str_w = u8g.getStrWidth(str_buffer);
         u8g.drawTriangle(d+str_w+6,x*h+14, d+str_w+1,x*h+19, d+str_w+6,x*h+24);
         u8g.drawStr(d, x*h+14, str_buffer);
         u8g.setDefaultForegroundColor();
      }else{
        d = (w-u8g.getStrWidth(str_buffer))/2;//center text
        u8g.setDefaultForegroundColor();
        int x = i-starting_position;
        //if the current menu is the selected one, draw a box around it
        if ( i == menuPosition ) {
             u8g.drawBox(0, x*h+14, w, h-2);
             u8g.setDefaultBackgroundColor();
         }
         u8g.drawStr(d, x*h+14, str_buffer);
         u8g.setDefaultForegroundColor();
      }
    }
  }

}

///////////////////////////////////////// HEADER test  //////////////////////////////////
void drawHeader(byte left, byte right, byte middle, bool limit = true)
{
  //debug_print("Drawing header");
  // if the menu to display is the main menu, display the selected puzzle mode instead of "menu"
  if (middle == 0) {
    middle = game_mode;
  }
  u8g_uint_t w, d;
  w = u8g.getWidth();
  //Set Titular
  u8g.setFont(u8g_font_6x13);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  strcpy_P(str_buffer, (char*)pgm_read_word(&(string_array[middle])));
  d = (w-u8g.getStrWidth(str_buffer))/2;
  //check string width and adjust font size in order to have it fit the space
  if(w-u8g.getStrWidth(str_buffer)> 55 || !limit){
    u8g.drawStr(d, 0, str_buffer);
  }else if(w-u8g.getStrWidth(str_buffer)< 55){
    //debug_print("Downscaling to 5x7");
    u8g.setFont(u8g_font_5x7);
    u8g.setFontRefHeightText();
    u8g.setFontPosTop();
    d = (w-u8g.getStrWidth(str_buffer))/2;
    if(w-u8g.getStrWidth(str_buffer)< 55){
      //debug_print("Downscaling to 4x6");
      u8g.setFont(u8g_font_4x6);
      u8g.setFontRefHeightText();
      u8g.setFontPosTop();
      d = (w-u8g.getStrWidth(str_buffer))/2;
      u8g.drawStr(d, 2, str_buffer);
    }else{
      u8g.drawStr(d, 1, str_buffer);
    }
  }
  //Set Info
  u8g.setFont(u8g_font_u8glib_4);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  if(left!= false){
    strcpy_P(str_buffer, (char*)pgm_read_word(&(string_array[left])));
    u8g.drawStr( 0, 2, str_buffer);
  }
  if(left!= false){
    strcpy_P(str_buffer, (char*)pgm_read_word(&(string_array[right])));
    d = (w-u8g.getStrWidth(str_buffer));
    u8g.drawStr( d, 2, str_buffer);
  }
  u8g.drawHLine(0, 12, 128);
}
///////////////////////////////////////// DISPLAY CUSTOM MESSAGE //////////////////////////////////
void display_message(byte string1, byte string2 = false, int duration = 2500, bool rewrite = false, long value = 2147483647, bool header = false, byte left = false, byte right = false, byte mid = false)
{
  u8g.firstPage();
      do
      {
            if(header)
            {
              drawHeader(left,right,mid);
            }
            u8g_uint_t w, d;
            w = u8g.getWidth();
            //Set Text
            u8g.setFont(u8g_font_6x13);
            u8g.setFontRefHeightText();
            u8g.setFontPosTop();
            if(string1 != false){
              strcpy_P(str_buffer, (char*)pgm_read_word(&(string_array[string1])));
              d = (w-u8g.getStrWidth(str_buffer))/2;
              u8g.drawStr(d, 25, str_buffer);
            }
            if (string2 != false) {
              strcpy_P(str_buffer, (char*)pgm_read_word(&(string_array[string2])));
              d = (w-u8g.getStrWidth(str_buffer))/2;
              u8g.drawStr(d, 40, str_buffer);
            }
            if(value != 2147483647){
              char str[256];
              sprintf(str, "%lld", value);
              d = (w-u8g.getStrWidth(str))/2;
              u8g.setPrintPos(d, 40);
              u8g.print(value);
            }

      } while( u8g.nextPage() );

      if(duration){
         delay(duration);
      }
      if(rewrite){
         display_rewrite_required = 1;
      }
}

void redo_list_tics(bool list[], byte initial_item_id){
  for (byte i = 0; i < input_count; i++) {
    //debug_print("counter = ", i);
    //debug_print("item id = ", initial_item_id+i);
    //debug_print("value = ", list[i]);
    MenuList[initial_item_id+i][3] = list[i];
  }
}

void redo_out_tics(){
  if(out_type[selected_output] == 0){
    MenuList[10][3] = 1;
    MenuList[11][3] = 0;
  }else{
    MenuList[10][3] = 0;
    MenuList[11][3] = 1;
  }
}

void redo_yes_no_ticks(bool value)
{
  debug_print("redo_yes_no_ticks");
  debug_print("Bool Value: ", value);
  if(value == true)
  {
    MenuList[70][3] = 1;
    MenuList[71][3] = 0;
  }else{
    MenuList[70][3] = 0;
    MenuList[71][3] = 1;
  }
  menu_redraw_required = 1;
}
