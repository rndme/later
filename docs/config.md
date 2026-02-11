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
* `LATER_EDITOR_URL` - text. A script URL to link from the editor interface, used to fork.

## Default-Disabled features
You can activate additional functionality by using macro define tag, example: `#define LATER_CRON 1`


| Feature | Storage | RAM Use | Description |
|---|---|---|---|
| LATER_UART_PORT_DISABLE | 0 | 0 | Disables UART port, allowing it to be used for GPIO |
| LATER_ARRAY | NA | 256b | Provides an [array tool](expansion.md#arrays) to help manage larger amounts of data |
| LATER_PREFS | 5kb | 200b | A fully-managed configuration tool with gui user-facing config, file-based persistence, etc |
| SAMPLER_ENABLED | 1kb | 984b | Data collection tool with stats like avg, max, maxAtTime, etc |
| HIGH_RES_TIMING | 1.2k | 300b | Captures internal later perf data, turns on by specifiying println destination |
| LATER_LINE_PROFILING | 0.2k | 1kb*  | Measure perf of each line. Uses 1kb per script instance slot |
| LATER_CSV | 2.4k | 396b | A CSV tool. See getCSV() code. Provides powerful `csv` command/block. |
| LATER_CRON | .9k | 256b | Enables `/cron.tab` batch jobs, one per line as `mins /filename.bat` |







