#ifndef later_h
#define later_h

#include "FS.h"

//#include <algorithm>

#ifdef LATER_UART_PORT
#define LATER_PORT LATER_UART_PORT
#else
#define LATER_PORT Serial
#endif

// now define print and println commands
#define LATER_PRINT(s) LATER_PORT.print(s)
#define LATER_PRINTLN(s) LATER_PORT.println(s)

/*
#if LATER_UART_PORT == NULL
#undef LATER_PRINT
#define LATER_PRINT(s)
#undef LATER_PRINTLN
#define LATER_PRINTLN(s)
#endif
*/	

#ifndef LATER_INSTANCES
#define LATER_INSTANCES 4
#endif

#ifndef LATER_PROGRAM_SIZE
#define LATER_PROGRAM_SIZE 1024
#endif

#ifndef LATER_LOG_SIZE
#define LATER_LOG_SIZE 4096
#endif

#ifndef LATER_PIXEL_NAME
#define LATER_PIXEL_NAME strip
#endif

#ifndef LATER_SERVER_NAME
#define LATER_SERVER_NAME server
#endif

#define LATER_PLAIN "text/plain"
#define LATER_CORS "Access-Control-Allow-Origin"


#ifdef WEBSERVER_H 
#define ESP8266WEBSERVER_H
#endif

#ifndef DANOS_EDITOR_URL
#define DANOS_EDITOR_URL "https://pagedemos.com/later/js/"
#endif


















#include <Arduino.h>
#include <map>

