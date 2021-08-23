
# Templates
These insert useful common and system-provided numbers into a program. They are delimited by `{` and `}`, with a key/path name in the middle.


## Custom templates
Use `Later.addTemplate()` to define new substituios for scripts to use.
Make sure to wrap in `{braces}`, then using a lambda or macro to define the value of the template:

```c++
Later.addTemplate("{version}",  []()->unsigned long{return 202101;});// using lambda
Later.addTemplate("{zip}",  TEMPLATE(90210)); // using TEMPLATE MACRO
```
  

## Built-in templates

### Common
* **{adc}**   : analogRead A0
* **{i}**    : cursor of for-loop
* **{line}**    : current parsed line number
* **{gpioN}**   : digitalRead of pin #N, ex: {gpio5}


### Network
* **{ip}** : last octet of IP address
* **{net}** : network IP mask (usually a 0 or 1)
* **{chan}** :  WiFi Channel  
* **{rssi}** : WiFi Signal Strength     


### System
* **{ram}** : free memory in heap
* **{frag}** :  Heap Fragmentation percentage   
* **{flash}** : Flash Storage Size  
* **{leds}** : # of RGB LEDs configured
* **{runs}** : # of times same program has run
* **{cpu}** :  CPU Frequency   
* **{mac}** :  MCU unique identifier - serial number
* **__FILE** : a special format, the script's file name, as TEXT
 


### Subroutines
* **{arity}**    : the count of arguments actually passed to a sub-routine
* **{arg0}**    : from sub-routine, first argument passed
* **{arg1}**    : from sub-routine, second argument passed
* **{arg2}**    : from sub-routine, third argument passed
* **{arg3}**    : from sub-routine, fourth argument passed
* **{E.pin}**    : from event sub-routine, pin that changed state
* **{E.value}**    : from event sub-routine, new pin value
* **{E.time}**    : from event sub-routine, ms timer when pin changed state
* **{E.ms}**    : from event sub-routine, duration since last change in ms



### Random
* **{rnd}**  : a random number between 0 and 1024
* **{rnd2}** : a random number between 0 and 1
* **{rnd8}** : a random number between 0 and 255
* **{rnd16}** : a random number between 0 and 65536
* **{rnd_digit}** : a random number between 0 and 9
* **{rnd_reg}**: a random number +/- 2^31


### Time and Timers and Counters
* **{timer}**: system uptime in ms
* **{micros}**: system uptime in us
* **{micros64}** : Truncated 64 bit system timestamp     
* **{cycle}** : Current CPU Cycle   
* **{runtime}**: file execution runtime in ms
* **{time.day}**    : time - day of week 0 (sun) - 6 (sat)
* **{time.hour}**   : time - hour of day
* **{time.minute}** : time - min of hour
* **{time.second}** : time - second of min
* **{time.epoc}**   : time - epoc unix timestamp















