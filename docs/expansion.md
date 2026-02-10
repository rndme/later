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


Print JSON of many variables to http response:
```c++
    // print JSON response with a list of named variables, eg: json age, mode, lastTime
    Later.addCommand("json", [](char * v, LATER_LINE * ln, LATER_ENVIRON * s )->bool {
      nsLATER::laterUtil::splitStringByChar(v, ',');
      if (nsLATER::laterUtil::split_count > 1) {

        nsLATER::uniPrintln("{");

        char valbuff [18];

        for (int i = 0; i < nsLATER::laterUtil::split_count; i++) {
          // trim left:
          while (nsLATER::laterUtil::splits[i][0] == ' ')nsLATER::laterUtil::splits[i]++;

          // find comma delim:
          char * ptr = strchr(nsLATER::laterUtil::splits[i], ',');
          if (ptr) ptr[0] = '\0'; // chop at first comma

          // trim right:
          ptr = strchr(nsLATER::laterUtil::splits[i], ' ');
          if (ptr) ptr[0] = '\0'; // chop at first space

          char* slot;
          char key[16];
          key[0] = '$';

          strcpy(key + 1, nsLATER::laterUtil::splits[i]);
          slot = nsLATER::getVarName(key, s->index); // use composite to get/make allocated slot
          nsLATER::uniPrint(" \"");
          nsLATER::uniPrint(key + 1);
          nsLATER::uniPrint("\":\t");
          itoa (s->VARS[slot[1] - 65], valbuff, 10);
          nsLATER::uniPrint( valbuff );
          nsLATER::uniPrintln(", ");

        }//next var
        nsLATER::uniPrintln("} ");
      }//end if vars passed?
    });//end command:json
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

Read serial port byte by byte
```c++
    Later.addFunction("UART", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {
      if (Serial.available()) return Serial.read();
      return 0;
    });
```    




## Arrays

```c++
#ifdef LATER_ARRAY

