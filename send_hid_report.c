#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hidapi/hidapi.h>

typedef unsigned char uint8_t;
typedef struct __attribute__((packed))
{
    uint8_t command; // CMD_SET_INDEX, CMD_ADD_REPORT, etc.
    uint8_t data[7]; // Command-specific payload
} hid_host_cmd_t;

typedef struct __attribute__((packed))
{
    uint8_t report_id; // Report ID
    uint8_t command;   // CMD_SET_INDEX, CMD_ADD_REPORT, etc.
    uint8_t data[7];   // Command-specific payload
} hid_report_t;

// Replace with your macropad's actual VID and PID
#define VENDOR_ID 0xcafe
#define PRODUCT_ID 0x4004

int main()
{
    int res;
    hid_report_t report = {0}; // HID report buffer (1st byte is report ID)
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

    // Clear the report buffer
    // memset(report, 0x00, sizeof(report));

    // Example: Set report ID to 0, and send "macro 1" command
    report.report_id = 0x02; // Report ID
    report.command = 0x02;   // Command code, e.g., macro 1
    report.data[0] = 0x01;   // Example data for macro 1
    // Send the report
    res = hid_write(handle, (uint8_t *)&report, sizeof(report));
    if (res < 0)
    {
        fprintf(stderr, "Error writing to device: %ls\n", hid_error(handle));
    }
    else
    {
        printf("HID report sent successfully.\n");
    }
    // res = hid_write(handle, report, sizeof(report));

    // if (res < 0)
    // {
    //     fprintf(stderr, "Error writing to device: %ls\n", hid_error(handle));
    // }
    // else
    // {
    //     printf("HID report sent successfully.\n");
    // }

    // Close the device
    hid_close(handle);
    // Finalize the hidapi library
    hid_exit();

    return 0;
}
