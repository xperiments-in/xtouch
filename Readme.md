# xtouch developer preview

## Building

Open in VSCode and wait for the PlatformIO dependencies to be installed

Copy `lv_conf.h` to `.pio/libdeps/esp32dev/lv_conf.h`

Copy `User_Setup.h` to `.pio/libdeps/esp32dev/TFT_eSPI/User_Setup.h` overwrite if needed

Open platformio.ini and change `upload` and `monitor` port values as needed

```
upload_port = /dev/cu.wchusbserial42440
monitor_port = /dev/cu.wchusbserial42440
```
