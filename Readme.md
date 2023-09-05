# xTouch Developer Preview

Welcome to the xTouch developer preview! This README provides instructions for building and setting up the xTouch firmware on your ESP32 development board.

## Requeriments

- VSCode
- PlatformIO

## Building Instructions

To build the xTouch firmware, follow these steps:

1. **Open in Visual Studio Code (VSCode)**: Open the project in Visual Studio Code and wait for PlatformIO dependencies to be installed automatically.

2. **Copy `lv_conf.h`**: Copy the `lv_conf.h` file to the `.pio/libdeps/esp32dev/` directory. This file is essential for configuring the LVGL library. If a `lv_conf.h` file already exists in that directory, you may need to overwrite it.

3. **Copy `User_Setup.h`**: Copy the `User_Setup.h` file to the `.pio/libdeps/esp32dev/TFT_eSPI/` directory. Overwrite the existing file if necessary. This step is crucial for configuring the TFT_eSPI library.

4. **Open `platformio.ini`**: Open the `platformio.ini` file in your project and make the following adjustments as needed:

```
upload_port = /dev/cu.wchusbserial42440
monitor_port = /dev/cu.wchusbserial42440
```

Replace `/dev/cu.wchusbserial42440` with the appropriate upload and monitor port values for your ESP32 development board.

5. **Flash the Firmware**: Use PlatformIO within VSCode to flash the firmware to your ESP32 development board.

6. **Create `xtouch.json` Configuration File**: Create a file named `xtouch.json` in the root directory of your SD card. This file will contain the Wi-Fi credentials needed for the xTouch application to connect to your network. Replace `"your_ssid_name"` and `"your_ssid_password"` with your Wi-Fi network's SSID and password, respectively. The file's contents should look like this:

```json
{
  "ssid": "your_ssid_name",
  "pwd": "your_ssid_password"
}
```

Insert the SD into the screen and reboot
