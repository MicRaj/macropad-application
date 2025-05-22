#ifndef READ_DSL_FILE_H
#define READ_DSL_FILE_H

#include <stdio.h>
#include <string.h>
#include "parse_dsl.h"
#include "../macro_programming/macro_programming.h"

char **read_file(const char *filename, int *line_count_out);

#endif // READ_DSL_FILE_H