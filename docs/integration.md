
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
Setting a `global` or `store` value from scripts, ex: `store $ip=123`, enables fetching that value from the ESP's `/store/` endpoint.
You can get all such values as a TSV table at `http://{esp ip}":80/store/`, or a specific one as a numeric literal at `http://{esp ip}":80/store/?key=ip`.
See [the store api](/docs/api.md#http-access) section for details.

### To http - fetch
You can push out data to a remote HTTP server using GET params on a HTTP call from the ESP.
The URL in a `fetch` call is templated, making data embeding simple and easy.
Example: `fetch http://192.168.1.1:1880/incoming/?dev={mac}&type=moisture&value={adc}`


### To http - log

### To http - print

### To http - test

### To sketch - store

### To sketch - variables

### To sketch - functions

### To files - write

### To files - append

### To serial - print

### To serial - println







## Getting Data To Scripts


### From http - variables

### From http - store

### From http - fetch

### From http - macros

### From sketch - functions

### From sketch - store

### From sketch - commands

### From files - read


