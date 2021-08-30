
# Integrations
Getting data into and out of scripts is easy using a wide variety of techniques provided by built-in exposures, interfaces and APIs.


#### Getting Data OUT From Scripts
* http :  [store](#to-http---store),  [fetch](#to-http---fetch),  [log](#to-http---log),  [print](#to-http---print),  [test](#to-http---test)
* sketch :  [store](#to-sketch---store),  [variables](#to-sketch---variables),  [functions](#to-sketch---functions)
* files :  [write](#to-files---write),  [append](#to-files---append)
* serial :  [print](#to-serial---print),  [println](#to-serial---println)

#### Getting Data IN To Scripts
* http :  [variables](#from-http---variables),  [store](#from-http---store),  [fetch](#from-http---fetch),  [macros](#from-http---macros)
* sketch :  [functions](#from-sketch---functions),  [store](#from-sketch---store),  [commands](#from-sketch---commands)
* files :  [read](#from-files---read)



## Getting Data From Scripts

### To http - store
Setting a `global` or `store` value from scripts, ex: `store ip=123`, enables fetching that value from the ESP's `/store/` endpoint.
You can get all such values as a TSV table at `http://{esp ip}:80/store/`, or a specific one as a numeric literal at `http://{esp ip}:80/store/?key=ip`.
See [the store api](/docs/api.md#http-access) section for details.

### To http - fetch
You can push out data to a remote HTTP server using GET params on a HTTP call from the ESP.
The URL in a `fetch` call is templated, making data embeding simple and easy.
Example: `fetch http://192.168.1.1:1880/incoming/?dev={mac}&type=moisture&value=$avg`

### To http - log
Use the log feature to buffer and expose larger amounts of ESP-generated data. Calling the `log` command appends the templated line to the internal log with a timestamp.
That logged data and messages are available at `http://{esp ip}:80/log/`
This API provides several optional parameters to filter and select the data, see [the log api](/docs/api.md#log) section for details. 

### To http - print
When running a script via http, data can be returned to the response using `print` and `println` (as well as `assert` and `timer`).
Output-producing lines are fully templated with variables, templates, macros, arrays, etc.
Example: calling a file named `myscript.bat` containing `print Hello World` via `http://{esp ip}:80/myscript/` returns `Hello World` as the HTTP response.

### To http - test
All of a script's variable and some DMA expressions (and log message, stats, etc) are available at `http://{esp ip}:80/test/`. 
If multiple scripts are running, you can specify a file name to choose one:  `http://{esp ip}:80/log/?name=/myscript.bat`.
Only scripts with `option persist` or `option interval=n` are preserved after execution and made available to this interface.

### To sketch - store
Setting a `global` or `store` value from scripts, ex: `store ip=123` exposes it to C++ via the Store Class.
In your sketch, this can be reached as `unsigned long customIP = nsLATER::LATER_STORE.get("ip");`.
You can also push data into scripts with this API, example: `nsLATER::LATER_STORE.set("ip", 101);`.

### To sketch - variables
Sketch variables can be reached from C++ via `nsLATER::SCRIPTS[int instance]->VARS[int slot]`. A lookup for slots is held by a [map](https://www.cplusplus.com/reference/map/map/) at `nsLATER::LATER_VAR_NAMES[int instance]`, which holds an index linking the auto-replaced script variable name's new shortcut letter `(index + 65 = runtime char name)`.

### To sketch - functions
You can call scripting [custom functions](/README.md#custom-functions) defined by your sketch to link between the two.
```c++
// define a byte array:
static byte Q[65];

// define some custom functions for later scripts to reach the array:
Later.addFunction("SET", FUNCTION( return Q[a] = b  )); 
Later.addFunction("GET", FUNCTION( return Q[a]  ));

// set a default byte value for the first slot:
Q[0]=123;
```
`Q[]` can be used from C++ just like any other variable.
From the later script, you can read that byte array like `$val=GET(0)`, and alter it like `$status=SET(0, 222)`.

### To files - write
Output can be re-directed into a SPIFFS file using the `>>` operator, ex: `print Hello World >>/text.txt`, which would leave the file `text.txt` containing `Hello World`.
Output-producing lines are fully templated with variables, templates, macros, arrays, etc.
You can fetch any SPIFFS file from HTTP as ex: `http://{esp ip}:80/text.txt`, or use your sketch code to process the SPIFFS file yourself.

### To files - append
Output can be re-directed and appended to SPIFFS files using the `>>>` operator, ex: `print {runs}, >>/runs.txt`, which would leave the file `runs.txt` containing `1,2,3,4,5` is ran 5 times.
Output-producing lines are fully templated with variables, templates, macros, arrays, etc.
You can fetch any SPIFFS file from HTTP as ex: `http://{esp ip}:80/text.txt`, or use your sketch code to process the SPIFFS file yourself.


### To serial - print
If not invoked from HTTP, `print` and `println` output to the `Serial` port, which can be specified using a sketch macro, ex: `#define LATER_UART_PORT Serial1`.
You can also write a [custom command](/docs/expansion.md#commands) that outputs the script-provided composited line on any port or even a non-serial interface of your liking.

### To serial - println
If not invoked from HTTP, `print` and `println` output to the `Serial` port, which can be specified using a sketch macro, ex: `#define LATER_UART_PORT Serial1`.
You can also write a [custom command](/docs/expansion.md#commands) that outputs the script-provided composited line on any port or even a non-serial interface of your liking.


## Getting Data To Scripts


### From http - variables
Variable values can be set by GET parameters in the HTTP call that runs the script, example: `http://{esp ip}:80/myscript?mode=5` to pre-set `$mode`. 
If a GET-passed variable is _assigned_ a value in the script, the http-provided value is discarded at that point.
The value of an undeclared variable is `0`, which makes it tricky to determine between a missing param and one set to 0.
Use GET macro syntax (which are empty instead of `0` when unset) to handle such ambiguities. 

### From http - store
A remote client can set new values for `global` or `store` script values by name from `http://{esp ip}:80/store/`.
For exmaple, `http://{esp ip}:80/store/?key=mynum&value=123` to set `{&mynum}` seen by scripts.
See [the store section](/docs/api.md#store) for details.



### From http - fetch

### From http - macros

### From sketch - functions

### From sketch - store

### From sketch - commands

### From files - read


