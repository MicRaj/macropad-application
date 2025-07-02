#ifndef CHAR_TO_HID_MAP_H
#define CHAR_TO_HID_MAP_H

#include <stdint.h>
#include "keycodes.h"

typedef struct
{
    char symbol;
    uint8_t keycode;
} char_hid_mapping_t;

// Modifier symbol to modifier bit mapping
extern const char_hid_mapping_t modifier_mappings[];
extern const int modifier_mappings_count;

// Character to HID keycode mappings
extern const char_hid_mapping_t character_mappings[];
extern const int character_mappings_count;

#endif // CHAR_TO_HID_MAP_H