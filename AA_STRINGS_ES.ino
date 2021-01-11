

  ////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////       STRINGS      //////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  const byte state = 2;//
  const byte secuence = 3;//
  const byte wires = 4;//
  const byte morse = 5;
  const byte simon = 6;//
  const byte checklist_mode = 49;//
  const byte trip_wire = 66;//

  //llistes de items i strings dls menús
  byte MenuList[menu_items_count][4]={
    // ID - PARENT - FUNCTION - ACTIVE
    {0,254, 1, 0},   // 0 menu
    {1, 0, 1, 0},    // 1 CHOOSE PUZZLE
    {2, 7, 1, 0},    // 2 input state (PUZZLE MODE)
    {3, 7, 3, 0},    // 3 input sequence  (PUZZLE MODE)
    {4, 252, 6, 0},    // 4 connect wires (PUZZLE MODE)
    {5, 252, 1, 0},    // 5 morse code (PUZZLE MODE)
    {6, 7, 1, 0},    // 6 simon game (PUZZLE MODE)
    {7, 0, 17, 0},    // 7 PUZZLE SETTINGS
    {8, 33, 1, 0},   // 8 output type
    {9, 33, 5, 0},   // 9 output delay
    {10, 8, 4, 0},   // 10 NO Normally open
    {11, 8, 4, 0},   // 11 NC Normally Closed
    {12, 77, 1, 0},   // 12 OUTPUT SETTINGS
    {13, 252, 0, 0}, // 13 SELECT
    {14, 252, 0, 0}, // 14 SECONDS
    {15, 252, 0, 0}, // 15 ADD
    {16, 252, 0, 0}, // 16 ERROR: SEQUENCE IS
    {17, 2, 0, 0},   // 17 SAVING STATE IN
    {18, 2, 0, 0},   // 18 SAVED
    {19, 2, 0, 0},   // 19 YOU CAN RELEASE
    {20, 3, 0, 0},   // 20 FIRST
    {21, 3, 0, 0},   // 21 SECOND
    {22, 3, 0, 0},   // 22 THIRD
    {23, 3, 0, 0},   // 23 FOURTH
    {24, 3, 0, 0},   // 24 FIFTH
    {25, 3, 0, 0},   // 25 SIXTH
    {26, 3, 0, 0},   // 26 SEVENTH
    {27, 3, 0, 0},   // 27 EIGTH
    {28, 3, 0, 0},   // 28 NINTH
    {29, 3, 0, 0},   // 29 TENTH
    {30, 3, 0, 0},   // 30 PRESS NEXT
    {31, 5, 7, 0},   // 31 NEW MORSE SOLUTION
    {32, 5, 1, 0},   // 33 MORSE DASH DURATION
    {33, 12, 1, 0},  // 33 OUTPUT 1
    {34, 12, 1, 0},  // 34 OUTPUT 2
    {35, 12, 1, 0},  // 35 OUTPUT 3
    {36, 32, 9, 0},  // 36 0.5S
    {37, 32, 9, 0},  // 37 0.6S
    {38, 32, 9, 0},  // 38 0.7S(R)
    {39, 32, 9, 0},  // 39 0.8S
    {40, 32, 9, 0},  // 40 0.9S
    {41, 32, 9, 0},  // 41 1S
    {42, 252, 0, 0}, // 42 ERROR: AT LEAST ONE
    {43, 252, 0, 0}, // 43 INPUT MUST BE ON
    {44, 252, 0, 0}, // 44 ERROR: ONLY ONE
    {45, 252, 0, 0}, // 45 INPUT MUST BE ON
    {46, 252, 0, 0}, // 46 FINISH
    {47, 252, 0, 0}, // 47 NEXT
    {48, 252, 0, 0}, // 48 SOLVED
    {49, 7, 1, 0},   // 49 CHECKLIST (PUZZLE MODE)
    {50, 252, 0, 0}, // 50 CHECKLIST SAVED
    {51, 49, 10, 0}, // 51 INPUT 1
    {52, 49, 10, 0}, // 52 INPUT 2
    {53, 49, 10, 0}, // 53 INPUT 3
    {54, 49, 10, 0}, // 54 INPUT 4
    {55, 49, 10, 0}, // 55 INPUT 5
    {56, 49, 10, 0}, // 56 INPUT 6
    {57, 49, 10, 0}, // 57 INPUT 7
    {58, 49, 10, 0}, // 58 INPUT 8
    {59, 49, 10, 0}, // 59 INPUT 9
    {60, 49, 10, 0}, // 60 INPUT 10
    {61, 252, 11, 0}, // 61 SAVE
    {62, 252, 0, 0}, // 62 TOO SHORT
    {63, 252, 0, 0}, // 63 SAVING WIRES
    {64, 252, 0, 0}, // 64 SAVING
    {65, 252, 0, 0}, // 65 PLEASE WAIT
    {66, 7, 8, 0},   // 66 TRIP WIRE (PUZZLE MODE)
    {67, 6, 1, 0},   // 67 RANDOM
    {68, 6, 12, 0},  // 68 NUMBER OF INPUTS
    {69, 6, 1, 0},   // 69 SOUNDS
    {70, 67, 13, 0}, // 70 YES
    {71, 67, 13, 0}, // 71 NO
    {72, 6, 1, 0},   // 72 DIFFICULTY
    {73, 72, 14, 0}, // 73 EASY
    {74, 72, 14, 0}, // 74 MEDIUM
    {75, 72, 14, 0}, // 75 HARD
    {76, 6, 15, 0},  // 76 NUMBER OF ROUNDS
    {77, 0, 1, 0},  // 77 OTHER SETTINGS
    {78, 77, 18, 0},// 78 VOLUME
    {79, 78, 254, 0},// 78 SET VOLUME 0-30
    {80, 253, 2, 0} // 79 BACK
  };// ID - PARENT - FUNCTION - ACTIVE


    //////////////// ENGLISH /////////////////////

      const static char EN_0[] PROGMEM = "MENU";
      const static char EN_1[] PROGMEM = "TIPO DE PUZZLE";
      const static char EN_2[] PROGMEM = "ESTADO";
      const static char EN_3[] PROGMEM = "SECUENCIA";
      const static char EN_4[] PROGMEM = "CABLES";
      const static char EN_5[] PROGMEM = "CODIGO MORSE";
      const static char EN_6[] PROGMEM = "SIMON";
      const static char EN_7[] PROGMEM = "AJUSTES DE PUZZLE";
      const static char EN_8[] PROGMEM = "TIPO DE SALIDA";
      const static char EN_9[] PROGMEM = "RETRASO DE SALIDA";
      const static char EN_10[] PROGMEM = "OFF AL SOLUCIONAR";
      const static char EN_11[] PROGMEM = "ON AL SOLUCIONAR";
      const static char EN_12[] PROGMEM = "SALIDAS";
      const static char EN_13[] PROGMEM = "ESCOGER";
      const static char EN_14[] PROGMEM = "DRETRASO EN SEGUNDOS";
      const static char EN_15[] PROGMEM = "MAS";
      const static char EN_16[] PROGMEM = "ERROR: LA SECUENCIA ES";
      const static char EN_17[] PROGMEM = "GUARDANDO ESTADO EN";
      const static char EN_18[] PROGMEM = "GUARDADO!";
      const static char EN_19[] PROGMEM = "PUEDES SOLTAR";
      const static char EN_20[] PROGMEM = "MANTEN PASO 1 Y";
      const static char EN_21[] PROGMEM = "MANTEN PASO 2 Y";
      const static char EN_22[] PROGMEM = "MANTEN PASO 3 Y";
      const static char EN_23[] PROGMEM = "MANTEN PASO 4 Y";
      const static char EN_24[] PROGMEM = "MANTEN PASO 5 Y";
      const static char EN_25[] PROGMEM = "MANTEN PASO 6 Y";
      const static char EN_26[] PROGMEM = "MANTEN PASO 7 Y";
      const static char EN_27[] PROGMEM = "MANTEN PASO 8 Y";
      const static char EN_28[] PROGMEM = "MANTEN PASO 9 Y";
      const static char EN_29[] PROGMEM = "MANTEN PASO 10 Y";
      const static char EN_30[] PROGMEM = "PULSA SIGUIENTE";
      const static char EN_31[] PROGMEM = "GUARDAR NUEVA SOLUCION";
      const static char EN_32[] PROGMEM = "DURACIÓN LINIA";
      const static char EN_33[] PROGMEM = "SALIDA 1";
      const static char EN_34[] PROGMEM = "SALIDA 2";
      const static char EN_35[] PROGMEM = "SALIDA 3";
      const static char EN_36[] PROGMEM = "0.5s";
      const static char EN_37[] PROGMEM = "0.6s";
      const static char EN_38[] PROGMEM = "0.7s (recommendado)";
      const static char EN_39[] PROGMEM = "0.8s";
      const static char EN_40[] PROGMEM = "0.9s";
      const static char EN_41[] PROGMEM = "1s";
      const static char EN_42[] PROGMEM = "ERROR: NINGUN";
      const static char EN_43[] PROGMEM = "INPUT ENCENDIDO";
      const static char EN_44[] PROGMEM = "ERROR: MAS DE UN";
      const static char EN_45[] PROGMEM = "INPUT ENCENDIDO";
      const static char EN_46[] PROGMEM = "ACABAR";
      const static char EN_47[] PROGMEM = "SIG";
      const static char EN_48[] PROGMEM = "SOLUCIONADO";
      const static char EN_49[] PROGMEM = "LISTA";
      const static char EN_50[] PROGMEM = "LISTA GUARDADA";
      const static char EN_51[] PROGMEM = "INPUT 1";
      const static char EN_52[] PROGMEM = "INPUT 2";
      const static char EN_53[] PROGMEM = "INPUT 3";
      const static char EN_54[] PROGMEM = "INPUT 4";
      const static char EN_55[] PROGMEM = "INPUT 5";
      const static char EN_56[] PROGMEM = "INPUT 6";
      const static char EN_57[] PROGMEM = "INPUT 7";
      const static char EN_58[] PROGMEM = "INPUT 8";
      const static char EN_59[] PROGMEM = "INPUT 9";
      const static char EN_60[] PROGMEM = "INPUT 10";
      const static char EN_61[] PROGMEM = "GUARDAR";
      const static char EN_62[] PROGMEM = "DEMASIADO CORTO";
      const static char EN_63[] PROGMEM = "GUARDANDO CABLES EN";
      const static char EN_64[] PROGMEM = "GUARDANDO";
      const static char EN_65[] PROGMEM = "ESPERA";
      const static char EN_66[] PROGMEM = "TRAMPA";
      const static char EN_67[] PROGMEM = "ALEATORIO";
      const static char EN_68[] PROGMEM = "NUMBERO DE INPUTS";
      const static char EN_69[] PROGMEM = "SONIDOS PISTA";
      const static char EN_70[] PROGMEM = "SI";
      const static char EN_71[] PROGMEM = "NO";
      const static char EN_72[] PROGMEM = "VELOCIDAD";
      const static char EN_73[] PROGMEM = "LENTO";
      const static char EN_74[] PROGMEM = "MEDIO";
      const static char EN_75[] PROGMEM = "RAPIDO";
      const static char EN_76[] PROGMEM = "NUMERO DE RONDAS";
      const static char EN_77[] PROGMEM = "OTROS AJUSTES";
      const static char EN_78[] PROGMEM = "VOLUMEN";
      const static char EN_79[] PROGMEM = "AJUSTAR VOLUMEN 0-30";
      const static char EN_80[] PROGMEM = "ATRAS";



  ////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////   STRING ARRAY     //////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////

  //STRING ARRAY

  const char * const string_array [menu_items_count] PROGMEM =
  {
    EN_0,
    EN_1,
    EN_2,
    EN_3,
    EN_4,
    EN_5,
    EN_6,
    EN_7,
    EN_8,
    EN_9,
    EN_10,
    EN_11,
    EN_12,
    EN_13,
    EN_14,
    EN_15,
    EN_16,
    EN_17,
    EN_18,
    EN_19,
    EN_20,
    EN_21,
    EN_22,
    EN_23,
    EN_24,
    EN_25,
    EN_26,
    EN_27,
    EN_28,
    EN_29,
    EN_30,
    EN_31,
    EN_32,
    EN_33,
    EN_34,
    EN_35,
    EN_36,
    EN_37,
    EN_38,
    EN_39,
    EN_40,
    EN_41,
    EN_42,
    EN_43,
    EN_44,
    EN_45,
    EN_46,
    EN_47,
    EN_48,
    EN_49,
    EN_50,
    EN_51,
    EN_52,
    EN_53,
    EN_54,
    EN_55,
    EN_56,
    EN_57,
    EN_58,
    EN_59,
    EN_60,
    EN_61,
    EN_62,
    EN_63,
    EN_64,
    EN_65,
    EN_66,
    EN_67,
    EN_68,
    EN_69,
    EN_70,
    EN_71,
    EN_72,
    EN_73,
    EN_74,
    EN_75,
    EN_76,
    EN_77,
    EN_78,
    EN_79,
    EN_80
  };

const byte number_of_modes = 7;
const byte puzzle_modes[number_of_modes]
{
  2,3,4,5,6,49,66
};
