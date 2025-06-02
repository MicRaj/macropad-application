#include "macro_programming.h"

void send_clear_command(hid_device *handle)
{

    int res;
    hid_cmd_report_t report = {0}; // HID report buffer (1st byte is report ID)

    report.report_id = REPORT_ID_CUSTOM; // Report ID
    report.command = CMD_CLEAR;          // Command code, e.g., macro 1

    // Send the report
    hid_write(handle, (uint8_t *)&report, sizeof(report));
}

void send_add_command(hid_device *handle, hid_macro_report_t data)
{
    int res;
    hid_cmd_report_t report = {0};

    report.report_id = REPORT_ID_CUSTOM; // Report ID
    report.command = CMD_ADD;            // Command code, e.g., macro 1
    report.data[0] = data.modifier;
    memcpy(&report.data[1], data.keycode, 6); // copy 6 keycodes

    // Send the report
    res = hid_write(handle, (uint8_t *)&report, sizeof(report));
    if (res < 0)
    {
        fprintf(stderr, "Error sending add command: %ls\n", hid_error(handle));
    }
}

void send_commit_command(hid_device *handle, uint8_t index)
{
    int res;
    hid_cmd_report_t report = {0};

    report.report_id = REPORT_ID_CUSTOM; // Report ID
    report.command = CMD_COMMIT;         // Command code, e.g., macro 1
    report.data[0] = index;              // Example data for macro 1

    // Send the report
    hid_write(handle, (uint8_t *)&report, sizeof(report));
}