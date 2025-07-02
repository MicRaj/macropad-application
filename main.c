#include "macro_programming/macro_programming.h"
#include "parse_dsl/read_dsl_file.h"
#include <unistd.h>

#define VENDOR_ID 0xcafe
#define PRODUCT_ID 0x400c
#define PRG_INTF 1

int main()
{
    struct hid_device_info *devs, *cur_dev;
    hid_device *handle = NULL;
    if (hid_init())
    {
        fprintf(stderr, "Failed to initialize hidapi\n");
        return 1;
    }
    const char *version = hid_version_str();
    printf("HIDAPI version: %s\n", version);

    devs = hid_enumerate(VENDOR_ID, PRODUCT_ID);
    cur_dev = devs;

    while (cur_dev)
    {
        printf("Found: %s (Interface: %d, Usage Page: 0x%04hx, Usage: 0x%04hx)\n",
               cur_dev->path, cur_dev->interface_number,
               cur_dev->usage_page, cur_dev->usage);

        if (cur_dev->interface_number == PRG_INTF && handle == NULL)
        {
            handle = hid_open_path(cur_dev->path);
        }
        cur_dev = cur_dev->next;
    }

    hid_free_enumeration(devs);

    if (!handle)
    {
        fprintf(stderr, "Unable to open interface\n");
        return 1;
    }

    // send_clear_command(handle);
    // send_add_command(handle, HID_REPORT_SIMPLE(MOD_LEFT_SHIFT, KEY_H));
    // send_add_command(handle, HID_REPORT_SIMPLE(0, KEY_I));
    // send_add_command(handle, HID_REPORT_SIMPLE(MOD_LEFT_SHIFT, KEY_1));
    // send_add_command(handle, HID_REPORT_EMPTY);
    // send_commit_command(handle, 2);

    // send_clear_command(handle);
    int macro_slot;
    int num_lines;
    int num_reports;
    char **lines = read_file("program.txt", &num_lines);

    if (lines == NULL)
        return 1;

    for (int i = 0; i < num_lines; i++)
    {
        send_clear_command(handle);
        printf("Line %d: %s\r\n", i + 1, lines[i]);
        hid_macro_report_t *reports = parse_macro_dsl(lines[i], &num_reports, &macro_slot);
        for (int j = 0; j < num_reports; j++)
        {
            // Debug prints
            printf("Report %d: modifier: %02x, keycode: ", j + 1, reports[j].modifier);
            for (int k = 0; k < 6; k++)
            {
                printf("%02x ", reports[j].keycode[k]);
            }
            printf(" Macro Slot: %d \r\n", macro_slot);

            send_add_command(handle, reports[j]);
            send_add_command(handle, HID_REPORT_EMPTY); // Send empty report after each macro report, can be optimised
        }
        free(lines[i]); // Free each line after processing
        // send_add_command(handle, HID_REPORT_EMPTY); Might be need in the future, empty report is sent by the firmware when a macro is played.
        send_commit_command(handle, macro_slot);
    }
    send_flash_command(handle); // Flash the current macro_store to flash

    free(lines); // Free the array of pointers

    // Close the device
    hid_close(handle);
    hid_exit();

    return 0;
}
