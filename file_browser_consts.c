#include "file_browser.h"

void (* const FB_FUNCS[FB_ACTION_LEN])(screen * sc) = {
  move_fb_cursor_up,
  move_fb_cursor_down,
  move_fb_cursor_left,
  move_fb_cursor_right,
  fb_delete_before_cursor,
  toggle_filename_browsing,
  fb_enter_pressed,
  fb_enter_pressed
};

const t_key FB_BUTTONS[FB_ACTION_LEN] = {
  KEY_NSPIRE_UP,
  KEY_NSPIRE_DOWN,
  KEY_NSPIRE_LEFT,
  KEY_NSPIRE_RIGHT,
  KEY_NSPIRE_DEL,
  KEY_NSPIRE_TAB,
  KEY_NSPIRE_ENTER,
  KEY_NSPIRE_RET,
};
