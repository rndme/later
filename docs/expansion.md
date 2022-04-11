# Expanding Capabilities



## Commands
Commands can accept string input, unlike `Functions`.
Use `Later.addCommand()` to define new commands (line start words in scripts).


```c++
Later.addCommand("wipe", [](char * v, DANOS_LINE * ln, DANOS_ENVIRON * scr )->bool { return (nsDANOS::setRunLog[0] = '\0');  }); // using lambda
Later.addCommand("myprint", COMMAND( return DANOS_PRINTLN(value);  )); // using COMMAND MACRO
```
	
	
### Useful Commands


Explicit serial writing, or when defining a different port like SoftwareSerial:
```c++
Later.addCommand("serial", COMMAND( Serial.println(value); return strlen(value); ));
// script usage: serial this is some text to print to serial. print text print.
```

Change ESP's wifi device identifier:
```c++
Later.addCommand("name", COMMAND( WiFi.hostname(value); return 1; ));
// script usage: name my_cool_name
```

Send a line with WebSockets:
```c++
// up top in sketch body:
#include <WebSocketsServer.h>
WebSocketsServer webSocket = WebSocketsServer(81);

bool webSocketConnected = 0;
int webSocketSlot = 0;
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  webSocketSlot = num;
  switch (type) {
    case WStype_DISCONNECTED:
      webSocketConnected = 0;
      break;
    case WStype_CONNECTED:
      webSocketConnected = 1;
      break;
  }
}

// in setup():
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    
    Later.addCommand("send", [](char * v, LATER_LINE * ln, LATER_ENVIRON * scr )->bool { 
      if (webSocketConnected) webSocket.sendTXT(webSocketSlot, v); 
      return 1;  
    });

// in loop():
  webSocket.loop();
  
// script usage: send [1,2,"to event.data on client"]
```
   
   
   Integrating with a config manager using setConfig(k,v) and saveConfig():
```c++
    Later.addCommand("savecfg",  COMMAND( saveConfig(); return 1; )); 
    Later.addCommand("cfg", [](char * v, LATER_LINE * ln, LATER_ENVIRON * scr )->bool {
      nsLATER::laterUtil::splitStringByChar(v, ',');
      if (nsLATER::laterUtil::split_count > 1) {
        strchr(nsLATER::laterUtil::splits[0],',')[0]='\0'; // chop at first comma
        nsLATER::laterUtil::trimRight(nsLATER::laterUtil::splits[0]);
        setConfig(nsLATER::laterUtil::splits[0], nsLATER::laterUtil::splits[1]);
      }
      return 1;
    });
// script usage: cfg=wifi_ip, 212
```

    


## Templates
Use `Later.addTemplate()` to define new substituios for scripts to use.
Make sure to wrap in `{braces}`, then using a lambda or macro to define the value of the template:

```c++
Later.addTemplate("{version}",  []()->unsigned long{return 202101;});// using lambda
Later.addTemplate("{zip}",  TEMPLATE(90210)); // using TEMPLATE MACRO
```

### Useful Templates


Custom fast random range to avoid math in script-land:
```c++
Later.addTemplate("{rnd100}",  randomReg() % 100 ); // random 0-99
// script usage: $fxDelay = {rnd100}
// script usage: fetch http://192.168.1.1?a={rnd100}&b=123
```

## Functions

### Useful Functions

dump raw parsed program: (might be better as command, but this works)
```c++
Later.addFunction("DUMP", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {
  nsLATER::uniPrintln("\n============= PROGRAM DUMP ================");
  nsLATER::uniPrint(nsLATER::getCurrent()->program);
  nsLATER::uniPrintln("\n============= END PROGRAM DUMP ============\n");
  return 1;
});
// script usage: $jnk = DUMP(0)
```

Pin pulsing w/o delay or blocking:
```c++
Later.addFunction("TONE", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {
  tone((uint8_t )a, (unsigned int)b, c);
  return 1;
});
// script usage: $ret = TONE(2, 8, 1000) // pin 2 at 8hz for 1 second
```   

System-wide shared fast byte array access:
```c++
static byte Q[128];

Later.addFunction("GET", FUNCTION( return Q[a]  ));
Later.addFunction("SET", FUNCTION( return Q[a] = b  ));

// script usage: $ret = SET(0, 123)
// script usage: $x = GET(0) // will be 123
```

Get current Neopixel strip pixel raw color by index:
```c++
Later.addFunction("LEDCOLOR", FUNCTION( return LATER_PIXEL_NAME.getPixelColor(a)  )); 
// script usage: $myColor = LEDCOLOR(5) // get color of 6th (count em) pixel
```

Sigma Delta control
```c++
//#include "sigma_delta.h"
const int SDPIN = 5; // pin to configure for sigdel
uint32_t reqFreq = 9765; // 312500 max
uint32_t realFreq;
realFreq = sigmaDeltaSetup(0, reqFreq); // (chan, hz)  returns actual s.d. freq in hz
sigmaDeltaAttachPin(SDPIN);
sigmaDeltaWrite(0, 0);


Later.addFunction("SIGMA", FUNCTION( return sigmaDeltaWrite(0, a)  )); 
// script usage: $ret = SIGMA(128) // set avg pin output half-way (0-255)
```

DHT-11 temp and humidity sensor reading
```c++
#include <DHT.h>
#define DHTTYPE DHT11
const int DHTPIN = 4;
DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266

// in setup()
dht.set_pin(DHTPIN);        // initialize temperature sensor
dht.begin();        // initialize temperature sensor
Later.addFunction("HUMID", FUNCTION( return (unsigned long)dht.readHumidity()));
Later.addFunction("TEMP", FUNCTION( return (unsigned long)dht.readTemperature()));
//end setup() code
// script usage: $temp = TEMP(0)
// script usage: $humid = HUMID(0)
```

    


