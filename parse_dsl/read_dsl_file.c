#include "read_dsl_file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10
#define MAX_LINE_LENGTH 512

char **read_file(const char *filename, int *line_count_out)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("Error opening file!");
        return NULL;
    }

    char **lines = malloc(sizeof(char *) * MAX_LINES);
    if (lines == NULL)
    {
        perror("Memory allocation failed");
        fclose(fp);
        return NULL;
    }

    int count = 0;
    char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, sizeof(buffer), fp) && count < MAX_LINES)
    {
        buffer[strcspn(buffer, "\n")] = '\0'; // Strip newline

        // Allocate memory for the line
        lines[count] = malloc(strlen(buffer) + 1);
        if (lines[count] == NULL)
        {
            perror("Line allocation failed");
            break;
        }

        strcpy(lines[count], buffer);
        count++;
    }

    fclose(fp);

    if (line_count_out)
    {
        *line_count_out = count;
    }

    return lines;
}