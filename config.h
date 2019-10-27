#pragma once

// BLE settings
#undef BLE_NUS_MIN_INTERVAL
#undef BLE_NUS_MAX_INTERVAL
#undef BLE_HID_MAX_INTERVAL
#undef BLE_HID_SLAVE_LATENCY
#define BLE_NUS_MIN_INTERVAL  30
#define BLE_NUS_MAX_INTERVAL  60
#define BLE_HID_MAX_INTERVAL  80
#define BLE_HID_SLAVE_LATENCY 10

// Copy from ErgoDox EZ
#define MOUSEKEY_INTERVAL    20
#define MOUSEKEY_DELAY       0
#define MOUSEKEY_TIME_TO_MAX 5
#define MOUSEKEY_MAX_SPEED   4
#define MOUSEKEY_WHEEL_DELAY 0

#define TAPPING_TERM    200
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)
