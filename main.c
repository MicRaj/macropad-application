#include "macro_programming/macro_programming.h"
#include "parse_dsl/read_dsl_file.h"
#include <unistd.h>

#define VENDOR_ID 0xcafe
#define PRODUCT_ID 0x4004

int main()
{
    hid_device *handle;
    // Initialize the hidapi library
    if (hid_init())
    {
        fprintf(stderr, "Failed to initialize hidapi\n");
        return 1;
    }

    // Open the device using the VID and PID
    handle = hid_open(VENDOR_ID, PRODUCT_ID, NULL);
    if (!handle)
    {
        fprintf(stderr, "Unable to open device\n");
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
        printf("Line %d: %s\n", i + 1, lines[i]);
        hid_macro_report_t *reports = parse_macro_dsl(lines[i], &num_reports, &macro_slot);
        for (int j = 0; j < num_reports; j++)
        {
            printf("Report %d: modifier: %02x, keycode: ", j + 1, reports[j].modifier);
            for (int k = 0; k < 6; k++)
            {
                printf("%02x ", reports[j].keycode[k]);
            }
            printf(" Macro Slot: %d ", macro_slot);
            printf("\n");
            send_add_command(handle, reports[j]);
            send_add_command(handle, HID_REPORT_EMPTY);
            // sleep(1); // Sleep for 1 second between commands
        }
        free(lines[i]); // Free each line
        send_commit_command(handle, macro_slot);
    }

    free(lines); // Free the array of pointers

    // Close the device
    hid_close(handle);
    // Finalize the hidapi library
    hid_exit();

    return 0;
}
