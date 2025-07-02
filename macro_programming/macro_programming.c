#include "macro_programming.h"

void send_clear_command(hid_device *handle)
{
    int res;
    hid_cmd_report_t report = {0};

    report.report_id = REPORT_ID_CUSTOM;
    report.command = CMD_CLEAR;

    hid_write(handle, (uint8_t *)&report, sizeof(report));
}

void send_add_command(hid_device *handle, hid_macro_report_t data)
{
    int res;
    uint8_t buffer[ENDPOINT_SIZE] = {0}; // 1 report_id + 1 command + 7 data bytes (needs +1 to work)

    buffer[0] = REPORT_ID_CUSTOM;
    buffer[1] = CMD_ADD;
    buffer[2] = data.modifier;
    memcpy(&buffer[3], data.keycode, 6);

    res = hid_write(handle, buffer, sizeof(buffer));
    if (res < 0)
    {
        fprintf(stderr, "Error sending add command: %ls\n", hid_error(handle));
    }
}

void send_commit_command(hid_device *handle, uint8_t index)
{
    int res;
    hid_cmd_report_t report = {0};

    report.report_id = REPORT_ID_CUSTOM;
    report.command = CMD_COMMIT;
    report.data[0] = index;

    hid_write(handle, (uint8_t *)&report, sizeof(report));
}

void send_flash_command(hid_device *handle)
{
    int res;
    hid_cmd_report_t report = {0};

    report.report_id = REPORT_ID_CUSTOM;
    report.command = CMD_FLASH;

    hid_write(handle, (uint8_t *)&report, sizeof(report));
}
