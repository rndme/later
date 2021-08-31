# Configuring Later

There are several macro-based over-rides that can be configured from the host sketch to control the footprint and operation of later scripts.



## Macro Options
These are specified as a normal macro definition, example: `#define LATER_UART_PORT Serial1`.


* `LATER_UART_PORT` - text. Sets the output serial port, over-riding `Serial` default.
* `LATER_INSTANCES` - int. How many scripts can run at once? Default 4, reduce to save RAM.
* `LATER_PROGRAM_SIZE` - int. How many bytes of RAM to allocate for program text, default 1024.
* `LATER_LOG_SIZE` - int. How many bytes of RAM to allocate for system logging, shared by all scripts; default 4k.
* `LATER_PIXEL_NAME` - text. The Neopixel driver instance name used in `Adafruit_NeoPixel strip(...);`
* `LATER_SERVER_NAME` - text. The webserver instance name, default `server`.
* `DANOS_EDITOR_URL` - text. A script URL to link from the editor interface, used to fork.