void addLaterArrays() {

#ifdef ESP32

  ///////////////////////////////////
  // LATER ARRAY ADDON

  /* Functions, Templates, and array Command methods

      FUNCTIONS
      ARRAY(n)   // returns the value at element #n, ex: $v=ARRAY(2) // get third element
      INDEXOF(v) // returns the array index of the first element to equal v

      TEMPLATES
      {[length]} // used elements
      {[limit]}  // max index
      {[avg]}    // mean
      {[max]}    // max value in array
      {[min]}    // min value in array
      {[sum]}    // sum of all elements
      {[pop]}    // value of last element, which is removed
      {[shift]}  // value of first element, which is removed

      COMMANDS
      array clear                     // empty the array
      array dump                      // print array as JSON
      array fill value,?count,?start  // injects a set value into the array 1+ times
      array filter conditional        // used conditional syntax to remove elements, ex: array filter > 3
      array length n                  // sets the array length to n elements, discarding anything greater
      array push a,?b,?c,?...rest     // adds values to end of array
      array reverse                   // reverse order of elements
      array sort                      // ascending sort
      array splice pos,remove_count,?value (dd: upgrade to ...rest?)
      array unshift a,?b,?c,?...rest  // adds values to start of array
  */


  // ARRAY FUNCTIONS:
  Later.addFunction("ARRAY", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {
    if (a >= ARRAY_LENGTH) return -1;
    return ARRAY[a];
  });

  Later.addFunction("INDEXOF", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {
    if (b < 1) b = 0;
    if (b >= ARRAY_LENGTH) b = ARRAY_LENGTH ;
    for (int i = b; i < ARRAY_LENGTH; i++) if (a == ARRAY[i]) return i;
    return -1;
  });

  // ARRAY TEMPLATES:
  Later.addTemplate("{[length]}", TEMPLATE(  ARRAY_LENGTH  ));
  Later.addTemplate("{[limit]}", TEMPLATE(  ARRAY_LIMIT  ));
  Later.addTemplate("{[pop]}",  []()->unsigned long{
    unsigned long val = ARRAY[ARRAY_LENGTH - 1];
    ARRAY_LENGTH--;
    return val;
  });
  Later.addTemplate("{[min]}",  []()->unsigned long{
    unsigned long min = ARRAY[0];
    for (int i = 1; i < ARRAY_LENGTH; i++) {
      if (ARRAY[i] < min)  min = ARRAY[i];
    }
    return min;
  });
  Later.addTemplate("{[max]}",  []()->unsigned long{
    unsigned long max = ARRAY[0];
    for (int i = 1; i > ARRAY_LENGTH; i++) {
      if (ARRAY[i] < max) max = ARRAY[i];
    }
    return max;
  });
  Later.addTemplate("{[median]}",  []()->unsigned long{
    unsigned long min2 = ARRAY[0];
    for (int i = 1; i > ARRAY_LENGTH; i++) if (ARRAY[i] < min2) min2 = ARRAY[i];


    int halfCount = ARRAY_LENGTH / 2;
    int val = ARRAY[0];
    int biggerCount = 0;
    for (int i = 0; i < ARRAY_LENGTH; i++) {
      val = ARRAY[i];
      if (val <= min2) continue;
      //biggerCount = ARRAY.filter(x => x > val ).length
      biggerCount = 0;
      for (int ii = 0; ii < ARRAY_LENGTH; ii++) {
        if (val < ARRAY[ii]) biggerCount++;
      }
      if (biggerCount > halfCount) min2 = val ;
      if (biggerCount == halfCount) return val;
    }
    return 0;
  });

  Later.addTemplate("{[sum]}",  []()->unsigned long{
    unsigned long sum = 0;
    for (int i = 0; i < ARRAY_LENGTH; i++)sum += ARRAY[i];
    return sum;
  });
  Later.addTemplate("{[avg]}",  []()->unsigned long{
    unsigned long sum = 0;
    if (ARRAY_LENGTH == 0) return 0;
    for (int i = 0; i < ARRAY_LENGTH; i++)sum += ARRAY[i];
    return sum / ARRAY_LENGTH;
  });
  Later.addTemplate("{[shift]}",  []()->unsigned long{
    unsigned long val = ARRAY[0];
    for (int i = 1; i < ARRAY_LENGTH; i++) {
      ARRAY[i - 1] = ARRAY[i];
    }
    ARRAY_LENGTH--;
    return val;
  });

  // ARRAY COMMANDS:
  Later.addCommand("array", [](char * v, LATER_LINE * ln, LATER_ENVIRON * scr )->bool {

    char * argPtr = strchr(v, ' ');
    if (argPtr && strlen(argPtr)) {
      nsLATER::laterUtil::splitStringByChar(argPtr + 1, ',');
    } else{
      nsLATER::laterUtil::split_count = 0;
    }

    if (strstr(v, "dump") == v) {
      char buffer [20];
      nsLATER::uniPrint("[ ");
      for (int i = 0; i < ARRAY_LENGTH; i++) {
        itoa(ARRAY[i], buffer, 10);
        nsLATER::uniPrint(buffer);
        if (i + 1 != ARRAY_LENGTH) nsLATER::uniPrint(", ");
      }
      nsLATER::uniPrintln(" ]");

      return 1;
    }//end if dump?

    if (strstr(v, "clear") == v) {
      ARRAY_LENGTH = 0;
      return 1;
    }//end if clear?

    if (strstr(v, "length") == v) {
      unsigned long a = argPtr ? std::stoul(argPtr, nullptr, 10 ) : ARRAY_LENGTH;
      if ( a > ARRAY_LENGTH) return ARRAY_LENGTH;
      ARRAY_LENGTH = a;
      return 1;
    }//end if length?

    if (strstr(v, "push") == v) {
      for (int i = 0; i < nsLATER::laterUtil::split_count ; i++) {
        if ( ARRAY_LENGTH < ARRAY_LIMIT ) ARRAY[ARRAY_LENGTH++] = std::stoul( nsLATER::laterUtil::splits[i], nullptr, 10 );
      }
      return 1;
    }//end if push?

    if (strstr(v, "reverse") == v) {
      std::reverse(ARRAY, ARRAY + ARRAY_LENGTH);
      return 1;
    }//end if reverse?

    if (strstr(v, "sort") == v) {
      std::sort(ARRAY, ARRAY + ARRAY_LENGTH);
      return 1;
    }//end if sort?


    //////////////////////////////////////////////////////////////////


    if (strstr(v, "filter") == v) {
      //std::sort(ARRAY, ARRAY + ARRAY_LENGTH);
      bool ok = false;
      char buff[32];
      int termLen;
      char * ptr = argPtr;

      for (int i = 0; i < ARRAY_LENGTH; i++) { // set all invalid elements to -1
        // make string with compare expression for each element:
        itoa(ARRAY[i], buff, 10);
        termLen = strlen(buff);
        buff[termLen] = ' ';
        strcpy(buff + termLen, ptr);
        //Serial.print("exppr:"); Serial.println(buff);
        ok = nsLATER::evalConditionalExpression(buff, scr);
        if (!ok) ARRAY[i] = -1;
      }

      int newLen = 0;
      int subStrart = 0;
      for (int i = 0; i < ARRAY_LENGTH; i++) { // remove -1 elements, preserving order

        if (ARRAY[i] == -1) {
          // find next non- -1    element, move to i
          for (int subi = (i + 1); subi < ARRAY_LENGTH; subi++) {
            if (subi < subStrart) subi = subStrart;
            if (ARRAY[subi] != -1) {
              ARRAY[i] = ARRAY[subi];
              subStrart = subi + 1;
              break;
            }//end if !-1
          }//next subi

        } else { //end if -1?
          newLen++;
        }
      } // next elm

      ARRAY_LENGTH = newLen;
      return 1;
    }//end if filter?


    if (strstr(v, "unshift") == v) {
      unsigned int toAdd = nsLATER::laterUtil::split_count;
      int newLen = ARRAY_LENGTH + toAdd;

      if (newLen > ARRAY_LIMIT) { // if array will become too long, cut down right side to make them fit
        ARRAY_LENGTH = newLen - ARRAY_LIMIT;
        newLen = ARRAY_LENGTH + toAdd;
      }

      int curs = ARRAY_LENGTH;
      int toMove = ARRAY_LENGTH + 1;

      // scootch over elements from a to length by toAdd slots:
      for (int i = 0; i < toMove; i++) ARRAY[newLen - i] = ARRAY[curs - i];

      // fill in new data
      for (int i = 0; i < toAdd; i++) ARRAY[i] = std::stoul( nsLATER::laterUtil::splits[i], nullptr, 10 );
      ARRAY_LENGTH += toAdd;
      return 1;
    }//end if unshift?

    if (strstr(v, "fill") == v || strstr(v, "splice") == v) {
      unsigned long a = 0, b = 0, c = 0;
      unsigned int arity = nsLATER::laterUtil::split_count;
      if (arity > 0) a = std::stoul( nsLATER::laterUtil::splits[0], nullptr, 10 );
      if (arity > 1) b = std::stoul( nsLATER::laterUtil::splits[1], nullptr, 10 );
      if (arity > 2) c = std::stoul( nsLATER::laterUtil::splits[2], nullptr, 10 );

      if (strstr(v, "fill") == v ) {

        switch (arity) {
          case 0: return 0; break;
          case 1: // one argument given, fill entire array with value
            std::fill(ARRAY, ARRAY + ARRAY_LENGTH, a);
            break;
          case 2: // two arguments given: value, count, start at 0
            std::fill(ARRAY, ARRAY + b, a);
            break;
          case 3: // all 3 arguments given: value, count, start
            std::fill(ARRAY + c, ARRAY + c + b, a);
            break;
          default: return 0;
        }//end switch arity

      } else { // splice

        switch (arity) { // pos, toRem, data...
          case 0: case 1: return 0; break;
          case 2: // two arguments given, remove b slots at a
            if (ARRAY_LENGTH - a < b) b = ARRAY_LENGTH - a; // keep b within array bounds, (eg allow b=999 to chop)
            for (int i = a; i < ARRAY_LENGTH; i++) ARRAY[i] = ARRAY[i + b];
            ARRAY_LENGTH -= b; // same each step/permutation of splice arity
            break;

          default: //3+
            bool hasRemovals = b > 0;
            unsigned int toAdd = (nsLATER::laterUtil::split_count - 2);
            if (!hasRemovals) {
              int curs = ARRAY_LENGTH;
              int newLen = ARRAY_LENGTH + toAdd;
              int toMove = (ARRAY_LENGTH - a) + 1;

              // scootch over elements from a to length by toAdd slots:
              for (int i = 0; i < toMove; i++) ARRAY[newLen - i] = ARRAY[curs - i];

              // fill in new data
              for (int i = 0; i < toAdd; i++) ARRAY[i + a] = std::stoul( nsLATER::laterUtil::splits[i + 2], nullptr, 10 );
              ARRAY_LENGTH += toAdd;
              ARRAY_LENGTH -= b; // same each step/permutation of splice arity
            } else { // has removals
              // first remove at pos, like there was no new data

              if (ARRAY_LENGTH - a < b) b = ARRAY_LENGTH - a; // keep b within array bounds, (eg allow b=999 to chop)
              for (int i = a; i < ARRAY_LENGTH; i++) ARRAY[i] = ARRAY[i + b];
              ARRAY_LENGTH -= b; // same each step/permutation of splice arity

              // now just do same thing as arity=2, but don't adjust (shrink) length again
              int curs = ARRAY_LENGTH;
              int newLen = ARRAY_LENGTH + toAdd;
              int toMove = (ARRAY_LENGTH - a) + 1;

              // scootch over elements from a to length by toAdd slots:
              for (int i = 0; i < toMove; i++) ARRAY[newLen - i] = ARRAY[curs - i];

              // fill in new data
              for (int i = 0; i < toAdd; i++) ARRAY[i + a] = std::stoul( nsLATER::laterUtil::splits[i + 2], nullptr, 10 );
              ARRAY_LENGTH += toAdd;
            }//end if hasRemovals?
            break;

        }//end switch arity

        return 1;
      }//end if fill or splice?
    }//end if fill/splice
    return 1;
  });//end array command


  // END OF LATER ARRAY ADDON
  ///////////////////////////////////

#endif


}


#endif
```
