#ifndef PARSE_DSL_H
#define PARSE_DSL_H
#include "../macro_programming/macro_programming.h"
#include "stdio.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Modifier bitmask map
#define MOD_CTRL 0x01
#define MOD_SHIFT 0x02
#define MOD_ALT 0x04
#define MOD_GUI 0x08

hid_macro_report_t *parse_macro_dsl(const char *dsl, int *out_len);
#endif