#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hidapi/hidapi.h>

// Replace with your macropad's actual VID and PID
#define VENDOR_ID 0xcafe
#define PRODUCT_ID 0x4004

int main()
{
    int res;
    unsigned char report[64]; // HID report buffer (1st byte is report ID)
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
    memset(report, 0x00, sizeof(report));

    // Example: Set report ID to 0, and send "macro 1" command
    report[0] = 0x02; // Report ID
    report[1] = 0x04; // Command code, e.g., macro 1

    // Send the report
    res = hid_write(handle, report, sizeof(report));
    if (res < 0)
    {
        fprintf(stderr, "Error writing to device: %ls\n", hid_error(handle));
    }
    else
    {
        printf("HID report sent successfully.\n");
    }

    // Close the device
    hid_close(handle);
    // Finalize the hidapi library
    hid_exit();

    return 0;
}
