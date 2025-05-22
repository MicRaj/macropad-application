#include "parse_dsl.h"

// Map ASCII letter to HID keycode (only for a-z, A-Z)
uint8_t char_to_hid(char c)
{
    if ('a' <= c && c <= 'z')
        return 0x04 + (c - 'a');

    return 0;
}

// Count how many macro reports are needed in the DSL string
int count_macro_reports(const char *dsl)
{
    int count = 0;
    for (int i = 0; dsl[i]; i++)
    {
        if (isalpha(dsl[i]))
        {
            count++;
            // Skip chorded keys
            while (dsl[i + 1] == '+' && isalpha(dsl[i + 2]))
            {
                i += 2;
            }
        }
    }
    return count;
}

hid_macro_report_t *parse_macro_dsl(const char *dsl, int *out_len)
{
    int count = count_macro_reports(dsl);
    if (out_len)
        *out_len = count;
    hid_macro_report_t *reports = calloc(count, sizeof(hid_macro_report_t));
    if (!reports)
        return NULL;

    uint8_t modifier = 0;
    int i = 0, r = 0;

    while (dsl[i] && r < count)
    {
        modifier = 0;

        // Read modifiers
        while (dsl[i])
        {
            if (dsl[i] == '!')
                modifier |= MOD_SHIFT;
            else if (dsl[i] == '^')
                modifier |= MOD_CTRL;
            else if (dsl[i] == '@')
                modifier |= MOD_ALT;
            else if (dsl[i] == '#')
                modifier |= MOD_GUI;
            else
                break;
            i++;
        }

        // If next is letter, start new report
        if (isalpha(dsl[i]))
        {
            hid_macro_report_t report = {0};
            report.modifier = modifier;
            int kc = 0;

            report.keycode[kc++] = char_to_hid(dsl[i++]);

            // Handle chorded keys: +X+Y...
            while (dsl[i] == '+' && isalpha(dsl[i + 1]) && kc < 6)
            {
                i++; // skip '+'
                report.keycode[kc++] = char_to_hid(dsl[i++]);
            }

            reports[r++] = report;
        }
        else
        {
            // Skip unknown characters
            i++;
        }
    }

    return reports;
}
