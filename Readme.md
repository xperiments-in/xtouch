# ![image](readme-assets/xtouch.png)

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/I3I8PSAYU)

[Discord Server](https://discord.gg/RytEDEgfR3)

## NEW 5 inch Screen

![image](readme-assets/xtouch_5.png)

### xtouch-pro **NEW WEBSITE**

- [https://xtouch.pro/](https://xtouch.pro/)
- [BUY New 5inch Screen](https://s.click.aliexpress.com/e/_DBdoa6n)

## 2.8 - Table of Contents

1. [Introduction](#introduction)
   - [Required Hardware](#required-hardware)
   - [Optional Hardware](#optional-hardware)
   - [Powering the xtouch Screen](#powering-the-xtouch-screen)
2. [Features](#features)
3. [Installation](#installation)
4. [Screens](#screens)
   - [Main](#main-screen)
   - [Temperature / Fan](#temperature--fan-screen)
   - [Control](#control-screen)
   - [Filament](#filament-screen)
   - [Settings](#settings-screen)
5. [OTA Update Procedure](#ota-update-procedure)
6. [Standard Firmware Update](#standard-firmware-update)
7. [Troubleshooting](#troubleshooting)

## Introduction

The xtouch screen is a revolutionary addition to your BambuLab Printer, enhancing the user experience and providing advanced control and monitoring capabilities. This detailed README.md guide will walk you through the product's features, installation process, and the functionality of different screens.

### Required Hardware

![image](readme-assets/screen-2-8.png)
![image](readme-assets/screen-2-8-back.png)

Currently, it has only been tested on the affordable 2.8-inch ESP32-2432S028R board, which is available for purchase here:

- [ESP32-2432S028R](https://s.click.aliexpress.com/e/_DmcFFVz)
- [ESP32-2432S028R](https://s.click.aliexpress.com/e/_EwiGjNZ)

### Optional Hardware

- **[DS18B20 Temperature Sensor](docs/temperature-sensor.md)**: For printers that do not have an integrated chamber temperature sensor, you have the option to add an external DS18B20 temperature sensor. This sensor will provide accurate chamber temperature readings and enhance the functionality of your xtouch screen. Connector on the screen is 1.25 MZ JST 4P.
- **DS18B20 P1P/P1S Chamber Temp Enclosure**: Additionally, we have created a 3D model that allows you to easily integrate the DS18B20 Temperature Sensor inside your P1P/P1S printer.

You can buy the Temperature Sensor here:

- [Temp Sensor A](https://s.click.aliexpress.com/e/_ol1shM9)
- [Temp Sensor B](https://s.click.aliexpress.com/e/_EvOTULH)

You can find the 3D models

<img src="https://github.com/xperiments-in/xtouch/assets/417709/a8d14564-09e9-4d36-9ad9-10fd8f295c86" width="200">
<img src="https://github.com/xperiments-in/xtouch/assets/417709/22871bdf-ba37-44f0-a4b3-33c6352f7f86" width="300">

- [Model A](https://makerworld.com/en/models/19658)
- [Model B](https://makerworld.com/en/models/42533)

### Powering the xtouch Screen

The xtouch screen can be powered in two different ways: through a USB port or via a JST 1.25 4-pin connector. Below are the details on how to power the screen using each method:

#### Powering via USB

1. Connect a suitable USB cable to an available USB port on your computer or a USB power source.

2. At the opposite end of the USB cable, connect the USB connector to the xtouch screen.

3. Ensure that the xtouch screen is turned on and that power is being supplied properly through the USB cable. The screen should light up and display the startup information.

#### Powering via the JST 1.25 4-Pin Connector

The JST 1.25 4-pin connector is an alternative method for powering the xtouch screen. Here is a pinout diagram of this connector:

<img src="readme-assets/power-pinout.png" width="300" style="padding-bottom:16px">

To power the screen using this connector, follow these steps:

1. Locate the JST 1.25 4-pin connector on the xtouch screen.

2. Align the pins of the JST 1.25 connector with the corresponding pins on the xtouch screen.

3. Connect the JST 1.25 connector to the xtouch screen, ensuring that the pins are properly aligned.

4. Provide the proper power through the JST 1.25 connector using a compatible power source. Make sure the polarity is correct to prevent damage to the screen.

5. Turn on the xtouch screen and verify that it is receiving power properly.

The choice between USB and the JST 1.25 4-pin connector depends on your preference and resource availability. Make sure the xtouch screen receives the necessary power for optimal operation.

## Features

- **Advanced Touch Screen**: A touch screen interface for intuitive printer control.
- **Status Indicators**: Top bar indicating WiFi connectivity, camera status, timelapse recording, and AMS status.
- **Temperature Monitoring**: Real-time display of nozzle, bed, and chamber temperatures.
- **Printing Control**: Full control over your print job, including the ability to change print speed during printing.
- **Precise Control**: Control your printer's XYZ position with adjustable head movement steps (1mm and 10mm).
- **Filament Handling**: Load, unload, extrude, and retract filament (Note: Filament handling available only for printers without AMS initially).
- **Switch Between Printers**: With a single xtouch screen, you can seamlessly switch between different printers. The access code for linked printers is saved for future use, making it convenient to switch printer connections.
- **Customizable Settings**: Access a wide range of LCD and printer-related settings.
- **OTA Updates**: Enable over-the-air updates for firmware enhancements.

## Installation

# xtouch Screen Setup and Installation Guide

This guide will walk you through the steps required to initialize and configure your xtouch screen for use with your 3D printer.

---

## Required Tools and Preparation

Before beginning, ensure you have the following:

1. **Computer with Google Chrome Installed** (only for downloading the config file)

2. **USB Cable**

3. **Formatted FAT32 SD Card (≤ 32GB Recommended)**

4. **xtouch.json Configuration File**

   - Visit: **[https://xperiments.in/xtouch-bin/localOnly.html](https://xperiments.in/xtouch-bin/localOnly.html)**
   - Fill in the required information (WiFi SSID, Password, and your BambuLab account details).
   - Download the `xtouch.json` file and place it on the **root of the SD card**.

## No Chrome extensions, token logins, or cloud provisioning are needed anymore!

## Installation Process

### Step 1: Open the Online Installer in Google Chrome

1. Open **Google Chrome** on your computer.
   > **Note:** Other browsers are not supported for this process.
2. Navigate to the installer page by entering the following URL:  
   **[https://xperiments.in/xtouch-bin](https://xperiments.in/xtouch-bin)**

### Step 2: Use the Online Installer

1. On the web page, click the **"Connect"** button to establish a connection between your computer and the xtouch screen.
2. From the list of available ports displayed, select the serial port assigned to your xtouch screen.
3. Once connected, click the **"Install xtouch"** button to start the installation process.

---

## Screens

### Main Screen

- **Top Bar**: Displays WiFi, camera, timelapse, and AMS status.
- **Light Control**: Toggle the printer's light on/off.
- **Temperature Indicators**: Real-time nozzle, bed, and chamber temperature indicators.
- **Status Area**: The Status Area on the touch screen serves two main purposes:

  - **Idle State**: When the printer is not in use, it displays a "Ready" message with the main logo.
  - **Printing State**: During printing, it provides pause/stop buttons, a progress bar, layer info, and a print speed selector for real-time control and monitoring.

### Temperature / Fan Screen

On this screen, you'll find four buttons, each representing the temperature or fan speed of a specific sensor. Tapping any of these buttons will direct you to a numeric keyboard screen where you can easily adjust the corresponding temperature or speed value. After making your changes, you can return to the initial screen with a simple tap.

### Control Screen

This screen provides essential controls for managing your printer:

- **Homing**: Initiates printer homing procedure.
- **XYZ Position Control**: Enables precise control of the print head's XYZ position.
- **Step Size**: Allows you to toggle between 1mm and 10mm head movement increments for finer or quicker adjustments.

### Filament Screen

- **Filament Handling**: Load, unload, extrude, and retract filament (Note: Filament handling available only for printers without AMS initially).

### Settings Screen

#### LCD

- **Change Backlight**: In the "Change Backlight" settings, you can adjust the screen backlight to your preferred brightness level.
- **Set Screen Sleep Time**: Set Screen Sleep Time: Adjusts the screen's inactivity timer. When the screen is idle for the specified time (in minutes), it enters sleep mode to save power. Set to 0 to keep the screen always active. During an active print job, the screen stays on for real-time monitoring.
- **Invert Screen Colors**: Toggle to reverse screen colors. Useful for addressing compatibility issues with certain devices.
- **Flip Screen**: Flip the screen orientation.

#### XTOUCH

- **AUX FAN**: Enable the auxiliary fan for printers that initially lack it.
- **CHAMBER Temp**: Enable chamber temperature monitoring for printers without it.
- **OTA Update**: Enable OTA upgrades for firmware updates.

## OTA Update Procedure

The xtouch screen supports Over-The-Air (OTA) firmware updates, making it easy to keep your device up to date with the latest features and improvements. To enable and utilize OTA updates, follow these steps:

1. **Access the Settings Screen**:

   - Navigate to the Settings Screen on your xtouch screen.

2. **Enable OTA Updates**:

   - In the Settings Screen, locate the OTA Update section. You will find an option to enable OTA updates. Toggle this option to "ON" to enable automatic firmware update checks.

3. **Automatic Update Check on Boot**:

   - With OTA updates enabled, your touch screen will automatically check for firmware updates every time it boots up.

4. **Download and Apply Updates**:

   - If an update is available, the touch screen will automatically download the latest firmware and apply the upgrade. This process is seamless and requires no manual intervention.

By enabling OTA updates in the Settings Screen, you ensure that your xtouch screen stays current with the latest software enhancements and bug fixes without the need for manual updates. This convenient feature ensures that you always have access to the best performance and functionality that the device can offer.

## Standard Firmware Update

If you prefer to manually update the firmware of your xtouch screen or if OTA updates are not enabled, you can follow this procedure:

1. **Download the Update Firmware File**:

   - Visit the official xtouch sebsite or the designated firmware update source to download the latest firmware update file. Ensure that you download this file with the [firmware.bin](https://github.com/xperiments/xtouch-bin/raw/refs/heads/main/fw/firmware.bin) name.

2. **Copy the Firmware File to the Root of the SD Card**:

   - Insert the SD card into your computer's card reader.
   - Copy the downloaded firmware update file [firmware.bin](https://github.com/xperiments/xtouch-bin/raw/refs/heads/main/fw/firmware.bin) to the root directory of the SD card. Do not place it in any subdirectories.

3. **Reboot the xtouch screen**:

   - Insert the SD card containing the firmware update file into the xtouch screen if it's not already inserted.

   - Reboot the touch screen. You can do this by turning it off and then turning it back on.

4. **Apply the Firmware Update**:

   - Once the touch screen has booted up, it will detect the presence of the firmware update file on the SD card.

   - The touch screen will apply the firmware update.

   - The update process may take a few minutes to complete. Do not turn off the touch screen or remove the SD card during this time.

5. **Completion and Verification**:

   - After the firmware update is successfully applied, the touch screen will notify you that the update is complete.

   - You can verify the firmware version in the touch screen's settings section to ensure that it matches the latest version.

By following these steps, you can manually update the firmware of your xtouch screen to the latest version, ensuring that you have access to all the latest features and improvements.

## Troubleshooting

If you encounter issues during the installation or operation of your BambuLab Printers Touch Screen, you can refer to the following troubleshooting steps to resolve common problems:

1. **Use a Data Cable**:

   - Ensure that you are using a data cable (not just a charging cable) to connect your touch screen to your computer during the installation process. A data cable is required for proper communication.

2. **SD Card Compatibility**:

   - Keep in mind that SD cards from different manufacturers may behave differently. While many SD cards work seamlessly, some may not be fully compatible with the touch screen. If you experience issues with an SD card, consider trying a different brand or model to see if it resolves the problem.

3. **Recalibrating the Screen**:

   If you encounter touch screen calibration issues or misalignment, you can recalibrate the screen by removing the `touch.json` file located in the `xtouch` directory on the SD card. Follow these steps:

   - Power off the xtouch screen.
   - Remove the SD card from the touch screen.
   - Insert the SD card into your computer.
   - Navigate to the `xtouch` directory on the SD card.
   - Delete the `touch.json` file.
   - Safely eject the SD card from your computer.
   - Reinsert the SD card into the touch screen.
   - Power on the touch screen.

   The touch screen will automatically perform a recalibration process upon startup.

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/I3I8PSAYU)
