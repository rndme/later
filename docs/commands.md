# Commands

Every line of code has a command. 
As an interpreted language, even loops, conditionals, etc are commands.
The list below details the built-in commands, and you can create custom script commands inside your sketch using `Later.addCommand`.


* [Basic](#basic)  [ pinMode, sleep, freeze, set, analogWrite, type ]
* [IO](#io)  [ delete, fetch, println, print, resume, suspend, type ]
* [Neopixel](#neopixel)  [ solid, pixel, grad, render, rotate ]
* [Debug](#debug)  [ log, clear, assert, timer ]
* [Flow](#flow)  [ if, iif, else, fi, switch, case, default, end switch, sub, gosub, on, interval, call, return, exit, start, finish ]
* [Loops](#loops)  [ for, next, continue, do, loop, break ]
* [Variables](#variables)  [ var, static, global, store ]
* [System](#system)  [ #include=, #define=KEY literal value(s), run, option, cgi, noop, unload ]


## Basic

**pinMode**   [_int_ **pin**, _str_ **mode**] <br>
Sets the mode on a GPIO pin as [OUTPUT, INPUT, INPUT_PULLUP] <br>
```js
pinMode 2, INPUT_PULLUP
pinMode 5, OUTPUT
```


**sleep**   [_int_ **ms**]    [ex1](#) <br>
Does nothing for n ms. Blocking- other scripts and wifi won't be handled for the duration. For a non-blocking version, use `freeze` instead.<br>
```js
set 2, 1 // light on
sleep 500 // wait half a second
set 2, 0 // light off
```


**freeze**   [_int_ **ms**]    [ex1](#) <br>
Does nothing for n ms. Non-blocking- temporarily passes control back to system without ending program.<br>
```js
set 2, 1 // light on
sleep 500 // wait half a second
set 2, 0 // light off
```
**set**   [_int_ **pin**, _int_ **value**]    [ex1](#) <br>
digitalWrite. aka gpio, write, digitalWrite, and set<br>
```js
set 2, 1 // turn lamp relay on
```


**analogWrite**   [_int_ **pin**, _int_ **duty**]    [ex1](#) <br>
analogWrite. Writes a PWM value to a GPIO pin, from 0 - 1023 <br>
```js
analogWrite 2, 512 // turn lamp on half brightness
```



## IO

**delete**   [_text_ **fileName**]    [ex1](#) <br>
Removes a stored file. Cannot be recovered, except maybe by 3-letter agencies.<br>
```js
delete /file.ext
```

**fetch**   [_text_ **url**]    [ex1](examples#test) <br>
GET a URL. Used to phone home and grab external data for scripts. Accepts variable and template placeholders in url. For more info about handling and processing a response, see RESPONSE section. alias: ping<br>
```js
// basic phone-home to node-red:
fetch http://192.168.0.1:1880/temps/?place=basement&temp=$temp

// basic scrape:
fetch http://192.168.0.1:1880/doors/
$status = &RESPONSE->json("front") // grab front door state from node-red's api
digitalWrite 2, $status // update indicator LED
```


**println**   [_text_ **content**]    [ex1](#) <br>
Prints composited line to uart (Serial) or response (http) and inserts a new line after<br>
```js
option persist
println you have seen this message {runs} times
```


**print**   [_text_ **content**]    [ex1](#) <br>
Prints composited line (w/o break) to uart (Serial) or response (http)<br>
```js
option persist
print {rnd}, 
```


**resume**   [_string_ **filename** ]    [ex1](#) <br>
Loads and restores persited state of suspended script by name. This loads all the state and variables from the flash and then executes the named script. If state cannot be loaded, this performs the same as `run`. If there are no free program slots at time of calling, it will automatically queue for 100ms and try again until successful. <br>
```js
resume /other.bat // load and rehydrate other script, continue running after
```

**suspend**   [_string_ **filename** or int_ **ms**]    [ex1](#) <br>
Suspends and unloads a script by name, or if given a number, suspends the current script and sets it to resume in that milliseconds. This saves all the state and variables to the flash and then frees up a program slot. <br>
```js
suspend 30000 // persists state, exits, unloads, and resumes in 30 seconds
suspend /other.bat // persist and unload other script, continue running after
```

**type**   [_string_ **filename** or **%RAM%**]    [ex1](#) <br>
Prints a file to stdOut (http, socket, or serial). Prints the contents of a file by name.
```js
type /testinlog.txt
// or
type %RAM%
```


## Neopixel


**solid**   [_color_ **color**]    [ex1](#) <br>
Sets neopixel RGB leds to one solid color. See Colors section for more info<br>
```js
solid $bg  // set to a user-defined color variable
solid #000 // blank via short hex
solid #123456 // set it to some 6 digit hex
solid RGB(64, 0, 64) // dark magenta
solid HSV(64512, 255, 128) // bright red
```


**pixel**   [_int_ **index**, [_int_ **span**]  `->` _color_ **color**]  [ex1](#) <br>
Set neopixel rgb led(s) to a specified color. See Colors section for more info<br>
```js
pixel 0,{leds} ->RGB(0,0,0) // silently blank out full strip
pixel 0, 5 ->RGB(32,0,0) // set first 5 pixels to dark red
pixel 6 ->#020 // pixel number 6 dark green
render // update LEDs, otherwise nothing happens
```


**grad**   [_int_ **index**, _int_ **span**  `->` _color_ **from**,  _color_ **to** ]  [ex1](#) <br>
Set neopixel rgb leds to a range of gradient colors between 2 endpoints.<br>
```js
grad 0,{leds} ->RGB(255,0,0), RGB(0,0,255) // whole strip red to blue
render // updates LEDs, otherwise nothing happens
```



**render**   [void]    [ex1](#) <br>
Renders the current neopixel state to the actual LEDs. 
Used with `pixel` and `grad`, otherwise changes don't "show up". 
A seperate render allows many single pixels to be updated per frame instead of per pixel.
<br>
```js
pixel 0,5 ->RGB(0,64,0) // set first 5 pixels to 1/4th bright green
render // updates LEDs, otherwise nothing happens
```


**rotate**   [_int_ **slots**]    [ex1](#) <br>
Scoot all pixel color values to the right by the specified number of pixels<br>
```js
grad 0,{leds} ->RGB(255,0,0), RGB(0,0,255) // whole strip red to blue
for 0; {leds}; 1 
  rotate 1 // animate the gradient, sliding and wrapping
  freeze 100
next
```





## Debug

**log**   [_text_ **content**]    [ex1](#) <br>
Logs composited line to debug RAM buffer. (read via /log/ and /test/ endpoints).<br>
```js
log ram free: {ram}\tdata: $sum
```


**clear**   [void]    [ex1](#) <br>
Clears all logged data from the RAM debug buffer.<br>
```js
clear 
log this is the only line in the log right now
```

**assert**   [( _int_ **term1** _compare operator_ _int_ **term2** )   `->` _text_ **description**]   [ex1](#) <br>
Compares two values and prints the result as a test summary, perfect for unit testing.<br>
```js
$x = (2 + 5)
assert  ($x = 7) -> var assign expression
// yields: OK   -  var assign expression :: -

assert  ({timer} > 0) -> timer template working
// yields: OK   -  timer template working :: -

assert  ({timer} = 0) -> timer template default value
// yields: FAIL   -  timer template default value :: ({timer} = 0) -
```




**timer**   [_text_ **label**]    [ex1](#) <br>
Used for high-resolution performance profiling. 
The first call starts the timer. 
Subsequent calls calculate the elapsed time and print the formatted result with the label.
The time taken to run the `timer` command and actually print the results is factored out, making it simple to use.  <br>
```js
option persist
// prints:"T+5571: Summed 100: 4950" (Runtime in uS may vary)
timer start
$x = 0
for 0; 100; 1
 $x = +{i}
next
timer Summed 100: $x
```





## Flow

**if**   [_int_ **term1** _compare operator_  _int_ **term2**]    [ex1](#) <br>
Compare 2+ terms; `if 5 > $y > 1`. w/ only 1 term, uses `>0` as compare and term2. 
Begins a block of guarded code. ! prefix inverts whole condition result at end. See %conditionals section for more info.<br>
```js
option persist
if {runs} < 1
  println first time running!
fi

if !{runs}
  println first time running!
fi

if {runs}
  println Not the first time running...
end if
```


**iif**   [_int_ **term1** _compare operator_  _int_ **term2** [`:` _text_ **code**]]    [ex1](#) <br>
Inline if doesn't begin a block; no `else` or `fi/end if` line is supported. Iif only guards the next line. If there's a colon (`:`) with code to the right of it after the conditional expression, that code is taken as the next line, allowing compact single-outcome toggles.<br>
```js
iif {runs}
  println Program has run {runs} times.

iif !{runs} : println First time running!
```


**else**   [void]    [ex1](#) <br>
Inverts conditional outcome guarding for the remainder of if block. <br>
```js
if {runs} < 1
  println first time running!
else
  println Already ran {runs} times.
fi
```


**fi**   [void]    [ex1](#) <br>
Ends guarded code block started by `if` command or extended by `else` command. Alias: "end if"<br>



**switch**   [_int_ **toMatch**]    [ex1](#) <br>
A one-of-the-above-match conditional block. - Used with `case`, `default`, and `end switch` commands. Compares an unknown value to a list of possible matches. Once a match is found, the code below that match is executed until another `case` or `default` is found or the end of the block is reached. Unlike C++, `case`s don't "fall through", so there's no need for an explicit `break` after every `case`. br>
```js
$coin1 = {rnd2}
$coin2 = {rnd2}
$outcome= ($coin1 + $coin2)
switch $outcome
 case 1
  println One head, one tail.
 case 2
  println Two heads.
 default
  println Two Tails.
end switch
```

**case**   [_int_ **offer**]    [ex1](#) <br>
Inside of switch block, offers a match for the switched value. <br>

**default**   [void]    [ex1](#) <br>
Inside of switch block, offers a default code section to run is no match is found for the switched value. <br>

**end switch**   [void]    [ex1](#) <br>
Ends the switch block; surprising, huh?<br>



**sub**   [_text_ **name**] `{`   [ex1](#) <br>
Begins subroutine definition. Called via `gosub`, `call`, `on`, and `interval`. 
Subroutines hold code meant to be called several times, reducing repetition. 
Numerical values can be returned from a subroutine and assigned to a variable using `return` and `call`. <br>
```js
sub 
```


**gosub**   [_text_ **name** [[[_int_ **arg0**], _int_ **arg1**], _int_ **arg2**], _int_ **arg3** ]  [ex1](#) <br>
Jumps to a subroutine, executes code in that sub, continues flow on the following line.
Optional arguments can be passed after the sub name, up to 4, separated by commas.
These data are available inside the sub as `{arg0} .. {arg3}` template placeholders.
<br>
```js
gosub 
```


**on**   [_int_ **pin**, _text_ **sub** [, _text_ **type**]]    [ex1](#) <br>
monitors a GPIO pin for state changes, and fires a sub routine on changes.
Type is `RISING`, `FALLING`, or `CHANGE`, corresponding to the hi/lo edge causing the change. 
Default mode is `change`, which fires whenever hi goes low or low goes hi.
 See %Events section for details.<br>
```js
option interval 50
sub doButton {
  println Button {E.pin} was pressed for {E.ms}ms.
}
start
on 2, doButton, FALLING
```


**interval**   [_int_ **ms**, _text_ **subName**]    [ex1](#) <br>
Runs a subroutine every n ms. The interval line itself checks for period experation, it's not a background process, so make sure a programs `option interval` is _less_ than the interval you want to target. This is handy where you want to update an animation 30 times a second, but want to change a base color 4 times a second; do that part in an interval-fired subroutine.<br>
```js
interval 500, colorChange
```


**call**   [_text_ **var** `=` _text_ **subroutine** [_int_ **argument**...] ]    [ex1](#) <br>
Assigns a subroutine return value to a variable.
It can only be used for variable assignment, not arbitrarily like a Function call can. <br>

```js
// prints: 9
sub sum
 return ({arg0} + {arg1})
}
call $x = sum 4, 5
println $x
```


**return**   [_int_ **pin**, _text_ **mode**]    [ex1](#) <br>
Returns a variable assignment value to a `call` commands from a subroutine and ends subroutine execution.
Can also be used to end subroutine execution early without assigning the return.<br>
```js
// prints: 29
sub sum
 return ({arg0} + {arg1}) // do math, return result
}
call $x = sum 14, 15
println $x
```


**exit**   [void]    [ex1](#) <br>
Ends program execution early. Does not unload or cancel `option interval`. <br>
```js
if {runtime} > 5000
  exit // ends execution if running longer than 5 seconds
fi
```


**start**   [void]    [ex1](#) <br>
Dynamically set top of program. Somewhat like `static` for vars, but for any code. 
Code before this line will only run once, upon first run. 
Used to setup a program's parameters, hardware, etc.<br>
```js
option interval=500
pinMode 2, OUTPUT
digitalWrite 2, 0 // turn built-in LED on
solid #000  // blank all neopixels
start // end config begin "main" program:
println I am a program, run {runs} times. Run program run.
```


**finish**   [void]    [ex1](#) <br>
Defines a program's exit point. Most useful with `interval` and `persist` with `option` command. Code after this line will only run when the script is unloaded. Good for re-setting flags/counts and turning off LED strips; Code and environment cleanup.<br>
```js
option interval=20
solid HSV({runs}, 255, 64) // show a different hue each time
finish
solid #000 // turn all neopixels off
```


## Loops 


**for**   [_int_ **start**, _int_ **stop**, _int_ **step** ]    [ex1](#) <br>
A semi-traditional for loop. Loops through the block starting a counter (`{i}`) at **start** then
(inc/dec)rementing {i} by **step** until reaching **start**<br>
```js
// prints: 0,1,2,3,4,
for 0; 5; 1
 print {i},
next
```


**next**   [void]    [ex1](#) <br>
Closes for loop block. Returns flow to top of loop. <br>
```js
// prints: 0,1,2,3,4,99
for 0; 5; 1
 print {i},
next
print 99
```


**continue**   [_int_ **pin**, _text_ **mode**]    [ex1](#) <br>
Returns flow to top of for loop instead of waiting for a `next`. Still increments the counter. 
Used to skip over remaining for loop code.<br>
```js
// prints: 0,1,2,3,4 (no trailing comma)
for 0; 5; 1
 print {i}
 iif {i} = 4 : continue
 print , 
next
```


**do**   [_int_ **pin**, _text_ **mode**]    [ex1](#) <br>
set loop top. Optionally proceeded with `until(conditional)` or `while(conditional)`. use `break` to manually exit.<br>
```js
$x = 0
do 
  $x = +1
  iif {runtime} > 100 : break
loop
println Counted to $x in 100ms
```


**loop**   [_int_ **pin**, _text_ **mode**]    [ex1](#) <br>
returns flow to do statement<br>
```js
loop 
```



**break**   [_int_ **pin**, _text_ **mode**]    [ex1](#) <br>
*  **break**  early exists a do loop<br>
```js
break 
```

## Variables


**var**   [_text_ **$name** = _int_ **value**]    [ex1](#) <br>
Defines a regular unsigned integer variable and assigns a numerical value each time it's encountered, typically from a literal, expression, array, template, function, or other variable.
 Name _must_ start with `$`, like PHP. Program scope. The var command itself is actually optional and will be auto-inserted if a line starts with a variable assignment. <br>
```js
var $a = 3
var $b = ($a * 3) // ==9
$c = ($a + $b) // ==12
$c = +10 // ==22
$d = {rnd} // == who knows? (0-1023)
```


**static**   [_text_ **$name** = _int_ **value**]    [ex1](#) <br>
Defines a static variable. These are the same as `var` but only assign upon first encounter, not each encounter by mutating to a `noop`. See variables section. <br>
```js
for 0; 5; 1
 static $count = {i}
 var $count2 = {i}
next
// $count == 0, the value assigned the first time.
// $count2 == 4, the last value assigned
```


**global**  [_text_ **$name** = _int_ **value**]    [ex1](#) <br>
defines a system-wide variable reached via `{&name}` syntax and available to read/write from the `/store/` api. The super globals are available to all scripts to enable IPC and async HTTP interaction with non-currently-running programs. <br>
```js
global 
```


**store**   [_text_ **name** = _int_ **value**]    [ex1](#) <br>
defines a system-wide variable reached via `{&name}` syntax and available to read/write from the `/store/` api. The namespace is shared with `global`. These values are written to SPIFFS so values as persisted across reboots. The super globals are available to all scripts to enable IPC and async HTTP interaction with non-currently-running programs. <br>
```js
store myVar = 123
```
```js
$mySavedVar = {&myVar}
```

**flash**   [_text_ **fileName** [<|>]  **vars[,...]**  ]    [ex1](#) <br>
Load or save a list of variables to a text file. Good for persisting certain vars over power cycles, without exposing to the `store` interface. Can also be used for versioning, or creating "modes" with groups of presets. This is faster than using `suspend` / `resume` to persist application state.


```js
$a = 1
$b = 2
$c = 3
// save these vars  for later
flash mystate < a, b, c
/* creates a file (/mystate.var) containing:
a=1
b=2
c=3
*/
```

```js
$a = 101
$b = 420
$c = 99
// load some vars saved in above example:
flash mystate > a, c
println $a, $b, $c // shows 1, 420, 3
```

## System

**#include=**   [_text_ /**fileName**]    [ex1](#) <br>
Injects a file into the current program. Filename must start with `/`.<br>
```js
#include=/colors.bat
```


**#define=KEY literal value(s)**   [_text_ **key** ` ` _text_ **content** ]    [ex1](#) <br>
define a parse-time named macro replacement substituted for @KEY placeholders in script. Since they run before everything else, they can be used to composite variable/template names, pre-fill arrays, etc. <br>
```js
#define=BUTTON 5
#define=VER 1.2.4
#define=RAMP 1,16,55,99,150,255,512,999
println button state: {gpio@BUTTON}  (ver: @VER)

for 0; 8; 1 // fade on-board LED out:
  analogWrite 2, [@RAMP][{i}] // current tween value
  sleep 33
next
```


**run**   [_text_ **fileName**]    [ex1](#) <br>
Executes another script by filename, starting with `/`. 
Control is passed to the callee until terminated or intervaled, then returned to the calling script.<br>
Most often used in `autoexec.bat`, but can be used anywhere within limits.
```js
run /doormon.bat 
```


**option**   [_text_ **options**]    [ex1](#) <br>
Specifies options that affect the the lifetime and operation of the program.
Multiple options can be fed to the command, separated by space or commas.
There are presently 6 main options:

* `persist` - preserves a loaded program in RAM after it executes, keeping variable values, run counts, etc.
* `interval=n` - automatically runs a program repeatedly and endlessly every `n` milliseconds specified. Implies `persist`. Web responses end after the first execution, whereupon `print` defers to Serial.<br>
* `debug` - prints each line of executed code after interpolation and before interpretation.
* `socket` - changes print to broadcast over `webSocket` if connected
* `noget` - disables GET-param variable value passing, except `static` vars.
* `noget!` - disables all GET-param variable value passing, even `static` vars.

```js
// prints hello once a second:
option interval=1000
println Hello!
```


**cgi**   [_text_ **fileName**]    [ex1](#) <br>
Executes a CGI template file and prints the results. 
Templates are plain-text files that contain output and some of the placeholder/features used by scripts. <br>
Avilable features include `$vars`, `{templates}`, and `(paren expressions)`.
This makes it easier to format custom web responses or spit out formatted serial data to externally log.

```js
cgi=/temp.cgi
```




**noop**   [void]    [ex1](#) <br>
does nothing, but does so quickly. `static` commands are switched to this upon first invocation.<br>
```js
noop // do nothing
```




**unload**   [_text_ **filename** or *]    [ex1](#) <br>
unload another script by file name, starting with `/`. The star wildcard unloads all scripts.
Useful to swap out an animation scripts upon button press, aka changing a "mode". <br>
```js
unload /reds.bat
```









