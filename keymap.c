#include QMK_KEYBOARD_H
#include "app_ble_func.h"

extern keymap_config_t keymap_config;

enum ergodash_ble_layers {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _MOUSE,
};

enum ergodash_ble_keycodes {
  AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
  BLE_DIS,              /* Disable BLE HID sending              */
  BLE_EN,               /* Enable BLE HID sending               */
  USB_DIS,              /* Disable USB HID sending              */
  USB_EN,               /* Enable USB HID sending               */
  DELBNDS,              /* Delete all bonding                   */
  ADV_ID0,              /* Start advertising to PeerID 0        */
  ADV_ID1,              /* Start advertising to PeerID 1        */
  ADV_ID2,              /* Start advertising to PeerID 2        */
  ADV_ID3,              /* Start advertising to PeerID 3        */
  ADV_ID4,              /* Start advertising to PeerID 4        */
  BATT_LV,              /* Display battery level in milli volts */
  DEL_ID0,              /* Delete bonding of PeerID 0           */
  DEL_ID1,              /* Delete bonding of PeerID 1           */
  DEL_ID2,              /* Delete bonding of PeerID 2           */
  DEL_ID3,              /* Delete bonding of PeerID 3           */
  DEL_ID4,              /* Delete bonding of PeerID 4           */
  ENT_DFU,              /* Start bootloader                     */
  ENT_SLP,              /* Deep sleep mode                      */
  QWERTY,
};

// Fillers to make layering more clear
#define XXXXXXX KC_NO
#define _______ KC_TRNS
#define KC_JPN  LALT(KC_GRV)

