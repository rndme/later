
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

