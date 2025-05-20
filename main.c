#include "macro_programming/macro_programming.h"

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

    send_clear_command(handle);
    send_add_command(handle, HID_REPORT_SIMPLE(MOD_LEFT_SHIFT, KEY_H));
    send_add_command(handle, HID_REPORT_SIMPLE(MOD_LEFT_SHIFT, KEY_I));
    send_add_command(handle, HID_REPORT_SIMPLE(MOD_LEFT_SHIFT, KEY_1));
    send_add_command(handle, HID_REPORT_EMPTY);
    send_commit_command(handle, 1);

    // Close the device
    hid_close(handle);
    // Finalize the hidapi library
    hid_exit();

    return 0;
}
