
## HTTP APIs

### /log/

Provides filtered access to data gathered with log (_) commands

* **take**   number: limits the maximum number of results to return
* **skip**   number: omits the first N valid results
* **filter**   string: literal term that valid results match
* **exclude**    string: literal term that valid results don't match
* **after**    number: ms timestamp beginning valid results 
* **before**    number: ms timestamp ending valid results 
* **larger**    number: minimal string length of valid results
* **smaller**    number: maximum string length of valid results
* **count**    any: returns just the number of valid results


### /store/
To allow sharing data between scripts and reboots, there's a built-in key:value store avilable to http and programtically from scripts.

#### HTTP Access
* `/store/` : view TSV table of stored values
* `/store/?key=mynum` :  fetch value of _mynum_
* `/store/?key=mynum&value=123` :  set key _mynum_ to `123` and save
* `/store/?key=mynum&value=123&ram=1` :  set key _mynum_ to `123` w/o saving


#### Programatic Access
* `store=mynum=123` : sets _mynum_ to `123` and saves
* `global=mynum=123` : sets _mynum_ to `123` w/o saving
* `$x={&mynum}` : sets local variable `$x` to the global stored value _mynum_; 123 using above examples

 
 
### /run/
Execute a script by calling from the run endpoint: `/run/?name=file.bat`. 
You can preset and update variable values by name using GET param key=value pairs. 

Since script variable assignments over-write passed values when the declaration executes,
  use conditionals or http-only variable names to differentiate defaults, assigned/current values, 
and web-passed values/defaults.

```
// year.bat, called as /run/?name=year.bat&webYear=2022
// using call-time data from URL on a run-once:
$year = 2021 // default year
if $webYear > 0
  $year = $webYear
end if
println Adding new job for $year...
```

If you never want `0` as a passed value, you can use a more succinct default expression:

```
// year2.bat, called as /run/?name=year2.bat&year=2022
// using call-time data from URL on a run-once:
$year = ($year | 2021)
println Adding new job for $year...
```

Or you can use the even shorter default assignment operator, which keeps a non-zero value and assigns to anything else:

```
// year2.bat, called as /run/?name=year2.bat&year=2022
// using call-time data from URL on a run-once:
$year =:2021 // == right side of ($year > 0 ? $year : 2021)
println Adding new job for $year...
```


If you use a `start` section, then the assignment only happens on "startup". 
Not passing a param would simply use whatever that variable was last set to.

```
// year3.bat, called repeatedly as /run/?name=year3.bat&year=2015
// using call-time data from URL on a persistent script:
$year = 2021 // default year
start
println Adding new job for $year...
```

As a shortcut, `.bat` files also run by file name without extension, allowing vanity URL endpoints, ex: `/year` or `/year?webYear=2030`

Example autoexec.bat:
```
// door monitoring device - boot script
sleep 333 // wait to allow user time to press cancel button 
if {gpio0} > 0
  println Starting door monitor.
  run /doormon.bat
else
  println SAFE MODE!
end if
```

### /dir/
A JSON Array of Objects decribing the files save on the ESP.

#### Example return
```js
[
{"type":"file","name":"test2.bat","size":"58B","mime":"text/plain"},
{"type":"file","name":"neo7-lightlevel.bat","size":"469B","mime":"text/plain"},
{"type":"file","name":"neo7-clock-wheel.bat","size":"1017B","mime":"text/plain"},
{"type":"file","name":"test-ledpos.bat","size":"285B","mime":"text/plain"},
{"type":"file","name":"colors-def.bat","size":"142B","mime":"text/plain"},
{"type":"file","name":"autoexec.bat","size":"195B","mime":"text/plain"}
]
```





### /test/
View a detailed inspection of the last executed script; the parsed code, current variable values, the runtime log, and stats.


#### Special Needs Flags
These enable handling of certain constructs within the line's argument ( anything to the right of the starting command).

* `H`: Needs HTTP Response parsing
* `O`: Needs Output - interpolates placeholders - ex: `println`, `log`
* `A`: Needs Array processing - ex: `[1,2][$x]`
* `E`: Needs Expression processing  - ex: `(1 + 2 / 3)`
* `V`: Needs Variable processing - ex: `println Total: $tot`
* `T`: Needs Templates processing - ex: `println Time Take: {runtime}`


