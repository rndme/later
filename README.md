# Later


## About
Later is a drop-in Arduino scripting library for ESP microcontrollers hosting  
compilation-free glue code for 
monitoring sensors, controlling things, and creating RGB LED animations.

It's designed for hobbyists who can't remember which sketch they used on which device.

The built-in HTTP web interface enables easy code editing of the on-device batch programs.
Since the code lives on the thing, there's nothing to lose.
You can instantly make live code changes without rebooting or waiting on OTA, dramatically cutting the dev cycle period.
The extra time lets you tweak that perfect level of brightness or beep durations for killer device UX.




### Pros
* Easy to add to an existing Arduino sketch.
* Easy to create new scripting functionality from within the sketch.
* Realtime AF: deploy live code changes from a text file upload or built-in web-editor. 
* APIs to dump/edit live variables, manage, and interact with running programs.



### Cons
* It's interpreted code, which runs slower than native C/C++.
* It's a whole new language you don't know, yet.
* Exclusively for the ESP family of MCUs, chiefly the 8266.



## Getting Started
If you've not done so, install the [arduino enviroment](https://www.arduino.cc/en/software) and add [ESP8266 support](https://github.com/esp8266/Arduino#installing-with-boards-manager).

Now use `git clone git@github.com:rndme/later.git` or download [the repo zip](https://github.com/rndme/later/archive/refs/heads/master.zip) and unzip it to your `arduino/libraries/` folder.

Once installed, you can use one of the built-in example sketches or just manually add the needed pieces to a new or existing sketch.
```C++
#include "SPIFFS.h"
#include <later.h>

// in setup(), usually the end:
Later.setup();

// in loop, anywhere:
Later.loop();

```

Upload the sketch to the ESP, then navigate to the ESP's wifi address in a browser to arrive at the landing page. From there, head to the editor to start writing your first script.

See the [scripts](scripts/) folder for some inspiration.



## Bite size demos
Simple but practical examples in a half-dozen lines of code or less.
These can all be named `autoexec.bat` to create instant single-purpose devices.


#### Heater controller w/hysteresis
```  // tries to keep analog value between 80 and 170
option interval = 30000 // run every 30 seconds
iif {adc} < 100 : digitalWrite 2, 1 // too cold, turn heat on
iif {adc} > 150 : digitalWrite 2, 0 // too hot, turn heat off
```


####  animated neopixel rainbow 
``` 
option interval = 20  // target 50FPS
for 0; {leds}; 1 // start; max; step
  $hue = ({runs} + {i} * 100 % 65000)
  pixel {i}->HSV($hue, 255, 100)
next
render
```





#### ADC Data logger (SPIFFS)
``` // appends ADC sample to file w/timestamp + count
option interval=5000 // run every 5 seconds
static $readCount = 0
$avg = ({adc} + {adc} + {adc} / 3) // reduce noise by averaging 3 samples
$readCount = +1 // increment counter
println $readCount	{time.epoc}	$avg >>>/mydata.txt
```

#### GPIO Read API (HTTP or Serial)
``` // prints to Serial if not run from http
println { 
println  "analog": {adc},
println  "pin_0": {gpio0},
println  "pin_2": {gpio2}
println }
```


#### GPIO Write HTTP API
``` // set GPIO2 via GET: /autoexec?value=123&pin=2
$pin=:2	// default gpio 2 if ommited from GET params
if $value > 1
  analogWrite $pin, ($value % 1024)
else
  digitalWrite $pin, $value
fi
print Set GPIO #$pin to $value
```


#### Blink w/o Delay
There's several ways, here's a couple neat ones.

``` // blink via interval option and static state
option interval = 250  // target 4FPS
static $state = 1 // on or off?
digitalWrite 2, $state // make it so
$state = (1 - $state) // toggle
```

``` // blink via infinite loop
$state = 1 // on or off?
do
  digitalWrite 2, $state // achieve blinkedness
  $state = (1 - $state) // do the other one next time
  freeze 250 // look Ma, I'm non-blocking
loop
```

``` // blink via interval'd subroutine calls
option interval = 10  // check 100x a second, only fire 4x
sub blink {
  digitalWrite 2, $state // undeclared vars are zero
  $state = (1 - $state) // toggle 0/1
} // end blink()
interval 250, blink
```


## Commands
There are dozens of built-commands and programming structures to write a program. 
You can also create your own to host inside your sketch.
View a complete list with detailed usage and examples in the [commands documentation](docs/commands.md).
	

## Variables
Variables begin with $ and store numeric values from 0 to 2^32. 
They are replaced early, so they can be used anywhere a number would be used, like in conditionals, loop params, etc. 

All variables are positive integers. All scope is global to the single script. Subroutines don't have private variables, they read/write the same variables as inline code. 
There is no way to undefine a variable within a script once created, without reloading the script.
Default variable value if un-assigned is 0, positive integers only, init once via `$a=123`.
GET runtime setting: `/batch?mode=3` sets `$mode=3` before `/batch.bat` runs.
You can create "local static" variables using the `static` command, eg. `static $count=0`, which only assign a value the first time they are encountered. You can create supervariables accessible to all scripts using the `global` command, eg. `global lastseen={timer}`, which are read via &-prefixed template-syntax: `{&lastseen}`. If you want the superglobal value to persist between reboots, you can save it to a local file/EEPROM during assignment by using the `store` command the same as `global`.




Define a variable by name as the key:

`$count = 0 // zero is default, must be positive`

You can modify a variable by setting the value with a mutative prefix to add, subtract, modulo, etc:

```c++
$count = +1 // increment the count
$count = -1 // decrement the count
$count =*10 // scale the count 10X
$countIsOdd = $count  // assignment and duplication
$countIsOdd =^2 // MOD 2. 1 if odd, 0 if even
```

### Assignment Operators

These single-char flags prefix the data assigned to a variable to affect the resulting var in useful ways.

* `+` - add the value to the current variable instead of replacing it
* `-` - subtract the value from the current variable instead of replacing it
* `*` - multiply the value by the current variable instead of replacing it
* `/` - divide the value of the current variable instead of replacing it
* `^` - raise the current variable  to the power of the assigned value
* `%` - assign the remainder of current variable divided by the value
* `<` - assigns a `0` if variable is greater than the value, `1` if smaller
* `>` - assigns a `1` if variable is greater than the value, `0` if smaller
* `!` - assigns a `0` if variable is the same as the value, `1` if different
* `?` - assigns the new value if var is non-zero, keeps the var if it's zero
* `:` - assigns the new value if var is zero, keeps the var if it's non-zero
			
			

### Variable Commands

* `var $x = 123` The normal definition, normally used via short-cut `$x = 123`
* `static $x = 123` Only applies the first time it's run, then is ignored, good for defaulting values
* `static $obj={a:1,b:2,c:3}` `static` can also create apparent literal objects, read with a dot, eg: `$obj.b`, equal to 2 here. The base variable contains the key:value pair count.
* `static $obj=[1,2,3]` `static` can also create apparent literal arrays, read with a dot, eg: `$obj.1`, equal to 2 here. The base variable contains the element count.
* `global x=123` Sets a system-wide variable, read through a template, eg: `{&x}` here. See [Store section](/docs/api.md#store) fro more info.
* `store x=123` Sets a system-wide variable same as `global`, but the value is saved to internal storage for persistence between reboots.




## Arrays

Use a JSON numeric array literal as an assignment lookup table:

   ```$day = [1,7,15,28][$someIndex] // defaults to 0 on overflow```

There are faster fixed-width array literals as well:

   ```$c=[&3;11 22 33 44][2] - 3 is width of each element in bytes```

And custom-delimiter arrays as well:

`$b=[& ;11 22 33 44][2] where the char between & and _ is the delimiter`

You can return  the length of an array (last index) with a `=` flag:

`$count=[11, 22, 33, 44][=] - sets $count to 3, the last element's index`

You can return an index instead of the element value with a `&` prefix flag:

`$b=[11, 22, 33, 44][&22] - sets $b to 2. Starts at 1 so 0 is a miss`

You can return a LT or GT first-match as well with `<` or `>` flags:

`$b=[11, 22, 33, 44][>20] - sets $b to 22, the first hit GT 20`

Finally, such compares can be used to lookup indices as well:

`$b=[11, 22, 33, 44][&>20] - sets $b to 2, the index of first hit GT 20`


## Templates
These insert useful common and system-provided numbers into a program. 
They are delimited by `{` and `}`, with a key/path name in the middle, eg. `{time.hour}`.
Read all about templates in the [templates documentation](docs/templates.md).

## Strings
There are no String variables, but there's literal input/output and String-handling tools, much like a batch or shell script. 
Text can come from a web fetch (`$RESPONSE`), a macro replacement (`println month: @month`), or from a program itself (`println Uptime: {timer}`).
Arrays can yield discrete text from an index (`[AM,PM][$isPM]`). Format, filter, and alter text using string tags. Useful for web api responses and data logging.


### Available String Tags
* `<#escape hello world#>` makes text url-safe, eg: `hello%20world`
* `<#upper hello world#>` makes text uppercase, eg: `HELLO WORLD`
* `<#lower Hello World!#>` makes text lowercase, eg: `hello world!`
* `<#trim   Hello World!   #>` removes leading and trailing space from text, eg: `Hello World!`
* `<#hex 254#>` converts a number into hexadecimal form, eg: `fe`
* `|<#pad40 99#>|` pads a string to the first digit's width using the 2nd character against the rest, eg: `|0099|`



## Colors
Several color formats are supported by Later. 
literals: `#ABC` or `#abc` or `#AABBCC` or `#aabbcc`, or `r,g,b` where each is 0-255 as digits or variables
Colors variables: `$c=RGB(255,255,255)` and `$c=HSL(64000,255,255)` can be used.


Color variables can even be mixed with simple math:
```
  $red = RGB(255,0,0)
  $blue = RGB(0,0,255)
  $magenta=($red + $blue)
```

The pixel command supports a variety of blend modes (via the current and a new specified color) using a hint prefix with the color specifier. Ex: `pixel 0->+RGB(10,10,10) // lighten existing color by 10 levels`. Available prefixes:

```pixel=5->&0 // dims all channels by half```


* `<` subtracts a random amount to the existing color. clamped at 0. new color's rgb values are max to add.
* `>` adds a random amount to the existing color. clamped at 255. new color's rgb values are max to add.
* `+` add new color to existing color clamped at 255 - lightens or shades
* `-` subtract new color from existing color clamped at 0 - darkens
* `*` adds/subtracts a random range to the old  - each rgb level of new color is the range's span
* `&` averages the old and new color, reducing flashiness


## Expressions
You can perform math and comparisons inside of a parenthesis, left to right order of operations, carrying the value each operation
```c++
$a = (1 + 2 + 3) // sets $a to 6
$b = (2 * 3 + 10 / 2) // sets $b to 8: equiv to (((2*3) +10) / 2)  
```

You can also perform an operation on a whole set of comma-seperated numbers by putting the operator first (lisp-style):
```$c = (+1,2, 3 , 4,5) // sets $c to 15; the sum of all digits```

### Expression Operators
* Arithmetic: `+-*/%` performs math on numbers
* Boolean Comparison: `!=&`  0 or 1 if evaluating to true as not same, same, and both true respectively
* Value Comparison: `<>` used lisp-style as min/max ex: `(>3,5,7)==7`, or as a compare yielding 0 or 1 ex: `(5 < 7)==1`
* Ternary Usage: `?:` a special syntax to write an expression like `($x > 9 ? 2 : 1)` or even just `($z ? 2 : 1)`. must appear at end of chain.
* Defaults: `|` keeps left side if non-zero, otherwise picks right side `(0|5)==5` and `(3|5)==3`.


## Conditionals
The `if cond`, `iif cond`, `do while(cond)`, and `do until(cond)` commands use a common conditional syntax.
The basic premise is comparing two numbers using comparison operators. 
Multiple evaluations are supported using AND (`&`) and OR (`|`) functionality. 
`else` can be used to invert an `if` clause; doing one thing if true, another if false.
`if` blocks can be nested, even deeply, but `else` cannot be nested to avoid the dangling else problem. 
A workwround is to have two sperate `if` statement with an inverted condition, eg. `if(cond)` and `if(!cond)`. 
Note that `else` can be nested in one+ `if` blocks, it cannot be nested in an outer `else`.
If the first term in a conditional is `!`, the whole conditional evaluation is inverted, including AND.


### `iif` command
`iif` is like if, but inline and without `else` support.
 In basic form, `iif condition` guards the next line of code with the conditional evaluation.
 If the condition is true, the line after is run, if false, it's skipped.
 
 ```
 iif $x > 6
   println Please pass a day of the week
 ```
 
 There's an optional code-brevity enhancement to `iif` using a colon to place the code to be executed after the conditional, using a `:` as a delimiter.
 
 ```
 iif $x > 6 : println x is bigger than six
 ```
 

### Conditional Operators

* `=` - true if left and right numbers are the same
* `!` - true if left and right numbers are NOT the same
* `<` - true if left is less than right 
* `>` - true if left is greater than right
* `%` - true if left modulo right is non-zero
* `&` - true if left and right are both non-zero, chaining logic
* `|` - true if left is zero, moving to evaluate next conditional, chaining logic



## Functions
These take 0-3 numbers and return a number. Most of the built-ins are math-focued, and you can define your own in your host sketch:

### Built-in Functions
* **MIN**(x,y) - the lessor of x or y
* **MAX**(x,y) - the greater of x or y
* **SQRT**(x) - square root of x. integer.
* **CBRT**(x) - cube root of x. integer.
* **POW**(x,y) - takes x to the power of y
* **MAP**(val,maxFrom,maxTo) - scales value from 0-maxFrom to 0-maxTo.
* **RGB**(r,g,b) - construct a reg, green, blue color value. values above 255 and below zero roll-over (unsigned)
* **CRGB**(r,g,b) - same as RGB() but slower and clamped to 255 and 0 when over/under respectively.
* **HSV**(hue,sat,val) - construct a color using HSL instead of RGB values
* **CSPRNG**(a,b) - returns a fast and supposedly true random number between a and b
* **PRNG**(a,b) - returns a pseudo random number between a and b
* **SEED**(a) - sets chain of values given by PRNG using an integer seed value
* **GPIO**(pin) - returns a digitalRead of the specified GPIO pin. Unlike templates (eg. `{GPIO2}`), a var names the port.

### Custom Functions
You can define new function in your Arduino sketch that can the be reached by scripts.

```c++
Later.addFunction("SUM", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {return a + b + c;}); // using lambda

Later.addFunction("PRODUCT", FUNCTION(return (a * b) * (c ? c : 1);)); // using FUNCTION MACRO with a,b,c pre-named formal parameters
```





## Subroutines
Named chunks of code, subroutines can be called manually, in response to an interrupt, or on an interval.
Called manually using gosub, arguments can be passed to the sub as {arg0}...{arg3} as seen by contained code.
```
gosub myRoutine 11, 22, 33 
```

Arguments are _local_ "variables", the rest of a program's vars are available to the subroutine to read and change.
Values can be returned to a variable assignment using `call`, but most simply cause side-effects like print or a GPIO for output.

`interval = n, name` runs the sub on a schedule, less often than the main program. 
Intervals will only possibly fire when execution reaches it (no hidden background subscriptions), use w/ option=interval (<n) or with repeated manual invocations via http


### Events
Events invoke subroutines based on GPIO pin state changes, making it simple to monitor for button presses, etc. 
As the subroutine is invoked a few special meta data are produced to assist handling logic:

Basic syntax: `on= pinNumber, subName[, FALLING|RISING|CHANGE*|EDGE]` - fires the subroutine when a GPIO pin changes state

#### Event Meta
*  `{E.pin}` : from event sub-routine, pin that changed state
*  `{E.value}` : from event sub-routine, new pin value
*  `{E.time}` : from event sub-routine, ms timer when pin changed state
*  `{E.ms}` : from event sub-routine, duration since last change in ms

#### Types of pin changes that can trigger events:

* `CHANGE` - a pin changes from HIGH to LOW _or_ from LOW to HIGH - the default
* `FALLING` - a pin changes from HIGH to LOW
* `RISING` - a pin changes from LOW to HIGH





## &RESPONSE
`&RESPONSE` provides a very basic set of tools to process response data from HTTP fetch commands. 
Due to the limited RAM of the ESP, response is limited to 1400 bytes, and cursor operations will mutate the data.


### Commands 
* `&RESPONSE->after(literal)` : void - discards all data before and including `literal`
* `&RESPONSE->before(literal)`: void - discards all data after and including `literal`
* `&RESPONSE->count(literal)` : number - command is replaced by the number of times `literal` appears in current response
* `&RESPONSE->json(literal)` : number - command is replaced by first integer found after literal, typically a key name
* `&RESPONSE->length` : number - command is replaced by the number of bytes in current response
* `&RESPONSE->linecount` : number - command is replaced by the number of lines in current response
* `&RESPONSE->status` : number - command is replaced by the HTTP status code of the response
* `&RESPONSE->text` : string - command is replaced by entire current response 



## Range Operator
The range operator, `..`, completes a by-one integer sequence between the numbers to the right and left of it.
It runs at parse time and injects literal numbers into the script, so it's size is limited by line length limitations.

`println 1..5` returns `1,2,3,4,5`
`println 9..6` returns `9,8,7,6`


## Macros
`#define=key 123` creates parse-time "macro" literal replacements substituted for `@key`, `123` in this example.
These values are unparsed, so text, lists, and numbers can be macro'd and will be literaly placed un-modified.
You can also inject GET parameters with macro syntax (ex: `@param`), much like variable's GET mapping, but unparsed and replaced once at load.
This can be used to detect empty parameters (ex: `if 1@param > 9`) that could be a `0`, which cannot be determined by a variable since they default to `0`.
Compared to variables, the literal values left by macros need parsing each evaluation, 
which results in about half the performance of variables; vars: 3.6us vs macros: 7us on the 8266. The difference is usually negligable, but for tight loops demanding top performance, copy literals to variables.





## autoexec.bat
Code contained in the special `/autoexec.bat` file runs upon startup. Use it to show start messages, default LED strips, launch another script file by name, or just do a small task.
It's a decent idea to add a pause before running any files or commands, to allow a manual over-ride in case a broken script is saved.




## Program Execution

### Line interpretation 
Each line begins with a command, and usually has value(s) passed to the command. 
The commands are parsed into a 1-char command code for fast switch()ing during execution.
Each block command (eg. loops, sub, switch, etc) is scanned to find entrance and exit lines.
Special features of each line are detected (uses variables, has templates, has expressions, has RESPONSE methods, needs output, has Array, etc)
whitespace is removed when possible. "\n", "\s", and "\t" literals are unescaped for outputting newline, space, and tab respectively.


### Line Execution
After parsing, lines are stored for processing, which entails visiting each line from top to bottom.
Upon each line, a copy is made and special syntax features are composited in the following order:


#### Syntax features order of substitution

1.  &RESPONSE-> embeds processed
1.  {templates} value replaced w/ literals
1.  $variables processed (composited w/output or DMA'd on assignment)
1.  (expression - s) evaluated and composited
1.  [arr,ays][0] single value selected and composited
1.  --option debug line printed here--
1.  commands=processed (line value resulting from above steps gets interprated)