namespace nsLATER {



////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#line 1 "danscript.ino"
//@TAKE
#include <map>

struct cmp_str { // converts pointers into stirng values to find terms in map and let map balance red/black tree of K:V pairs
  bool operator()(char const *a, char const *b) const  {
    return strcmp(a, b) < 0;
  }
};
#ifdef WEBSERVER_H
#define ESP8266WEBSERVER_H
#endif
char TEMPLATE_BUFFER[48];
char TEMPLATE_KEY_BUFF[16];
//>> var names can consit of the following letters and numbers:
const char VARCHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_$1234567890.";
const char VARLIST[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"; // -65 to get slot 0-64, 8 slots in middle aren't used for 57 or so slots
const char CMDCHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()_+=-`~,.<>{}[];:'?/|"; // 92 chars
//<<
std::map<std::string,  long> LATER_VAR_NAMES[LATER_INSTANCES];
unsigned long VAR_NAME_COUNT[LATER_INSTANCES];

std::map<std::string, char *> DEFINES[LATER_INSTANCES];

const std::string RETURN_SYMBOL = "$return";
char setRunLog[LATER_LOG_SIZE] = "";
/*
  off= pin, sub
  Event argument "object"
  {E.ms} - ms when event occoured
  {E.pin}
  {E.value}

*/
//>> public types, used to make callbacks for commands+function, run backups or mods, etc
typedef struct LATER_EVENT {
  int pin = -1; // which pin to watch?
  // char name[16]; // name of subroutine to run when true
  unsigned long value; // pin value, maybe other data
  unsigned long ms; // timer when event happened
  unsigned long msNext; // timer when event happened
} LATER_EVENT;
LATER_EVENT EVENT[3];

typedef struct LATER_OPTIONS {
  bool debug; // print debug info to the console?
  bool perf; // print perf info to the console?
  bool strict; // disable legacy handlers and slower features?
  bool persist; // keep the script in ram?
} LATER_OPTIONS;

// 37800b free before bumping up lines from 64 to 96
// 35644

typedef struct LATER_LINE {
  int start, stop; // position of line in raw program[] buffer
  byte data, len, flags, exit; //line nums/size, exit line num, flag bits: {hasTemplate,hasVar,hasStatic,hasParens}
  char cmd; // shorthand command code
} LATER_LINE;

typedef struct LATER_ENVIRON {
  byte index; // which numer of SCRIPTS are we?
  long i; // what line are we at?
  LATER_LINE lines[128]; // holds meta about each line
  char program[LATER_PROGRAM_SIZE]; // program code string buffer
  long lineCount = 0; // how many parsed code lines are in the program?
  unsigned long loadedAt, startedAt, runs, duration, runTime, parseTime, reads, writes, interval; // ms timestamp at program start, how many executions?
  char fileName[32]; // file name of the program

  long forTop[4], forStep[4], forIndex[4], forStart[4], forEnd[4], forLevel = 0; // int_fast16_t

  long switchExit; // tracking switch statement cases
  char switchTerm[16]; // term used to lexically match case statements buffer
  char contentType[32]; // used for http response, set by #type= "macro"

  unsigned long intervals[8] = {0, 0, 0, 0,   0, 0, 0, 0}; // ms timer snapshots for repeating sections ; interval command
  byte intervalCount = 0; // how many intervals are active?
  unsigned long VARS[57];// holds variable values
  unsigned long subArgs[8];
  byte subReturnLine; // for calling subs, calling line goes here
  int status; // for returning web call success, errs, etc
  byte resumeLineNumber; // for freeze, where to thaw?
  // bool persist; // unload after execution if false;
  unsigned long resumeMillis; // for freeze, when to thaw?
  unsigned long timer; // for tracking timer commands
  byte arity; // how many args passed
  byte startLineNumber = 0; // over-rides the default of 0 as top line, to allow simple+effecient run-once code via start command
  byte exitLineNumber = 0; // over-rides the default last line from the real last line. can be jumped over in unload() to allow cleanup routine
  unsigned long subReturnValue = 99; // stores var slot for call command to recieve value
  bool calledFromWeb; // switches print from Serial to server
  LATER_OPTIONS options;
} LATER_ENVIRON;
//<<

LATER_ENVIRON SCRIPTS[LATER_INSTANCES]; // dd666
// cdefnoqrstux
// left: YA py
// char cmd name constants
#define LATER_analogWrite 'w'
#define LATER_assert 'k'
#define LATER_break 'B'
#define LATER_call 'h'
#define LATER_case 'K'
#define LATER_cgi 'j'
#define LATER_clear 'C'
#define LATER_continue 'O'
#define LATER_default 'U'
#define LATER_delete 'e'
#define LATER_digitalWrite 'G'
#define LATER_do 'D'
#define LATER_else 'E'
#define LATER_end 'X'
#define LATER_endsub 'Q'
#define LATER_exit 'x'
#define LATER_fi 'F'
#define LATER_for 'R'
#define LATER_freeze 'f'
#define LATER_global 'm'
#define LATER_gosub 'Y'
#define LATER_grad 'a'
#define LATER_if 'I'
#define LATER_iif 'b'
#define LATER_interval 'i'
#define LATER_log 'L'
#define LATER_loop 'P'
#define LATER_next 'N'
#define LATER_noop 'n'
#define LATER_on 'v'
#define LATER_option 'c'
#define LATER_ping 'H'
#define LATER_pinMode 'M'
#define LATER_pixel 'A'
#define LATER_print 'T'
#define LATER_println 'l'
#define LATER_render 'r'
#define LATER_return 'Z'
#define LATER_rotate 'o'
#define LATER_run 'u'
#define LATER_sleep 'S'
#define LATER_solid 's'
#define LATER_start 'z'
#define LATER_static 'd'
#define LATER_store 'g'
#define LATER_sub 'J'
#define LATER_switch 'W'
#define LATER_timer 't'
#define LATER_unload 'q'
#define LATER_var 'V'
//for the template engine:
// container for user-defined program variables
std::map<const char *,  char, cmp_str> LATER_CMDS = {
  {"_", 'l'},
  {"__", 'l'},
  {"analogWrite", 'w'},
  {"assert", 'k'},
  {"attachInterrupt", 'v'}, // alias: on
  {"break", 'B'},
  {"call", 'h'},
  {"case", 'K'},
  {"cgi", 'j'},
  {"clear", 'C'},
  {"continue", 'O'},
  {"default", 'U'},
  {"define", 'd'},
  {"delete", 'e'},
  {"del", 'e'},
  {"delay", 'S'},// alias: sleep
  {"digitalWrite", 'G'},
  {"do", 'D'},
  {"else", 'E'},
  {"end", 'X'},
  {"endsub", 'Q'},
  {"erase", 'e'},// alias: delete
  {"exit", 'x'},
  {"fetch", 'H'}, //alias: ping
  {"fi", 'F'},
  {"finish", 'x'},
  {"for", 'R'},
  {"freeze", 'f'},
  {"global", 'm'},
  {"gosub", 'Y'},
  {"gpio", 'G'},// alias: digitalWrite
  {"grad", 'a'},
  {"if", 'I'},
  {"iif", 'b'},
  {"int", 'V'}, // alias: var
  {"interval", 'i'},
  {"log", 'L'},
  {"loop", 'P'},
  {"next", 'N'},
  {"noop", 'n'},
  {"on", 'v'},
  {"option", 'c'},
  {"ping", 'H'},
  {"pinMode", 'M'},
  {"print", 'T'},
  {"println", 'l'},
  {"pixel", 'A'},
  {"render", 'r'},
  {"return", 'Z'},
  {"rotate", 'o'},
  {"run", 'u'},
  {"set", 'G'},// alias: digitalWrite
  {"show", 'r'},
  {"sleep", 'S'},
  {"solid", 's'},
  {"start", 'z'},
  {"static", 'd'},
  {"store", 'g'},
  {"sub", 'J'},
  {"switch", 'W'},
  {"timer", 't'},
  {"unlink", 'e'},// alias: delete
  {"unload", 'q'},
  {"var", 'V'},
  {"wend", 'P'},// alias: loop
  {"write", 'G'}// alias: digitalWrite
};
//>> for defining custom commands and expression handlers:
// for addCommand:
#define COMMAND(expr) { [](char * value, LATER_LINE * line, LATER_ENVIRON * script )->bool { expr  ;}}

// for addFunction: pass function body using a,b,c parameters
#define FUNCTION(expr) { [](unsigned long a=0, unsigned long b=0, unsigned long c=0)->unsigned long { expr ;}}

// supports the auto end point recording and simplified http path/handler
#ifdef ESP8266WEBSERVER_H
#define SUB_PATH(_key, _expr) server.on("/" #_key, _expr); server.on("/" #_key "/", _expr);PATHS["/" #_key]=#_expr
#endif
//<<
// used inline in intitial expression function and template libs
#define RAWFUNC(key,expr) { key, [](unsigned long a=0, unsigned long b=0, unsigned long c=0)->unsigned long {return expr;}}
#define REPRAW(key,expr) { key, []()->unsigned long {return expr;}}
#define TEMPLATE(expr) []()->unsigned long {return expr;}

unsigned long randomReg();
#line 387 "danscript.ino"
unsigned long clamp(int a);
#line 458 "danscript.ino"
LATER_ENVIRON* getCurrent();
#line 551 "commands.ino"
template <class text>void uniPrintln(text content);
#line 564 "commands.ino"
template <class text>void uniPrint(text content);
#line 724 "commands.ino"
void loadStoredValuesForStore();
#line 31 "config.ino"
void APPLY_CONFIG();
#line 37 "config.ino"
void handleConfigInterface();
#line 60 "config.ino"
void handleConfigLang();
#line 82 "config.ino"
byte setConfig(String key, String value);
#line 97 "config.ino"
void handleConfig();
#line 110 "config.ino"
void loadConfig();
#line 153 "config.ino"
void saveConfig();
#line 4 "core.ino"
unsigned long Number( const char * str, const unsigned long * VARS );
#line 21 "core.ino"
char * getVarName(char * longName, int scriptIndex);
#line 31 "core.ino"
char getVarNameNumber(char * longName, int scriptIndex);
#line 38 "core.ino"
int loadScript(String filename);
#line 439 "core.ino"
void removeDoubleLines(char * buff);
#line 449 "core.ino"
void removeMultiLineComments(char * buff);
#line 465 "core.ino"
void replaceVarNames(char * line, int scriptIndex);
#line 483 "core.ino"
void autoEqualsInsert(char * line);
#line 516 "core.ino"
void buildExitPoints( LATER_ENVIRON * SCRIPT );
#line 758 "core.ino"
void processVariableExpressions(char * line, unsigned long * VARS);
#line 779 "core.ino"
bool processArray(char * line, unsigned long * VARS, int varSlot);
#line 943 "core.ino"
bool evalMath(char * s, LATER_ENVIRON * script, int DMA);
#line 1151 "core.ino"
bool evalConditionalExpression(char * string_condition, LATER_ENVIRON * s);
#line 1218 "core.ino"
void popHttpResponse();
#line 1231 "core.ino"
bool processResponseEmbeds(char * line, LATER_ENVIRON * s);
#line 1382 "core.ino"
void processStringFormats(char* s);
#line 1511 "core.ino"
void handleEval();
#line 1524 "core.ino"
void handleDump();
#line 1752 "core.ino"
void runScript();
#line 2516 "core.ino"
void finishRun(LATER_ENVIRON * s);
#line 34 "http.ino"
void handleGenericHttpRun(String fn);
#line 71 "http.ino"
void handleAPI();
#line 86 "http.ino"
void handleDelete();
#line 109 "http.ino"
void bindServerMethods();
#line 168 "http.ino"
void handleLS();
#line 247 "http.ino"
void handleEditor();
#line 278 "http.ino"
String getContentType(String filename);
#line 300 "http.ino"
bool handleFileRead(String path);
#line 373 "http.ino"
void handleFileUpload();
#line 413 "http.ino"
void handleFileList();
#line 520 "http.ino"
void handleUnload();
#line 533 "http.ino"
void handleRun();
#line 596 "http.ino"
void handleLog();
#line 776 "http.ino"
void handleCommandList();
#line 814 "http.ino"
void handleStore();
#line 850 "http.ino"
void addJSON(char * buff, const char * key, unsigned long value);
#line 858 "http.ino"
void addJSON(char * buff, const char * key, const char * value);
#line 867 "http.ino"
void backtrack(char * buff);
#line 871 "http.ino"
void handleScripts();
#line 944 "http.ino"
void handleBench();
#line 5 "mod.ino"
int HTTPRequest(char * url);
#line 146 "templates.ino"
unsigned long processTemplateExpressionsNumber(const char * line);
#line 178 "templates.ino"
void processTemplateExpressions2(char * line, LATER_ENVIRON * s);
#line 387 "danscript.ino"
unsigned long  clamp(int a) {
  return a > 0 ? (a < 255 ? a : 255) : 0;
}

std::map < const char *, unsigned long(*)(unsigned long, unsigned long, unsigned long), cmp_str > FUNCS = {
  RAWFUNC("MIN", min(a, b)),
  RAWFUNC("MAX", max(a, b)),
  RAWFUNC("SQRT", sqrt(a)),
  RAWFUNC("CBRT", cbrt(a)),
  RAWFUNC("POW", pow(a, b)),
  { "MAP", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {
      float rate = (float)b / (float)c;
      return rate * (float) a;
    }
  },

#ifdef ADAFRUIT_NEOPIXEL_H
  RAWFUNC("RGB", Adafruit_NeoPixel::Color(a, b, c)),
  RAWFUNC("CRGB", Adafruit_NeoPixel::Color(clamp(a), clamp(b), clamp(c))),
  RAWFUNC("HSV", Adafruit_NeoPixel::ColorHSV(a, b, c)),
#endif
  RAWFUNC("CSPRNG", ( (randomReg()) % ((a + 1) - b)) + b),
  RAWFUNC("PRNG", (rand() % ((a + 1) - b)) + b),
  {"SEED", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {srand(a); return 1;}}
};
//
//>> main public interface:
class LaterClass {
  public:
    bool debug = true;
    int scriptCount = LATER_INSTANCES;
    int currentScript = 0;
    int loadedScripts = 0;
    int lastEventSlot = -1;

    bool started = 0; // has .setup() been called yet?
    char httpResponseTextBuffer[1400] = {0};
    char * httpResponseText;

    unsigned long bootRam; // how big is heap on load

    void setup();
    void loop();
    LATER_ENVIRON * getByName(const char * fileName);
    LATER_ENVIRON *  load(const char * fileName);
    void init(const char * fileName);
    void unload(const char * fileName);
    void run(const char * fileName);
    void dump(const char * fileName);
    bool addCommand(const char * commandName, bool(*)(char *, LATER_LINE *, LATER_ENVIRON * s) ); // define a new command
    bool addFunction(const char * commandName, unsigned long(*)(unsigned long, unsigned long, unsigned long) );
    bool addTemplate(const char * key, unsigned long(*)() );

    std::map <char, bool(*)(char *, LATER_LINE *, LATER_ENVIRON *)> addons;

} Later ;
//<<
LATER_ENVIRON * getCurrent() {
  return &SCRIPTS[Later.currentScript];
} //end getCurrent()
unsigned long randomReg() {
#ifdef ESP8266
  return RANDOM_REG32;
#else
  return esp_random();
#endif
}
void LaterClass::setup() {

  started = true;

#ifdef ESP8266WEBSERVER_H
  bindServerMethods();
#endif
  bootRam = ESP.getFreeHeap();

  for (int i = 0; i < scriptCount; i++) {
    VAR_NAME_COUNT[i] = 0;
    SCRIPTS[i].index = i;
  }//next script

  loadStoredValuesForStore();

  if (debug) LATER_PRINTLN("Later - Setup()");
  /// this has to be added here so that it can use function prototype defined after the rest of the Functions
  Later.addFunction("DMA", FUNCTION( getCurrent()->VARS[a] = b; return b;  )); // using FUNCTION MACRO
  // run autoexec.bat if available
  if (SPIFFS.exists("/autoexec.bat")) {
    if (debug) LATER_PRINTLN("Later - Autoexec will run");
    run("/autoexec.bat");
    if (debug) LATER_PRINTLN("Later - Autoexec ran");
    unload("/autoexec.bat");
  }
}//end DS setup()
void LaterClass::loop() {


  unsigned long ms = millis();

  // look for interval processes:
  for (int i = 0; i < scriptCount; i++) {
    if (  (SCRIPTS[i].interval > 0) && (ms > SCRIPTS[i].resumeMillis) ) {
      run(SCRIPTS[i].fileName);
    }
  }//next i
  // look for frozen processes
  for (int i = 0; i < scriptCount; i++) {
    if (SCRIPTS[i].resumeMillis && (ms > SCRIPTS[i].resumeMillis) ) {
      run(SCRIPTS[i].fileName);
    }
  }//next i

}//end DS loop()
LATER_ENVIRON * LaterClass::getByName(const char * fileName) {
  int slot = -1;
  for (int i = 0; i < scriptCount; i++) {

    if ( SCRIPTS[i].lineCount &&  (!strcmp(fileName, SCRIPTS[i].fileName)) ) {
      slot = i;
      break;
    }
  }//next i
  if (slot == -1) return NULL;
  return &SCRIPTS[slot];
}//end getByName();
void LaterClass::init(const char * fileName) {
  LATER_ENVIRON * s = getByName(fileName);
  if (s) return;
}//end DS init()
void LaterClass::unload(const char * fileName) {
  LATER_ENVIRON * s = getByName(fileName);
  if (!s) return;

  // check here if linecount and lastline are the same, if not, run code after that exit point

  if (s->lineCount != s->exitLineNumber ) {
    int oldScript = Later.currentScript;
    Later.currentScript = s->index;

    s->resumeLineNumber = s->exitLineNumber + 1; // jump past normal exit
    s->exitLineNumber = 0; // don't stop until end
    runScript();
    Later.currentScript = oldScript;
  }//end if
  //remove script and reset options
  loadedScripts--;
  s->fileName[0] = '\0';
  memset ( s->program, '\0', LATER_PROGRAM_SIZE);
  s->i = 0;
  s->resumeMillis = 0;
  s->interval = 0;
  s->i = 0;
  s->startLineNumber = 0;
  s->resumeLineNumber = 0;
  s->exitLineNumber = 0;
  s->lineCount = 0;
  s->options.debug = 0;
  s->options.persist = 0;
  s->options.perf = 0;
  s->options.strict = 0;
  s->forLevel = 0;
  s->intervalCount = 0;
  s->duration = 0;
  //s->program[0] = '\0';
  strcpy(s->contentType, LATER_PLAIN);

  // reset any used VARs to zero
  for (int i = 0, mx = VAR_NAME_COUNT[s->index]; i < mx; i++) s->VARS[i] = 0;

  LATER_VAR_NAMES[s->index].clear();
  VAR_NAME_COUNT[s->index] = 0;
  if (debug) LATER_PRINTLN("Later - unloaded " + String(fileName));
}//end unload()
LATER_ENVIRON *  LaterClass::load(const char * fileName) {

  LATER_ENVIRON * s = getByName(fileName);
  if (s) return s;

  int rez = loadScript(fileName);
  if (!rez) {
    if (debug) LATER_PRINTLN("Later - load failed1: " + String(fileName));
    return NULL;
  }

  loadedScripts++;


  s = getByName(fileName);
  if (!s) {
    if (debug) LATER_PRINTLN("Later - load failed2: " + String(fileName));
    return NULL;
  }

  s->duration = 0;
  s->calledFromWeb = 0;
  s->runs = 0;
  s->resumeLineNumber = 0;
  if (debug) LATER_PRINTLN("Later - loaded " + String(fileName));
  return s;
}//end DS load()
void LaterClass::run(const char * fileName) {
  // find script in POOL, run, or load if not found;

  LATER_ENVIRON * s = getByName(fileName);

  if (!s) s =  load(fileName);     //s = getByName(fileName);
  if (!s) return;
  currentScript = s->index;
  s->timer = 0;
  runScript();
  if (!s->options.persist) unload(s->fileName);

}//end DS run()
bool LaterClass::addFunction(const char * commandName, unsigned long(* callBack)(unsigned long, unsigned long, unsigned long)   ) {
  if (started) {
    if (debug) LATER_PRINTLN("ERROR!  .addFunction() cannot be called after .setup()");
    return 0;
  }

  FUNCS[commandName] = callBack;
  return 1;
};
bool LaterClass::addCommand(const char * commandName, bool(*callBack)(char *, LATER_LINE *, LATER_ENVIRON *)  ) {

  if (started) {
    if (debug) LATER_PRINTLN("ERROR!  .addCommand() cannot be called after .setup()");
    return 0;
  }

  char possibleNames[92];
  strncpy(possibleNames, CMDCHARS, 91);
  possibleNames[91] = '\0';

  // loop through existing vars, remove cmd char from possible char list
  for (auto const & x : LATER_CMDS)   {
    char c = x.second;
    char * hit = strchr(possibleNames, c);
    if (hit) hit[0] = ' ';
  }//next command

  // now possibleNames is all spaces and unused chars, grab the first non-space:
  int charPos = strspn (possibleNames, " ");
  if (charPos > 90) return 0; // no more names
  const char cmdChar = possibleNames[charPos];
  LATER_PRINTLN("adding command [" + String(cmdChar) + ":" + String(commandName) + "] to known commands");
  // set command to that char
  LATER_CMDS[commandName] = cmdChar;
  addons[cmdChar] = callBack;
  return 1;
};//end addCommand()

//
//@TAKE

//demo ntc usage:

//demo dht usage:
/*  humidity = dht.readHumidity();          // Read humidity (percent)
  temp_f = dht.readTemperature(true);     // Read temperature as Fahrenheit
  if (isnan(humidity) || isnan(temp_f)) return;
*/
//http://192.168.0.91/set?p=16,OUTPUT&16=1&s=500&16=0&s=500&16=1

#line 1 "commands.ino"

namespace laterUtil {
char * splits[10];
int split_count;
int intFromHexChar(char c) {
  if (c < 58) return c - 48;
  return (c - 64) + 10;
}
bool isTheSame(char * data, const char * term) {
  if (data[0] != term[0]) return 0;
  return !strcmp(data, term);
}
void splitStringByChar(char* hay, char term) {
  char * ptr = hay;
  int i = 1;
  splits[0] = hay;
  while ( (ptr = strchr(ptr, term)) ) {
    char * p = ptr;
    splits[i++] = p + 1;
    ptr += 1;
  }//wend
  split_count = i;
}
char * copyUntilChar(char * str, char of) { // copyUntilChar("hello world", ' ') == "hello"
  char * endPtr = strchr(str, of);
  int len = endPtr - str;
  static char buff[48];
  if (!endPtr) return str;
  strncpy(buff, str, len);
  buff[len] = '\0';
  return buff;
}//end copyUntilChar()
char * trimRight(char * str) {
  for (int i = strlen(str) - 1 ; i > 0; i--) {
    if (isspace (str[i]) ) {
      str[i] = '\0';
    } else {
      break;
    }
  } // next
  return str;
}//end trimRight()
bool startsWith(char * hay, const char * needle) {
  return ! memcmp ( hay, needle, strlen(needle));
}
int indexOf(char * base, const char * term) {
  char * p = strstr(base, term);
  if (!p) return -1;
  return strlen(base) - strlen(p);
}//end indexOf
char * replace (char * str, const char * term, const char * rep) {

  char * start = strstr(str, term);
  if (!start) return str; //nothing to replace, return copy

  //char * result = str;
  unsigned int replen = strlen(rep),
               termlen = strlen(term);
  // if the length of the hit and rep is the same, we can just copy it out:
  if ( replen == termlen ) {
    strncpy(start, rep, replen);
    return str;
  }

  char buff[80];
  strcpy(buff, start + termlen);

  // char * str2 = buff;
  strncpy(start, rep, replen ); // copy rep into result
  strcpy(start + replen, buff); // copy tail from orig into result
  return str;

}//end replace()
//format bytes -boo switch out of strings
String formatBytes(size_t bytes) {
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  } else {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}
char * fileToBuff(String fileName) {
  static char buff[2048];
  char * p = buff;
  memset ( buff, '\0', 2048);

  if (!fileName.startsWith("/")) fileName = "/" + fileName;
  File file = SPIFFS.open(fileName, "r");
  if (file) {
    while (file.available()) {
      file.readBytes(p, 256);
      p += 256;
      //break;
      yield();
    }
    file.close();
  }
  return buff;
}//end fileToBuff()
char * fileToBuffInclude(String fileName) {
  static char buff[1024];
  char * p = buff;
  memset ( buff, '\0', 1024);

  if (!fileName.startsWith("/")) fileName = "/" + fileName;
  File file = SPIFFS.open(fileName, "r");
  if (file) {
    while (file.available()) {
      file.readBytes(p, 256);
      p += 256;
      //break;
      yield();
    }
    file.close();
  }
  return buff;
}//end fileToBuff()
bool buffToFile(String  fileName,  char * value, bool append) {
  //something is evil here dd666
  if (!fileName.startsWith("/")) fileName = "/" + fileName;
  File file5 = SPIFFS.open( fileName, append ? "a" : "w");
  if (file5) {
    file5.print(value);
    file5.close();
    return 1;
  }
  return 0;
}//end buffToFile()
#ifdef ADAFRUIT_NEOPIXEL_H
uint32_t parseColor(char * ptr, LATER_ENVIRON * s) {
  int colorLength, commaPos;
  uint32_t color;
  while (isspace(ptr[0])) ptr++; // trim left, maybe move to compilation stage, as optomization
  colorLength = strlen(ptr);


  if (ptr[0] == '#') { // #ABC or #abc or #AABBCC or #aabbcc
    if (colorLength == 4) {
      color = LATER_PIXEL_NAME.Color(intFromHexChar(toupper(ptr[1])) * 16, intFromHexChar(toupper(ptr[2])) * 16, intFromHexChar(toupper(ptr[3])) * 16);
    } else { // #AABBCC
      color =  strtoul(ptr + 1, NULL, 16);
    } // end color hex code handling
  } else { // number or r,g,b
    commaPos = laterUtil::indexOf(ptr, ",");
    if (commaPos > 0) {  // $r, $g, $b
      byte r, g, b;
      r = Number(ptr, s->VARS);
      ptr += commaPos + 1;
      g = Number(ptr, s->VARS);
      b = Number(strchr(ptr, ',') + 1, s->VARS);
      color = LATER_PIXEL_NAME.Color(r, g, b);
    } else { // no comma, just a big long
      color = Number(ptr, s->VARS); //strtoul(ptr, NULL, 10);
    }//end non-hex color handling
  }//end if
  return color;
}//end parseColor()
#endif
}//end namespace
namespace laterCMD {
void runPinMode(char * line) {
  char * v, *k;

  // need pin#, mode
  v = strchr(line, ',') + 1;
  while (v[0] == ' ') v++;
  char * v2 = strchr(v, ' ');
  if (v2) v2[0] = '\0';  // cleanup to strmatch
  k = laterUtil::copyUntilChar(line, ',');

  if (!strcmp(v, "OUTPUT")) {
    pinMode( atoi(k), OUTPUT );
    return;
  }
  if (!strcmp(v, "INPUT")) {
    pinMode( atoi(k), INPUT );
    return;
  }
  if (!strcmp(v, "INPUT_PULLUP")) {
    pinMode( atoi(k), INPUT_PULLUP );
    return;
  }


}//end runPinMode()
void runPortWrite (char * line, unsigned long * VARS, bool isDigital) {
  char * v, *k;
  v = strchr(line, ',') + 1;
  k = laterUtil::copyUntilChar(line, ',');
  if (isDigital) {
    digitalWrite(Number(k, VARS), Number(v, VARS));
  } else {
#ifdef ESP8266
    analogWrite(Number(k, VARS), Number(v, VARS));
#endif
  }
}//end runPortWrite()
void compositeLine(char * linebuff, LATER_ENVIRON * s) {
  replaceVarNames(linebuff, s->index);
  processTemplateExpressions2(linebuff, s);
  processVariableExpressions(linebuff, s->VARS);
  evalMath(linebuff, s, -1);
}//end compositeLine()

void runCGI(char * lb, LATER_ENVIRON * s) {
  char * buff = laterUtil::fileToBuff(String(lb));
  char * p = buff; //strchr(buff, '\n');
  int offset = 0;
  char * linebuff;

  while (p) {

    linebuff = laterUtil::copyUntilChar(p + offset, '\n');
    if (!offset) offset = 1;
    /*
        // composite line :
        replaceVarNames(linebuff, s->index);
        processTemplateExpressions2(linebuff, s);
        processVariableExpressions(linebuff, s->VARS);
        evalMath(linebuff, s, -1);
    */
    compositeLine(linebuff, s);
    uniPrintln(linebuff);
    p = strchr(p + 1, '\n');
  }//wend line
  // now process each line of the buffer:
}//end runCGI()

void runEval(char * lb, LATER_ENVIRON * s) {
  char * buff = lb; // laterUtil::fileToBuff(String(lb));
  char * p = buff; //strchr(buff, '\n');
  int offset = 0;
  char * linebuff;

  while (p) {
    linebuff = laterUtil::copyUntilChar(p + offset, '\n');
    if (!offset) offset = 1;
    compositeLine(linebuff, s);
    uniPrintln(linebuff);
    p = strchr(p + 1, '\n');
  }//wend line
  // now process each line of the buffer:
}//end runEval()

void runAssert(char * lb, LATER_LINE * l, LATER_ENVIRON * s) {
  //  four sections A OP B > COMMENT

  // lets just hand ls for now
  //can i just use parens for mathy ones? not really, and no equals

  unsigned long rez = Number(lb, s->VARS);
  uniPrint( rez ? "OK   - " : "FAIL - ");
  uniPrint(strstr(lb, "->") + 2);
  uniPrint(" :: ");

  if (!rez) {
    char * lp;
    char linebuff[80];
    lp = s->program + l->start;
    strncpy(linebuff, lp, l->len);
    linebuff[l->len] = '\0';
    lp = strstr(linebuff, "->");
    if (lp) lp[1] = '\0';
    uniPrintln(linebuff);
  } else {
    uniPrintln("-");
  }


}//end runAssert()

#ifdef ADAFRUIT_NEOPIXEL_H
int add(int a, int b) {
  return min(a + b, 255);
}

int subtract(int a, int b) {
  return max(b - a, 0);
}

int within(int range, int base) {
  int n = (randomReg() % (range * 2)) - range ;
  return min(255, max(base + n, 0));
}

int rndSubtract(int range, int base) {
  int n = randomReg() % range;
  return max(base - n, 0);
}
int rndAdd(int range, int base) {
  int n = randomReg() % range;
  return min(base + n, 255);
}
void runSetPixel(char * line, LATER_ENVIRON * s) {

  char * ptr = line;
  uint32_t color;
  int indPos = laterUtil::indexOf(line, "->"),
      commaPos = laterUtil::indexOf(line, ",") + 1,
      startPos = Number(line, s->VARS),
      howMany = 1;
  if (commaPos && commaPos < indPos) howMany =  Number(line + commaPos, s->VARS);

  ptr += indPos + 2;

  //  1,2->|#11,22,33
  // look for

  char flag = 0;
  if (strpbrk (ptr, "+-<>*&")) {
    flag = ptr[0];
    ptr++;
  }
  if (startPos + howMany >  LATER_PIXEL_NAME.numPixels()) return;

  color = laterUtil::parseColor(ptr, s);  // LATER_PRINTLN("pix color:" + String(color));
  // here we can apply shit like bright, avg, rnd, etc
  if (flag) {

    byte  r1 = (color >> 16) & 0xFF,
          g1 = (color >> 8) & 0xFF,
          b1 = color % 256;
    uint32_t colorOld;

    for (int i = startPos, mx = startPos + howMany; i < mx; i++) {

      colorOld = LATER_PIXEL_NAME.getPixelColor(i);

      byte r2 = (colorOld >> 16) & 0xFF,
           g2 = (colorOld >> 8) & 0xFF,
           b2 = colorOld % 256;

      switch (flag) {
        case '+':
          color = LATER_PIXEL_NAME.Color( add(r1, r2), add(g1, g2), add(b1, b2));
          break;

        case '-':
          color = LATER_PIXEL_NAME.Color( subtract(r1, r2), subtract(g1, g2), subtract(b1, b2));
          break;

        case '*':
          color = LATER_PIXEL_NAME.Color( within(r1, r2), within(g1, g2), within(b1, b2));
          break;

        case '>':
          color = LATER_PIXEL_NAME.Color( rndAdd(r1, r2), rndAdd(g1, g2), rndAdd(b1, b2));
          break;

        case '<':
          color = LATER_PIXEL_NAME.Color( rndSubtract(r1, r2), rndSubtract(g1, g2), rndSubtract(b1, b2));
          break;

        case '&':
          color = LATER_PIXEL_NAME.Color( (r1 + r2) / 2, (g1 + g2) / 2, (b1 + b2) / 2);
          break;
          //case '': break;
      }//end switch()

      LATER_PIXEL_NAME.fill(color, i, 1);

    }//next pixel
    return;
  }//end if flag?

  LATER_PIXEL_NAME.fill(color, startPos, howMany);

}//end setPixel()
void runRotate(long dist) {
  int mx = LATER_PIXEL_NAME.numPixels() - 1;
  uint16_t  i = 0;

  //scoot them by memorizing next, then moving last to next
  uint32_t last;
  last = LATER_PIXEL_NAME.getPixelColor( mx );
  for (i = mx; i > 0; i--)  LATER_PIXEL_NAME.setPixelColor( i, LATER_PIXEL_NAME.getPixelColor( i - 1 ));
  LATER_PIXEL_NAME.setPixelColor( 0, last );
} // edn runRotate()

void runGrad(char * line, LATER_ENVIRON * s) {
  char * ptr = line;
  uint32_t col, col2;
  int indPos = laterUtil::indexOf(line, "->"),
      commaPos = laterUtil::indexOf(line, ",") + 1,
      startPos = Number(line, s->VARS),
      howMany = LATER_PIXEL_NAME.numPixels();

  if (commaPos && commaPos < indPos) howMany =  Number(line + commaPos, s->VARS);

  ptr += indPos + 2;

  char * ptr2 = strchr(ptr, ',');
  ptr2[0] = '\0';
  col = laterUtil::parseColor(ptr, s);
  ptr2[0] = ',';
  ptr = strchr(ptr, ',');
  col2 = laterUtil::parseColor(ptr + 1, s);
  byte  r1 = (col >> 16) & 0xFF,
        g1 = (col >> 8) & 0xFF,
        b1 = col % 256,
        r2 = (col2 >> 16) & 0xFF,
        g2 = (col2 >> 8) & 0xFF,
        b2 = col2 % 256;

  float fhm = howMany,
        rd = (float)(r1 - r2) / fhm,
        gd = (float)(g1 - g2) / fhm,
        bd = (float)(b1 - b2) / fhm;

  LATER_PIXEL_NAME.setPixelColor(startPos, col); // set first one pure

  for (unsigned int i = 1, mx = howMany; i < mx; i++) {
    LATER_PIXEL_NAME.setPixelColor(startPos + i,
                                   r1 - (rd * i),
                                   g1 - (gd * i),
                                   b1 - (bd * i)
                                  );
  }//next i
  LATER_PIXEL_NAME.setPixelColor(startPos + howMany, col2);// set last one pure

}//end runGrad()
#endif
//end of neopixel handlers
void logMe(const char * line) {
  int max_size = LATER_LOG_SIZE - 1025;
  unsigned int log_len = strlen(setRunLog);
  unsigned int data_len = strlen(line) + 8;
  char buf[15] = {'\n'};

  if (  (log_len + data_len) >= LATER_LOG_SIZE ) { // too long
    memmove ( setRunLog, setRunLog + 1024, 1024 );
    setRunLog[max_size] = '\0';
  }//end if too long?

  ltoa(millis(), buf + 1, 10);
  data_len = strlen(buf);
  buf[data_len] = '\t';
  strncat(setRunLog, buf, data_len + 1);
  strcat(setRunLog, line);
}//end logsetlog()
}//end namespace laterCMD::
template <class text>
void uniPrintln(text content) {
  auto s = getCurrent();
  if (s->calledFromWeb) {
#ifdef ESP8266WEBSERVER_H
    server.sendContent(content);
    server.sendContent("\n");
#endif
  } else {
    LATER_PRINTLN(content);
  }
}//end uniPrintln()

template <class text>
void uniPrint(text content) {
  auto s = getCurrent();
  if (s->calledFromWeb) {
#ifdef ESP8266WEBSERVER_H
    server.sendContent(content);
#endif
  } else {
    LATER_PRINT(content);
  }
}//end uniPrint()
//>> storage class
typedef struct LATER_ITEM { // 28b per item
  unsigned long dt = 0;
  unsigned long value = 0;
  unsigned int ver = 0;
  char key[16] = {0};
} LATER_ITEM;

typedef struct LaterStore {
  String fileName = "/store.ini";
  LATER_ITEM items[24];
  unsigned long time = 0;
  int length = 0;

  int getIndex(const char * key);
  unsigned long get(const char * key);
  unsigned long match(const char * key);
  bool set(const char * key, unsigned long value);
  bool update(const char * key, unsigned long value);
  bool unset(const char * key);
  char * stringify(int index);
  bool save();
  bool load();
  bool loaded;
} LaterStore;
//<<

int LaterStore::getIndex(const char * key) {
  if (!loaded) load();
  for (int i = 0; i < length; i++) {
    if (strcmp(items[i].key, key) == 0) return i;
  }
  return -1;
}//end getIndex()

unsigned long LaterStore::get(const char * key) {
  int index = getIndex(key);
  if (index == -1) return NULL;
  return items[index].value;
}//end get()

unsigned long LaterStore::match(const char * key) {
  return 0;
}//end match()

bool LaterStore::set(const char * key, unsigned long value) {

  int index = getIndex(key);
  if (index == -1) index = length++;
  if (index > 23) return 0;
  items[index].value = value;
#ifdef NTP_DEFAULT_LOCAL_PORT
  items[index].dt = time = timeClient.getEpochTime();
#else
  items[index].dt = time = millis();
#endif

  items[index].ver++;
  strcpy(items[index].key, key);
  save();
  return 1;
}//end set()
bool LaterStore::update(const char * key, unsigned long value) { // same as set() but doesn't save
  int index = getIndex(key);
  if (index == -1) index = length++;
  if (index > 23) return 0;
  items[index].value = value;
#ifdef NTP_DEFAULT_LOCAL_PORT
  items[index].dt = time = timeClient.getEpochTime();
#else
  items[index].dt = time = millis();
#endif

  items[index].ver++;
  strcpy(items[index].key, key);
  return 1;
}//end update()
bool LaterStore::unset(const char * key) {
  int index = getIndex(key);
  if (index == -1) return 0;
  length--;
  items[index].value = 0;
  items[index].dt = 0;
  items[index].ver = 0;
  save();
  return 1;
}//end unset()

char * LaterStore::stringify(int index) {
  LATER_ITEM * it = &items[index];
  static char buffer[32];
  sprintf ( buffer, "%s\t%lu\t%d\t%lu", it->key, it->dt, it->ver, it->value );
  return buffer;
}//end stringify();
bool LaterStore::save() {
  File file = SPIFFS.open(fileName, "w");
  if (!file) return false;
  for (int i = 0; i < 24; i++) {
    LATER_ITEM * it = &items[i];
    if (it->ver < 1) continue;
    file.println(stringify(i));
  }
  file.print('\n');

  file.close();
  return 1;
}//end save()
bool LaterStore::load() {
  if (loaded) return 0;
  loaded = 1;

  File file = SPIFFS.open(fileName, "r");
  if (!file) return false;
  int index = 0;
  char line[32];

  while (file.available()) {
    strcpy(line, file.readStringUntil('\n').c_str());
    LATER_ITEM * it = &items[index++];
    sscanf ( line, "%s\t%lu\t%u\t%lu", it->key, &it->dt, &it->ver, &it->value );
  }//wend line
  length = index - 1;
  file.close();
  return 1;
}//end save()
//>> singleton sotrage instance
LaterStore LATER_STORE;
//<<
void loadStoredValuesForStore() {
  LATER_STORE.load();
}

#line 1 "config.ino"
//@TAKE

#line 1 "core.ino"
// core for danscript, the actual interpreter and stuff
unsigned long Number( const char * str, const unsigned long * VARS ) {
  //unsigned long theNumber;
  while (str[0] == ' ') str++; // fast left-side trim
  if (str[0] == '@' && str[2] == '_') {
    return  VARS[str[1] - 65];
  } else {
    if (str[0] == '{')
      return processTemplateExpressionsNumber(str);
    else
      return strtoul(str, NULL, 10); // atoi(str);
  }// end if var format?
  return 0; // failsafe
}//end Number()
char * getVarName(char * longName, int scriptIndex) {
  std::string strKey = longName; // use string for simpler lifetime management

  if (!LATER_VAR_NAMES[scriptIndex].count(strKey)) LATER_VAR_NAMES[scriptIndex][strKey] = VAR_NAME_COUNT[scriptIndex]++;
  static char buffer [4] = "@-_";
  buffer[1] = VARLIST[LATER_VAR_NAMES[scriptIndex][strKey]];
  return buffer;
}

char getVarNameNumber(char * longName, int scriptIndex) {
  std::string strKey = longName;
  if (!LATER_VAR_NAMES[scriptIndex].count(strKey)) LATER_VAR_NAMES[scriptIndex][strKey] = VAR_NAME_COUNT[scriptIndex]++;
  return VARLIST[LATER_VAR_NAMES[scriptIndex][strKey]] - 65;
}
int loadScript(String filename) { //dd666 make this a class method
  unsigned long st = micros();
  if (filename[0] != '/') filename = "/" + filename;
  char * fileBuff = laterUtil::fileToBuff(filename);
  while ( isspace(fileBuff[0])) fileBuff++; // trim left

  int slot = 0;
  for (; slot < LATER_INSTANCES; slot++) {
    if (SCRIPTS[slot].lineCount == 0) break;
  }
  LATER_ENVIRON * SCRIPT = &SCRIPTS[slot];
  SCRIPT->loadedAt = millis();
  SCRIPT->i = 0;
  strcpy(SCRIPT->fileName, filename.c_str());

  char * inc = strstr(fileBuff, "#include");
  while (inc) {
    char incLine[24];
    strncpy(incLine, inc, 23);

    size_t fnpos = strcspn(incLine, " =\"" );
    char * fnPtr = incLine + fnpos + 1;

    fnpos = strcspn(fnPtr, " \"\n" );
    fnPtr[fnpos] = '\0';
    char * incbuf = laterUtil::fileToBuffInclude(fnPtr);

    unsigned long inclen = strlen(incbuf);
    unsigned long tailpos = (inc - fileBuff) + strlen(incLine); // where include line orig ends

    memmove(
      fileBuff + tailpos + inclen - strlen(incLine) ,
      fileBuff + tailpos,
      2048 - (tailpos + inclen)
    );

    // now sandwich in the new include contents:
    memcpy(inc, incbuf, inclen);
    inc = strstr(fileBuff, "#include"); // WORKS!
  }//wend include?

  while (strstr(fileBuff, "__FILE__")) laterUtil::replace(fileBuff, "__FILE__", filename.c_str());// swap out "macro"

  char * contentType = strstr(fileBuff, "#type=");
  while (contentType) {
    strncpy(SCRIPT->contentType, contentType + 6, 31);
    size_t ctend = strcspn(SCRIPT->contentType, "\n ;\t");
    SCRIPT->contentType[ctend] = '\0';
    contentType[0] = '\'';
    contentType = strstr(fileBuff, "#type=");
  }//wend contentType

  //#define TABLE_SIZE 100
  char * dec = strstr(fileBuff, "#define=");
  if (dec) DEFINES[slot].clear();
  while (dec) {
    // wipe out define call in program text:
    dec[0] = '/';
    dec[1] = '/';

    dec = dec + 8; // skip over "define="...

    size_t defpos = strcspn(dec, " ");
    char * defValp = dec + defpos + 1;

    char decName[16];
    strncpy(decName, dec, defpos);
    decName[defpos] = '\0';

    DEFINES[slot][decName] = defValp;
    dec = strstr(fileBuff, "#define="); // grab next one (if any)
  }//wend define
  char clean[1024];
  char * outptr = clean;
  char * cleanptr = clean;

  removeDoubleLines(fileBuff);
  removeMultiLineComments(fileBuff);

  //    Parse program into lines
  char * lb = fileBuff; //strstr(buff, "\n");
  char line[80];
  //char lineCopy[80];
  char cmd[16];
  char macro[16];
  char macroRep[64];
  int lineCount = 0;
  int endpos = strcspn( fileBuff, "\n");
  int lineLen = 0;
  char rangeBuffer[64];
  char temp[12];
  bool isPrintBlock = 0;
  bool isStaticPrintBlock = 0;
  // build up lines:
  while (strlen(lb) > 1) {

    // copy program code into line buffer so we can mess it up
    strncpy( line, lb, endpos);
    line[endpos] = '\0';

    laterUtil::trimRight(line);

    if (strstr(line, "iif")) {
      int colpos =  strcspn( line, ":");
      if (colpos > 0 && line[colpos - 1] == ' ' && line[colpos + 1] == ' ') {
        endpos = colpos;
        line[colpos] = '\0';
        lb[colpos] = '\n';
        laterUtil::trimRight(line);
      }
    }
    lb += endpos + 1; // should endpos be re-calced?

    // trim front of line:
    while (isblank(lb[0])) lb++;

    endpos = strcspn( lb, "\n");
    // do stuff with now-trimmed line, then copy it to clean, if needed

    // remove comments -- needs to chill a bit for later, check if print, log, fetch, etc.
    int commentPos = laterUtil::indexOf(line, "//");
    if (commentPos > -1 ) {
      if (commentPos == 0) {
        line[0] = '\0';
      } else {
        int cmdLen = strcspn(line, " =");
        strncpy(cmd, line, cmdLen);
        cmd[cmdLen] = '\0';
        if (!strstr(",_,log,print,println,fetch,ping,timer,", cmd)) line[commentPos] = '\0'; // zap line at comment unless used by command
      }//end if not whole line comment?
    }//end if has comment?

    if (line[0] == '\'') line[0] = '\0'; // skip VB-style comment line, also used internally by multi-line comments to curtail buffer resizing

    laterUtil::trimRight(line);
    lineLen = strlen(line);
    if (lineLen) { // filter empty lines
      // look for any @macro usages first thing
      char * macroPtr = strchr(line, '@');
      while (macroPtr) {
        macroPtr[0] = '?'; // stop same re-find
        size_t macroNameLen = 1;
        for (macroNameLen = 1; macroNameLen < 16; macroNameLen++) {
          if (!isalnum(macroPtr[macroNameLen])) break;
        }

        strncpy(macro, macroPtr, macroNameLen);
        macro[macroNameLen] = '\0';

        char * macroBuffPtr = macro + 1;
        char * macroRepPtr = DEFINES[slot][macroBuffPtr];
        // check GET params for match if no pre-defined macro exists under the name:
        if (!macroRepPtr) macroRepPtr = (char *)server.arg(macroBuffPtr).c_str();

        if (macroRepPtr) {
          size_t macroRepLen = strcspn(macroRepPtr, "\n");

          // cleanup optional semi delimiter on macro names:
          if (macroPtr[macroNameLen] == ';') {
            macro[macroNameLen] = ';';
            macro[macroNameLen + 1] = '\0';
          }
          strncpy(macroRep, macroRepPtr, macroRepLen);
          macroRep[macroRepLen] = '\0';
          laterUtil::trimRight(macroRep);
          laterUtil::replace(line, macro, macroRep);
        }//end if

        macroPtr = strchr(line, '@');
      }//end if macro?

      // inject var= into plain var declarations; $x=1 into var=$x=1
      if (line[0] == '$') {
        if ( strchr(line, '{') && strchr(line, ':') && line[lineLen - 1] == '}') {
          laterUtil::replace(line, "$", "define=$");
        } else {
          laterUtil::replace(line, "$", "var=$");
        }

        laterUtil::replace(line, " =", "=");
        laterUtil::replace(line, "= ", "=");
        lineLen = strlen(line);
      }//end if plain syntax var declaration line?

      //replace range operators with csv ints within the range bounds
      char * rangePtr = strstr(line, "..");
      while (rangePtr) {
        //rangePtr[0]=' ';
        //rangePtr[1]=' ';

        // find first, last number
        int endCap = Number(rangePtr + 2, SCRIPT->VARS);

        // track backwards to find base range start:
        for (int i = 0; i < 10; i++) {
          rangePtr--;
          if (!isdigit(rangePtr[0])) {
            rangePtr++;
            break;
          }
        }
        int startCap = Number(rangePtr, SCRIPT->VARS) + 1;
        rangeBuffer[0] = ',';
        memset(rangeBuffer + 1, 0, 48);

        if ( endCap == startCap) endCap++;

        if ( endCap > startCap) {
          for (int i = startCap; i < endCap; i++) {
            itoa(i, temp, 10);
            strcat(rangeBuffer, temp);
            strcat(rangeBuffer, ",");
          }
        } else {
          for (int i = startCap - 2; i > endCap ; i--) {
            itoa(i, temp, 10);
            strcat(rangeBuffer, temp);
            strcat(rangeBuffer, ",");
          }
        }

        laterUtil::replace(line, "..", rangeBuffer);
        rangePtr = strstr(line, "..");

      }//wend range symbols

      if (line[0] == '&' && line[1] == 'R' ) { //&& startsWith(line, "&RESPONSE->")) {
        laterUtil::replace(line, "&RESPONSE->", "res=&RESPONSE->");
        lineLen = strlen(line);
      }//end if plain syntax var declaration line?

      // } to end subs
      if (line[0] == '}') {
        laterUtil::replace(line, "}", "endsub=}");
        lineLen = strlen(line);
      }//end if close sub brace?

      // allow void calls to optionally have an empty parens:
      laterUtil::replace(line, "()", "");

      // handle ends:
      if (laterUtil::startsWith(line, "end")) {
        laterUtil::replace(line, "end sub", "endsub=}");
        laterUtil::replace(line, "end if", "fi=end if");
        laterUtil::replace(line, "end do", "loop=loop");
        laterUtil::replace(line, "end switch", "end=end switch");
      }//end if end

      if (line[0] == '<' && line[1] == '?') {
        isPrintBlock = 1;
        if (line[2] == '!') {
          line[2] = ' ';
          isStaticPrintBlock = 1;
        }
        line[0] = '_';
        line[1] = '=';
        continue;
      }

      if (line[0] == '?' && line[1] == '>') {
        isPrintBlock = 0;
        line[0] = '_';
        line[1] = '=';
        isStaticPrintBlock = 0;
        continue;
      }

      if (!isPrintBlock) autoEqualsInsert(line);
      replaceVarNames(line, SCRIPT->index);
      lineLen = strlen(line);

      ///////////////////////////////
      // deduce command:

      int cmdPos = laterUtil::indexOf(line, "=");
      if (cmdPos < 0)cmdPos = 0;
      strncpy(cmd, line, cmdPos);
      cmd[cmdPos] = '\0';
      char cmdChar = LATER_CMDS[cmd];

      // cleanup value after command:
      char * linePtr = line;
      linePtr += cmdPos + 1;
      if (!isPrintBlock) {
        while (linePtr[0] == ' ')linePtr++;

        if (linePtr[0] == '=') {
          linePtr++;
          while (linePtr[0] == ' ')linePtr++;
        }

      } else {
        linePtr = line;
        cmdChar = LATER_println;
      }
      lineLen = strlen(linePtr);

      ///////////////////////////////////////
      // FLAGS: set byte flag based on the value
      // b2         b1      b1
      // hasParens, hasVar, hasTemplate
      byte flag = 0;

      //////////  %templates% ? LSB
      char * tempPtr = strchr(linePtr, '{'); // look for opening template expression
      if (tempPtr && tempPtr[1] != ' ' && strchr(tempPtr + 1, '}') && !isStaticPrintBlock) flag += 1; // also has later close template delim
      //////////  $vars ? 2s
      // look for var usage, minding var commands themselves
      if (cmdChar == 'V' || cmdChar == LATER_static) { // look only after first equal for this
        if (strchr(strchr(linePtr, '='), '@')) flag += 2;// vars after assign
      } else {
        if (strchr(linePtr, '@')) flag += 2;// vars
      }

      if (strchr(linePtr, '(') && strchr(linePtr, ')') && !isStaticPrintBlock ) flag += 4;
      //////////  [x,y][arrays] ?  8s
      if (strstr(linePtr, "][") && !isStaticPrintBlock ) flag += 8;

#ifdef ESP8266HTTPClient_H_
      //////////  &RESPONSE usage ?  32s
      if (strstr(linePtr, "&RESPONSE->") && !isStaticPrintBlock) flag += 32;
#endif

      ////////// output ?  16s - interpolate var and %templates% in code line itself?

      if (cmdChar == LATER_log || cmdChar == LATER_switch || cmdChar == LATER_print || cmdChar == LATER_println || cmdChar == LATER_ping || cmdChar == LATER_timer || cmdChar == LATER_assert || cmdChar == LATER_run || Later.addons[cmdChar]   ) {
        flag += 16;
      } else { // don't need whitespace in any other command, right. asume and let's try iy
        // collapse whitespace here

        if ( (!isPrintBlock) && strchr(line, ' ') && (cmdChar != LATER_gosub) && (cmdChar != LATER_call) && (cmdChar != LATER_interval)  && (cmdChar != LATER_option) && (cmdChar != LATER_var) && (!strstr(linePtr, "][")) &&  (!Later.addons[cmdChar])  ) {

          while (strchr(linePtr, ' ')) laterUtil::replace(linePtr, " ", "");
          lineLen = strlen(linePtr);
        }
      }//end if non-output command?
      // populate script line object with accumulated data:
      LATER_LINE * sLine = &SCRIPT->lines[lineCount];
      sLine->len = lineLen; // how many chars is line?
      sLine->start = (outptr - cleanptr); // first line byte in clean buffer
      sLine->stop  = (outptr - cleanptr) + lineLen;// last line byte in clean buffer
      sLine->cmd = cmdChar;
      SCRIPT->lines[lineCount].flags = flag;

      // copy to clean:
      strncpy (outptr, linePtr, lineLen );
      outptr[lineLen] = '\n';
      outptr += lineLen + 1;

      if (lineCount++ > 128) break; // failsafe here, remove for prod?
    }//end if line not empty?
  } // wend endpos > 0

  outptr[0] = '\0';

  // move clean buffer to script object
  strcpy(SCRIPT->program, clean);

  // populate SCRIPT object with parsed program meta and data:
  SCRIPT->lineCount = lineCount ;
  SCRIPT->forTop[0] = -1;
  SCRIPT->runs = 0;

  buildExitPoints(SCRIPT);
  SCRIPT->parseTime = micros() - st;
  return 1;
}//end loadScript()
void removeDoubleLines(char * buff) {
  // replace double lines with single, repeat if needed
  char * start = strstr(buff, "\n\n");
  while (start) {
    start[0] = ' '; // turn first linebreak into plain space )it gets trimmed later)
    start = strstr(buff, "\n\n");
  }
}//end removeDoubleLines()
void removeMultiLineComments(char * buff) { // remove multi line comments by turning span into single-line comments w/o re-sizing buffer
  int mlcPos = laterUtil::indexOf(buff, "/*");
  if (mlcPos > -1) {
    // find next */
    char * cmtPtr = buff + mlcPos;
    int mlcEndPos = laterUtil::indexOf(cmtPtr, "*/");
    if (mlcEndPos > -1) {
      for (int i = 0; i < mlcEndPos; i++) if (cmtPtr[i] == '\n') cmtPtr[i + 1] = '\''; // insert single-line comment after line breaks
      cmtPtr[1] = '/';
      cmtPtr[mlcEndPos] = ' ';
      cmtPtr[mlcEndPos + 1] = ' ';
    }//end if closing comment?
  }//end if multi-line comment?
}
void replaceVarNames(char * line, int scriptIndex) { // turns $fancyName into @a_, @b_, etc...
  char * varPos = strchr(line, '$');
  while (varPos) {
    int len = strspn(varPos, VARCHARS);
    char varname[32];
    char newname[7];

    strncpy(varname, varPos, len);
    varname[len] = '\0';

    strcpy(newname, getVarName(varname, scriptIndex));
    laterUtil::replace (line, varname, newname);

    varPos = strchr(line, '$');
  }//end if var declaration?
}//end replaceVarNames()
void autoEqualsInsert (char * line) { // inserts '=' into any line not having one after the command (first "word" in line)
  int cmdLen = strspn (line, VARLIST);
  int valPos = cmdLen;
  char c = line[valPos];
  if (c == '=') return; // equals right after command name, no prob whatsoever

  while (line[valPos] == ' ') valPos++;
  c = line[valPos];

  if (c == '=') {// space after cmd, then an equal
    line[cmdLen] = '=';
    line[valPos] = ' ';
    return;
  }

  if (valPos > cmdLen) {//space after cmd, then a non-equal
    line[cmdLen] = '=';
    return;
  }

  if (valPos == cmdLen) { // empty command like render
    line[valPos] = '=';
    line[valPos + 1] = '0';
    line[valPos + 2] = '0';
    line[valPos + 3] = '\0';
    return;
  }

}//end autoEqualsInsert()
void buildExitPoints( LATER_ENVIRON * SCRIPT  ) { // scan and calculate exit points for commands that jump up/down
  auto * whole = SCRIPT->lines;
  int mx = SCRIPT->lineCount;
  int ind, varCache;
  char * k, * v, * c;

  // compute Exit points for each line:
  for (int index = 0; index < mx; index++) {
    LATER_LINE * line = &whole[index];
    switch (line->cmd) {

      case LATER_if: // if
        for (int i = index + 1, need = 1; i < mx; i++) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_fi) need--;
          if (x->cmd == LATER_else) need--;
          if (x->cmd == LATER_if) need++;
          if (need == 0) {
            line->exit = i;
            break;
          }
        }
        break;

      case LATER_iif: // iif
        line->exit = index + 1;
        break;

      case LATER_else: // else
        for (int i = index + 1, need = 1; i < mx; i++) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_fi) need--;
          if (x->cmd == LATER_if) need++;
          if (x->cmd == LATER_else) need++;
          if (need == 0) {
            line->exit = i;
            break;
          }
        }
        break;

      case LATER_for: case LATER_continue:  //for
        for (int i = index + 1, need = 1; i < mx; i++) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_next) need--;
          if (x->cmd == LATER_for) need++;
          if (need == 0) {
            line->exit = i;
            break;
          }
        }
        ; break;

      case LATER_do: //do
        for (int i = index + 1, need = 1; i < mx; i++) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_loop) need--;
          if (need == 0) {
            line->exit = i;
            break;
          }
        }
        ; break;

      case LATER_switch: // switch
        for (int i = index + 1; i < mx; i++) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_end  ) { // end
            line->exit = i;
            break;
          }
        }
        ; break;

      case LATER_case: // case
        for (int i = index + 1; i < mx; i++) {
          LATER_LINE * x = &whole[i];
          if ( x->cmd == LATER_case || x->cmd == LATER_default || x->cmd == LATER_end  ) { // case, default, or end
            line->exit = i - 1;
            break;
          }
        }
        ; break;

      case LATER_break:  // break, exits do loop (not needed w/ case since there's no fall-through)
        for (int i = index + 1, need = 1; i < mx; i++) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_loop) need--;
          if (x->cmd == LATER_do) need++;
          if (need == 0) {
            line->exit = i + 1;
            break;
          }
        }
        break;
      /*
            case LATER_continue: // continue, for for or do loop
              for (int i = index - 1, need = 1; i > 0; i--) {
                LATER_LINE * x = &whole[i];
                if (x->cmd == LATER_next) need++;
                if (x->cmd == LATER_for) need--;
                if (x->cmd == LATER_do) need--;
                if (x->cmd == LATER_loop) need++;
                if (need == 0) {
                  line->exit = i - 1;
                  break;
                }
              }
              break;
      */

      case LATER_next: // next, go to for
        for (int i = index - 1, need = 1; i > 0; i--) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_next) need++;
          if (x->cmd == LATER_for) need--;
          if (need == 0) {
            line->exit = i;
            break;
          }
        }
        break;
      case LATER_loop: // looP
        for (int i = index - 1, need = 1; i > 0; i--) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_loop) need++;
          if (x->cmd == LATER_do) need--;
          if (need == 0) {
            line->exit = i - 1;
            break;
          }
        }
        break;

      case LATER_sub: case LATER_return: // subroutine
        for (int i = index + 1, need = 1; i < mx; i++) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_endsub) need--;
          if (need == 0) {
            line->exit = i;
            break;
          }
        }
        break;
      case LATER_gosub: case LATER_on: case LATER_interval: // sub finder by name
        k =  SCRIPT->program + line->start;
        varCache = 0;

        //cut in here and scoot k down if it's an on call instead of gosub
        if ( line->cmd == LATER_on) {
          k = strchr(k, ',') + 1; // find 1st comma, 2nd arg (sub name)
          while ( !isalnum(k[0]) )k++; // advance to subname start

          v = strchr(k, ','); // 3rd argument (event type)?
          if (v) {
            varCache = 1; // flag as spoilt with 3rd arg, or maybe used line.data, duh
            c = v;
            while ( !isalnum(v[0]) ) v++;
            // set line.data with type of interrupt
            if (!strncmp(v, "RISING", 6))  line->data = 1;
            if (!strncmp(v, "FALLING", 7)) line->data = 2;
            c[0] = '\0'; // chop off mode to match sub name
          }
          k =  strchr(SCRIPT->program + line->start, ',') + 1;
        }//end if on?

        // if it's an interval call instead of gosub, to set line.data to intervals count
        if (line->cmd == LATER_interval) line->data = SCRIPT->intervalCount++;

        v = k;
        while (isalnum(v[0]))v++;
        ind = v - k;
        for (int i = index - 1, z; i > 0; i--) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_sub) {
            v =  SCRIPT->program + x->start;
            z = strncmp(k, v, ind);
            if (!z) {
              line->exit = i;
              break;
            }
          }//end if sub dec line?
        }//next

        // cleanup injected null terminator
        if ( line->cmd == LATER_on && varCache) c[0] = ',';
        break;
      case LATER_call: // sub finder by name
        //varCache = 0;
        k =  SCRIPT->program + line->start;

        //cut in here and scoot k down past var anme and equal sign
        k = strchr(k, '=') + 1; // find 1st comma, 2nd arg (sub name)
        while ( !isalnum(k[0]) )k++; // advance to subname start
        v = k;
        //c = k;
        while ( isalnum(v[0]) ) v++; // v is end of sub name +1
        // backup char after sub name
        varCache = v[0];
        c = v;
        // cpount arguments, set line.data to it
        //line->data = ind;
        if (varCache == ' ' || varCache == ',') line->data = (v - (SCRIPT->program + line->start));
        v[0] = '\0'; // chop off at name
        ind = v - k; // length of sub name

        for (int i = index - 1, z; i > 0; i--) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_sub) {
            v =  SCRIPT->program + x->start;
            z = strncmp(k, v, ind);
            if (!z) {
              line->exit = i;
              c[0] = varCache;
              break;
            }
          }//end if sub dec line?
        }//next

        break;
    }//end switch()
  }//next line
}//end buildExitPoints()
void processVariableExpressions(char * line, unsigned long * VARS) {
  static char buff[16];
  static char varname[8];
  char * atPtr = strchr(line, '@');
  unsigned long val;

  while (atPtr) {
    long varSlot = atPtr[1] - 65;
    strncpy(varname, atPtr, 3);
    varname[3] = '\0';
    val = VARS[varSlot];

    laterUtil::replace (atPtr, varname, ltoa(val, buff, 10 )  );
    atPtr = strchr(atPtr + 1, '@');
  }//end if var declaration?

}//end processVariableExpressions()
bool processArray(char * line, unsigned long * VARS, int varSlot) {
  char * ptr  = strchr(line, '[');
  //

  char * assign = ptr;
  char delim = ',';
  // find delim between elements and index:
  char * indDelim = strstr(ptr, "][");
  if (!indDelim) return false;
  int elmSectionLength = indDelim - ptr;
  indDelim += 2;

  // cut in here to look for special access modifiers:
  //  [1,3,5][>4] == 5 comparison lookup
  //  [1,3,5][&3] == 1 addressof lookup

  char lookupModeFlag = 0;
  if (strspn (indDelim, "<>&") > 0) {
    //ptr++;

    lookupModeFlag = indDelim[0];
    indDelim++;

    // look for both options:

    bool isAddressCall =  (lookupModeFlag == '&');
    if (isAddressCall) {

      if (strspn (indDelim, "<>") == 1) {
        lookupModeFlag = indDelim[0];
        indDelim++;
        // ptr++;
      }//is a secondary compare being used?

    }//end if address call?

    unsigned int valueNeeded = Number(indDelim, VARS);


    // ratchet between commas, inclrementing ptr as needed
    unsigned int elmValue, elmsFound = 1;
    char dlm[2] = {delim};
    bool valid  = false;

    while (ptr != NULL) {
      ptr++;
      elmValue = Number(ptr, VARS);
      /*

          uniPrint("ptr:");
          uniPrintln(ptr);
          uniPrint("elmsFound:");
          uniPrintln(String(elmsFound).c_str());

          uniPrint("elmValue:");
          uniPrintln(String(elmValue).c_str());

      */

      switch (lookupModeFlag) {
        case '>': valid = elmValue > valueNeeded; break;
        case '<': valid = elmValue < valueNeeded; break;
        case '&': valid = elmValue == valueNeeded; break;
      }//end switch compare type

      if (valid) {
        if (varSlot > -1) {//DMA?

          if (!isAddressCall) elmsFound = elmValue;
          VARS[varSlot] = elmsFound;

          return true;
        }//dma?
        // no non-dma return,  yet

        break;
      }//end if valid?
      elmsFound++;
      ptr = strchr(ptr + 1, delim);  // skip commas until count == index
    }//wend comma segment

    if (varSlot > -1) {//DMA?
      VARS[varSlot] = 0;
      return true;
    }//dma?

  }//end if reverse lookup?
  unsigned int indexNeeded = Number(indDelim, VARS);

  if (ptr[1] == '&' && ptr[3] == ';') { // fixed width/custom delim flag?
    if ( isdigit(ptr[2]) ) {
      int width = ptr[2] - 48;
      ptr += 4;
      ptr += (width * indexNeeded);
      ptr[width] = '\0';
      if (varSlot > -1) {
        VARS[varSlot] = Number(ptr, VARS);
        return true;
      }
    } else {//end fixed width, begin custom delim
      delim = ptr[2];
      ptr += 3;
    }//end if
  }//end if static array or custom delim?
  // chop off index segment from elements, making last option look like a middle one to simplify element find routine below
  ptr[elmSectionLength] = delim;
  ptr[elmSectionLength + 1] = '\0';

  // ratchet between commas, inclrementing ptr as needed
  unsigned int elmLength, elmsFound = 0;
  char dlm[2] = {delim};

  while (ptr) {
    if (elmsFound++ == indexNeeded) {
      elmLength = strcspn (ptr + 1, dlm); //","); // this could be pointer math instead
      break;
    }
    ptr = strchr(ptr + 2, delim);  // skip commas until count == index
  }//wend comma segment
  if (ptr) {
    if (varSlot > -1) {//DMA?
      VARS[varSlot] = Number(ptr + 1, VARS);
      return true;
    }//dma?

    char * ending = strchr(indDelim, ']');
    char * ending2 = ending + 1;
    int bonusLen = strlen(ending2);

    if (bonusLen) { // content after array in same line as array
      ptr[elmLength + 1] = '\0';
      sprintf(assign, "%s%s", ptr + 1, ending2);
    } else { // nothing to the right of array, quick copy:
      strncpy(assign, ptr + 1, elmLength);
      assign[elmLength] = '\0';
    }//end if bonus?

  } else { // no ptr, missed elm, default to 0:
    if (varSlot > -1) {//DMA?
      VARS[varSlot] = 0;
      return true;
    }//dma?
  }//ptr?

  return false;
}//end processArray()
bool evalMath(char * s, LATER_ENVIRON * script, int DMA) {
  char * ptr = strchr(s, '(');
  if (!ptr) return 0;

  char * ptrOrig = ptr + 0;
  ptr++; // skip past open paren
  unsigned long * VARS = script->VARS;
  bool hasFunc = 0;
  char * ptrCmd = ptr;

  char * leftPadPtr = s;
  while (leftPadPtr[0] == ' ')leftPadPtr++;
  int prefixLen = (ptr - leftPadPtr);

  if ( prefixLen > 3 ) { // && isupper(s[prefixLen - 2])  // prefix content long enough to be a command?
    ptrCmd = laterUtil::copyUntilChar(s, '(');
    // find command prefix if any:
    for (unsigned int i = strlen(ptrCmd) - 2; i > 0; i--) {
      if (!isupper(ptrCmd[i])) {
        ptrCmd += i + 1;
        break;
      }// endif upper?
    }//next i
    while (ptrCmd[0] == ' ')ptrCmd++;
    hasFunc = strlen(ptrCmd) > 2;
  } //end if any prefix content?

  if (DMA > -1) { // can't use DMA if in an array, since presumably that array wants dma as well.
    char * inArr = strchr(leftPadPtr, ']');
    if (inArr && inArr[1] == '[') DMA = -1;
  }



  while (ptr[0] == ' ') ptr++; // trim left
  char * rp = strchr(ptr, ')');
  char OVERRIDE = 0;

  // array of longs and an array of ops, synced
  unsigned long nums[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // numbers to be mathed upon
  char ops[8]; // list of match operators to use
  unsigned int i = 0,
               len = strlen(ptr),
               pos = strcspn (ptr, "+-*/%<>!&?,:=|");

  if (pos == len && !hasFunc) return 0; //ltoa( 0, s, 10 );// nothing to do, default to zero

  if (pos == 0) { // lisp-style operand first and data to follow?
    OVERRIDE = ptr[0];
    ptr++;
    pos = strcspn (ptr, "+-*/%<>!&?,:)=|");

  }

  while (pos) {//put num/term into stack, slide string, try to grab next

    nums[i] = Number(ptr, VARS); //atoi(ptr);
    ops[i] = ptr[pos];
    if (ops[i++] == ')') break;
    if (i > 7) break;
    ptr += pos + 1;
    pos = strcspn (ptr , "+*-/%<>=!&?,:)|");
  }//wend pos

  /*
    if (strlen(ptr)) { // anything left? populate last elements
      LATER_PRINTLN("evalMath: last chance needed");
      nums[i] = Number(ptr, VARS); //atoi(ptr);
      ops[i++] = ')';
    }
  */
  /* // works, always? needs last chance?
    while ( pos < strlen(ptr) ) {//put num/term into stack, slide string, try to grab next
      nums[i] = Number(ptr, VARS); //atoi(ptr);
      ops[i] = ptr[pos];
      if (ops[i++] == ')') break;
      ptr += pos + 1;
      pos = strcspn (ptr, "+*-/%<>^!&?,");
    }//wend pos

    if (strlen(ptr)) { // anything left? populate last elements
      LATER_PRINTLN("evalMath: last chance needed");
      nums[i] = Number(ptr, VARS); //atoi(ptr);
      ops[i++] = ')';
    }
  */
  unsigned long varCache = nums[0], tempInt;

  if (hasFunc) { // has function
    auto cb = FUNCS[ptrCmd];
    if (cb) varCache = cb( nums[0], nums[1], nums[2] );
  } else { // calc


    for (unsigned int ii = 1; ii < i; ii++) {
      tempInt = nums[ii];
      if (OVERRIDE) ops[ii - 1] = OVERRIDE;

      switch ( ops[ii - 1]) {
        case ':': break; // do nothing, this is peeked by the ? operation
        case '?': varCache = varCache > 0 ? tempInt : nums[ii + 1] ; break;
        case '+': varCache += tempInt; break;
        case '-': varCache = varCache -  tempInt; break;
        case '*': varCache *= tempInt; break;
        case '/': if (tempInt) varCache /= tempInt; break;

        case '|': varCache = varCache ? varCache : tempInt; break;
        case '!': varCache = varCache == tempInt ? 0 : 1; break;

        // these will work lisp-style
        case '&': varCache = varCache && tempInt ? 1 : 0; break;

        // rewritten to work lisp-style
        //case '>': varCache = varCache > tempInt ? 1 : 0; break;
        //case '<': varCache = varCache > tempInt ? 0 : 1; break;

        // re-rewritten to work lisp-style OR compare style
        //case '>': varCache = varCache > tempInt ? varCache : tempInt; break;
        //case '<': varCache = varCache > tempInt ? tempInt : varCache; break;

        case '<':
          if (OVERRIDE) { // lisp style:
            varCache = varCache > tempInt ? tempInt : varCache;
          } else { // compare style
            varCache = varCache > tempInt ? 0 : 1;
          }
          break;

        case '>':
          if (OVERRIDE) { // lisp style:
            varCache = varCache > tempInt ? varCache : tempInt;
          } else { // compare style
            varCache = varCache > tempInt ? 1 : 0;
          }
          break;
        case '=': varCache = varCache == tempInt ? 1 : 0; break;

        case '%': if (tempInt) varCache = varCache % tempInt; break;
        case ',': break;
        case ')': break;
      }//end operation switch
    }//next ii
  }//end if function or expression?

  if (DMA > -1) {
    VARS[DMA] = varCache;
    return 1;
  }


  // non DMA call, must interpolate result into code line as literal number
  if (hasFunc) ptrOrig -= strlen(ptrCmd);   // include function name in output replacing

  int repLen = (rp - ptrOrig) + 1;
  memset(ptrOrig, '\2', repLen);

  char placeholder[32];
  placeholder[repLen] = '\0';
  memset(placeholder, '\2', repLen);

  char outputTerm[18];
  // outputTerm[repLen] = '\0'; // needed?
  laterUtil::replace(s, placeholder, ltoa( varCache, outputTerm, 10 ) );


  if (strchr(s, ')') ) evalMath(s, script,  DMA);

  return 0;
} // end evalMath
bool evalConditionalExpression(char * string_condition, LATER_ENVIRON * s) {
  unsigned long * VARS = s->VARS;
  char * ptr = string_condition;
  char op;
  unsigned long term1, term2; // the values to compare
  bool ifConditionTrue = false,
       shouldInvert = false;

  if (ptr[0] == '!') {
    shouldInvert = true;
    ptr++;
    while (ptr[0] == ' ') ptr++; // trim left
  }
  char * opPtr = strpbrk (ptr, "=!<>%&|");
  term1 =  Number(ptr, VARS); // atoi(ptr); LHS
  if (!opPtr) { // if asking for truthyness of a single term, compare to zero and leave
    ifConditionTrue = term1 > 0;
    if (shouldInvert) ifConditionTrue = !ifConditionTrue;
    return ifConditionTrue;
  }

  while (opPtr) {
    op = opPtr[0];
    term2 =  Number(opPtr + 1, VARS); // atoi( opPtr + 1 ); RHS

    switch (op) {
      case '=': ifConditionTrue = term1 == term2; break;
      case '!': ifConditionTrue = term1 != term2; break;
      case '>': ifConditionTrue = term1 > term2; break;
      case '<': ifConditionTrue = term1 < term2; break;
      case '%': ifConditionTrue = term1 % term2; break;
      case '|': if (ifConditionTrue) return !shouldInvert; ifConditionTrue = true; break;
    }

    if (!ifConditionTrue) {
      if ( !opPtr || opPtr[0] != '|' ) break;
    }

    term1 = term2;
    opPtr = strpbrk (opPtr + 1, "=!<>%&|");
  }

  if (shouldInvert) ifConditionTrue = !ifConditionTrue;

  return ifConditionTrue;
} // end evalConditionalExpression()
/*  RESPONSE METHODS AND PROPERTIES

  count
  indexOf
  like
  dd666
  //numbers[]
  //lines[]
  x length
  x lineCount
  x status
  x text

*/
#ifdef ESP8266HTTPClient_H_
void popHttpResponse() {
  if (Later.httpResponseTextBuffer[0]) return;
  if (http.getSize() > 1400) return;
  if (http.getSize() == 0) return;


  strcpy(Later.httpResponseTextBuffer, (char*) http.getString().c_str());
  Later.httpResponseTextBuffer[http.getSize()] = '\0';
  Later.httpResponseText = Later.httpResponseTextBuffer;
  //Later.httpResponseText[0] = '\0';
}

bool processResponseEmbeds(char * line, LATER_ENVIRON * s) {
  /*
    if (!http.headers()) {
    line[0] = '0';
    line[1] = '\0';
    return 0;
    }
  */

  //unsigned long * VARS = s->VARS;
  //char * ptr = line;
  char prop[16];
  char numResp[16];
  int totalCommandLength = 0;
  char * propStart = strstr(line, "&RESPONSE->");
  if (!propStart) return 0;
  propStart += 11; // == "&RESPONSE->".length
  // find prop up to  non-VARLIST
  unsigned long count = 0;

  totalCommandLength += (propStart - line);
  int propLen = strspn(propStart, VARLIST);
  strncpy(prop, propStart, propLen);
  prop[propLen] = '\0';
  totalCommandLength += propLen;

  if (prop[0] < 'k') {

    if (laterUtil::isTheSame(prop, "after")) {
      popHttpResponse();

      char term[32]; //find phrase to match and replace key holder
      strcpy(term, propStart + propLen + 1);
      if (  (propStart = strchr(term, ')'))  ) propStart[0] = '\0';
      totalCommandLength += strlen(term) + 2;
      propStart = Later.httpResponseText; // count matches:
      if (!propStart) return 0;
      int len = strlen(Later.httpResponseText);
      Later.httpResponseText = strstr(propStart, term);
      Later.httpResponseText += strlen(term);

      int lost = len - strlen(Later.httpResponseText);
      strncpy(term, line, totalCommandLength); // refill term with replace token
      term[totalCommandLength] = '\0';
      laterUtil::replace(line, term, ultoa(lost, numResp, 10 ));
      return 1;
    }

    if (laterUtil::isTheSame(prop, "before")) {
      popHttpResponse();

      char term[32]; //find phrase to match and replace key holder
      strcpy(term, propStart + propLen + 1);
      if ( (propStart = strchr(term, ')')) ) propStart[0] = '\0';
      totalCommandLength += strlen(term) + 2;
      propStart = Later.httpResponseText; // count matches:
      if (!propStart) return 0;
      int len = strlen(Later.httpResponseText);
      // now chop off anything after the term:
      Later.httpResponseText = strstr(propStart, term);
      if (!Later.httpResponseText) return 0;
      Later.httpResponseText[0] = '\0';
      Later.httpResponseText = propStart;

      int lost = len - strlen(Later.httpResponseText);
      strncpy(term, line, totalCommandLength); // refill term with replace token
      term[totalCommandLength] = '\0';
      laterUtil::replace(line, term, ultoa(lost, numResp, 10 ));
      return 1;
    }

    if (laterUtil::isTheSame(prop, "count")) {
      popHttpResponse();
      char term[32]; //find phrase to match and replace key holder
      strcpy(term, propStart + propLen + 1);
      if (  (propStart = strchr(term, ')'))  ) propStart[0] = '\0';
      totalCommandLength += strlen(term) + 2;
      propStart = Later.httpResponseText; // count matches:
      if (propStart) while (   (propStart = strstr(propStart + 1, term))  )count++;

      strncpy(term, line, totalCommandLength); // refill term with replace token
      term[totalCommandLength] = '\0';
      laterUtil::replace(line, term, ultoa(count, numResp, 10 ));
      return 1;
    }

    if (laterUtil::isTheSame(prop, "json")) {
      popHttpResponse();
      char term[40]; //find phrase to match and replace key holder
      strcpy(term, propStart + propLen + 1);
      if (  (propStart =  strchr(term, ')'))  ) propStart[0] = '\0';
      totalCommandLength += strlen(term) + 2;

      propStart = strstr(Later.httpResponseText, term) + strlen(term) ; // count matches:
      propStart = strpbrk (propStart, "0123456789");
      if (propStart) count = strtoul (propStart, NULL, 10);
      strncpy(term, line, totalCommandLength); // refill term with replace token
      term[totalCommandLength] = '\0';
      laterUtil::replace(line, term, ultoa(count, numResp, 10 ));
      return 1;
    }

  } else {

    if (laterUtil::isTheSame(prop, "length")) {
      ltoa(http.getSize(), numResp, 10 );
      laterUtil::replace(line, "&RESPONSE->length", numResp);
      return 1;
    }
    if (laterUtil::isTheSame(prop, "lineCount")) {
      popHttpResponse();
      int lines = 1;
      char * pline = strchr(Later.httpResponseText, '\n');
      while (pline) {
        lines++;
        pline = strchr(pline + 1, '\n');
      }
      ltoa(lines, numResp, 10 );
      laterUtil::replace(line, "&RESPONSE->lineCount", numResp);
      return 1;
    }

    //try and push stsatus into line
    if (laterUtil::isTheSame(prop, "status")) {
      ltoa(s->status, numResp, 10 );
      laterUtil::replace(line, "&RESPONSE->status", numResp);
      return 1;
    }
    if (laterUtil::isTheSame(prop, "text")) {
      popHttpResponse();
      laterUtil::replace(line, "&RESPONSE->text", Later.httpResponseText );
      return 1;
    }

  }//end if early or late in alpha?
  return 0;
}//end processResponseEmbeds();
#endif
void processStringFormats(char* s) { // finds format flags in form of <#flag string#>, replacing between <##> with result
  char * left = strstr(s, "<#");
  if (!left) return;
  char * nested = strstr(left + 1, "<#");
  if (nested) left = nested;

  char flagName[10]; // name of flag (aka command)
  char buff[48];
  char out[48];
  int i = 0;
  //unsigned long n;
  //char * outs;

  int endPos = laterUtil::indexOf(left, "#>") + 2;
  if (endPos == 1) return;

  strncpy(buff, left, endPos);
  buff[endPos] = '\0';

  int flagLen = laterUtil::indexOf(left, " ");
  if (flagLen == -1) return;

  strncpy(flagName, left + 2, flagLen - 2);
  flagName[flagLen - 2] = '\0';

  strncpy(out, left + flagLen + 1, (endPos - flagLen) - 2);
  out[(endPos - flagLen) - 3] = '\0';
  int slen = strlen(out);

  ///////////////////////////////////////////////

  bool more = 1;

  /*
    LATER_PRINTLN("flag found:" + String(left) + ";");
    LATER_PRINTLN("orig buff:" + String(buff) + ";");
    LATER_PRINTLN("out buff:" + String(out) + ";");
  */
  if (flagName[0] < 'm') {// low aplha flag, check first half of flags:

    if (more && !strcmp(flagName, "escape")) {

      nested = left + flagLen + 1; //same as orig and thus out copy, but with #> at end

      memset(out, '\0', 48 );
      int mx = strlen(nested) - 2;
      char c;
      char code[5];
      code[0] = '%';
      char * codePtr = code + 1;

      for (int i = 0; i < mx; i++) {
        c = nested[i];
        if (isalnum(c)) {
          out[strlen(out)] = c;
        } else { // escape and copy
          codePtr[2] = '\0';
          codePtr[3] = '\0';
          ltoa(c, codePtr, 16 );
          strcat(out, code);
        }
      }//next

      more = 0;
    }//end escape

    if (more && !strcmp(flagName, "hex")) {
      ltoa( atol(out), out, 16 );
      more = 0;
    }//end hex

    if (more && !strcmp(flagName, "lower")) {
      for (; i < slen; i++) out[i] = tolower(out[i]);
      more = 0;
    }//end lower

  } else { //   /\lo or hi\/ alpha tag name?

    if (more && laterUtil::startsWith(flagName, "pad")) {
      int amt = (flagName[3] - 48) - slen;
      char filler = flagName[4];


      if (amt > 0) {
        memset(out, filler, amt);
        strncat(out + amt, left + flagLen + 1, slen);
        out[ flagName[3] - 48 ] = '\0';
      }
      more = 0;
    }//end pad
    if (more && !strcmp(flagName, "trim")) {
      char * ns = out;
      while (isblank(ns[0])) ns++;
      strcpy(out, ns);
      laterUtil::trimRight(out);
      more = 0;
    }//end trim

    if (more && !strcmp(flagName, "upper")) {
      for (; i < slen; i++) out[i] = toupper(out[i]);
      more = 0;
    }//end upper

  }//end if hi/low first char?

  if (!more) {
    laterUtil::replace(s, buff, out);
    if (strchr(s, '<')) processStringFormats(s);
  }

  /*
    <escape
     <hex
     <upper
     <lower
     <pad1..9
     <trim
    <json
  */

}//end processStringFormats()

void handleEval() {
  char linebuff[160];
  LATER_ENVIRON * s = server.hasArg("name") ? Later.getByName(server.arg("name").c_str()) : getCurrent();

  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.sendHeader(LATER_CORS, "*");
  server.send ( 200, LATER_PLAIN, " ");
  strcpy(linebuff, server.arg("code").c_str());
  laterCMD::runEval(linebuff, s);
  server.sendContent("");//ends and closes response
}//end handleEval()

#ifdef ESP8266WEBSERVER_H
void handleDump() {

  LATER_ENVIRON * s = server.hasArg("name") ? Later.getByName(server.arg("name").c_str()) : getCurrent();
  if (!s) s = getCurrent();
  LATER_LINE * l;
  char linebuff[80];
  char respbuff[20];
  char * lp;
  char dbg[88];
  char flagList[] = "HOAEVT";

  server.sendHeader(LATER_CORS, "*");

  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send ( 200, LATER_PLAIN, "\n");

  sprintf(dbg, "%ld lines in %db from ", s->lineCount, strlen(s->program) );
  server.sendContent(dbg);
  server.sendContent(s->fileName);

  sprintf(dbg, "\nRAM:%d,  runs:%lu,  subRet:%u, resumeLine:%u\n", ESP.getFreeHeap(), s->runs, s->subReturnLine,  s->resumeLineNumber);
  server.sendContent(dbg);
  sprintf(dbg, "Line:%ld, forStart:%ld, forEnd:%ld, forStep:%ld, forIndex:%ld", s->i, s->forStart[s->forLevel], s->forEnd[s->forLevel], s->forStep[s->forLevel], s->forIndex[s->forLevel]);
  server.sendContent(dbg);
  //String bonus = " ";
  bool bonus = true;
  server.sendContent("\n\nLINES:\n #  exit         HOAEVT flags  \tOP  value\n");
  for (int i = 0, mx = s->lineCount; i < mx; i++) {
    l = &s->lines[i];
    lp = s->program + l->start;
    strncpy(linebuff, lp, l->len);
    linebuff[l->len] = '\0';
    if (i > 9) bonus = false;
    if (bonus) server.sendContent(" ");
    server.sendContent(itoa(i, respbuff, 10));
    server.sendContent(" -> ");
    server.sendContent(itoa(l->exit, respbuff, 10));
    server.sendContent(" \t[");
    itoa(l->flags + 256, respbuff, 2);
    lp = respbuff;
    lp += 3;  // print out any active flags with abbr in the slot, else empty space:
    for (int f = 0; f < 6; f++)  lp[f] = (lp[f] == '1') ? flagList[f] : ' ';

    server.sendContent(lp);
    server.sendContent("]\t");
    respbuff[0] = l->cmd ? l->cmd : '?';
    respbuff[1] = '\0';
    server.sendContent(respbuff);
    server.sendContent(" = ");
    server.sendContent(linebuff);
    server.sendContent("\n");
  }//next line

  server.sendContent(" #  exit         HOAEVT flags  \tOP  value\n");
  server.sendContent("\nVALUE REGISTERS:\n#  \tSYM\tval\texpr\n");

  for (auto const & x : LATER_VAR_NAMES[s->index])   {
    server.sendContent(itoa(x.second, linebuff, 10));
    server.sendContent( ".\t@");

    linebuff[0] = (char)VARLIST[x.second];
    linebuff[1] = '\0';
    server.sendContent(linebuff);
    server.sendContent("_\t");
    server.sendContent(itoa(s->VARS[x.second], linebuff, 10));
    server.sendContent("\t");
    server.sendContent(x.first.c_str());
    server.sendContent("\n");
  }

  server.sendContent("\n-------- SYSTEM LOG -----------\n");
  server.sendContent(setRunLog);
  server.sendContent("\n-------- END PROGRAM DEBUG -----------\n");
  server.sendContent("");//ends and closes response
} // end handle dump()
#endif
void runScript() {

  LATER_ENVIRON * s = getCurrent();
  LATER_LINE * l;
  static char linebuff[80]; // holds a copy of the code line to alter as needed to run, keeps orig intact
  char * lp = s->program; // start point of master line
  static char tempbuff[32]; // for utility use by built-in functions

  s->startedAt = micros();
  s->runs++;

  int hits = 0; // used for runaway code detection
  char * k, * v; // used by hard-coded commands to parse thier own lines
  char * lb; // line buffer pointer to used for line selection and processing
  unsigned long varCache, tempInt; // used by hard-coded commands to store numbers insde raw (scopeless) switch
  int varSlot = 0; // used by DMA
  bool usedDMA = false; // dma needed? (since varSlot 0 is legit, this ride-along flag is needed)

  if (!s->exitLineNumber) s->exitLineNumber = s->lineCount;

  for (s->i = s->resumeLineNumber; s->i < s->exitLineNumber; s->i++) {
    l = &s->lines[s->i]; //    parsed line struct, members: [start, stop, data, len, flags, cmd]
    if (l->cmd == LATER_noop) continue; // the fastest command, no pre-processing done. used by static/define et al.

    // pop temp line buffer:
    lp = s->program + l->start;
    strncpy(linebuff, lp, l->len);
    linebuff[l->len] = '\0';
    lb = linebuff;

    usedDMA = 0;

    ////////////////////////////////////
    // line buffer formed, process line:

    // skip over all flag handling if no flag at all is set:
    if (l->flags) {
#ifdef ESP8266HTTPClient_H_
      // if ajax response operation, do that:
      if (((l->flags >> 5) & 0x01) == 1) {
        if (l->cmd == LATER_var || l->cmd == LATER_static || l->cmd == LATER_store || l->cmd == LATER_global ) { // assign ret to a vary:
          processResponseEmbeds(strchr(linebuff, '=') + 1, s);
        } else { // template result into line:
          processResponseEmbeds(linebuff, s);
        } // end if var or other cmd?
      }//handle response access
#endif
      if ((l->flags % 2 == 1) && (((l->flags >> 4) & 0x01) == 1)) {
        processTemplateExpressions2(linebuff, s);
      } // end if output-needing templates?
      if ( ((l->flags >> 4) & 0x01) == 1) {
        processVariableExpressions(linebuff, s->VARS);
      }//end if output-needing vars?

      //evaluate paren expressions into numbers
      if ( ((l->flags >> 2) & 0x01) == 1) {
        if (l->cmd == LATER_var || l->cmd == LATER_static || l->cmd == LATER_store || l->cmd == LATER_global) { // assignment mode, skip past name= and use dma if possible:
          usedDMA = evalMath(strchr(linebuff, '=') + 1, s, linebuff[1] - 65);
        } else {
          evalMath(linebuff, s, -1);
        } // end if var or other cmd?
      }//end if parens flag?
      // detect arrays and process:
      if ( ((l->flags >> 3) & 0x01) == 1) {
        if (l->cmd == LATER_var || l->cmd == LATER_static || l->cmd == LATER_store || l->cmd == LATER_global ) {
          usedDMA = processArray(strchr(linebuff, '=') + 1, s->VARS, linebuff[1] - 65);
        } else {
          processArray(linebuff, s->VARS, -1);
        } // end if var or other cmd?
      }//end if array?

    }//end if flags?

    if (hits++ > 32700) {
      uniPrintln("runaway loop detected, aborting");
      break;
    }

    if (s->options.debug) uniPrintln(linebuff);

    ////////////////////////////////////
    ////////////////////////////////////
    // linebuff has been pre-processed by flag and is ready to feed to commands
    switch (l->cmd) { // do command-y stuff with value by cmd, see COMMANDS:

      case LATER_noop:  continue; // do nothing. res (removed) still fired line prep, noop doesn't case LATER_res:

      case LATER_var: case LATER_static: case LATER_store: case LATER_global: // init variable to value

        if (l->cmd == LATER_static  ) {// never come back here again
          l->cmd = LATER_noop;
          l->flags = 0;

          if (strchr(linebuff, ':') && strchr(linebuff, '{')) { // defining a json literal?
            unsigned int b = linebuff[1] - 65;
            char varName[24];
            int baseLen = 0;

            //  reflect human var names from shortcut char to use for adding .prop names to base var name.
            for (auto const & x : LATER_VAR_NAMES[s->index])   {
              if (x.second == b ) {
                strcpy(varName, x.first.c_str());
                strcat(varName, ".");
                baseLen = strlen(varName);
                break;
              }//end if matching var?
            }//next var name
            char * p = strchr(linebuff, '{');
            char * pcolon;
            char * pname = varName;
            int slot = 0;
            int keyCount = 0;
            while (p) { // dig through json literal to define vars:

              p++;
              while (p[0] == ' ') p++; // trimleft
              pcolon = strchr(p, ':');
              if (!pcolon) break; // no more values, bail
              keyCount++;
              varName[baseLen] = '\0'; // reset composite var name holder
              strncat(varName, p, pcolon - p);

              slot = getVarNameNumber(varName, s->index); // use composite to get/make allocated slot
              s->VARS[slot] = Number(pcolon + 1, s->VARS); // set var value from literal

              p = strchr(pcolon, ','); // next k:v pair
              if (!p) p = strchr(pcolon, '}'); // last pair?

            }//wend k:v pair
            // now set root object to a count of properties:
            varName[baseLen - 1] = '\0';
            slot = getVarNameNumber(varName, s->index); // use composite to get/make allocated slot
            s->VARS[slot] = keyCount;
            continue;
          }//end if "json" literal?
        }//end if static/define?

        if (usedDMA) continue;

        // split on equal, get name and value
        v = strchr(linebuff, '=') + 1;
        varSlot = linebuff[1] - 65;
        while (v[0] == ' ') v++; // trim lef, right of compare operator char
        if (isdigit(v[0])) {
          varCache = strtoul(v, NULL, 10); // atol(v);
        } else {
          //setup mathy bits:
          varCache =  s->VARS[varSlot];

          if (l->cmd == LATER_store || l->cmd == LATER_global) {
            k = laterUtil::trimRight(laterUtil::copyUntilChar(linebuff, '='));
            varCache = LATER_STORE.get(k);
          }

          if (v[0] == '%') {
            tempInt = Number(v, s->VARS); // atol(v + 1);
          } else {
            tempInt = Number(v + 1, s->VARS); // atol(v + 1);
          }


          switch (v[0]) {
            case '+': varCache += tempInt; break;
            case '-': varCache = varCache -  tempInt; break;
            case '*': varCache *= tempInt; break;
            case '/': varCache /= tempInt; break;
            case '^': varCache = pow(varCache, tempInt); break;
            case '%': varCache = varCache % tempInt; break;
            case '<': varCache = tempInt > varCache ? 1 : 0; break;
            case '>': varCache = tempInt < varCache ? 1 : 0; break;
            case '!': varCache = tempInt == varCache ? 0 : 1; break;
            case '?': varCache = varCache ? tempInt : varCache; break;
            case ':': varCache = varCache ? varCache : tempInt; break;
            default: varCache =  Number(v, s->VARS); break; //atol(v); break;
          }//end operation switch

        }
        if (l->cmd == LATER_store) {
          k = laterUtil::trimRight(laterUtil::copyUntilChar(linebuff, '='));
          LATER_STORE.set(k, varCache);
        } else {
          if (l->cmd == LATER_global) {
            k = laterUtil::trimRight(laterUtil::copyUntilChar(linebuff, '='));
            LATER_STORE.update(k, varCache);
          } else {
            s->VARS[varSlot] = varCache;
          }

        }
        continue;
        break;

      case LATER_for: // forLoop
        if (s->forTop[s->forLevel] != -1) { // already in loop? shift up a level
          s->forLevel++;
        }
        s->forTop[s->forLevel] = s->i;
        laterUtil::splitStringByChar(linebuff, ';');

        s->forStart[s->forLevel] = Number(laterUtil::splits[1] ? laterUtil::splits[0] : 0, s->VARS); // for debugging, forIndex is really used
        s->forEnd[s->forLevel] = Number(laterUtil::splits[1] ? laterUtil::splits[1] : laterUtil::splits[0], s->VARS);
        s->forStep[s->forLevel] = laterUtil::splits[2] ? Number( laterUtil::splits[2], s->VARS) : 1;
        s->forIndex[s->forLevel] = s->forStart[s->forLevel];
        if (s->forEnd[s->forLevel] < s->forStart[s->forLevel]) { // hi-lo?
          if (s->forStep[s->forLevel] > 0) s->forStep[s->forLevel] *= -1;
        }//end if hi-low order?

        continue;
        break;
      case LATER_next: // forLoop's Next
        s->forIndex[s->forLevel] += s->forStep[s->forLevel];

        if (s->forStep[s->forLevel] > 0) { // works

          if (s->forIndex[s->forLevel] >= s->forEnd[s->forLevel]) { // done
            s->forTop[s->forLevel] = -1;
            // shift down a level if not on zero
            if (s->forLevel) s->forLevel--;
          } else { // keep going
            s->i = l->exit;
          }

        } else { // counting down

          if (s->forIndex[s->forLevel] <= s->forEnd[s->forLevel]) { //done
            s->forTop[s->forLevel] = -1;
            // shift down a level if not on zero
            if (s->forLevel) s->forLevel--;
          } else { // keep going
            s->i = l->exit;
          }

        }//end if count up or down?

        continue;
        break;
      case LATER_do: // do
        if (linebuff[0] == 'w') {
          if (!laterUtil::startsWith(linebuff, "while")) continue;
          if (!evalConditionalExpression(linebuff + 5, s)) s->i = l->exit;
        }//end if while

        if (linebuff[0] == 'u') { //blah
          if (!laterUtil::startsWith(linebuff, "until")) continue;
          if (evalConditionalExpression(linebuff + 5, s)) s->i = l->exit;
        }//end if until

        continue;
        break;
      case LATER_if: case LATER_iif: // If/Iff
        if (!evalConditionalExpression(linebuff, s)) s->i = l->exit;
        continue;
        break;

      //  not needed because IFs will always come out line after fi or else, which is co-incidently IF's line.exit
      case LATER_else: // ELSE
        s->i = l->exit;
        continue;
        break;

      case LATER_switch: // sWitch
        strcpy(s->switchTerm, linebuff);
        s->switchTerm[strlen(linebuff)] = '\0';
        s->switchExit = l->exit;
        continue;
        break;
      case LATER_case: // case (Kse)
        if (!s->switchTerm[0]) {
          s->i = s->switchExit;
        } else {
          if (!strcmp(s->switchTerm , linebuff)) { // match? yes:
            s->switchTerm[0] = '\0';
          } else { // no match, go to next case statement to look for a match
            s->i = l->exit;
          }//end if case match?
        }//end if expired switch's case?
        continue;
        break;

      case LATER_default: // switch default
        if (!s->switchTerm[0]) {
          s->i = s->switchExit;
        } else {
          s->switchTerm[0] = '\0';
        }
        continue;
        break;

      case LATER_end: //end switch might need to become LATER_end_switch, if other ends are needed
        s->switchTerm[0] = '\0';
        continue;
        break;
      case LATER_sub: //sub routine
        if (!s->subReturnLine) {
          s->i = l->exit;
          continue;
        }
        continue;
        break;
      case LATER_endsub: //sub end
        if (s->subReturnLine) {
          s->i = s->subReturnLine;
          s->subReturnLine = 0;
          s->subArgs[0] = 0;
          s->subArgs[1] = 0;
          s->subArgs[2] = 0;
          s->subArgs[3] = 0;

        }
        continue;
        break;

      case LATER_gosub: //sub call

        // look for arguments, populate as needed
        k = strchr(linebuff, ' ');
        if (k) {
          while (isSpace(k[0])) k++;
          laterUtil::splitStringByChar(k, ',');
          for (int i = 0; i < laterUtil::split_count; i++)    s->subArgs[i] = Number(laterUtil::splits[i], s->VARS);
        }//end if args?

        s->subReturnLine = s->i;
        s->i = l->exit;
        continue;
        break;

      case LATER_call: //call call
        // look for arguments, populate as needed
        if (l->data) {
          k = linebuff;
          k += l->data;
          while (isSpace(k[0])) k++;
          laterUtil::splitStringByChar(k, ',');
          int i = 0;
          for (i; i < laterUtil::split_count; i++)    s->subArgs[i] = Number(laterUtil::splits[i], s->VARS);
          s->arity = i;
        }//end if args?

        s->subReturnValue = linebuff[1] - 65;
        s->subReturnLine = s->i;
        s->i = l->exit;
        continue;
        break;
      case LATER_interval: //interval sub call

        // find interval, compare to lastFire
        k = strchr(linebuff, ' ');
        if (k) {
          tempInt = Number(k, s->VARS);
          if (  (s->intervals[ l->data ] + tempInt) < millis()  ) { //ready?
            s->intervals[ l->data ] = millis();
            s->subReturnLine = s->i;
            s->i = l->exit;
          }//end if ready?
        }//end if interval

        continue;
        break;

      case LATER_return: //sub return
        if (s->subReturnLine) {

          tempInt = Number(lb, s->VARS);
          if (s->subReturnValue < 99) s->VARS[s->subReturnValue] = tempInt;
          s->i = s->subReturnLine;
          s->subReturnLine = 0;
          s->subArgs[0] = 0;
          s->subArgs[1] = 0;
          s->subArgs[2] = 0;
          s->subArgs[3] = 0;
          continue;
        }
        continue;
        break;
      case LATER_continue:
        s->i = l->exit - 1;
        continue;
        break;

      case LATER_loop:
        s->i = l->exit;
        continue;
        break;

      case LATER_break:
        s->i = l->exit;
        continue;
        break;
#ifdef ESP8266HTTPClient_H_
      case LATER_ping: //  http request url
        yield();
        s->status = HTTPRequest(linebuff);
        yield();

        Later.httpResponseTextBuffer[0] = '\0';
        Later.httpResponseText = Later.httpResponseTextBuffer;

        s->status = HTTPRequest(linebuff);
        yield();
        //Later.httpResponseText = Later.httpResponseTextBuffer;

        continue;
        break;
#endif

      case LATER_print: case LATER_println:// print value
        laterUtil::replace(linebuff, "\\n", " \n");
        laterUtil::replace(linebuff, "\\t", " \t");
        laterUtil::replace(linebuff, "\\s", " ");
        processStringFormats(linebuff);

        // look for output redirect:
        if ( (v = strstr(linebuff, ">>")) ) {
          // i think this might need to be copied to a buff to get the filename w/o fucking up the rest of the system.

          tempInt = 0;
          k = v;
          v[0] = '\0';
          v += 2;
          if (v[0] == '>') { // append? (>>>)
            tempInt = 1;
            v++;
          }//append?
          while (v[0] == ' ') v++;
          laterUtil::trimRight(v);

          laterUtil::buffToFile(v, linebuff, tempInt);
          s->writes++;
          k[0] = '>';
        } else {
          if (l->cmd == LATER_println) {
            uniPrintln(linebuff);
          } else {
            uniPrint(linebuff);
          }
        }
        continue;
        break;

      case LATER_log: // log value
        processStringFormats(linebuff);
        laterCMD::logMe(linebuff);
        continue;
        break;
      case LATER_clear: // clear log value
        setRunLog[0] = '\0';
        continue;
        break;
      case LATER_delete: // delete variable

        continue;
        break;
      case LATER_sleep: // sleep ms
        if (strchr(lb, ',')) {
          delayMicroseconds(Number(linebuff, s->VARS));
        } else {
          delay(Number(linebuff, s->VARS));
        }

        continue;
        break;
      /*
            case LATER_sleepu: // sleep us
              delayMicroseconds(Number(linebuff, s->VARS));
              continue;
              break;
      */
      case LATER_pinMode: // setPinMode
        laterCMD::runPinMode(lb);
        continue;
        break;
      case LATER_digitalWrite:
        laterCMD::runPortWrite(lb, s->VARS, true);
        continue;
        break;

      case LATER_analogWrite:
        laterCMD::runPortWrite(lb, s->VARS, false);
        continue;
        break;
#ifdef ADAFRUIT_NEOPIXEL_H
      case LATER_pixel: // paint rgb leds
        laterCMD::runSetPixel(lb, s);
        continue;
        break;
      case LATER_render: // update painted rgb leds
        LATER_PIXEL_NAME.show();
        continue;
        break;
      case LATER_rotate: // update painted rgb leds
        laterCMD::runRotate( Number(lb, s->VARS) );
        continue;
        break;
      case LATER_grad:
        laterCMD::runGrad(lb, s);
        continue;
        break;
      case LATER_solid: // paint all rgb leds

        k = lb + 0;
        LATER_PIXEL_NAME.fill( laterUtil::parseColor(k, s), 0, LATER_PIXEL_NAME.numPixels() );
        LATER_PIXEL_NAME.show();

        continue;
        break;

#endif
      case LATER_timer: // print hi-res timestamp to
        tempInt = micros();
        if (!s->timer) {
          s->timer = tempInt;
        } else {

          char buf[12];
          uniPrint( "T+" );
          uniPrint( ltoa( tempInt - s->timer, buf, 10 ) );
          uniPrint(":\t");
          uniPrintln(lb);
          s->timer =  micros();
        }
        continue;
        break;
      case LATER_option:
        //bool debug; // print debug info to the console?
        //bool perf; // print perf info to the console?
        //bool strict; // disable legacy handlers and slower features?
        if (strstr(lb, "debug")) s->options.debug = true;
        if (strstr(lb, "perf")) s->options.perf = true;
        if (strstr(lb, "strict")) s->options.strict = true;
        if (strstr(lb, "persist")) s->options.persist = true;

        if ((k = strstr(lb, "interval"))) {
          // find next digits
          v = strpbrk(k + 8, "0123456789"); // locate first digit(s) after "interval"
          s->interval = Number(v, s->VARS);
          s->options.persist = true;
        }
        // interval? might need own command to accepts number of millis

        continue;
        break;
      case LATER_freeze: // suspend operation for given MS
        s->resumeLineNumber = s->i + 1;
        s->resumeMillis = millis() + Number(lb, s->VARS);
        s->duration = (micros() -  s->startedAt) / 1000;
        return;
        continue;
        break;
      case LATER_on: // subscript pin change and other events
        //on= pin, sub[, FALLING|RISING|CHANGE|EDGE]
        varCache = Number(lb, s->VARS); // pin

        varSlot = -1; // known handler? if so, grab slot
        for (int i = 0; i < 3; i++) {
          if (varCache == EVENT[i].pin) { // stop on first non-set slot, since -1 is default and matches varSlot
            varSlot = i;
            break;
          }
        }//next

        if (varSlot > -1) { // known? run sub
          // compare sub with event object and parsed params

          tempInt = digitalRead(varCache);

          if ( EVENT[varSlot].value != tempInt ) {
            // update last value:
            EVENT[varSlot].value = tempInt;
            EVENT[varSlot].ms = EVENT[varSlot].msNext;
            EVENT[varSlot].msNext = millis();
            Later.lastEventSlot = varSlot;

            if (l->data == 1 && tempInt != 1) continue; // rising only
            if (l->data == 2 && tempInt == 1) continue; // falling only

            s->subReturnLine = s->i;
            s->i = l->exit;
          }//end if change?

        } else { // unknown event, subscribe it by populating first empty event slot

          // find first unused slot:
          for (int i = 0; i < 3; i++) {
            if (EVENT[i].pin == -1) {
              varSlot = i;
              break;
            }
          }//next
          EVENT[varSlot].pin = varCache;
          EVENT[varSlot].value = digitalRead(varCache);
          EVENT[varSlot].msNext = millis();
        }//end if known handler?

        continue;
        break;
      case LATER_run:
        laterUtil::trimRight(lb);
        Later.run(lb);
        continue;
        break;
      case LATER_unload:
        laterUtil::trimRight(lb);
        Later.unload(lb);
        if (!strcmp(lb, s->fileName)) return;
        continue;
        break;

      case LATER_start:
        if (lb[0] == '0' && lb[1] == '0') { // default 00
          s->startLineNumber = s->i + 1; // next line is new top
        } else {
          s->startLineNumber = Number(lb, s->VARS); // top specified
        }
        continue;

      case LATER_exit:
        s->exitLineNumber = s->i;
        finishRun(s);
        return;
        break;
      case LATER_assert:
        laterCMD::runAssert(lb, l, s);
        continue;
        break;

      case LATER_cgi:
        laterCMD::runCGI(lb, s);
        continue;
        break;

      default:
        if ( Later.addons[ l->cmd  ] ) {
          Later.addons[ l->cmd  ](  lb, l, s);
          continue;
        }
        if (s->options.debug)uniPrint("Err: Unknown Command");
        break;

    }//end switch ?command?
  }// next line loop
  finishRun(s);
}//end runScript()
void finishRun(LATER_ENVIRON * s) {
  s->runTime = micros() -  s->startedAt;
  s->duration += s->runTime;
  s->resumeLineNumber = s->startLineNumber;
  if (s->interval > 0) {
    s->resumeMillis = (s->interval - 1) + (millis() - ( s->runTime / 1000));
  } else {
    s->resumeMillis = 0;
  }
}//end finishRun()
//

#line 1 "docs.ino"
//@TAKE

#line 1 "http.ino"

File fsUploadFile;
byte mac[6];  // the bytes of the station MAC address
const char * const RST_REASONS[] = {
  "REASON_DEFAULT_RST",
  "REASON_WDT_RST",
  "REASON_EXCEPTION_RST",
  "REASON_SOFT_WDT_RST",
  "REASON_SOFT_RESTART",
  "REASON_DEEP_SLEEP_AWAKE",
  "REASON_EXT_SYS_RST"
};
const char * const FLASH_SIZE_MAP_NAMES[] = {
  "FLASH_SIZE_4M_MAP_256_256",
  "FLASH_SIZE_2M",
  "FLASH_SIZE_8M_MAP_512_512",
  "FLASH_SIZE_16M_MAP_512_512",
  "FLASH_SIZE_32M_MAP_512_512",
  "FLASH_SIZE_16M_MAP_1024_1024",
  "FLASH_SIZE_32M_MAP_1024_1024"
};
////////////////////////////////////////////
#ifdef ESP8266WEBSERVER_H
std::map<std::string,  std::string> PATHS;
void handleGenericHttpRun(String fn) {

  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.sendHeader(LATER_CORS, "*");

  LATER_ENVIRON * s = Later.load((char*)fn.c_str()); //dd666, move this somewhere better:
  if (!s) {
    server.send ( 504, LATER_PLAIN, "504 - refused to load");
    server.sendContent("");
    return;
  }
  // load vars from url into script enviroment:
  String key, value, banned = ",$name,$content-type";
  for (uint8_t i = 0; i < server.args(); i++) {
    key =  "$" + server.argName(i);
    value = server.arg(i);
    if (banned.indexOf(',' + key + ',') > -1) continue;
    char slot = getVarNameNumber((char*)key.c_str(), s->index);
    s->VARS[(int)slot] = value.toInt();
  }

  server.send ( 200, s->contentType, ""); // start response
  s->calledFromWeb = 1;
  Later.run((char*)fn.c_str()); // execute em!
  server.sendContent(""); // finish response
  /*
      if (server.hasArg("persist")) return;
    if (s->options.persist) return;

    if (  !strchr(fnp, '~') ) {
      Later.unload(fnp);
    } else {
      s->options.persist = true;
    }
  */
}//end handleGenericHttpRun();

void handleAPI() { // break in here and look for default.bat or index.bat
  String fn = "/index.bat";
  if (SPIFFS.exists(fn) && !server.hasArg("default")) {
    handleGenericHttpRun(fn);
    return;
  }//end if bat file found?

  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.sendHeader(LATER_CORS, "*");
  server.send ( 200, "text/html", F("<body><h1>Later Endpoints</h1><big><big><ul>\n"));
  char line[64];
  for (const auto &x : PATHS) server.sendContent(sprintf(line, "<li><a href=%s>%s</a>\n", x.first.c_str(), x.first.c_str()) ? line : line );
  server.sendContent( "" );
}

void handleDelete() {
  String fn = server.arg("name");

  if (!server.hasArg("name")) {
    server.send ( 403, "text/plain", F("403 - no file specified by name GET param"));
    return;
  }

  if (fn[0] != '/') fn = "/" + fn; // optionalize preceding slash

  if (SPIFFS.exists(fn)) {
    SPIFFS.remove(fn);
    server.send ( 200, "text/plain", F("200 - file deleted"));
    return;
  }//end if bat file found?

  // should not make it this far, file not found:
  server.send ( 402, "text/plain", F("402 - existing file not specified by name GET param"));
}
void bindServerMethods() {

  server.on("/", handleAPI); // this style of sub won't be listed

  // subscript public GET endpoints:
  SUB_PATH(run, handleRun);
  //@TAKE
  SUB_PATH(scripts, handleScripts);
  SUB_PATH(log, handleLog);
  SUB_PATH(dir, handleFileList);
  SUB_PATH(ls, handleLS);
  SUB_PATH(delete, handleDelete);
  SUB_PATH(editor, handleEditor);
  SUB_PATH(store, handleStore);
  SUB_PATH(unload, handleUnload);
  SUB_PATH(test, handleDump);
  SUB_PATH(eval, handleEval);
  SUB_PATH(help, handleCommandList);
  SUB_PATH(bench, handleBench);
  server.on("/upload", HTTP_POST, []() {
    server.send(200, LATER_PLAIN, "ok");
  }, handleFileUpload);
  server.onNotFound([]() {
    String fn = server.uri() + ".bat";
    if (SPIFFS.exists(fn)) {
      handleGenericHttpRun(fn);
      return;
    }//end if bat file found?
    if (!handleFileRead(server.uri()))
      server.send(404, LATER_PLAIN, "FileNotFound: " + server.uri() );
  });
}//end bindServerMethods()
#ifdef ESP8266

#else

#endif
void handleLS() { // replace with non-string non-crap:

  String path = server.arg("dir");
  if (path == "") path = "/";
#ifdef ESP8266
  Dir dir = SPIFFS.openDir(path);
#else
  File dir = SPIFFS.open(path);
#endif
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.sendHeader(LATER_CORS, "*");
  server.send ( 200, "text/html", "");

  server.sendContent(F("<html><head><title>"));
  server.sendContent(path);
  server.sendContent(F("</title><style>@import 'https://maxcdn.bootstrapcdn.com/bootswatch/3.3.7/cyborg/bootstrap.min.css';\n  a,b,small { display: inline-block; min-width: 11em;}"));
  server.sendContent(F(" ol li { margin-top: 0.25em; font-size: 125%; }</style></title></head><body class=container> <h1>"));
  server.sendContent(path);
  server.sendContent(F("</h1> <ol id=list></ol><script>["));

  File entry;

#ifdef ESP8266
  while (dir.next()) {
    entry = dir.openFile("r");
#else
  entry = dir.openNextFile();
  while (entry) {
#endif

    if (strlen(entry.name()) > 2) {
      bool isDir = false;
      server.sendContent(",\n{\"type\":\"");
      server.sendContent((isDir) ? "dir" : "file");
      server.sendContent("\",\"name\":\"");
#ifdef ESP8266
      server.sendContent(entry.name() + 1);
#else
      server.sendContent(entry.name() + 1);// Ignore '/' prefix
#endif
#ifdef ESP8266
      server.sendContent( "\",\"size\":\"");
      server.sendContent(laterUtil::formatBytes(dir.fileSize()));
#endif
#ifdef ESP32
      server.sendContent( "\",\"size\":\"");
      server.sendContent(laterUtil::formatBytes(dir.size()));
#endif

      server.sendContent("\",\"mime\":\"");
      server.sendContent(getContentType(entry.name()));
      server.sendContent("\"}");
      entry.close();

    }//end if name long?

#ifdef ESP32
    entry = dir.openNextFile();
#endif
  }

  server.sendContent(F("].filter(Boolean).map(function(a){list.appendChild(document.createElement('li')).innerHTML='<input type=button onclick=\"doDel(nextElementSibling.href)\" value=X > '+a.name.link('./'+a.name)+' '+'run'.link('/run/?name='+encodeURIComponent(a.name))+'  ' +'edit'.link('/editor/#'+a.name)+' ' + a.size.bold()+' ' + a.mime.small(); });function doDel(fn){if(!confirm('ERASING FILE: '+fn+'\\n\\nThis CANNOT be undone !!!'))return; var path = '/' + fn.split('/').pop(); fetch('/delete/?name='+encodeURIComponent(path)).then(function(){location.reload();});return false;}</script>"));
  server.sendContent(F("<hr><form id=f1 method=post action=/upload enctype=multipart/form-data target=_blank><label>Upload Embeded File <input onchange='setTimeout(function(){f2.click()},222);' accept='application/*'  type=file name=file></label><input type=submit value=Upload id=f2 ></form></body>"));
  server.sendContent("");
}
//25968 > 26268 > 26772
void handleEditor() {


  // move this to a multipart response, print most of it, then print define path to script, then print html page closer/footer.

  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.sendHeader(LATER_CORS, "*");
  server.send ( 200, "text/html", "");

  server.sendContent(F(  "<!doctype html><html><head>\n    <meta charset=\"UTF-8\">    <title>later editor</title>\n<link rel=icon href=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAAFiUAABYlAUlSJPAAAAAcSURBVDhPY/hr+fc/JXjUgFEDQHjUgGFgwN//AJBjMi73juieAAAAAElFTkSuQmCC> \n<link rel=stylesheet type=text/css href='//maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css' />\n<style>\tbody {background:#000;color:#888;padding-top:5px; } #files{ width: 7em; }  #val {overflow: scroll;width: 99%; height: 85vh; font: 24px monospace; } div#stats {position: fixed;top: 1em;right: 3em;width: 40%;background: #111;padding: 1em;overflow: auto;height: 90vh;border: 1px solid #888;font: 20px monospace;}\n</style>\n</head>\n<body class=container-fixed><a href='/docs/'>Home</a>\n   <select id=files onchange='loadme(value)'>\n  <option value=\"\">Load File...<option>\n  </select>  &nbsp; \n <label>Filename: \n  <input type=text id=inpname size=32>\n</label>\n    &nbsp;   &nbsp; \n   <input type=button class='btn btn-success btn-sm' value=Save id=btnsave onclick='saveIt(inpname.value, val.value)'>\n&nbsp;   &nbsp; \n   <input type=button class='btn btn-warning btn-sm' value=Run id=btnrun onclick='runme(inpname.value)'> \n&nbsp;   &nbsp; \n   <input type=button class='btn btn-info btn-sm' value=Test id=btntest onclick='test()'> \n&nbsp;   &nbsp; <label> auto-test <input type=checkbox id=chkauto></label>\n\n&nbsp;   &nbsp;\n&nbsp;   &nbsp; <label> URL Params <input type=input id=inpqs value=\"&reload=true\" size=24></label>\n\n   <input type=button class='btn btn-xs btn-info pull-right btn-sm' value=\"?\" id=btnhelp onclick='showHelp()'> \n\n<br> \n<div id=edwrap>\n<textarea id=val rows=40 cols=90></textarea></div>\n\n<div id=stats></div>\n<form method='POST' action='/update' target=_blank enctype='multipart/form-data' onsubmit='setTimeout(function(){file11.value=null}, 25000)' >\n                  <input id=file11 type='file' accept='application/*' name='update'>\n                  <input type='submit' value='Update'>\n               </form>\n\n\n<script>\nvar url = '/';\n\nfunction saveIt(name, value) {\n\tif(!name) return alert('filename blank, try again');\n\tvar dbs = document.body.style,\n\t\tfile = new File([value], name, {\n\t\t\ttype: \"text/plain\",\n\t\t}),\n\t\tform = new FormData();\n\tdbs.opacity = 0.5;\n\tform.append('file', file, name);\n\tfetch(url + 'upload', {\n\t\tbody: form,\n\t\tmethod: 'POST',\n\t\tmode: 'cors'\n\t}).then(x => {\n\t\tdbs.opacity = 1;\n\t\tdir();\n\t\tlocation.hash = name;\n\t\tdocument.title=\"@\"+name;\n\t});\n}\n\nfunction dir() {\n\tfetch(url + 'dir').then(x => x.json()).then(x => {\n\t\tfiles.options.length = 1;\n\t\tx.sort(function(a,b){return a.name>b.name?1:-1;}).map(function(a, i) {\n\t\t\tfiles.appendChild(new Option(a.name + \" : \" + a.size, a.name));\n\t\t});\n\t})\n}\n\n \nfunction test() {\n\tfetch(url + 'test').then(x => x.text()).then(x=>{\n\t\t stats.innerText= x;\t\n\t});\n}\n\n\nfunction loadme(file) {\n        var dbs = document.body.style;\n\tdbs.opacity = 0.3;\n\tfetch(url + file).then(x => x.text()).then(x => {\n\t\tval.value = x;\n\t\tinpname.value = file;\n\t\tval.focus();\n\t\tdbs.opacity = 1;\n\t\tlocation.hash = file;\n\t\tdocument.title=\"@\"+file;\n\t});\n\n}\nvar cache;\nfunction showHelp(){\n  var done = x=>{\n   var s = x.split(/<\\/?pre/i)[1].slice(1).trim();\n   cache = x;\n   stats.innerText = s;\n  };\n  if(cache) return done(cache);\n  fetch(\"/docs/\").then(x=>x.text()).then(done);\n}\n\nfunction runme(file) {\n\tif(!file) return alert(\"no file chosen\");\n\tvar dbs = document.body.style;\n\tdbs.opacity = 0.3;\n\tfetch(url + \"run?name=\" + encodeURIComponent(file) + inpqs.value ).then(x => x.text()).then(x => {\n\t\tval.focus();stats.title=x;\n\t\tdbs.opacity = 1;\n\t\tif(chkauto.checked) setTimeout(test, 500);\n\t});\n}\nif(location.hash) loadme(location.hash.slice(1));\nsetTimeout(dir, 140);\n</script>"));

  server.sendContent("<script src=");
  server.sendContent(LATER_EDITOR_URL);
  server.sendContent("></script>");
  server.sendContent("\n</body>\n</html>");
  server.sendContent("");
}//end handle editor
String getContentType(String filename) {
  if (server.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".mp3")) return "audio/mp3";
  else if (filename.endsWith(".json")) return "application/json";
  return LATER_PLAIN;
}

bool handleFileRead(String path) {
  if (path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    server.sendHeader(LATER_CORS, "*");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}
/*

  void handleStatus() {
  String message = "{\n\n";
  message.reserve(512);

  const rst_info * resetInfo = system_get_rst_info();

  #ifndef NO_WIFI
  FSInfo fso_info;
  SPIFFS.info(fso_info);

  message += " \"timestamp\":\t\"" + String(millis()) + "." + String(micros()) + "\",\n";
  message += " \"systime\":\t" + String(system_get_time()) + ",\n";
  message += " \"cycles\":\t" + String(  ESP.getCycleCount()) + ",\n";

  message += " \"rssi\":\t" + String(  WiFi.RSSI() ) + ",\n";

  message += " \"analog\":\t" + String(analogRead(A0)) + ",\n";
  message += " \"reset\":\t\"" + String(RST_REASONS[resetInfo->reason]) + "\",\n";
  message += " \"chipid\":\t\"" + String(system_get_chip_id(), HEX) + "\",\n";
  message += " \"dev_mac\":\t\"" + String(mac[0], HEX) + ":" + String(mac[1], HEX) + ":" + String(mac[2], HEX) + ":" + String(mac[3], HEX) + ":" + String(mac[4], HEX) + ":" + String(mac[5], HEX) + "\",\n";
  message += " \"dev_ip\":\t\"" + String( WiFi.localIP().toString()) + "\",\n";
  message += " \"req_uri\":\t\"" + String(server.uri()) + "\",\n";
  message += " \"built\":\t\"" + String( __DATE__) + " " + String(__TIME__) + "\",\n";
  message += " \"flash\":\t\"" + String(FLASH_SIZE_MAP_NAMES[system_get_flash_size_map()]) + "\",\n";

  message += " \"flash_phy\":\t" + String(  ESP.getFlashChipRealSize()) + ",\n";
  message += " \"flash_ide\":\t" + String(  ESP.getFlashChipSize()) + ",\n";
  message += " \"flash_usd\":\t" + String(  fso_info.usedBytes ) + ",\n";
  message += " \"flash_tot\":\t" + String(  fso_info.totalBytes ) + ",\n";

  message += " \"board\":\t\"" + String(ARDUINO_BOARD) + "\",\n";
  message += " \"cpumhz\":\t" + String(system_get_cpu_freq()) + ",\n";
  message += " \"memkb\":\t" + String(system_get_free_heap_size()) + "\n";
  message += "\n}";
  server.sendHeader(LATER_CORS, "*");
  server.send(200, "application/json", message);
  #endif
  }
*/
static String filename;
void handleFileUpload() {

  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    filename = upload.filename;
    if (!filename.startsWith("/")) filename = "/" + filename;
#ifdef DEBUG_WEBSERVER
    Serial.printf("handleFileUpload Name: %s\n", filename.c_str());
#endif // DEBUG_WEBSERVER
    fsUploadFile = SPIFFS.open(filename, "w");
  }
  else if (upload.status == UPLOAD_FILE_WRITE) {
    if (fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  }
  else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile) {
      fsUploadFile.close();
      if ((!server.hasArg("reload")) && Later.getByName( (char*)filename.c_str() ))  Later.unload((char*)filename.c_str());
      if ((server.hasArg("reload")) && Later.getByName( (char*)filename.c_str() ))  Later.run((char*)filename.c_str());

      // handleSetFileLastFileName = ""; // bust any batch file caches
      server.sendHeader(LATER_CORS, "*");
      server.send(200, "text/html", F("<html><title>Done Uploading...</title><h1>Done</h1><script>location.replace('/ls');</script></html>"));
    }
#ifdef DEBUG_WEBSERVER
    Serial.printf(F("handleFileUpload Size: %u\n"), upload.totalSize);
#endif // DEBUG_WEBSERVER
  }
}//end handleFileUpload()
void handleFileList() {

  String path = server.arg("dir");
  if (path == "") path = "/";

#ifdef ESP8266
  Dir dir = SPIFFS.openDir(path);
#else
  File dir = SPIFFS.open(path);
#endif

  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.sendHeader(LATER_CORS, "*");
  server.send ( 200, "text/json", "[{}");

  File entry;

#ifdef ESP8266
  while (dir.next()) {
    entry = dir.openFile("r");
#else
  entry = dir.openNextFile();
  while (entry) {
#endif

    if (strlen(entry.name()) > 2) {

      bool isDir = false;
      server.sendContent(",\n{\"type\":\"");
      server.sendContent((isDir) ? "dir" : "file");
      server.sendContent("\",\"name\":\"");
#ifdef ESP8266
      server.sendContent(entry.name() + 1);
#else
      server.sendContent(entry.name() + 1);// Ignore '/' prefix
#endif
#ifdef ESP8266
      server.sendContent( "\",\"size\":\"");
      server.sendContent(laterUtil::formatBytes(dir.fileSize()));
#endif
#ifdef ESP32
      server.sendContent( "\",\"size\":\"");
      server.sendContent(laterUtil::formatBytes(entry.size()));
#endif
      server.sendContent("\",\"mime\":\"");
      server.sendContent(getContentType(entry.name()));
      server.sendContent("\"}");
      entry.close();

    }

#ifdef ESP32
    entry = dir.openNextFile();
#endif

  }

  server.sendContent("]");
  server.sendContent("");
  /*

    String path = server.arg("dir");

    Dir dir = SPIFFS.openDir(path);
    path = String();
    String output = "[";
    while (dir.next()) {
      File entry = dir.openFile("r");
      if (true)//entry.name()!="secret.json") // Do not show secrets
      {
        if (output != "[")
          output += ',';
        bool isDir = false;
        output += "\n{\"type\":\"";
        output += (isDir) ? "dir" : "file";
        output += "\",\"name\":\"";
        output += String(entry.name()).substring(1);
        output += "\",\"size\":\"" + laterUtil::formatBytes(dir.fileSize()) + "\",";

        output += "\"mime\":\"" + getContentType(entry.name()) + "";

        output += "\"}";
      }
      entry.close();
    }

    output += "\n]";
    server.sendHeader(LATER_CORS, "*");
    server.send(200, "text/json", output);

  */
}//end handFileList()
void handleUnload() {
  char fnb[32] = {'/'};
  char *fnp = fnb + 1;
  memset(fnp, '\0', 31);
  strcpy(fnp, server.arg("name").c_str());
  if (fnp[0] != '/') fnp = fnb;
  Later.unload(fnp);

  server.sendHeader(LATER_CORS, "*");
  server.send(200, "text/json", "true");
}
void handleRun() {

  char fnb[44] = {'/'};
  char *fnp = fnb + 1;
  memset(fnp, '\0', 43);
  strcpy(fnp, server.arg("name").c_str());
  if (fnp[0] != '/') fnp = fnb;

  if (SPIFFS.exists(fnp)) {
    handleGenericHttpRun(fnp);
    /*
        server.setContentLength(CONTENT_LENGTH_UNKNOWN);
        server.sendHeader(LATER_CORS, "*");

        LATER_ENVIRON * s = Later.load(fnp);
        if (!s) {
          server.send ( 503, LATER_PLAIN, "503 - refused to load");
          server.sendContent("");
          return;
        }

        // load vars from url into script enviroment:
        String key, value, banned = ",$reload,$name,$content-type";
        for (uint8_t i = 0; i < server.args(); i++) {
          key =  "$" + server.argName(i);
          value = server.arg(i);
          if (!isdigit(value[0])) continue;
          if (banned.indexOf(',' + key + ',') > -1) continue;
          char slot = getVarNameNumber((char*)key.c_str(), s->index);
          s->VARS[(int)slot] = value.toInt();
        }
        if (server.hasArg("content-type")) {
          server.send ( 200, server.arg("content-type"), "");
        } else {
          server.send ( 200,  s->contentType, "");
        }

        s->calledFromWeb = 1;
        Later.run(fnp);
        server.sendContent("");
        if (server.hasArg("persist")) return;
        if (s->options.persist) return;

        if (  !strchr(fnp, '~') ) {
          Later.unload(fnp);
        } else {
          s->options.persist = true;
        }

    */

    //LATER_INSTANCES
    return;
  }//end if bat file found?

  server.send(404, LATER_PLAIN, "404 - batch not found" );

}//end handleRun()
void handleLog() {

  server.sendHeader(LATER_CORS, "*");

  if ( server.hasArg("tail")) {
    int count = server.arg("tail").toInt();

    if (count < 1) { // passed in url w/o value or zero, grab just the last line:
      server.send(200, LATER_PLAIN, strrchr(setRunLog, '\n') + 1);
      return;
    }

    // grab tails chars specified by tail arg:
    int pos = strlen(setRunLog) - count;
    if (pos < 0) pos = 0;
    char *ret = setRunLog + pos;
    server.send(200, LATER_PLAIN, ret);
    return;
  }//end if tail arg?
  //////////////////////////////////////////////////////////////
  // processed results  - chunked line-by-line results:
  if (server.args() > 0) {
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);   //Enable Chunked Transfer
    server.send(200, LATER_PLAIN, "");                      //Send first part WITH header

    int pos = strcspn(setRunLog + 1, "\n");

    // take, skip, larger, smaller, after, before, filter, exclude, count

    char * rest = setRunLog;
    char line[64];
    const char * term = server.arg("filter").c_str();
    const char * exclude = server.arg("exclude").c_str();
    const char * after = server.arg("after").c_str();
    const char * before = server.arg("before").c_str();
    bool is_filter = server.hasArg("filter");
    bool is_after = server.hasArg("after");
    bool is_before = server.hasArg("before");
    bool is_larger = server.hasArg("larger");
    bool is_smaller = server.hasArg("smaller");
    bool is_exclude = server.hasArg("exclude");
    bool is_take = server.hasArg("take");
    bool is_skip = server.hasArg("skip");
    bool is_count = server.hasArg("count");
    unsigned long afterTime = strtoul(after, NULL, 0);
    unsigned long beforeTime = strtoul(before, NULL, 0);

    unsigned int largerThan = server.arg("larger").toInt();
    unsigned int smallerThan = server.arg("smaller").toInt();

    int takeLeft = server.arg("take").toInt();
    int skipLeft = server.arg("skip").toInt();
    int countOfResults = 0;
    unsigned long lineTime;
    char lineTimeString[16];


    bool is_wanted;

    int logLeft = strlen(rest);

    while ( (logLeft - pos) > 1 ) {
      // copy line from string to buffer:
      strncpy(line, rest + 1, pos);
      line[pos] = '\n';
      line[pos + 1] = '\0';

      // now filter by making sure line contains term

      is_wanted = 1;
      if (is_filter && is_wanted) is_wanted = strstr (line, term);
      if (is_exclude && is_wanted) is_wanted = !strstr (line, exclude);

      if (is_larger && is_wanted)  is_wanted =  strlen(line) > largerThan;
      if (is_smaller && is_wanted) is_wanted =  strlen(line) < smallerThan;
      if (is_after && is_wanted) {
        // parse a time from log line
        int delimPos =  strcspn(line, "\t: ");
        strncpy(lineTimeString, line, delimPos);
        lineTime =  strtoul(lineTimeString, NULL, 0);
        is_wanted = (lineTime > afterTime);
      }
      if (is_before && is_wanted) {
        // parse a time from log line
        int delimPos =  strcspn(line, "\t: ");
        strncpy(lineTimeString, line, delimPos);
        lineTime =  strtoul(lineTimeString, NULL, 0);
        is_wanted = (lineTime < beforeTime);
      }
      if (is_skip && is_wanted )  is_wanted = skipLeft-- < 1;
      if (is_take && is_wanted ) {
        is_wanted = takeLeft-- > 0;
        if (takeLeft < 0) break; // early bail optomize if no more results wanted
      }//end if take?
      // based on the guantlet above, do we still want the line in the results?
      if (is_wanted) {
        if (is_count) {
          countOfResults++;
        } else {
          server.sendContent( line );
        }
      }
      // find next line, if any
      if (rest[0]) {
        rest = strchr ( rest + 1, '\n' );
        pos = strcspn(rest + 1, "\n");
      } else {
        rest[0] = '\0';
        break;
      }

      logLeft = strlen(rest);

    } // wend rest
    if (is_count) {
      server.sendContent( String(countOfResults) );
    }

    server.sendContent(F("")); // this tells web client that transfer is done
    server.client().stop();
    //Tell browser no more content is coming
    return;
  }//end if params?
  //////////////////////////////////////////////////////////////
  // END processed results
  // serve whole log:
  server.send(200, LATER_PLAIN, setRunLog + 1);

}//end handleLog()
// before log api

// after log api:
void handleCommandList() {

  server.sendHeader(LATER_CORS, "*");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);   //Enable Chunked Transfer
  server.send(200, LATER_PLAIN, "COMMAND LISTING (duplicate keys are aliases)\n\nKey\tCommand\n");                      //Send first part WITH header

  char c[2] = {0, 0};
  for (auto const & x : LATER_CMDS)   {
    c[0] = x.second;
    if (!c[0]) continue;
    server.sendContent(c);
    server.sendContent("\t");
    server.sendContent(x.first);
    server.sendContent("\n");
  }
  server.sendContent("");
}//end handleCommandList()
// a 100-line or fewer key:value store with smart api for managing it. file backed peristent storage.

void handleStore() {

  if (server.hasArg("value")) {
    if (server.hasArg("ram")) {
      LATER_STORE.update(server.arg("key").c_str(), server.arg("value").toInt());
    } else {
      LATER_STORE.set(server.arg("key").c_str(), server.arg("value").toInt());
    }

  } else if (server.hasArg("key")) {
    server.sendHeader(LATER_CORS, "*");
    server.send(200, LATER_PLAIN, String(LATER_STORE.get(server.arg("key").c_str())));
    return;
  }

  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.sendHeader(LATER_CORS, "*");
  server.send ( 200, LATER_PLAIN, "key  \tepoc\tver\tvalue\n");

  for (int i = 0; i <  LATER_STORE.length; i++) {
    server.sendContent( LATER_STORE.stringify(i) );
    server.sendContent( "\n" );
  }//next

  server.sendContent("");

  // serve whole log:

} // handleStore()
int INDENT_LEVEL = 0;

void addJSON(char * buff, const char * key, unsigned long value) {
  char liner[52] = {'\t', '\t', '\t', '\t', '\t', '\t'};
  char * line = liner;
  line += INDENT_LEVEL;
  sprintf(line, "\"%s\": %lu,\n", key, value);
  strcat(buff, liner);
}

void addJSON(char * buff, const char * key, const char * value) {
  char liner[52] = {'\t', '\t', '\t', '\t', '\t', '\t'};
  char * line = liner;
  line += INDENT_LEVEL;

  sprintf(line, "\"%s\": \"%s\",\n", key, value);
  strcat(buff, liner);
}

void backtrack(char * buff) {
  buff[strlen(buff) - 2] = '\0';
}

void handleScripts() {

  int mx = Later.scriptCount;
  char out[2048] = {'{', '\n'};
  memset (out + 2, '\0', 2046);

  INDENT_LEVEL = 1;

  addJSON(out, "count", Later.loadedScripts);
  addJSON(out, "current", Later.currentScript);
  addJSON(out, "ms", millis());
  addJSON(out, "ram", ESP.getFreeHeap());
  addJSON(out, "bootram", Later.bootRam);
  strcat(out, "\t\"scripts\":[  \n"); // start scripts:
  INDENT_LEVEL = 2;
  // iterate scripts:
  for (int i = 0; i < mx ; i++) {
    if (!SCRIPTS[i].lineCount) continue;
    strcat(out, "\t{\n");

    addJSON(out, "fileName", SCRIPTS[i].fileName);
    addJSON(out, "index", SCRIPTS[i].index);
    addJSON(out, "frozen", SCRIPTS[i].resumeLineNumber ? 1 : 0);
    addJSON(out, "interval", SCRIPTS[i].interval  );
    addJSON(out, "persist", SCRIPTS[i].options.persist  );

    addJSON(out, "line", SCRIPTS[i].i);
    addJSON(out, "lines", SCRIPTS[i].lineCount);
    addJSON(out, "exit", SCRIPTS[i].exitLineNumber);
    addJSON(out, "chars", strlen(SCRIPTS[i].program));
    addJSON(out, "vars", LATER_VAR_NAMES[i].size());
    addJSON(out, "reads", SCRIPTS[i].reads);
    addJSON(out, "writes", SCRIPTS[i].writes);

    addJSON(out, "parseTime", SCRIPTS[i].parseTime);
    addJSON(out, "runTime", SCRIPTS[i].runTime);
    if (SCRIPTS[i].runs) addJSON(out, "avgTime", SCRIPTS[i].duration / SCRIPTS[i].runs);
    addJSON(out, "cpuTime", SCRIPTS[i].duration);
    addJSON(out, "lifeTime", (millis() - SCRIPTS[i].loadedAt) * (unsigned long)1000);
    addJSON(out, "runs", SCRIPTS[i].runs);
    backtrack(out);
    strcat(out, "\n\t},\n");
  }

  INDENT_LEVEL = 0;

  if (mx) backtrack(out);

  strcat(out, "\n\t\t]\n}");//end scripts


  server.sendHeader(LATER_CORS, "*");
  server.send(200, "text/json", out);
}
int ratchetPos = 0;
void handleBench() { // w/rgb: 39267us.  w/o rgb: 9us. w/o rgb but w/ output to prevent dead code skipping: 24u
  unsigned long st = micros();
  unsigned long et = micros();
  server.sendHeader(LATER_CORS, "*");
  server.send(200, "text/plain",  "rez" );
}

#endif

#line 1 "mod.ino"
#ifdef ESP8266HTTPClient_H_
int HTTPRequest(char * url) {
  // wait for WiFi connection
  yield();
  //static HTTPClient http;
  //HTTP = &http;
  http.end();
  http.setTimeout(5000);
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {

    yield();
    return httpCode;
  } else {
    return httpCode;
  }
}//end ajax()
#endif

#line 1 "templates.ino"
#ifdef ESP32
extern "C" {
  uint8_t temprature_sens_read();
}
uint64_t macAddress = ESP.getEfuseMac();
uint64_t macAddressTrunc = macAddress << 40;
unsigned long chipID = macAddressTrunc >> 40;
#endif
std::map < const char *, unsigned long(*)(), cmp_str > TEMPLATES2 = {
  REPRAW("{timer}", millis()),
  REPRAW("{rnd}", randomReg() % 1024),
  REPRAW("{rnd2}", randomReg() % 2),
  REPRAW("{rnd8}", randomReg() % 256),
  REPRAW("{rnd16}", randomReg() % 65536),
  REPRAW("{rnd_digit}", randomReg() % 10),
  REPRAW("{rnd_reg}", randomReg()),
  REPRAW("{i}", getCurrent()->forIndex[getCurrent()->forLevel]),
  REPRAW("{ii}", getCurrent()->forLevel > 0 ? (getCurrent()->forIndex[getCurrent()->forLevel - 1]) : 0),
  REPRAW("{iii}", getCurrent()->forLevel > 1 ? (getCurrent()->forIndex[getCurrent()->forLevel - 2]) : 0),
  REPRAW("{iiii}", getCurrent()->forLevel > 2 ? (getCurrent()->forIndex[getCurrent()->forLevel - 3]) : 0),
  REPRAW("{adc}", analogRead(A0)),
  REPRAW("{a0}", analogRead(A0)),
  REPRAW("{runtime}", (micros() - getCurrent()->startedAt) / 1000),
#ifdef NTP_DEFAULT_LOCAL_PORT
  REPRAW("{time.day}", timeClient.getDay()),
  REPRAW("{time.hour}", timeClient.getHours()),
  REPRAW("{time.minute}", timeClient.getMinutes()),
  REPRAW("{time.second}", timeClient.getSeconds()),
  REPRAW("{time.epoc}", timeClient.getEpochTime()),
#endif
  REPRAW("{micros}", micros()),

#ifdef ESP8266
  REPRAW("{micros64}", micros64()),
  REPRAW("{cycle}", esp_get_cycle_count()),
  REPRAW("{frag}", ESP.getHeapFragmentation()),
  REPRAW("{flash}", ESP.getFlashChipRealSize()),
  REPRAW("{mac}", system_get_chip_id()),
  REPRAW("{chan}", wifi_get_channel()),
  REPRAW("{cpu}", system_get_cpu_freq()),

#endif

  REPRAW("{rssi}", WiFi.RSSI()),
  REPRAW("{runs}", getCurrent()->runs),
  REPRAW("{ip0}",  WiFi.localIP()[0] % 255),
  REPRAW("{ip1}",  WiFi.localIP()[1] % 255),
  REPRAW("{ip2}",  WiFi.localIP()[2] % 255),
  REPRAW("{ip3}",  WiFi.localIP()[3] % 255),

  REPRAW("{ip}",  WiFi.localIP()[3] % 255),
  REPRAW("{net}",  WiFi.localIP()[2] % 255),
  REPRAW("{ram}", ESP.getFreeHeap()),
#ifdef ADAFRUIT_NEOPIXEL_H
  REPRAW("{leds}", LATER_PIXEL_NAME.numPixels()),
#endif
  REPRAW("{line}", getCurrent()->i),
  REPRAW("{gpio0}", digitalRead(0)),
  REPRAW("{gpio2}", digitalRead(2)),
  REPRAW("{gpio3}", digitalRead(3)),
  REPRAW("{gpio4}", digitalRead(4)),
  REPRAW("{gpio5}", digitalRead(5)),
  REPRAW("{gpio12}", digitalRead(12)),
  REPRAW("{gpio13}", digitalRead(13)),
  REPRAW("{gpio14}", digitalRead(14)),
  REPRAW("{gpio15}", digitalRead(15)),
  REPRAW("{gpio16}", digitalRead(16)),
#ifdef ESP32
  REPRAW("{gpio17}", digitalRead(17)),
  REPRAW("{gpio18}", digitalRead(18)),
  REPRAW("{gpio19}", digitalRead(19)),
  REPRAW("{gpio20}", digitalRead(20)),
  REPRAW("{gpio21}", digitalRead(21)),
  REPRAW("{gpio22}", digitalRead(22)),
  REPRAW("{gpio23}", digitalRead(23)),
  REPRAW("{gpio24}", digitalRead(24)),
  REPRAW("{gpio25}", digitalRead(25)),
  REPRAW("{gpio26}", digitalRead(26)),
  REPRAW("{gpio27}", digitalRead(27)),
  REPRAW("{gpio28}", digitalRead(28)),
  REPRAW("{gpio29}", digitalRead(29)),
  REPRAW("{gpio30}", digitalRead(30)),
  REPRAW("{gpio31}", digitalRead(31)),
  REPRAW("{gpio32}", digitalRead(32)),
  REPRAW("{gpio33}", digitalRead(33)),
  REPRAW("{gpio34}", digitalRead(34)),
  REPRAW("{gpio35}", digitalRead(35)),

  REPRAW("{temp}", temprature_sens_read()),
  REPRAW("{hall}", hallRead()),

  // replacements for 8266 versions:
  REPRAW("{cpu}", getCpuFrequencyMhz()),
  REPRAW("{mac}", chipID),
  REPRAW("{flash}", ESP.getFlashChipSize()),
  REPRAW("{cycle}", xthal_get_ccount()),
  REPRAW("{micros64}", xTaskGetTickCount()),


#endif

  REPRAW("{E.pin}", EVENT[Later.lastEventSlot].pin),
  REPRAW("{E.value}", EVENT[Later.lastEventSlot].value),
  REPRAW("{E.time}", EVENT[Later.lastEventSlot].ms),
  REPRAW("{E.ms}", EVENT[Later.lastEventSlot].msNext - EVENT[Later.lastEventSlot].ms ),
  REPRAW("{args}", server.args()),
  REPRAW("{arity}", getCurrent()->arity),
  REPRAW("{arg0}", getCurrent()->subArgs[0]),
  REPRAW("{arg1}", getCurrent()->subArgs[1]),
  REPRAW("{arg2}", getCurrent()->subArgs[2]),
  REPRAW("{arg3}", getCurrent()->subArgs[3]),

};//end map
bool LaterClass::addTemplate(  const char * key, unsigned long(* callBack)()   ) {
  if (started) {
    if (debug) LATER_PRINTLN("ERROR!  .addTemplate() cannot be called after .setup()");
    return 0;
  }

  if (key[0] != '{') {
    if (debug) LATER_PRINTLN("ERROR!  .addTemplate() key must be wrapped in braces; ex: {key}");
    return 0;
  }

  TEMPLATES2[key] = callBack;
  return 1;
};
unsigned long  processTemplateExpressionsNumber(const char * line) {

  char * ptrLeft = strchr(line, '{');
  if (!ptrLeft) return 0;

  bool storeCall = 0;
  int len = strcspn (ptrLeft + 1, "}") + 2; //end param delim
  // unsigned long val;

  if (ptrLeft[1] == '&') {
    storeCall = 1;
    ptrLeft += 2;
    len -= 3;
  }

  memcpy(TEMPLATE_KEY_BUFF, ptrLeft, len);
  TEMPLATE_KEY_BUFF[len] = '\0';

  if (storeCall) {
    return LATER_STORE.get(TEMPLATE_KEY_BUFF);
  } else {
    auto callback = TEMPLATES2[TEMPLATE_KEY_BUFF];
    if (callback) return callback(); //this needs to capture value, a ulong then push in sting if line.single flag is not set
    if (ptrLeft[1] == '@') return getCurrent()->VARS[ptrLeft[2] - 65];
  }
  return 0;
} // end processTemplateExpressionsNumber()
void processTemplateExpressions2(char * line, LATER_ENVIRON * s) { // also accept line.single flag or bool here

  char * ptrLeft = strchr(line, '{');
  if (!ptrLeft) return;

  bool storeCall = ptrLeft[1] == '&';
  bool varCall = ptrLeft[1] == '@';
  int len = strcspn (ptrLeft + 1, "}") + 2; //end param delim
  unsigned long val = 0;

  memcpy(TEMPLATE_KEY_BUFF, ptrLeft, len);
  TEMPLATE_KEY_BUFF[len] = '\0';

  auto callback = TEMPLATES2[TEMPLATE_KEY_BUFF];
  if (callback) val = callback();
  if (storeCall) {
    char buff[24];
    memcpy(buff, ptrLeft + 2, len - 3);
    buff[len - 3] = '\0';
    val = LATER_STORE.get(buff);
  }//end if store call?

  if (varCall) {
    val = s->VARS[ptrLeft[2] - 65];
  }//end if var call?

  if (val) {
    //this needs to capture value, a ulong then push in sting if line.single flag is not set
    if (!varCall) { // vars will get literally embded instead of aliasing the var for no reason:
      char * nam = getVarName(TEMPLATE_KEY_BUFF, s->index);
      s->VARS[nam[1] - 65] = val;
      int varLen = strlen(nam);
      memset ( TEMPLATE_BUFFER, ' ', 16);
      strncpy(TEMPLATE_BUFFER, nam, varLen);
      TEMPLATE_BUFFER[varLen] = '\0';
    } else {
      itoa(val, TEMPLATE_BUFFER, 10);
    }
    laterUtil::replace(line, TEMPLATE_KEY_BUFF, TEMPLATE_BUFFER);
  } else {
    laterUtil::replace(line, TEMPLATE_KEY_BUFF, "0"); // prevent re-process attempts on unknown keys
  }//end if val?


  // look for additional template expressions:
  ptrLeft = strchr(line, '{');
  if (!ptrLeft) return;

  // found more, process:
  if (strrchr ( ptrLeft + 1, '}' )) processTemplateExpressions2(line, s);

}//end processTemplateExpressions2()







//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
}
using nsLATER::Later;
using nsLATER::LATER_LINE;
using nsLATER::LATER_ENVIRON;

#endif
