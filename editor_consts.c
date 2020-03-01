#include "editor.h"

void (* const EDITOR_FUNCS[EDITOR_ACTION_LEN])(screen * sc) = {
  move_cursor_up,
  move_cursor_down,
  move_cursor_left,
  move_cursor_right,
  delete_before_cursor,
  insert_linebreak_after_cursor,
  insert_linebreak_after_cursor
};

const t_key EDITOR_BUTTONS[EDITOR_ACTION_LEN] = {
  KEY_NSPIRE_UP,
  KEY_NSPIRE_DOWN,
  KEY_NSPIRE_LEFT,
  KEY_NSPIRE_RIGHT,
  KEY_NSPIRE_DEL,
  KEY_NSPIRE_ENTER,
  KEY_NSPIRE_RET
};

const char normal_keypress[INSERT_ACTION_LEN] = {
  'a','b','c','d','e','f',
  'g','h','i','j','k','l',
  'm','n','o','p','q','r',
  's','t','u','v','w','x',
  'y','z','1','2','3','4',
  '5','6','7','8','9','0',
  '.','-','=','^','(',')',
  '*','/','+','-',',','?','%',' '
};
const char shift_keypress[INSERT_ACTION_LEN] = {
  'A','B','C','D','E','F',
  'G','H','I','J','K','L',
  'M','N','O','P','Q','R',
  'S','T','U','V','W','X',
  'Y','Z','1','2','3','4',
  '5','6','7','8','9','0',
  ':','_','>','"','[',']',
  '#','\\','&','_',';','!','$',' '
};
const char ctrl_keypress[INSERT_ACTION_LEN] = {
  'a','b','c','d','e','f',
  'g','h','i','j','k','l',
  'm','n','o','p','q','r',
  's','t','u','v','w','x',
  'y','z','1','2','3','4',
  '5','6','7','8','9','0',
  '.','~','<','\'','{','}',
  '*','|','+','~','`','?','@',' '
};

const t_key INSERT_BUTTONS[INSERT_ACTION_LEN] = {
  KEY_NSPIRE_A,
  KEY_NSPIRE_B,
  KEY_NSPIRE_C,
  KEY_NSPIRE_D,
  KEY_NSPIRE_E,
  KEY_NSPIRE_F,
  KEY_NSPIRE_G,
  KEY_NSPIRE_H,
  KEY_NSPIRE_I,
  KEY_NSPIRE_J,
  KEY_NSPIRE_K,
  KEY_NSPIRE_L,
  KEY_NSPIRE_M,
  KEY_NSPIRE_N,
  KEY_NSPIRE_O,
  KEY_NSPIRE_P,
  KEY_NSPIRE_Q,
  KEY_NSPIRE_R,
  KEY_NSPIRE_S,
  KEY_NSPIRE_T,
  KEY_NSPIRE_U,
  KEY_NSPIRE_V,
  KEY_NSPIRE_W,
  KEY_NSPIRE_X,
  KEY_NSPIRE_Y,
  KEY_NSPIRE_Z,
  KEY_NSPIRE_1,
  KEY_NSPIRE_2,
  KEY_NSPIRE_3,
  KEY_NSPIRE_4,
  KEY_NSPIRE_5,
  KEY_NSPIRE_6,
  KEY_NSPIRE_7,
  KEY_NSPIRE_8,
  KEY_NSPIRE_9,
  KEY_NSPIRE_0,
  KEY_NSPIRE_PERIOD,
  KEY_NSPIRE_NEGATIVE,
  KEY_NSPIRE_EQU,
  KEY_NSPIRE_EXP,
  KEY_NSPIRE_LP,
  KEY_NSPIRE_RP,
  KEY_NSPIRE_MULTIPLY,
  KEY_NSPIRE_DIVIDE,
  KEY_NSPIRE_PLUS,
  KEY_NSPIRE_MINUS,
  KEY_NSPIRE_COMMA,
  KEY_NSPIRE_QUESEXCL,
  KEY_NSPIRE_FLAG,
  KEY_NSPIRE_SPACE,
};
