#ifndef MACRO_PROGRAMMING_H
#define MACRO_PROGRAMMING_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/hidapi/hidapi/hidapi.h"
#include "keycodes.h"
// HID Report Struct (Report ID and reserved removed)
typedef struct __attribute__((packed)) // Make sure it is always 7 bytes
{
    uint8_t modifier;
    uint8_t keycode[6];
} hid_macro_report_t;

#define HID_REPORT_FULL(mod, k0, k1, k2, k3, k4, k5) \
    ((hid_macro_report_t){                           \
        .modifier = (mod),                           \
        .keycode = {(k0), (k1), (k2), (k3), (k4), (k5)}})

#define HID_REPORT_SIMPLE(mod, k0) \
    HID_REPORT_FULL((mod), (k0), 0, 0, 0, 0, 0)

#define HID_REPORT_EMPTY \
    HID_REPORT_FULL(0, 0, 0, 0, 0, 0, 0)

typedef struct __attribute__((packed))
{
    uint8_t report_id;
    uint8_t command;
    uint8_t data[7];
} hid_cmd_report_t; // HID command report structure

enum
{
    REPORT_ID_KEYBOARD = 1,
    REPORT_ID_CUSTOM,
};

enum
{
    CMD_CLEAR, // Clear the current working buffer (before adding new reports)
    CMD_ADD,   // Add a single hid_macro_report_t to the working buffer
    CMD_COMMIT // Save the working buffer to the specified macro slot
};

void send_clear_command(hid_device *handle);

void send_add_command(hid_device *handle, hid_macro_report_t data);

void send_commit_command(hid_device *handle, uint8_t index);

#endif