#### Example return
```
25 lines in 249b from /neo7-lightlevel.bat
RAM:7192,  runs:1338,  subRet:0, resumeLine:7
Line:25, forStart:0, forEnd:0, forStep:0, forIndex:0

LINES:
 #  exit         HOAEVT flags  	OP  value
 0 -> 0 	[      ]	c = interval=500
 1 -> 0 	[      ]	M = 4,INPUT_PULLUP
 2 -> 0 	[      ]	M = 2,INPUT_PULLUP
 3 -> 0 	[     T]	V = @A_={adc}
 4 -> 0 	[      ]	V = @B_=0
 5 -> 0 	[     T]	V = @C_={runs}
 6 -> 0 	[      ]	z = 00
 7 -> 0 	[   EVT]	V = @A_=({adc} + @A_ + @A_ + @A_ + {adc} / 5)
 8 -> 0 	[    V ]	V = @D_=@A_
 9 -> 11 	[    V ]	I = @D_>90
10 -> 0 	[      ]	V = @D_=90
11 -> 0 	[      ]	F = 00
12 -> 14 	[    V ]	I = @D_<9
13 -> 0 	[      ]	V = @D_=9
14 -> 0 	[      ]	F = 00
15 -> 24 	[    VT]	I = @C_<{runs}
16 -> 23 	[    V ]	I = @D_!@B_
17 -> 0 	[   EV ]	V = @E_=(@B_ + @D_ / 2)
18 -> 0 	[    V ]	V = @B_=@D_
19 -> 0 	[    V ]	m = light=@E_
20 -> 0 	[      ]	f = 200
21 -> 0 	[    V ]	m = light=@D_
22 -> 0 	[   E T]	V = @C_=({runs} + 2)
23 -> 0 	[      ]	F = 00
24 -> 0 	[      ]	F = 00
 #  exit         HOAEVT flags  	OP  value

VALUE REGISTERS:
#  	SYM	val	expr
1.	@B_	9	$last
3.	@D_	9	$level
2.	@C_	5	$lockTill
0.	@A_	2	$read
4.	@E_	4	$temp

-------- SYSTEM LOG -----------
```
Which is the result of running this script:
```
// background light level adjuster
// monitors ldr on ADC and sets global `light` variable

option= interval=500
pinMode=4,INPUT_PULLUP

pinMode=2,INPUT_PULLUP

$read={adc}
$last = 0
$lockTill = {runs}

start

$read = ({adc} + $read + $read + $read + {adc} / 5)

$level = $read
if $level > 90
  $level = 90
fi
if $level < 9
  $level = 9
fi


if $lockTill < {runs} 
    if $level ! $last
      $temp = ($last + $level / 2)
      $last = $level
      global=light=$temp
      freeze 200
      global=light=$level
      $lockTill = ({runs} + 2)
    fi
fi
  
```






### /scripts/
View a JSON list of running tasks with statistics, comparable to a _task manager_ or `top` utility.

#### Example return
```js
{
	"count": 1,     // # of scripts running
	"current": 1,   // last active script by index
	"ms": 7616721,  // current system clock
	"ram": 8200,    // device free heap
	"bootram": 11240,   // free heap at startup
	"scripts":[  // array of script stat objects
	{
		"fileName": "/neo7-clock-wheel.bat",
		"index": 1, // ~PID - here autoexec.bat used slot 0 to run this
		"frozen": 1,    // awaiting next interval?
		"interval": 28, // how many ms between invocations
		"line": 52,     // last executed line number - ~cursor
		"lines": 55,    // how many non-empty LOC?
		"exit": 52,     // exit point - last line of code or start of _after_ section 
		"chars": 528,   // ~bytes of code
		"vars": 16,     // how many $variables are in use?
		"reads": 0,     // how many file reads performed by script?
		"writes": 0,    // how many file writes performed by script?
		"parseTime": 15339, // us taken to parse script before executing
		"runTime": 20925,   // us taken to execute script once, the last time
		"avgTime": 22182,   // us taken to run a task a single time on average
		"cpuTime":  190612569,  // us taken to run task in total
		"lifeTime": 242115000,  // us since script was loaded (cpu/life = cpu utilization from 0.0 - 0.99)
		"runs": 8593
	}
		]
}
```
