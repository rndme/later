

## Project History
Later has seen a long evolution over several years as needs have grown alongside ambition. 
While the same basic goal of controlling ESPs from http requests is still present, 
it's moved from a mere API to a full-featured language of it's own right.

### Generation 0
A simple HTTP API to set GPIO pins on and off. 
This served as a basis for a home automation setup and worked fine for lighting, but not much else. 
When a need was discovered to rapidly blink a light when the doorbell rang, 
the limit of flying an ESP completely by wire presented itself with occasional network lags, resulting in jerky animations, which cannot be abided.

### Generation 1
Still all HTTP, but with many more commands and several crucial additions that let one request do a lot more than toggle pins.
All GET params were cycled in a for loop, allowing repeated params. 
A delay command enabled sending a blinking animation in one request instead of using many explicit on/off requests, 
for example `/set?2=1&sleep=200&2=0&sleep=200&2=1&sleep=200&2=0` to double pulse a notification light. 
Each command was also logged to the web response, enabling validation and HTTP reporting of ESP-known info like the temp from a DHT-11 sensor.

### Generation 2 - the first rewrite
To avoid long URLs for complex animations, a file-based abstraction of the HTTP GET interface was created. 
Each command resided on a single line and was written `command=argument`, same as a URL.
Primitive flow commands like goto/exit/repeat/ were introduced and the notion of an "execution cursor" was integrated. 
That allowed looping, early termination and several other DRY tools. The blinking notification example could now be coded as `?2=-1&sleep=200&repeat=4`.
This generation survived for years and was slowly expanded with IF/ELSE statements, FOR loops, variables, an async sleep (`freeze`), data logging, autoexec.bat startup scripts, cron-job scheduling of scripts, and more.

### Generation 3 - the current rewrite
Whilst having evolved into a somewhat of a language, gen2 was plagued by Arduino's String class handling all the program code. 
Long-running scripts would inevitable run out of heap and crash. Holiday neopixel animations wanted multi-tasking along with more speed and stability. 

#### Key improvements in gen 3

* no String class and no memory leaks - tasks can execute tens of millions of times, maybe more.
* multiple script execution - allows several tasks to run concurrently, reducing hardware needs and simplifying custom deployment.
* parse stage - instead of just hopping line to line, blocks are pre-scanned and mapped to exit points, allowing instant jumping instead of runtime searching.
* single-byte command symbols - allow fast switch()ing instead of slow and tedious string-matching of keys to human command names.
* script maturity - switch(), nested conditionals/loops, sub routines, start/finish lifetime management, 

