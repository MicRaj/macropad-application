#include "parse_dsl.h"
#include "char_to_hid_map.h"

uint8_t lookup_modifier(char symbol)
{
    for (int i = 0; i < modifier_mappings_count; i++)
    {
        if (modifier_mappings[i].symbol == symbol)
            return modifier_mappings[i].keycode;
    }
    return 0;
}

uint8_t lookup_keycode(char symbol)
{
    for (int i = 0; i < character_mappings_count; i++)
    {
        if (character_mappings[i].symbol == symbol)
            return character_mappings[i].keycode;
    }
    return 0;
}

// Count how many macro reports are needed in the DSL string
int count_macro_reports(const char *dsl)
{
    int count = 0;
    for (int i = 0; dsl[i]; i++)
    {
        if (lookup_keycode(dsl[i]) != 0)
        {
            count++;

            // Skip chorded keys like +X+Y
            while (dsl[i + 1] == '+' && lookup_keycode(dsl[i + 2]) != 0)
            {
                i += 2;
            }
        }
    }
    return count;
}

hid_macro_report_t *parse_macro_dsl(const char *dsl, int *out_len, int *macro_slot)
{
    int count = count_macro_reports(dsl);
    if (out_len)
        *out_len = count;
    hid_macro_report_t *reports = calloc(count, sizeof(hid_macro_report_t));
    if (!reports)
        return NULL;

    uint8_t keycode = 0;
    uint8_t modifier = 0;
    int i = 0, r = 0;

    // Read {macro_slot} if present
    if (isdigit(dsl[i]) && (dsl[i + 1] == ':'))
    {
        *macro_slot = dsl[i] - '0';
        if (*macro_slot < 0 || *macro_slot > 8)
        {
            *macro_slot = 0; // Default to 0 if out of range
        }
        i += 2;
    }
    else
    {
        *macro_slot = 0; // Default to 0 if no slot specified
    }

    while (dsl[i] && r < count)
    {
        modifier = 0;

        // Read modifiers
        while (dsl[i])
        {
            uint8_t mod = lookup_modifier(dsl[i]);
            if (mod == 0)
                break;
            modifier |= mod;
            i++;
        }

        keycode = lookup_keycode(dsl[i]);
        if (keycode != 0)
        {
            hid_macro_report_t report = {0};
            report.modifier = modifier;
            int kc = 0;

            report.keycode[kc++] = keycode;
            i++;

            // Handle chorded keys
            while (dsl[i] == '+' && dsl[i + 1] && kc < 6)
            {
                keycode = lookup_keycode(dsl[i + 1]); // skip the '+' character
                if (keycode == 0)
                    break;

                report.keycode[kc++] = keycode;
                i += 2; // Move past the '+' and the next character
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