#define LWR_SPC LT(_LOWER, KC_SPC)      // Turn on _LOWER layer when held, Space when tapped
#define RSE_ENT LT(_RAISE, KC_ENT)      // Turn on _RAISE layer when held, Enter when tapped
#define RSE_BSP LT(_RAISE, KC_BSPC)     // Turn on _RAISE layer when held, Backspace when tapped
#define MOU_SCL LT(_MOUSE, KC_SCLN)     // Turn on _MOUSE layer when held, ; when tapped
#define CTL_ESC LCTL_T(KC_ESC)          // Left Control when held, Esc when tapped
#define CTL_ESC LCTL_T(KC_ESC)          // Left Control when held, Esc when tapped
#define CTL_Z   LCTL_T(KC_Z)            // Left Control when held, z when tapped
#define CTL_SCL LCTL_T(KC_SCLN)         // Left Control when held, ; when tapped
#define CTL_GRV LCTL_T(KC_GRV)          // Left Control when held, ` when tapped
#define CTL_SLS RCTL_T(KC_SLSH)         // Right Control when held, / when tapped
#define GUI_QUO RGUI_T(KC_QUOT)         // Right Gui when held, " when tapped
#define SFT_ENT RSFT_T(KC_ENT)          // Right Shift when held, Enter when tapped
#define SFT_BSP RSFT_T(KC_BSPC)         // Right Shift when held, Backspace when tapped
#define SFT_BSL RSFT_T(KC_BSLS)         // Right Shift when held, \ when tapped
#define CAG_QUO LCAG_T(KC_QUOT)         // Ctrl+Alt+Gui when held, " when tapped
#define CAG_PUP LCAG_T(KC_PGUP)         // Ctrl+Alt+Gui when held, Page Up when tapped
#define CAG_PDN LCAG_T(KC_PGDN)         // Ctrl+Alt+Gui when held, Page Down when tapped
#define CAG_LBR LCAG_T(KC_LBRC)         // Ctrl+Alt+Gui when held, [ when tapped
#define CAG_RBR LCAG_T(KC_RBRC)         // Ctrl+Alt+Gui when held, ] when tapped

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                       ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
   * │   =    │   1    │   2    │   3    │   4    │   5    │  Del   │                       │   `    │   6    │   7    │   8    │   9    │   0    │   -    │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │  Tab   │   Q    │   W    │   E    │   R    │   T    │   [    │                       │   ]    │   Y    │   U    │   I    │   O    │   P    │   \    │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │CTL /ESC│   A    │   S    │   D    │   F    │   G    │  PgUp  │                       │  PgDn  │   H    │   J    │   K    │   L    │ ; / MOU│ ' / GUI│
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │ Shift  │ Z / CTL│   X    │   C    │   V    │   B    │ Space  │  Home  │     │  End   │  Enter │  N     │   M    │   ,    │   .    │ / / CTL│Sft/BkSp│
   * ├────────┼────────┼────────┼────────┼────┬───┴────┬─┬─┼────────┼────────┤     ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
   * │  Ctrl  │ CAG / '│  Alt   │  GUI   ││││││LWR/ SPC│││││ Space  │ BkSpace│     │  Tab   │  Enter │││││RSE/ ENT││││││  Left  │  Down  │   Up   │  Right │
   * └────────┴────────┴────────┴────────┴────┴────────┴─┴─┴────────┴────────┘     └────────┴────────┴─┴─┴────────┴────┴────────┴────────┴────────┴────────┘
   */
  [_QWERTY] = LAYOUT( \
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_DEL,                           KC_GRV,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                          KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_PGUP,                          KC_PGDN, KC_H,    KC_J,    KC_K,    KC_L,    MOU_SCL, GUI_QUO, \
    KC_LSFT, CTL_Z,   KC_X,    KC_C,    KC_V,    KC_B,             KC_HOME,        KC_END,           KC_N,    KC_M,    KC_COMM, KC_DOT,  CTL_SLS, KC_RSFT, \
    CTL_GRV, CAG_QUO, KC_LALT, KC_LGUI,     LWR_SPC,      KC_SPC , KC_BSPC,        KC_ENT,  KC_ENT,      RSE_ENT,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
  ),

  /*
   * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                       ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
   * │  F12   │   F1   │   F2   │   F3   │   F4   │   F5   │        │                       │        │   F6   │   F7   │   F8   │   F9   │  F10   │  F11   │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │   ~    │   !    │   @    │   #    │   $    │   %    │        │                       │        │   ^    │   &    │   *    │   (    │   )    │   |    │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        │        │        │        │                       │        │        │        │        │        │        │        │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        │        │        │        │        │     │        │        │        │        │        │        │        │        │
   * ├────────┼────────┼────────┼────────┼────┬───┴────┬─┬─┼────────┼────────┤     ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        ││││││        │││││        │        │     │        │        │││││        ││││││        │        │        │        │
   * └────────┴────────┴────────┴────────┴────┴────────┴─┴─┴────────┴────────┘     └────────┴────────┴─┴─┴────────┴────┴────────┴────────┴────────┴────────┘
   */
  [_LOWER] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                          _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,                          _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
    AD_WO_L, ADV_ID0, ADV_ID1, ADV_ID2, ADV_ID3, ADV_ID4, _______,                          _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,          _______,        _______,          _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,     _______,      _______, _______,        _______, _______,      _______,     _______, _______, _______, _______  \
  ),

  /*
   * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                       ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
   * │  F12   │   F1   │   F2   │   F3   │   F4   │   F5   │        │                       │        │   F6   │   F7   │   F8   │   F9   │  F10   │  F11   │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │   ~    │   !    │   @    │   #    │   $    │   %    │        │                       │        │   ^    │   &    │   *    │   (    │   )    │   |    │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        │        │        │        │                       │        │        │        │        │        │        │        │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        │        │        │        │        │     │        │        │        │        │        │        │        │        │
   * ├────────┼────────┼────────┼────────┼────┬───┴────┬─┬─┼────────┼────────┤     ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        ││││││        │││││        │        │     │        │        │││││        ││││││        │        │        │        │
   * └────────┴────────┴────────┴────────┴────┴────────┴─┴─┴────────┴────────┘     └────────┴────────┴─┴─┴────────┴────┴────────┴────────┴────────┴────────┘
   */
  [_RAISE] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                          _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,                          _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
    AD_WO_L, ADV_ID0, ADV_ID1, ADV_ID2, ADV_ID3, ADV_ID4, _______,                          _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,          _______,        _______,          _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,     _______,      _______, _______,        _______, _______,      _______,     _______, _______, _______, _______  \
  ),

  /*
   * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                       ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
   * │        │        │        │        │        │        │        │                       │        │        │        │        │        │        │        │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │        │        │ MClick │  MS_U  │ RClick │        │        │                       │        │        │ RClick │  WH_U  │ MClick │        │        │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │        │ LClick │  MS_L  │  MS_D  │  MS_R  │ LClick │        │                       │        │ LClick │  WH_L  │  WH_D  │  WH_R  │        │        │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        │        │        │        │        │     │        │        │        │        │        │        │        │        │
   * ├────────┼────────┼────────┼────────┼────┬───┴────┬─┬─┼────────┼────────┤     ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        ││││││        │││││        │        │     │        │        │││││        ││││││        │        │        │        │
   * └────────┴────────┴────────┴────────┴────┴────────┴─┴─┴────────┴────────┘     └────────┴────────┴─┴─┴────────┴────┴────────┴────────┴────────┴────────┘
   */
  [_MOUSE] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, KC_BTN3, KC_MS_U, KC_BTN2, _______, _______,                          _______, _______, KC_BTN2, KC_WH_U, KC_BTN3, _______, _______, \
    _______, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, _______,                          _______, KC_BTN1, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______, \
    _______, _______, _______, _______, _______, _______,          _______,        _______,          _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,     _______,      _______, _______,        _______, _______,      _______,     _______, _______, _______, _______  \
  ),

  /*
   * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                       ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
   * │        │        │        │        │        │        │        │                       │        │        │        │        │        │        │        │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        │        │        │        │                       │        │        │        │        │        │        │        │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        │        │        │        │                       │        │        │        │        │        │        │        │
   * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        │        │        │        │        │     │        │        │        │        │        │        │        │        │
   * ├────────┼────────┼────────┼────────┼────┬───┴────┬─┬─┼────────┼────────┤     ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
   * │        │        │        │        ││││││        │││││        │        │     │        │        │││││        ││││││        │        │        │        │
   * └────────┴────────┴────────┴────────┴────┴────────┴─┴─┴────────┴────────┘     └────────┴────────┴─┴─┴────────┴────┴────────┴────────┴────────┴────────┘
   *
   * [_SAMPLE] = LAYOUT(
   *   _______, _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, _______, \
   *   _______, _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, _______, \
   *   _______, _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, _______, \
   *   _______, _______, _______, _______, _______, _______,          _______,        _______,          _______, _______, _______, _______, _______, _______, \
   *   _______, _______, _______, _______,     _______,      _______, _______,        _______, _______,      _______,     _______, _______, _______, _______  \
   * ),
   */
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
  layer_state_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];

  if (record->event.pressed) {
    switch (keycode) {
      case DELBNDS:
        delete_bonds();
        return false;
      case AD_WO_L:
        restart_advertising_wo_whitelist();
        return false;
      case USB_EN:
        set_usb_enabled(true);
        return false;
        break;
      case USB_DIS:
        set_usb_enabled(false);
        return false;
        break;
      case BLE_EN:
        set_ble_enabled(true);
        return false;
        break;
      case BLE_DIS:
        set_ble_enabled(false);
        return false;
        break;
      case ADV_ID0:
        restart_advertising_id(0);
        return false;
      case ADV_ID1:
        restart_advertising_id(1);
        return false;
      case ADV_ID2:
        restart_advertising_id(2);
        return false;
      case ADV_ID3:
        restart_advertising_id(3);
        return false;
      case ADV_ID4:
        restart_advertising_id(4);
        return false;
      case DEL_ID0:
        delete_bond_id(0);
        return false;
      case DEL_ID1:
        delete_bond_id(1);
        return false;
      case DEL_ID2:
        delete_bond_id(2);
        return false;
      case DEL_ID3:
        delete_bond_id(3);
        return false;
      case BATT_LV:
        sprintf(str, "%4dmV", get_vcc());
        send_string(str);
        return false;
      case ENT_DFU:
        bootloader_jump();
        return false;
    }
  } else if (!record->event.pressed) {
    switch (keycode) {
      case ENT_SLP:
        sleep_mode_enter();
        return false;
    }
  }
  return true;
};
