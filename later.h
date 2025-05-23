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

#ifdef LATER_UART_PORT_DISABLE
#define LATER_PRINT(s) String(s)
#define LATER_PRINTLN(s) String(s)
#endif
#ifndef LATER_LOG_HEADER
#define LATER_LOG_HEADER ""
#endif

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

#ifndef LATER_LINE_BUFFER
#define LATER_LINE_BUFFER 96
#endif

#ifndef LATER_LINE_LIMIT
#define LATER_LINE_LIMIT 128
#endif


#ifndef LATER_RESUME_LIMIT
#define LATER_RESUME_LIMIT 5
#endif


#ifndef LATER_HTTP_CACHE
#define LATER_HTTP_CACHE 1400
#endif


#ifndef LATER_EVENT_COUNT
#define LATER_EVENT_COUNT 5
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



#ifndef SAMPLER_LENGTH
#define SAMPLER_LENGTH 100
#endif


#ifndef SAMPLER_TYPE
#define SAMPLER_TYPE unsigned long
#endif



#ifndef LATER_VARS_LENGTH
#define LATER_VARS_LENGTH 95
#endif

#ifndef LATER_FUNCTION_CACHE_LENGTH
#define LATER_FUNCTION_CACHE_LENGTH 10
#endif

#ifndef LATER_TEMPLATE_CACHE_LENGTH
#define LATER_TEMPLATE_CACHE_LENGTH 28
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
#ifdef HIGH_RES_TIMING
class Timer {
  public:
    unsigned long st;
    const char * label;
    const char * func;
    Timer(const char * desc, const char * fun) {
      st = micros();
      func = fun;
      label = desc;
    }
    ~Timer() {
      stop();
    }
    void stop() {
      unsigned long tot = micros() - st;
      Serial.printf ("%s (%s) : %u us \n", func, label, tot );
    }
};

#define TIMER(lab) Timer usTimer( lab, __PRETTY_FUNCTION__ );
#else

#define TIMER(lab) ;

#endif
#define DUMP(lab, val) { Serial.println(lab + String(val)); }

unsigned long processTemplateExpressionsNumber(const char * line);
char SYSTEM_OUTPUT_BUFFER[LATER_LINE_BUFFER] = {0, 0, 0};

union RGB_COLOR {
  std::int32_t value;     // occupies 4 bytes
  std::uint8_t chan[4];     // occupies 1 byte
};

RGB_COLOR RGB_PIXEL;
RGB_COLOR OLD_PIXEL;
RGB_COLOR NEW_PIXEL;

#include <map>
struct cmp_str { // converts pointers into stirng values to find terms in map and let map balance red/black tree of K:V pairs
  bool operator()(char const *a, char const *b) const noexcept {
    return strcmp(a, b) < 0;
  }
};
#ifdef WEBSERVER_H
#define ESP8266WEBSERVER_H
#endif

// reusable buffers:
char TEMPLATE_BUFFER[64];
char TEMPLATE_KEY_BUFF[24];
char INCLUDE_BUFFER[1024];
char TEMP_BUFFER[128];
char FILENAME_BUFFER[32];
char FILE_BUFF[2048];
char LINE_BUFF[LATER_LINE_BUFFER];
//>> var names can consit of the following letters and numbers:
const char VARCHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_$1234567890.";
const char VARLIST[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"; // -65 to get slot 0-64, 8 slots in middle aren't used for 57 or so slots
const char CMDCHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()_+=-`~,.<>{}[];:'?/|"; // 92 chars
//<<

typedef struct FLAGs {
  static const unsigned char T = 1, V = 2, E = 4, A = 8, O = 16, H = 32, N = 64;
} FLAGs;
const FLAGs FLAGS;
std::map<std::string,  unsigned int> LATER_VAR_NAMES[LATER_INSTANCES];
unsigned long VAR_NAME_COUNT[LATER_INSTANCES];

std::map<std::string, char *> DEFINES[LATER_INSTANCES];
char setRunLog[LATER_LOG_SIZE + 16] = "";


std::map <const char *, unsigned long, cmp_str> CONSTANTS[LATER_INSTANCES];

String lastFileName = "ahriglf6456343455"; // fileLoader cache

unsigned long APPLY_ARGS[4] = {0, 0, 0, 0};

//>> public types, used to make callbacks for commands+function, run backups or mods, etc

struct CsvState;
#ifdef HIGH_RES_TIMING

#define HRT_TIME(section) { unsigned long et = micros();  \
    HR_PERF. section  .total += et - st; \
    HR_PERF. section .count++; \
  }

#define HRT_COUNT(section) { HR_COUNTS.section++;\
  }
#define HRT_START unsigned long st=micros();
typedef struct HIGH_RES_COUNTS {
  unsigned int getVarName;
  unsigned int getVarNameNumber;
  unsigned int Number;
  unsigned int trimRight;
  unsigned int copyUntilChar;
  unsigned int indexOf;
  unsigned int replace;
  unsigned int splitStringByChar;
} HIGH_RES_COUNTS;
HIGH_RES_COUNTS HR_COUNTS;

typedef struct HIGH_RES_PERF_TIMING {
  unsigned long total; // ()
  unsigned long count; // ()
  unsigned long avg; // ()
} HIGH_RES_PERF_TIMING;

void dumpSection(const HIGH_RES_PERF_TIMING * sec, const char * label) {
  if (!sec->count) return;
  unsigned long avg = sec->total;
  avg = avg / sec->count;
  HIGH_RES_TIMING.println( String(label) + ": " + String(sec->count) + "x in\t" + String(sec->total) + "us,\t~" + String(avg)  );
}

typedef struct HIGH_RES_PERF_TIMINGS {

  HIGH_RES_PERF_TIMING array;
  HIGH_RES_PERF_TIMING cond;
  HIGH_RES_PERF_TIMING math;
  HIGH_RES_PERF_TIMING templates;
  HIGH_RES_PERF_TIMING vars;
  HIGH_RES_PERF_TIMING loop;
  HIGH_RES_PERF_TIMING number;
  HIGH_RES_PERF_TIMING getVarName;

  void reset() {
    array = {0, 0, 0};
    cond = {0, 0, 0};
    math = {0, 0, 0};
    templates = {0, 0, 0};
    vars = {0, 0, 0};
    loop = {0, 0, 0};
    number = {0, 0, 0};
  };

  void report() {
    dumpSection(&array, "arrs");
    dumpSection(&cond, "cond");
    dumpSection(&math, "math");
    dumpSection(&templates, "tmpl");
    dumpSection(&vars, "vars");
    dumpSection(&loop, "loop");
    dumpSection(&number, "number");
    dumpSection(&getVarName, "varName");

    HIGH_RES_TIMING.println( "\nCounts:");
    HIGH_RES_TIMING.println( "getVarName " + String(HR_COUNTS.getVarName));
    HIGH_RES_TIMING.println( "getVarNameNumber " + String(HR_COUNTS.getVarNameNumber));
    HIGH_RES_TIMING.println( "trimRight " + String(HR_COUNTS.trimRight));
    HIGH_RES_TIMING.println( "copyUntilChar " + String(HR_COUNTS.copyUntilChar));
    HIGH_RES_TIMING.println( "indexOf " + String(HR_COUNTS.indexOf));
    HIGH_RES_TIMING.println( "replace " + String(HR_COUNTS.replace));
    HIGH_RES_TIMING.println( "indexOf " + String(HR_COUNTS.indexOf));
    HIGH_RES_TIMING.println( "splitStringByChar " + String(HR_COUNTS.splitStringByChar));
  };

} HIGH_RES_PERF_TIMINGS;
HIGH_RES_PERF_TIMINGS HR_PERF;

#else
#define HRT_TIME(section) { }
#define HRT_START ;
#define HRT_COUNT(section) { }
#endif
#ifdef LATER_LINE_PROFILING
typedef struct LINE_PROFILE {
  unsigned long total; // ()
  unsigned long count; // ()
  unsigned long parse; // ()
} LINE_PROFILE;
#endif

typedef unsigned long (*noArgFunc) ();
typedef unsigned long (*threeArgFunc) (unsigned long a, unsigned long b, unsigned long c);

typedef struct LATER_EVENT {
  long pin = -1; // which pin to watch?
  // char name[16]; // name of subroutine to run when true
  unsigned long value; // pin value, maybe other data
  unsigned long ms; // timer when event happened
  unsigned long msNext; // timer when event happened
  long programSlot = -1; // holds link to running script
} LATER_EVENT;
LATER_EVENT EVENT[LATER_EVENT_COUNT];

typedef struct LATER_OPTIONS {
  bool debug; // print debug info to the console?
  bool perf; // print perf info to the console?
  bool strict; // disable legacy handlers and slower features?
  bool persist; // keep the script in ram?
  bool socket; // use web socket as print mechanism?
  bool noget; // disables GET param var value mapping
  bool step; // activate step-through mode, freezing after each line until /next/ is hit
} LATER_OPTIONS;

// 37800b free before bumping up lines from 64 to 96
// 35644
typedef struct LATER_RESUME {
  unsigned long timestamp; // when to re-activate script?
  char fileName[32]; // name of script file to activate
} LATER_RESUME;
typedef struct LATER_LINE {
  int start, stop; // position of line in raw program[] buffer
  byte data, len, flags, exit; //line nums/size, exit line num, flag bits: {hasTemplate,hasVar,hasStatic,hasParens}
#ifdef LATER_LINE_PROFILING
  LINE_PROFILE profile;
#endif
  char cmd; // shorthand command code
  char exprCache[11];
} LATER_LINE;

#ifdef LATER_CSV
struct CsvState {
  //const char * fn;
  //char * filter;
  bool hasLineParam = false;
  char delim = ',';
  // uint8_t id = 0;
  uint8_t skip = 0;
  uint8_t blockSize = 0;
  uint8_t morePointer = 0;
  uint8_t varSlots[12];
  char    delimStr[2] = ",";
  uint16_t lineNeeded = 1;
  char fn[36] = "";
  char filter[36] = "";
};
#endif

typedef struct LATER_ENVIRON {
  byte index; // which numer of SCRIPTS are we?
  long i; // what line are we at?
  LATER_LINE lines[LATER_LINE_LIMIT]; // holds meta about each line
  char program[LATER_PROGRAM_SIZE]; // program code string buffer
  char fileName[32]; // file name of the program

  char switchTerm[16]; // term used to lexically match case statements buffer
  char contentType[32]; // used for http response, set by #type= "macro"

  int eventSlot = -1; // when using events, store slot# here for unload to clean up
  int status; // for returning web call success, errs, etc
  int lastLineNumber = 0; // for file parser, caches last parsed line
  char * lastLinePtr; // for file parser, caches last parsed line
  noArgFunc TEMPS[ LATER_TEMPLATE_CACHE_LENGTH]; // local template function cache
  threeArgFunc FUNCS[LATER_FUNCTION_CACHE_LENGTH];// local function cache
  long lineCount = 0; // how many parsed code lines are in the program?
  long forTop[4], forStep[4], forIndex[4], forStart[4], forEnd[4], forLevel = 0; // int_fast16_t
  long switchExit; // tracking switch statement cases
  unsigned long counter = 0; // for the {counter} template

  unsigned long intervals[8] = {0, 0, 0, 0,   0, 0, 0, 0}; // ms timer snapshots for repeating sections ; interval command
  unsigned long loadedAt, startedAt, runs, duration, runTime, parseTime, reads, writes, interval; // ms timestamp at program start, how many executions?
  unsigned long VARS[LATER_VARS_LENGTH];// holds variable values
  unsigned int TEMP_COUNT = 0; // how many templates are cached?
  unsigned int FUNC_COUNT = 0; // how many functions are cached?
  unsigned int LITS_COUNT = 2; // how many literals are var-cached?
  unsigned long subArgs[8];
  unsigned long jumpIfOperand = 0; // stores one compare term per program for fast jumping around
  // bool persist; // unload after execution if false;
  unsigned long resumeMillis; // for freeze, when to thaw?
  unsigned long timer; // for tracking timer commands
  unsigned long subReturnValue = 99; // stores var slot for call command to recieve value
  byte intervalCount = 0; // how many intervals are active?
  char jumpIfOperator = 0;
  byte subReturnLine; // for calling subs, calling line goes here
  byte resumeLineNumber; // for freeze, where to thaw?
  byte arity; // how many args passed
  byte startLineNumber = 0; // over-rides the default of 0 as top line, to allow simple+effecient run-once code via start command
  byte exitLineNumber = 0; // over-rides the default last line from the real last line. can be jumped over in unload() to allow cleanup routine
  bool calledFromWeb; // switches print from Serial to server
  bool storeDirty; // set by store update, reset after first thereafter run
  bool isSuspended; // used by unload() to skip finish section code when suspending

  bool stepReady; // used by step option to toggle run/pause in each game loop
#ifdef LATER_CSV
  CsvState csv;
#endif

  LATER_OPTIONS options;

  unsigned long Number(const char * str) {

    if (str[0] == '@' ) { //&& str[2] == '_') {
      return  this->VARS[str[1] - 65];
    } else {
      if (str[0] == '{') {
        return processTemplateExpressionsNumber(str);
      } else {
        return str[1] ? strtoul(str, NULL, 10) : (str[0] - 48); // atoi(str);
      }
    }// end if var format?
    return 0; // failsafe
  }

  void freeze(unsigned long duration) {
    this->resumeLineNumber = this->i + 1;
    this->resumeMillis = millis() + duration;
    this->duration = (micros() -  this->startedAt) / 1000;
  }
} LATER_ENVIRON;
//<<

LATER_ENVIRON SCRIPTS[LATER_INSTANCES]; // dd666
// cdefnoqrstux
// left: y
// char cmd name constants
#define LATER_apply '6'
#define LATER_noop 'n'
#define LATER_else 'E'
#define LATER_var 'V'
#define LATER_store 'g'
#define LATER_global 'm'
#define LATER_static 'd'
#define LATER_goto '4'
#define LATER_fi 'F'
#define LATER_if 'I'
#define LATER_math '7'
#define LATER_csv '8'
#define LATER_end 'X'
#define LATER_pixel 'A'
#define LATER_solid 's'
#define LATER_render 'r'
#define LATER_rotate 'o'
#define LATER_sub 'J'
#define LATER_digitalWrite 'G'
#define LATER_analogWrite 'w'
#define LATER_print 'T'
#define LATER_println 'l'
#define LATER_for 'R'
#define LATER_next 'N'
#define LATER_start 'z'
#define LATER_gosub 'Y'
#define LATER_timer 't'
#define LATER_case 'K'
#define LATER_option 'c'
#define LATER_interval 'i'
#define LATER_sleep 'S'
#define LATER_pinMode 'M'
#define LATER_log 'L'
#define LATER_switch 'W'
#define LATER_ping 'H'
#define LATER_assert 'k'
#define LATER_break 'B'
#define LATER_call 'h'
#define LATER_cgi 'j'
#define LATER_clear 'C'
#define LATER_continue 'O'
#define LATER_default 'U'
#define LATER_delete 'e'
#define LATER_do 'D'
#define LATER_endsub 'Q'
#define LATER_exit 'x'
#define LATER_flash '3'
#define LATER_freeze 'f'
#define LATER_grad 'a'
#define LATER_iif 'b'
#define LATER_json '5'
#define LATER_loop 'P'
#define LATER_on 'v'
#define LATER_resume '1'
#define LATER_return 'Z'
#define LATER_run 'u'
#define LATER_suspend '2'
#define LATER_type 'p'
#define LATER_unload 'q'
const char COMMANDS_ENDING_WITH_LITERALS[] = {LATER_if, LATER_do, LATER_iif, LATER_freeze, LATER_sleep, LATER_goto, LATER_rotate, LATER_suspend, LATER_analogWrite, LATER_var, 0};
const char COMMANDS_STARTING_WITH_LITERALS[] = { LATER_interval, LATER_digitalWrite, LATER_analogWrite, LATER_for, LATER_sleep, 0};
const char COMMANDS_NEEDING_OUTPUT[] = { LATER_log, LATER_switch, LATER_print, LATER_println, LATER_ping, LATER_timer, LATER_assert, LATER_run, 0};
const char COMMANDS_NEEDING_WHITESPACE[] = {LATER_gosub, LATER_call, LATER_interval, LATER_flash, LATER_option, LATER_json, LATER_csv,  0};

// container for user-defined program variables
std::map<const char *,  char, cmp_str> LATER_CMDS = { // 300 bytes for all commands
  {"_", 'l'},
  {"__", 'l'},
  {"analogWrite", 'w'},
  {"apply", '6'},
  {"assert", 'k'},
  {"attachInterrupt", 'v'}, // alias: on
  {"break", 'B'},
  {"call", 'h'},
  {"case", 'K'},
  {"cgi", 'j'},
  {"clear", 'C'},
  {"continue", 'O'},
  {"csv", '8'},
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
  {"flash", '3'},
  {"for", 'R'},
  {"freeze", 'f'},
  {"global", 'm'},
  {"gosub", 'Y'},
  {"goto", '4'},
  {"gpio", 'G'},// alias: digitalWrite
  {"grad", 'a'},
  {"if", 'I'},
  {"iif", 'b'},
  {"int", 'V'}, // alias: var
  {"interval", 'i'},
  {"json", '5'},
  {"log", 'L'},
  {"loop", 'P'},
  {"math", '7'},
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
  {"resume", '1'},
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
  {"suspend", '2'},
  {"switch", 'W'},
  {"timer", 't'},
  {"type", 'p'},
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
#define SUB_PATH(_key, _expr, _blurb) LATER_SERVER_NAME.on("/" #_key, _expr); LATER_SERVER_NAME.on("/" #_key "/", _expr);PATHS["/" #_key]=#_expr;BLURBS["/" #_key]=#_blurb
#endif
//<<
// used inline in intitial expression function and template libs
#define RAWFUNC(key,expr) { key, [](unsigned long a=0, unsigned long b=0, unsigned long c=0)->unsigned long {return expr;}}
#define REPRAW(key,expr) { key, []()->unsigned long {return expr;}}
#define TEMPLATE(expr) []()->unsigned long {return expr;}
#ifdef SAMPLER_ENABLED

typedef struct LATER_SAMPLE {
  SAMPLER_TYPE value;
  unsigned long time;
};
typedef struct LATER_SAMPLER {
  LATER_SAMPLE data[SAMPLER_LENGTH];

  SAMPLER_TYPE lastValue;
  SAMPLER_TYPE total;
  SAMPLER_TYPE min;
  SAMPLER_TYPE max;
  SAMPLER_TYPE avg;

  unsigned long minTime;
  unsigned long maxTime;

  unsigned long lastTime;
  unsigned int limit = SAMPLER_LENGTH;
  unsigned int length;

  unsigned int add(SAMPLER_TYPE value);
  unsigned int clear(void);
};
unsigned int LATER_SAMPLER::add( SAMPLER_TYPE value ) {
  lastValue = value;
  lastTime = millis();

  if (length == limit) return 0;

  if (length == 0  ) {
    min = value;
    minTime = lastTime;
  }

  data[length++].value = value;
  data[length].time = lastTime;

  total += value;
  avg = total / length;

  if (min > value) {
    min = value;
    minTime = lastTime;
  }

  if (max < value) {
    max = value;
    maxTime = lastTime;
  }

  return length;
}
unsigned int LATER_SAMPLER::clear( ) {
  for (int i = 0; i < limit; i++) {
    data[i].value = 0;
    data[i].time = 0;
  }
  total = 0;
  avg = 0;
  min = 0;
  max = 0;
  minTime = 0;
  maxTime = 0;
  lastValue = 0;
  lastTime = 0;
  length = 0;
  return 1;
}

LATER_SAMPLER Sampler;

#endif

unsigned long randomReg();
#line 743 "danscript.ino"
unsigned long clamp(int a);
#line 889 "danscript.ino"
LATER_ENVIRON* getCurrent();
#line 1132 "commands.ino"
template <class text>void uniPrintln(text content);
#line 1151 "commands.ino"
template <class text>void uniPrint(text content);
#line 1311 "commands.ino"
void loadStoredValuesForStore();
#line 1316 "commands.ino"
unsigned long evalLite(char * lb, LATER_ENVIRON * s);
#line 1351 "commands.ino"
CsvState* getCSV(char * codeLine, LATER_ENVIRON * s);
#line 31 "config.ino"
void APPLY_CONFIG();
#line 37 "config.ino"
void handleConfigInterface();
#line 60 "config.ino"
void handleConfigLang();
#line 82 "config.ino"
byte setConfig(String key, String value);
#line 124 "config.ino"
void handleConfig();
#line 137 "config.ino"
void loadConfig();
#line 180 "config.ino"
void saveConfig();
#line 6 "core.ino"
unsigned long Number( const char * str, const unsigned long * VARS );
#line 24 "core.ino"
char * getVarName(const char* longName, const int scriptIndex);
#line 68 "core.ino"
char getVarNameNumber(char* longName, int scriptIndex);
#line 79 "core.ino"
void removeDoubleLines(char * buff);
#line 89 "core.ino"
void removeMultiLineComments(char * buff);
#line 105 "core.ino"
void replaceEndingLiterals(char * line, LATER_ENVIRON * s);
#line 127 "core.ino"
void replaceAllLiterals(char * line, LATER_ENVIRON * s);
#line 161 "core.ino"
void replaceStartingLiterals(char * line, LATER_ENVIRON * s);
#line 171 "core.ino"
void replaceVarNames(char * line, int scriptIndex);
#line 184 "core.ino"
void autoEqualsInsert(char * line);
#line 217 "core.ino"
void buildExitPoints( LATER_ENVIRON * SCRIPT );
#line 467 "core.ino"
void processVariableExpressions(char * line, unsigned long * VARS);
#line 520 "core.ino"
bool provideArrayReturnAll(char * assign, int elmSectionLength, long value);
#line 531 "core.ino"
bool processArray(char * line, LATER_ENVIRON * s, int varSlot);
#line 671 "core.ino"
bool evalMath(char * s, LATER_ENVIRON * script, int DMA);
#line 903 "core.ino"
bool evalConditionalExpression(char * string_condition, LATER_ENVIRON * s);
#line 1136 "core.ino"
void popHttpResponse();
#line 1154 "core.ino"
bool processResponseEmbeds(char * line, LATER_ENVIRON * s);
#line 1305 "core.ino"
void processStringFormats(char* s , int index );
#line 1443 "core.ino"
void handleEval();
#line 1463 "core.ino"
void outputPaddedNumber(unsigned long value, const char * suffix, int width);
#line 1497 "core.ino"
void finishRun(LATER_ENVIRON * s);
#line 34 "http.ino"
void handleGenericHttpRun(String fn);
#line 73 "http.ino"
void handleAPI();
#line 184 "http.ino"
void handleDelete();
#line 206 "http.ino"
void handleReboot();
#line 217 "http.ino"
void handleResume();
#line 231 "http.ino"
void handleSuspend();
#line 291 "http.ino"
void bindServerMethods();
#line 405 "http.ino"
void handleLS();
#line 482 "http.ino"
void handleEditor();
#line 513 "http.ino"
String getContentType(String filename);
#line 535 "http.ino"
bool handleFileRead(String path);
#line 608 "http.ino"
void handleFileUpload();
#line 648 "http.ino"
void handleFileList();
#line 752 "http.ino"
void handleUnload();
#line 777 "http.ino"
void handleRun();
#line 840 "http.ino"
void handleLog();
#line 1030 "http.ino"
void handleCommandList2();
#line 1068 "http.ino"
void handleStore();
#line 1107 "http.ino"
void addJSON(char *buff, const char *key, unsigned long value);
#line 1115 "http.ino"
void addJSON(char *buff, const char *key, const char *value);
#line 1124 "http.ino"
void backtrack(char *buff);
#line 1128 "http.ino"
void handleScripts();
#line 1 "loader.ino"
int loadScript(const char * scriptFileName);
#line 423 "loader.ino"
void replaceIncludes(char * fileBuff);
#line 458 "loader.ino"
void replaceSpecialMacros(char * fileBuff, const char * scriptFileName);
#line 480 "loader.ino"
void sniffContentType( char * fileBuff, LATER_ENVIRON * SCRIPT );
#line 493 "loader.ino"
void populateDefines(char * fileBuff, int scriptIndex);
#line 517 "loader.ino"
void deInlineVarAssignments(char * buff);
#line 541 "loader.ino"
int convertIIFs(char * line, char * lb, int endpos);
#line 562 "loader.ino"
void removeSingleLineComments(char * line, char * cmd);
#line 585 "loader.ino"
void harvestMacros(char * line, int scriptIndex);
#line 636 "loader.ino"
void cleanupVarDeclarations(char * line);
#line 658 "loader.ino"
void expandRangeOperators(char * line, LATER_ENVIRON * SCRIPT);
#line 708 "loader.ino"
void replaceEndCommands(char * line);
#line 723 "loader.ino"
bool embedVariables(char * line, bool isConstant, LATER_ENVIRON * SCRIPT);
#line 737 "loader.ino"
int parseVarCommands(char * line, char * linePtr, int lineData, LATER_ENVIRON * s);
#line 776 "loader.ino"
bool isStaticValue(char * str);
#line 781 "loader.ino"
void parsePixel(char * lb, LATER_LINE * l, LATER_ENVIRON * s );
#line 920 "loader.ino"
unsigned long applyArgs( LATER_LINE * l, LATER_ENVIRON * s );
#line 950 "loader.ino"
void parseArgsForApply(char * lb, char * CACHE );
#line 976 "loader.ino"
void parseApply(char * lb, LATER_LINE * l, LATER_ENVIRON * s );
#line 7 "mod.ino"
int HTTPRequest(char * url);
#line 2 "runner.ino"
void runScript();
#line 31 "templates.ino"
void getDate(unsigned long epoc);
#line 264 "templates.ino"
void embedTemplates(char * line, LATER_ENVIRON * s);
#line 307 "templates.ino"
void embedFunctions(char * line, LATER_ENVIRON * s);
#line 477 "templates.ino"
void processTemplateExpressions2(char * line, LATER_ENVIRON * s);
#line 684 "templates.ino"
uint8_t parseByteFromChars(char * ptr);
#line 697 "templates.ino"
void handleCommandList();
#line 810 "templates.ino"
void handleStep();
#line 891 "templates.ino"
void handleDump();
#line 743 "danscript.ino"
unsigned long  clamp(int a) {
  return a > 0 ? (a < 255 ? a : 255) : 0;
}

std::map < const char *, unsigned long(*)(unsigned long, unsigned long, unsigned long), cmp_str > FUNCS = {
  RAWFUNC("SUM", a + b + c),
  RAWFUNC("DIFF", a - b - c),
  { "MULT", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 1)->unsigned long {return a * b * c; }},
  { "DIV", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 1)->unsigned long {return a / b; }},
  { "AND", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 1)->unsigned long {return a && b && c; }},
  RAWFUNC("OR", a || b || c),
  RAWFUNC("OR", a || b || c),
  RAWFUNC("MIN", min(a, b)),
  RAWFUNC("MAX", max(a, b)),
  RAWFUNC("SQRT", sqrt(a)),
  RAWFUNC("CBRT", cbrt(a)),
  RAWFUNC("SIN", sin(a)),
  RAWFUNC("TAN", tan(a)),
  RAWFUNC("COS", cos(a)),
  RAWFUNC("GPIO", digitalRead(a)),
  RAWFUNC("ADC", analogRead(a)),
  RAWFUNC("MED", a > b ? ((a < c) ? a : (b < c ? c : b)) : ((b < c) ? b : (c < a ? a : c))),
  RAWFUNC("MODE", a == b ? a : (b == c ? b : a == c ? a : b)),
  RAWFUNC("AVG", (a + b + (c || 0)) / 3),
  RAWFUNC("CLAMP",  a > 0 ? (a < 255 ? a : 255) : 0 ),
  RAWFUNC("POW", pow(a, b)),
  { "MAP", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {
      float rate = (float)b / (float)c;
      return rate * (float) a;
    }
  },
  RAWFUNC("EQ", a == b),
  RAWFUNC("NEQ", a != b),
  RAWFUNC("MOD", a % b),
  RAWFUNC("GT", a > b), // can use these to make conditional replacement functions, like apply does.
  RAWFUNC("LT", a < b),
  RAWFUNC("GTE", a >= b),
  RAWFUNC("LTE", a <= b),
  RAWFUNC("ID", a),
  RAWFUNC("IIF", a ? b : c),
  RAWFUNC("ELSE", a ? a : b),
  RAWFUNC("AtBeC", a ? b : c),
  RAWFUNC("AtAeB", a ? a : b),
  RAWFUNC("AoBtAeC", (a || b) ? a : c),
  RAWFUNC("AoBtBeC", (a || b) ? b : c),
  RAWFUNC("AnBtAeC", a && b ? a : c),
  RAWFUNC("AnBtBeC", a && b ? b : c),
  RAWFUNC("NAND", !a || !b),
  RAWFUNC("NOT", !a),

#ifdef SAMPLER_ENABLED
  RAWFUNC("DATA", Sampler.add(a) ),
  RAWFUNC("DATA_VAL", Sampler.data[a].value ),
  RAWFUNC("DATA_AT", Sampler.data[a].time ),
#endif

#ifdef ADAFRUIT_NEOPIXEL_H
  RAWFUNC("RGB", Adafruit_NeoPixel::Color(a, b, c)),
  RAWFUNC("CRGB", Adafruit_NeoPixel::Color(clamp(a), clamp(b), clamp(c))),
  RAWFUNC("HSV", Adafruit_NeoPixel::ColorHSV(a, b, c)),
#endif
#ifdef __INC_FASTSPI_LED2_H
  { "RGB", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {
      return ((a * 256 * 256) + (b * 256) + c);
    }
  },
  { "HSV", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {
      LATER_PIXEL_TYPE x;
      x.setHSV(a / 256, b, c);
      return (x.r * 256 * 256) + (x.g * 256) + x.b;
    }
  },
  { "HSL", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {
      LATER_PIXEL_TYPE x;
      x.setHSV(a, b, c);
      return (x.r * 256 * 256) + (x.g * 256) + x.b;
    }
  },
#endif

  RAWFUNC("CSPRNG", ( (randomReg()) % ((a + 1) - b)) + b),
  RAWFUNC("PRNG", (rand() % ((a + 1) - b)) + b),
  {"SEED", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {srand(a); return 1;}}
};
//
//>> main public interface:
class LaterClass {
  public:
    bool debug = false;
    int scriptCount = LATER_INSTANCES;
    int currentScript = 0;
    int loadedScripts = 0;
    int lastEventSlot = -1;
    LATER_RESUME resumes[LATER_RESUME_LIMIT];

    bool started = 0; // has .setup() been called yet?
    char httpResponseTextBuffer[LATER_HTTP_CACHE] = {0};
    char * httpResponseText;

    unsigned long bootRam; // how big is heap on load

    void setup();
    void loop();
    LATER_ENVIRON * getByName(const char * fileName);
    LATER_ENVIRON *  load(const char * fileName);
    void init(const char * fileName);
    bool suspend(const char * fileName, unsigned long resumeMs);
    bool resume(const char * fileName);
    void unload(const char * fileName);
    void run(const char * fileName);
    void dump(const char * fileName);
    bool addCommand(const char * commandName, bool(*)(char *, LATER_LINE *, LATER_ENVIRON * s) ); // define a new command
    bool addFunction(const char * commandName, unsigned long(*)(unsigned long, unsigned long, unsigned long) );
    bool addTemplate(const char * key, unsigned long(*)() );

    std::map <char, bool(*)(char *, LATER_LINE *, LATER_ENVIRON *)> addons;

} Later ;
//<<
inline LATER_ENVIRON * getCurrent() {
  return &SCRIPTS[Later.currentScript];
} //end getCurrent()
inline unsigned long randomReg() {
#ifdef ESP8266
  return RANDOM_REG32;
#else
  return esp_random();
#endif
}
void LaterClass::setup() {

  started = true;

  setRunLog[LATER_LOG_SIZE + 14] = '#';
  setRunLog[LATER_LOG_SIZE + 15] = '\0';

#ifdef ESP8266WEBSERVER_H
  bindServerMethods();
#endif
  bootRam = ESP.getFreeHeap();

  for (int i = 0; i < scriptCount; i++) {
    VAR_NAME_COUNT[i] = 3;
    SCRIPTS[i].index = i;
  }//next script

  loadStoredValuesForStore();

  if (debug) LATER_PRINTLN("Later - Setup()");
  /// this has to be added here so that it can use function prototype defined after the rest of the Functions
  Later.addFunction("DMA", FUNCTION( getCurrent()->VARS[a] = b; return b;  )); // using FUNCTION MACRO
  // run autoexec.bat if available
  if (SPIFFS.exists("/autoexec.bat")) {
    if (debug) LATER_PRINTLN("Later - Autoexec.bat will run");
    run("/autoexec.bat");
    if (debug) LATER_PRINTLN("Later - Autoexec.bat ran");
    unload("/autoexec.bat");
  }
  // run autoexec.lnk if available

  if (SPIFFS.exists("/autoexec.lnk")) {
    if (debug) LATER_PRINTLN("Later - Autoexec.lnk will run");

    char TEMP_BUFFER[128];
    char * files = TEMP_BUFFER;
    memset(files, '\0', 128);

    File file = SPIFFS.open("/autoexec.lnk", "r");
    file.readBytes(files, 128);
    file.close();
    //char fileName[42];
    char * pch;
    char * eol;

    pch = strtok (files, "\n");
    while (pch != NULL) {
      strcpy(FILENAME_BUFFER, pch);
      eol = strchr(FILENAME_BUFFER, '\n');
      if (eol) eol[0] = '\0';
      if (strlen(FILENAME_BUFFER) > 3 && FILENAME_BUFFER[0] == '/' && strstr(FILENAME_BUFFER, ".bat") ) {
        run(FILENAME_BUFFER);
      }
      pch = strtok (NULL, "\n");
    }

    if (debug) LATER_PRINTLN("Later - Autoexec.lnk ran");
  }//end if autoexec.lnk?
}//end DS setup()
void LaterClass::loop() {


  unsigned long ms = millis();

  for (int i = 0; i < scriptCount; i++) {
    if (ms > SCRIPTS[i].resumeMillis) {
      // look for interval processes:
      if ( SCRIPTS[i].interval > 0) run(SCRIPTS[i].fileName);

      // look for frozen processes
      if (SCRIPTS[i].resumeMillis  ) run(SCRIPTS[i].fileName);
    }

  }//next i
  // look for suspended processes ready to resume:
  for (int i = 0; i < LATER_RESUME_LIMIT; i++) {
    if (Later.resumes[i].timestamp && (ms > Later.resumes[i].timestamp) ) {
      resume(Later.resumes[i].fileName);
    }
  }//next i

  // roll these loops

  // look for interupts here, from a table or something.
  for (int i = 0; i < LATER_EVENT_COUNT; i++) {
    auto e = EVENT[i];
    if (e.pin != -1 && (byte)digitalRead(e.pin) != e.value) {
      // run script here and now, if loaded.
      LaterClass::run( SCRIPTS[e.programSlot].fileName  );
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

bool LaterClass::resume(const char * fileName) {

  LaterClass::load(fileName);
  LATER_ENVIRON * s = getByName(fileName);

  if (!s) {
    if (SPIFFS.exists(fileName)) { // schedule to run soon, hopefully it can
      int i = 0;
      for (int mx = LATER_RESUME_LIMIT; i < mx; i++) if (strstr(Later.resumes[i].fileName, s->fileName)) break;
      if (i == LATER_RESUME_LIMIT) { // find first unused slot
        i = 0;
        for (int mx = LATER_RESUME_LIMIT; i < mx; i++) if ( Later.resumes[i].timestamp == 0) break;
      }
      if (i == LATER_RESUME_LIMIT) return false;
      //add to LATER_RESUME with ms and filename
      strcpy(Later.resumes[i].fileName, s->fileName);
      Later.resumes[i].timestamp = millis() + 100;
    }
    return false;
  }

  s->isSuspended = false;

  int i = 0; // wipe out any stored  resumes ref to this program:
  for (int mx = LATER_RESUME_LIMIT; i < mx; i++) if (strstr(Later.resumes[i].fileName, fileName)) break;
  if (i != LATER_RESUME_LIMIT) {
    Later.resumes[i].fileName[0] = '\0';
    Later.resumes[i].timestamp = 0;
  }//end if old schedule found?

  char stateFileName[32];
  strcpy(stateFileName, s->fileName);
  strcpy(stateFileName + strlen(stateFileName) , ".ram" );

  long int ssize = sizeof(*s);

  File file5 = SPIFFS.open( stateFileName, "r");
  if (file5) {
    file5.read((byte*) s, ssize);
    file5.close();
  } else {
    //return false;
  }

  LaterClass::run(fileName);

  return true;
}//end DS resume()

bool LaterClass::suspend(const char * fileName, unsigned long resumeMs) {
  LATER_ENVIRON * s = getByName(fileName);
  if (!s) return false;

  s->isSuspended = true;
  char stateFileName[32];
  strcpy(stateFileName, s->fileName);
  strcpy(stateFileName + strlen(stateFileName) , ".ram" );
  if (resumeMs > 0) {
    int i = 0;
    for (int mx = LATER_RESUME_LIMIT; i < mx; i++) if (strstr(Later.resumes[i].fileName, s->fileName)) break;
    if (i == LATER_RESUME_LIMIT) { // find first unused slot
      i = 0;
      for (int mx = LATER_RESUME_LIMIT; i < mx; i++) if ( Later.resumes[i].timestamp == 0) break;
    }

    //add to LATER_RESUME with ms and filename
    strcpy(Later.resumes[i].fileName, s->fileName);
    Later.resumes[i].timestamp = millis() + resumeMs;
  }

  long int ssize = sizeof(*s);

  File file5 = SPIFFS.open( stateFileName, "w");
  if (file5) {
    file5.write((byte*) s, ssize);
    file5.close();
  } else {
    return false;
  }

  LaterClass::unload(s->fileName);

  return true;
}//end DS suspend()
void LaterClass::unload(const char * fileName) {
  LATER_ENVIRON * s = getByName(fileName);
  if (!s) return;

  lastFileName = "";
  // check here if linecount and lastline are the same, if not, run code after that exit point

  if (s->lineCount != s->exitLineNumber && !s->isSuspended) {
    int oldScript = Later.currentScript;
    Later.currentScript = s->index;

    s->resumeLineNumber = s->exitLineNumber + 1; // jump past normal exit
    s->exitLineNumber = 0; // don't stop until end
    runScript();
    Later.currentScript = oldScript;
  }//end if

  // remove line data and exit points
  for (int i = 0; i < s->lineCount; i++) {
    s->lines[i].exit = 0;
    s->lines[i].data = 0;
    memset(s->lines[i].exprCache, 0, 10);
#ifdef LATER_LINE_PROFILING
    s->lines[i].profile = {0, 0, 0};
#endif
  }

#ifdef LATER_CSV
  memset(s->csv.fn, '\0', 16);
#endif

  //s->exprCacheLen = 0;
  //remove script and reset options
  loadedScripts--;
  s->fileName[0] = '\0';
  memset ( s->program, '\0', LATER_PROGRAM_SIZE);
  s->i = 0;
  s->resumeMillis = 0;
  s->interval = 0;
  s->i = 0;
  s->counter = 0;
  s->TEMP_COUNT = 0;
  s->FUNC_COUNT = 0;
  s->LITS_COUNT = 2;
  s->startLineNumber = 0;
  s->resumeLineNumber = 0;
  s->exitLineNumber = 0;
  s->lineCount = 0;
  s->options.noget = 0;
  s->options.debug = 0;
  s->options.socket = 0;
  s->options.persist = 0;
  s->options.perf = 0;
  s->options.step = 0;
  s->options.strict = 0;
  s->forLevel = 0;
  s->intervalCount = 0;
  s->duration = 0;
  //s->program[0] = '\0';
  strcpy(s->contentType, LATER_PLAIN);

  if (s->eventSlot > -1) { // cleanup events by resetting times and pint to defaults
    EVENT[s->eventSlot].pin = -1;
    EVENT[s->eventSlot].value = 0;
    EVENT[s->eventSlot].msNext = 0;
    EVENT[s->eventSlot].ms = 0;
    EVENT[s->eventSlot].programSlot = -1;
  } // end event cleanup

  // reset all VARs to zero
  for (int i = 0; i < LATER_VARS_LENGTH; i++) s->VARS[i] = 0;

  CONSTANTS[s->index].clear();
  LATER_VAR_NAMES[s->index].clear();
  VAR_NAME_COUNT[s->index] = 3;
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

  s = getByName(fileName);
  if (!s) {
    if (debug) LATER_PRINTLN("Later - load failed2: " + String(fileName));
    return NULL;
  }

  loadedScripts++;

  VAR_NAME_COUNT[s->index] = 3;
  LATER_VAR_NAMES[s->index][(std::string) "$DMA0"] = 0;
  LATER_VAR_NAMES[s->index][(std::string) "$DMA1"] = 1;
  LATER_VAR_NAMES[s->index][(std::string) "$DMA2"] = 2;

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

  char * possibleNames = TEMP_BUFFER;
  //char possibleNames[ 9 3];//char possibleNames[ 9 2];
  strcpy(possibleNames, CMDCHARS); //strncpy(possibleNames, CMDCHARS, 90); //strncpy(possibleNames, CMDCHARS, 91);
  possibleNames[91] = '\0';//possibleNames[91] = '\0';

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
//rx usage:
//char text[] = "a man needs $47.00 too feel rich these days.";
/*
  supports:

  tokens:
  /s -spacy
  /w -wordy
  /d -digity
  /t -{template}
  /v -@var

  suffixs:
  +  -one or more in a row

  flags:
  ^  -starts with

*/

class RX {
  public:

    char * rx;
    char * hay;
    int rxlen;
    int haylen;
    char token;
    char c;
    bool isStart = false;
    bool isEnd = false;
    bool isMany = false;
    bool wasValid = false;
    bool valid = false;
    int validCount = 0;
    int invalidCount = 0;
    bool secondTry = false;

    RX(char * rx) {
      this->rx = rx;

      rxlen = strlen(rx);
      isStart = rx[0] == '^';
      isEnd = rx[rxlen - 1] == '$';
      isMany = false; // for + suffixes

    }

    void nextToken() {
      while (rx[0] == '/') rx++;
      isMany = rx[1] == '+';
      token = rx[0];
    }
    int test(char * hay) {

      this->hay = hay;
      haylen = strlen(hay);

      if (isStart) rx++;

      int i = 0;

      // load up fist token fro rx, then compare it against each char in hay. bail on first miss if startswith

      nextToken();

      for (; i < haylen; i++) {
        c = hay[i];
        wasValid = valid;
        switch (token) {
          case 's': valid = c == ' ';  break;
          case 'w': valid = isalnum(c);  break;
          case 'd': valid = isdigit(c);  break;
          case 'v': valid = c == '@';  break;
          case 't': valid = c == '{';  break;
          case '.': valid = c ? true : false; break;
        }

        if (valid) {
          validCount++;
        } else {
          invalidCount++;
        }

        if (valid && !isMany) {
          rx++;
          nextToken();
        }

        if (!valid && !wasValid && secondTry && !isStart) {
          secondTry = 0;
          rx -= 3;
          nextToken();
          i--;
          continue;
        }

        if (!valid && wasValid && isMany && !isStart) {

          if (secondTry && strlen(rx) < 3 ) return i + 1;
          if (!secondTry) {
            i--;
            secondTry = 1;
            rx += 2;
            nextToken();
          }
          if (!token && invalidCount == 1) return i + 1;
        }

        if (!valid && isStart) return token ? i + 1 : 0;
        if (valid && !token) return i + 1;
      }//next
      return valid ? i + 1 : 0;

    }

};
namespace laterUtil {
char * splits[24];
int split_count;
int intFromHexChar(char c) {
  if (c < 58) return c - 48;
  return (c - 64) + 10;
}
bool isTheSame(char * data, const char * term) {
  if (data[0] != term[0]) return 0;
  return !strcmp(data, term);
}
void splitStringByChar(char* hay, char term)  noexcept {
  HRT_COUNT(splitStringByChar)
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
char * afterSubstring(char * str, const char * needle) {
  int len = strlen(needle);
  char * p = strstr(str, needle);
  if (!p) return NULL;
  return p + len;
}//end afterSubstring()

char * copyUntilChar(char * str, const char of) noexcept { // copyUntilChar("hello world", ' ') == "hello"
  HRT_COUNT(copyUntilChar)

  char * endPtr = strchr(str, of);
  int len = endPtr - str;
  static char buff[64];
  if (!endPtr) return str;
  strncpy(buff, str, len);
  buff[len] = '\0';
  return buff;
}//end copyUntilChar()
char * trimRight(char * str) noexcept {
  HRT_COUNT(trimRight)

  unsigned int i = strlen(str) - 1;
  for (; i > 0; i--) if (!isblank (str[i]) ) {
      str[i + 1] = '\0';
      break;
    }
  return str;
}//end trimRight()

inline char * trimLeft(char * str, bool aggressive = false) noexcept {
  if (!aggressive) {
    while (str[0] == ' ') str++;
  } else {
    while (isspace(str[0])) str++;
  }
  return str;
}//end trimLeft()
inline bool startsWith(const char * hay, const char * needle)  noexcept {
  return ! memcmp ( hay, needle, strlen(needle));
}
inline int indexOf(char * base, const char * term) noexcept {
  HRT_COUNT(indexOf)
  char * p = strstr(base, term);
  if (!p) return -1;
  return p - base;
}//end indexOf

char * replace (char * str, const char * term, const char * rep) noexcept {
  HRT_COUNT(replace)

  char * start = strstr(str, term);
  if (!start) return str; //nothing to replace, return copy

  //char * result = str;
  unsigned int replen = strlen(rep),
               termlen = strlen(term);

  //if rep smaller than term, inject rep and scoot remaining string left
  if (replen < termlen) {
    strncpy(start, rep, replen);
    strcpy(start + replen, start + termlen);  // copy tail from orig into result
    return str;
  }
  // if the length of the hit and rep is the same, we can just copy it out:
  if (replen == termlen) {
    strncpy(start, rep, replen);
    return str;
  }

  // if rep is bigger than the term scoot right first, then inject
  unsigned int len = strlen(start);
  unsigned int gap = replen - termlen;
  for (unsigned int i = len; i > termlen - 1; i--) {
    start[i + gap] = start[i];
  }
  memcpy(start, rep, replen);

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
  char * p = FILE_BUFF;

  if (lastFileName == fileName)  return p;

  lastFileName = fileName;

  if (fileName.startsWith("%RAM%")) {
    return p;
  }
  memset ( FILE_BUFF, '\0', 2048);

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
  return FILE_BUFF;
}//end fileToBuff()
char * fileToBuffInclude(String fileName) {
  char * p = INCLUDE_BUFFER;
  memset ( INCLUDE_BUFFER, '\0', 1024);

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
  return INCLUDE_BUFFER;
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
std::vector<uint16_t> linePos;
const char * indexedFileName;
void indexFile(const char* filename) {
  indexedFileName = filename;
  if (linePos.size() == 0) linePos.reserve(100);
  linePos.clear();
  linePos.emplace_back(0);

  uint16_t block_size = 256, pos = 0, leftover = 0, maxIndex = 0;
  char buff[block_size + 1];
  char * p = buff;

  File file = SPIFFS.open(filename, "r");

  if (file) {
    maxIndex = file.size() - 1;

    while (file.available()) {
      leftover = pos;
      pos = file.position();
      if ( (leftover && (leftover == pos)) ) break;
      file.readBytes(buff, block_size);

      p = buff;
      if (p[0] == '\n') linePos.emplace_back( pos + (p - buff) );
      if (p[1] == '\n') linePos.emplace_back( pos + ((p + 1) - buff) );

      while ( (p = strchr(p + 1, '\n')) ) linePos.emplace_back( pos + (p - buff) );

    }//wend file available
    file.close();

    // clean up past-end entries:
    while ( (leftover = linePos.back()) > maxIndex) linePos.pop_back();
    linePos.pop_back();

  }//end if file?
}// end indexFile()
char * getFileLine(const char* filename, uint16_t lineNumber ) {

  if (!indexedFileName || strcmp( indexedFileName, filename)) indexFile(filename);
  if ( lineNumber && lineNumber > linePos.size()) return NULL;

  int pos = linePos[lineNumber] ;
  if (lineNumber && !pos) return NULL;

  const int block_size = 96;
  static char buff[block_size + 1];

  File file = SPIFFS.open(filename, "r");
  if (file) {

    file.seek( pos, SeekSet);
    file.readBytes(buff, block_size);
    file.close();

    char * ending = strchr(buff + 1, '\n');
    if (ending) ending[0] = '\0';

    return buff;
  }//end if file?
  return NULL;
} // getFileLine()
#ifdef ADAFRUIT_NEOPIXEL_H
uint32_t parseColor(char * ptr, LATER_ENVIRON * s) {
  int colorLength, commaPos;
  uint32_t color;
  while (isblank(ptr[0])) ptr++; // trim left, maybe move to compilation stage, as optomization
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

#ifdef __INC_FASTSPI_LED2_H
uint32_t parseColor(char * ptr, LATER_ENVIRON * s) {
  int colorLength, commaPos;
  LATER_PIXEL_TYPE color;
  while (isblank(ptr[0])) ptr++; // trim left, maybe move to compilation stage, as optomization
  colorLength = strlen(ptr);
  uint32_t buff;
  commaPos = laterUtil::indexOf(ptr, ",");
  if (commaPos > 0) {  // $r, $g, $b
    byte r, g, b;
    r = Number(ptr, s->VARS);
    ptr += commaPos + 1;
    g = Number(ptr, s->VARS);
    b = Number(strchr(ptr, ',') + 1, s->VARS);
    buff += b;
    buff += g * 256;
    buff += r * (256 * 256);
    return buff;
  } else { // no comma, just a big long
    color = LATER_PIXEL_TYPE(Number(ptr, s->VARS)); //strtoul(ptr, NULL, 10);
  }//end non-hex color handling
  buff += color.raw[2];
  buff += color.raw[1] * 256;
  buff += color.raw[0] * (256 * 256);
  return buff;
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
    pinMode(  strtoul(k, NULL, 10), OUTPUT );
    return;
  }
  if (!strcmp(v, "INPUT")) {
    pinMode(  strtoul(k, NULL, 10), INPUT );
    return;
  }
  if (!strcmp(v, "INPUT_PULLUP")) {
    pinMode(  strtoul(k, NULL, 10), INPUT_PULLUP );
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

    analogWrite(Number(k, VARS), Number(v, VARS));

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
  char * p = buff;
  int len = 0;
  //char linebuff[LATER_LINE_BUFFER];
  //char linebuff[LATER_LINE_BUFFER];
  char * linebuff = LINE_BUFF;
  memset(linebuff, 0, 16);
  strcat(buff, "\n");

  while (1) {
    char * nextLine = strchr(p, '\n');
    if (!nextLine) break;
    len = nextLine - p;
    strncpy(linebuff, p, len);
    linebuff[len] = '\0';
    compositeLine(linebuff, s);
    if (strlen(linebuff)) uniPrintln(linebuff);
    p = nextLine + 1;
  }//wend line
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


  unsigned long rez = Number(lb, s->VARS);
  uniPrint( rez ? "PASS: " : "FAIL: ");
  char * p2 = strstr(lb, "->") + 2;
  while (p2[0] == ' ') p2++;
  uniPrint(p2);
  uniPrint(" :: ");

  if (!rez) {
    char * lp;
    //char linebuff[LATER_LINE_BUFFER];
    char * linebuff = LINE_BUFF;
    memset(linebuff, '\0', 36);

    lp = s->program + l->start;
    strncpy(linebuff, lp, l->len);
    linebuff[l->len] = '\0';

    // try to print the live rendered linebuff thqat failed
    lp = strstr(linebuff, "->");
    if (lp) lp[0] = '\0';
    lp--;
    if (lp) lp[0] = '\0';
    strcat(lp, "=");

    strstr(lb, "->")[0] = '\0';
    if (lb[0] == ' ') lb++;
    strcat(lp, lb);
    int len = strlen(lp);
    if (lp[len - 1] == ' ') lp[len - 1] = '\0';
    char * varPtr = strchr(linebuff, '@');
    if (varPtr) {
      strcat(lp, "; @");
      len = strlen(lp);
      lp[len] = varPtr[1];
      lp[len + 1] = '=';
      lp[len + 3] = '\0';
      itoa(s->VARS[varPtr[1] - 65], lp + len + 2, 10);
    }
    uniPrintln(linebuff);
  } else {
    uniPrintln("-");
  }
}//end runAssert()
#ifdef __INC_FASTSPI_LED2_H

int subtract(int a, int b) {
  return max(b - a, 0);
}

//}

uint8_t within(uint8_t  range, uint8_t  base) {
  uint8_t amt = randomReg() % range;
  if (randomReg() % 2) { //add
    return qadd8(amt, base);
  } else { //subtract
    if (base > amt) return base - amt;
    return 0;
  }
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
  LATER_PIXEL_TYPE parsedColor;
  int indPos = laterUtil::indexOf(line, "->"),
      commaPos = laterUtil::indexOf(line, ",") + 1,
      startPos = Number(line, s->VARS),
      howMany = 1;
  if (commaPos && commaPos < indPos) howMany =  Number(line + commaPos, s->VARS);

  ptr += indPos + 2;

  //  1,2->|#11,22,33
  // look for

  /*
    dblog+= "\n\n@"+String(millis())+"\n line: " + String(line) +"\n";
    dblog+= " ptr: " + String(ptr) +"\n";
    dblog+= " startPos: " + String(startPos) +"\n";
    dblog+= " howMany: " + String(howMany) +"\n";
  */

  char flag = 0;
  if (strpbrk (ptr, "+-<>*&LR") == ptr) {
    flag = ptr[0];
    ptr++;
  }

  if (flag == '@') { // wtf is this needed? fixes flag getting matched as "@"
    flag = '\0';
    ptr--;
  }

  if (startPos + howMany >  FastLED.size()) return;
  color = laterUtil::parseColor(ptr, s);  // LATER_PRINTLN("pix color:" + String(color));
  // here we can apply shit like bright, avg, rnd, etc


  if (flag) {

    byte  rArg = (color >> 16) & 0xFF,
          gArg = (color >> 8) & 0xFF,
          bArg = color % 256;
    LATER_PIXEL_TYPE colorNow;

    byte rNow, gNow, bNow;

    CHSV hsv;

    for (int i = startPos, mx = startPos + howMany; i < mx; i++) {

      colorNow = LATER_PIXEL_NAME[i];

      rNow = colorNow.red;
      gNow = colorNow.green;
      bNow = colorNow.blue;

      switch (flag) {
        case '+':
          LATER_PIXEL_NAME[i] += colorNow;
          break;

        case '-':
          LATER_PIXEL_NAME[i] -= colorNow;
          break;

        case '*':
          LATER_PIXEL_NAME[i].setRGB( within(rArg, rNow), within(gArg, gNow), within(bArg, bNow) );
          break;

        case '>':
          LATER_PIXEL_NAME[i] = LATER_PIXEL_TYPE( rndAdd(rArg, rNow), rndAdd(gArg, gNow), rndAdd(bArg, bNow));
          break;

        case '<':
          LATER_PIXEL_NAME[i] = LATER_PIXEL_TYPE( rndSubtract(rArg, rNow), rndSubtract(gArg, gNow), rndSubtract(bArg, bNow));
          break;

        case '&':
          LATER_PIXEL_NAME[i] = LATER_PIXEL_TYPE( (rArg + rNow) / 2, (gArg + gNow) / 2, (bArg + bNow) / 2);
          break;

        case 'R':
          hsv = rgb2hsv_approximate(colorNow);
          hsv.hue = qadd8(hsv.hue, rArg);
          hsv.sat = qadd8(hsv.sat, gArg);
          hsv.val = qadd8(hsv.val, bArg);
          LATER_PIXEL_NAME[i] = LATER_PIXEL_TYPE( hsv );
          break;

        case 'L':
          hsv = rgb2hsv_approximate(CRGB(colorNow));
          if (hsv.hue >= rArg) {
            hsv.hue -= rArg;
          } else {
            hsv.hue = (255 + hsv.hue) - rArg;
          }

          hsv.sat -= gArg;
          hsv.val -= bArg;
          LATER_PIXEL_NAME[i] = LATER_PIXEL_TYPE( hsv );
          break;

          //case '': break;
      }//end switch()

      //  LATER_PIXEL_NAME[i]=parsedColor;

    }//next pixel
    return;
  }//end if flag?
  for (int i = startPos, mx = startPos + howMany; i < mx; i++) {
    LATER_PIXEL_NAME[i] = color;
  }


}//end setPixel()
void runRotate(long dist) {

  int mx = FastLED.size() - 1;
  uint16_t  i = 0;

  //scoot them by memorizing next, then moving last to next
  LATER_PIXEL_TYPE last;
  last = LATER_PIXEL_NAME[mx];
  for (i = mx; i > 0; i--)  LATER_PIXEL_NAME[i] = LATER_PIXEL_NAME[ i - 1 ];
  LATER_PIXEL_NAME[0] =  last;

} // edn runRotate()

void runGrad(char * line, LATER_ENVIRON * s) {
  char * ptr = line;
  uint32_t col, col2;

  /*
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
  */
}//end runGrad()
#endif
#ifdef ADAFRUIT_NEOPIXEL_H

void subtractTo(uint8_t &adj, uint8_t &base) {
  if (base > adj) {
    base -= adj;
  } else {
    base = 0;
  }
}

void addTo(uint8_t &adj, uint8_t &base) {
  if ((255 - adj) > base) {
    base += adj;
  } else {
    base = 255;
  }
}

void dumpPixels() {
  Serial.println("\nPIXELS:");
  uint8_t * pxs = LATER_PIXEL_NAME.getPixels();
  for (int i = 0, mx = LATER_PIXEL_NAME.numPixels() * 3; i < mx; i += 3) {
    Serial.println(String(i) + ". " + String(pxs[i]) + "," + String(pxs[i + 1]) + "," + String(pxs[i + 2])   );
  }
}//end dumpPixels()
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
void rndSubtract(uint8_t &range, uint8_t &base) {
  uint8_t n = randomReg() % range;
  if (base > n) {
    base -= n;
  } else {
    base = 0;
  }
}
void rndAdd(uint8_t &range, uint8_t &base) {
  uint8_t n = randomReg() % range;
  if ((255 - n) > base) {
    base += n;
  } else {
    base = 255;
  }
}
void runSetPixel(char * line, LATER_ENVIRON * s) {

  char * ptr = line;
  LATER_LINE * l = &s->lines[s->i];
  char * CACHE = l->exprCache;
  int startPos = CACHE[0] ?  CACHE[1] : Number(line, s->VARS);
  int howMany =  CACHE[2] ?  CACHE[3] : Number(strchr(line + 1, ',') + 1, s->VARS);
  /*
    cache map
    0 isStaticIndex
    1 staticIndex
    2 isStaticSpan
    3 staticSpan
    4 mode flag
    5 isStaticColor
    6 staticRed
    7 staticGreen
    8 staticBlue
  */

  ptr = strchr(line, '>') + 2;
  char flag = CACHE[4];
  if (flag == '_') flag = 0;

  if (startPos + howMany >  LATER_PIXEL_NAME.numPixels()) return;

  if (CACHE[5]) {
    NEW_PIXEL.chan[2] = CACHE[6];
    NEW_PIXEL.chan[1] = CACHE[7];
    NEW_PIXEL.chan[0] = CACHE[8];
  } else {
    NEW_PIXEL.value = s->VARS[ptr[1] - 65];
  }

  // here we can apply shit like bright, avg, rnd, etc
  if (flag) {

    for (int i = startPos, mx = startPos + howMany; i < mx; i++) {

      OLD_PIXEL.value = LATER_PIXEL_NAME.getPixelColor(i);

      switch (flag) {

        case '+': // static add
          addTo(NEW_PIXEL.chan[2], OLD_PIXEL.chan[2]);
          addTo(NEW_PIXEL.chan[1], OLD_PIXEL.chan[1]);
          addTo(NEW_PIXEL.chan[0], OLD_PIXEL.chan[0]);
          LATER_PIXEL_NAME.fill(OLD_PIXEL.value, i, 1);
          break;

        case '-':
          subtractTo(NEW_PIXEL.chan[2], OLD_PIXEL.chan[2]);
          subtractTo(NEW_PIXEL.chan[1], OLD_PIXEL.chan[1]);
          subtractTo(NEW_PIXEL.chan[0], OLD_PIXEL.chan[0]);
          LATER_PIXEL_NAME.fill(OLD_PIXEL.value, i, 1);
          break;

        case '*':
          RGB_PIXEL.chan[2] =  within(NEW_PIXEL.chan[2], OLD_PIXEL.chan[2]);
          RGB_PIXEL.chan[1] =  within(NEW_PIXEL.chan[1], OLD_PIXEL.chan[1]);
          RGB_PIXEL.chan[0] =  within(NEW_PIXEL.chan[0], OLD_PIXEL.chan[0]);
          LATER_PIXEL_NAME.fill(RGB_PIXEL.value, i, 1);
          break;

        case '>'://rnd Add
          rndAdd(NEW_PIXEL.chan[2], OLD_PIXEL.chan[2]);
          rndAdd(NEW_PIXEL.chan[1], OLD_PIXEL.chan[1]);
          rndAdd(NEW_PIXEL.chan[0], OLD_PIXEL.chan[0]);
          LATER_PIXEL_NAME.fill(OLD_PIXEL.value, i, 1);
          break;

        case '<'://rnd subtract
          rndSubtract(NEW_PIXEL.chan[2], OLD_PIXEL.chan[2]);
          rndSubtract(NEW_PIXEL.chan[1], OLD_PIXEL.chan[1]);
          rndSubtract(NEW_PIXEL.chan[0], OLD_PIXEL.chan[0]);
          LATER_PIXEL_NAME.fill(OLD_PIXEL.value, i, 1);
          break;

        case '&':
          RGB_PIXEL.chan[2] =  (NEW_PIXEL.chan[2] + OLD_PIXEL.chan[2]) / 2;
          RGB_PIXEL.chan[1] =  (NEW_PIXEL.chan[1] + OLD_PIXEL.chan[1]) / 2;
          RGB_PIXEL.chan[0] =  (NEW_PIXEL.chan[0] + OLD_PIXEL.chan[0]) / 2;
          LATER_PIXEL_NAME.fill(RGB_PIXEL.value, i, 1);
          break;

      }//end switch()
    }//next pixel
    return;
  }//end if flag?

  LATER_PIXEL_NAME.fill(NEW_PIXEL.value, startPos, howMany);

}//end setPixel()
void runRotate(long dist) {
  int mx = LATER_PIXEL_NAME.numPixels() - 1;
  uint16_t  i = 0;

  /*
    uint8_t * pxs = LATER_PIXEL_NAME.getPixels();
    unsigned long lastPx = LATER_PIXEL_NAME.getPixelColor(mx);
    memmove(pxs+3, pxs, 3);
    LATER_PIXEL_NAME.setPixelColor(0, lastPx);
    dumpPixels();

  */

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
static unsigned int LOG_CURSOR = 0;
void logMe(const char* line) noexcept {  // turn into a circular log, accepting it will get out of order at some point

  if ((LOG_CURSOR + LATER_LINE_BUFFER) > LATER_LOG_SIZE) {
    LOG_CURSOR = 1;
    setRunLog[0] = '\n';
    setRunLog[1] = '\0';
  }

  ltoa(millis(), setRunLog + LOG_CURSOR, 10);  // works with ll set in resizer
  strcat(setRunLog, "\t");
  strcat(setRunLog, line);
  LOG_CURSOR += strlen(setRunLog + LOG_CURSOR) + 1;
  setRunLog[LOG_CURSOR - 1] = '\n'; // cancels null termination

}  //end logsetlog()
}//end namespace laterCMD::
template <class text>
void uniPrintln(text content) {
  auto s = getCurrent();
  strcpy(SYSTEM_OUTPUT_BUFFER, content);
#ifdef WEBSOCKETSSERVER_H_
  if (s->options.socket) {
    webSocket.broadcastTXT(content);
    return;
  }
#endif
  if (s->calledFromWeb) {
    LATER_SERVER_NAME.sendContent(content);
    LATER_SERVER_NAME.sendContent("\n");
  } else {
    LATER_PRINTLN(content);
  }
}//end uniPrintln()
template <class text>
void uniPrint(text content) {
  auto s = getCurrent();
  if (s->calledFromWeb) {
#ifdef ESP8266WEBSERVER_H
    LATER_SERVER_NAME.sendContent(content);
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
  if (index == -1) return 0;
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
unsigned long evalLite(char * lb, LATER_ENVIRON * s)  {
  char varChar;
  unsigned long tempInt = s->Number(lb);
  unsigned long varCache, varTemp;
  lb++;

  while (++lb && (varCache != tempInt)) {
    varCache = tempInt;
    varChar = (lb++)[0];
    varTemp = s->Number(lb++);

    switch (varChar) {
      case '+': tempInt += varTemp; break;
      case '-': tempInt -= varTemp; break;
      case '/': tempInt /= varTemp; break;
      case '*': tempInt *= varTemp; break;
      case '%': tempInt %= varTemp; break;
      case '^': tempInt ^= varTemp; break;
      //case ' ': break;
      case '|': tempInt = (tempInt || varTemp) ? 1 : 0; break;
      case '&': tempInt = (tempInt && varTemp) ? varTemp : 0; break;
      case '=': tempInt = (tempInt == varTemp) ? 1 : 0; break;
      case '!': tempInt = tempInt != varTemp; break;
      case '<': tempInt = tempInt < varTemp; break;
      case '>': tempInt = tempInt > varTemp; break;
    }
  }
  return tempInt;
}//end evalLite()
#ifdef LATER_CSV

CsvState * getCSV(char * codeLine, LATER_ENVIRON * s) {

  CsvState * state = &s->csv;
  char * varPtr = codeLine;
  int i;

  if (state->fn[0]) { // re-call, just re-assign line number:

    if (state->hasLineParam) {
      if ( (varPtr = laterUtil::afterSubstring(codeLine, "line="))  ) state->lineNeeded = Number(varPtr, s->VARS);
    } else {
      state->lineNeeded++;
    }
    return state;
  }//end if re-call?
  // init:
  if ((varPtr = laterUtil::afterSubstring(codeLine, "line="))) {
    state->lineNeeded =  Number(varPtr, s->VARS);
    state->hasLineParam = 1;
  }
  if ((varPtr = laterUtil::afterSubstring(codeLine, "file="))) strncpy(state->fn, varPtr, 35);
  if ((varPtr = laterUtil::afterSubstring(codeLine, "filter="))) strncpy(state->filter, varPtr, 35);
  if ((varPtr = laterUtil::afterSubstring(codeLine, "delim="))) state->delim = varPtr[0];
  if ((varPtr = laterUtil::afterSubstring(codeLine, "skip="))) state->skip = Number(varPtr, s->VARS);
  if ((varPtr = laterUtil::afterSubstring(codeLine, "block="))) state->blockSize = Number(varPtr, s->VARS);
  if ((varPtr = laterUtil::afterSubstring(codeLine, "more=@"))) state->morePointer = varPtr[0] - 65;

  if (!state->hasLineParam) state->blockSize = 2; // auto mode

  state->delimStr[0] = state->delim;
  memset(state->varSlots, 0, 12);

  char * spcPtr = strchr(state->fn, ' ');
  if (spcPtr)spcPtr[0] = '\0';

  spcPtr = strchr(state->filter, ' ');
  if (spcPtr)spcPtr[0] = '\0';

  /*
    DUMP("CSV:_codeLine:", codeLine);
    DUMP("CSV:file:", state->fn);
    DUMP("CSV:filter:", state->filter);
    DUMP("CSV:delim:", state->delim);
    DUMP("CSV:skip:", state->skip);
    DUMP("CSV:hasLineParam:", state->hasLineParam);
    DUMP("CSV:block:", state->blockSize);
    DUMP("CSV:more:", state->morePointer);
    DUMP("CSV:line:", state->lineNeeded);
  */

  int slotNumber = 0;
  varPtr = laterUtil::afterSubstring(codeLine, "vars=");
  if (!varPtr) varPtr = "AUTO";

  if (!strcmp(varPtr, "AUTO")) { // pull var names from data source for templating

    varPtr = laterUtil::getFileLine(state->fn, 0);
    char nameBuffer[17] = {'$', 0, 0};

    while (varPtr) { //find comma, and copy before it into buffer, trimming as needed and adding a $
      if (varPtr[0] == state->delim) varPtr++;
      while (varPtr[0] == ' ') varPtr++;

      int len = strcspn (varPtr, state->delimStr);
      strncpy(nameBuffer + 1, varPtr, len);
      nameBuffer[len + 1] = '\0';

      state->varSlots[slotNumber] = getVarNameNumber(nameBuffer, s->index);
      slotNumber++;
      varPtr = strchr(varPtr + 1,  state->delim);
    }//wend var list on csv header

    if (varPtr) { // get last one, not behind a delim
      strcpy(nameBuffer + 1, varPtr);
      state->varSlots[slotNumber] = getVarNameNumber(nameBuffer, s->index);
    }//end if one last value?

  } else { // hard-coded vars for templating
    char * spacePtr = strchr(varPtr, ' ');

    while (varPtr) {
      state->varSlots[slotNumber] = varPtr[1] - 65;
      slotNumber++;
      varPtr = strchr(varPtr + 1, '@');
      if (spacePtr && varPtr > spacePtr) break;
    }//wend var
  }//end if auto/manual vars?
  return state;
} //end getCSV()
#endif

#line 1 "config.ino"
//@TAKE

#line 1 "core.ino"
// core for danscript, the actual interpreter and stuff
unsigned long Number( const char * str, const unsigned long * VARS ) {
  //unsigned long theNumber;
  while (str[0] == ' ') str++; // fast left-side trim

  if (str[0] == '@' ) { //&& str[2] == '_') {
    return  VARS[str[1] - 65];
  } else {
    if (str[0] == '{') {
      return processTemplateExpressionsNumber(str);
    } else {
      return str[1] ? strtoul(str, NULL, 10) : (str[0] - 48); // atoi(str);
    }
  }// end if var format?
  return 0; // failsafe
}//end Number()
char* getVarName(const char* longName, const int scriptIndex) {
  HRT_START

  static char buffer[3] = "@~";
  // moved to find instead of count, which should be a bit faster
  auto search = LATER_VAR_NAMES[scriptIndex].find({longName});

  if (search != LATER_VAR_NAMES[scriptIndex].end()) {
    buffer[1] = search->second + 65;
  } else {
    if ( VAR_NAME_COUNT[scriptIndex] >= LATER_VARS_LENGTH) {
      VAR_NAME_COUNT[scriptIndex] = LATER_VARS_LENGTH;
    } else {
      if (VAR_NAME_COUNT[scriptIndex] > 25 && VAR_NAME_COUNT[scriptIndex] < 31) {
        VAR_NAME_COUNT[scriptIndex] = 32;
      }
      buffer[1] = (LATER_VAR_NAMES[scriptIndex][ {longName}] = VAR_NAME_COUNT[scriptIndex]++ ) + 65;
    }

  }

#ifdef HIGH_RES_TIMING
  unsigned long et = micros();
  HR_PERF.getVarName.total += et - st;
  HR_PERF.getVarName.count++;
#endif
  return buffer;
}
char getConstantNumber(char* valueString, LATER_ENVIRON * s, long res = -1) {
  int slot = LATER_VARS_LENGTH - s->LITS_COUNT++;
  unsigned long value = res != -1 ? res :  strtoul(valueString, NULL, 10);
  if (value == 0) return LATER_VARS_LENGTH - 1;

  for (int i = slot; i < LATER_VARS_LENGTH; i++) {
    if (s->VARS[i] == value) {
      s->LITS_COUNT--;
      slot = i;
      break;
    }
  }
  s->VARS[slot] = value;
  return slot;
}

char getVarNameNumber(char* longName, int scriptIndex) {
  HRT_COUNT(getVarNameNumber)

  auto search = LATER_VAR_NAMES[scriptIndex].find({longName});
  if (search != LATER_VAR_NAMES[scriptIndex].end()) {
    return search->second;
  } else {
    return LATER_VAR_NAMES[scriptIndex][longName] = VAR_NAME_COUNT[scriptIndex]++;
  }
}

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
void replaceEndingLiterals(char * line, LATER_ENVIRON * s) {
  unsigned int len = strlen(line);
  char sig = line[len - 1];
  if (isdigit(sig) && isDigit(   line[len - 2]  )) { // at least  2 digits, proceed

    char * digitStart = line + (len - 1);
    while (isDigit(digitStart[0]) ) digitStart--;
    digitStart++;
    len = strlen(digitStart);

    if (len > 1) {
      char symb = getConstantNumber(digitStart, s) + 65;
      memset(digitStart, ' ', len );
      digitStart[0] = '@';
      digitStart[1] = symb;
    }

  }//end if sig match?

}// end replaceEndingLiterals()
void replaceAllLiterals(char * line, LATER_ENVIRON * s) {

  char digs[] = "0123456789";

  char * nxtDigit = line;
  int len = 0;

  while ( (nxtDigit = strpbrk (nxtDigit, digs)) ) {

    len = 1;
    while (isdigit(nxtDigit[len]))len++;

    char symb = getConstantNumber(nxtDigit, s) + 65;
    memset(nxtDigit, ' ', len );
    if (len == 1) { // need to make room for var symbol w/single-digit numbers:
      int slen = strlen(nxtDigit);
      nxtDigit[slen + 1] = '\0';
      for (int i = slen; i > 0; i--) nxtDigit[i] = nxtDigit[i - 1];
    }
    nxtDigit[0] = '@';
    nxtDigit[1] = symb;
    nxtDigit += len + 1;
  }//wend digit char

}// end replaceAllLiterals()
void replaceStartingLiterals(char * line, LATER_ENVIRON * s) {


  // check if literal here, if so, also replace value with var symbol
  // find assigned value,

}//end replaceStartingLiterals()

void replaceVarNames(char * line, int scriptIndex) { // turns $fancyName into @a, @b, etc...
  char * varPos = line[0] == '$' ? line : strchr(line, '$');
  static char varname[32];
  while (varPos) {
    int len = strspn(varPos, VARCHARS);
    strncpy(varname, varPos, len);
    varname[len] = '\0';
    laterUtil::replace (varPos, varname, getVarName(varname, scriptIndex));
    varPos = strchr(varPos, '$'); // keep looking for more
  }//wend var declaration?
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
  c =  SCRIPT->program; // prevent un-init error
  // compute Exit points for each line:
  for (int index = 0; index < mx; index++) {
    LATER_LINE * line = &whole[index];
    switch (line->cmd) {

      case LATER_if: // if
        for (int i = index + 1, need = 1; i < mx; i++) {
          LATER_LINE * x = &whole[i];
          if (x->cmd == LATER_fi) need--;
          if (x->cmd == LATER_else && need == 1) need--;
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
            line->exit = i;
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
        if ( line->cmd == LATER_on) {// set line.data to edge type, and line.exit to subroutine start
          k = strchr(k, ',') + 1; // find 1st comma, 2nd arg (sub name)
          while ( !isalnum(k[0]) )k++; // advance to subname start
          line->data = 0;
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
        if (line->cmd == LATER_interval) {
          line->data = SCRIPT->intervalCount++;
          k =  strchr(SCRIPT->program + line->start, ',') + 1;
          while ( !isalnum(k[0]) ) k++; // trim?
        }

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
void processVariableExpressions(char * line, unsigned long * VARS) {// composites var values into literals for output

  HRT_START

  static char buff[16];
  static char varname[8];
  char * atPtr = strchr(line, '@');
  unsigned long val;

  while (atPtr) {
    long varSlot = atPtr[1] - 65;
    strncpy(varname, atPtr, 2);
    varname[2] = '\0';
    val = VARS[varSlot];

    laterUtil::replace (atPtr, varname, ltoa(val, buff, 10 )  );
    atPtr = strchr(atPtr + 1, '@');
  }//end if var declaration?

  HRT_TIME(vars)

}//end processVariableExpressions()
bool provideArrayReturnAll(char * assign, int elmSectionLength, long value) {
  char * ending  = strchr(assign + elmSectionLength + 1, ']') + 1;
  ltoa(value, assign, 10 );
  memmove(assign + strlen(assign), ending, strlen(ending) + 1);
  return false;
}//end provideArrayReturn();
bool processArray(char * line,  LATER_ENVIRON * s,  int varSlot) {

  unsigned long * VARS = s->VARS;
  if (varSlot == -1 && line[0] == '@'  && line[2] == '=' ) varSlot = line[1] - 65;
  //LATER_LINE * l = &s->lines[s->i];

  char * ptr  = strchr(line, '[');
  char * assign = ptr;
  char delim = ',';
  // find delim between elements and index:
  char * indDelim = strstr(ptr, "][");
  if (!indDelim) return false;
  int elmSectionLength = indDelim - ptr;
  indDelim += 2;
  while (indDelim[0] == ' ') indDelim++;

  // cut in here to look for special access modifiers:
  //  [1,3,5][>4] == 5 comparison lookup
  //  [1,3,5][&3] == 1 addressof lookup

  char lookupModeFlag = 0;
  if (strchr("<>&=", indDelim[0])) {
    lookupModeFlag = indDelim[0];
    indDelim++;

    // look for both options:
    bool isAddressCall =  (lookupModeFlag == '&');
    if (isAddressCall) {
      if (strspn (indDelim, "<>") == 1) {
        lookupModeFlag = indDelim[0];
        indDelim++;
      }//is a secondary compare being used?
    }//end if address call?

    unsigned int valueNeeded = Number(indDelim, s->VARS);
    unsigned int elmValue, elmsFound = 1;
    bool valid  = false;

    while (ptr != NULL) {
      ptr++;
      elmValue = Number(ptr, VARS);

      switch (lookupModeFlag) {
        case '>': valid = elmValue > valueNeeded; break;
        case '<': valid = elmValue < valueNeeded; break;
        case '&': valid = elmValue == valueNeeded; break;
      }//end switch compare type
      if (valid) {
        if (!isAddressCall) elmsFound = elmValue;
        if (varSlot > -1) return (VARS[varSlot] = elmsFound) || 1;
        return provideArrayReturnAll (assign, elmSectionLength, elmsFound);
        break;
      }//end if valid?
      elmsFound++;
      ptr = strchr(ptr + 1, delim);  // skip commas until count == index
    }//wend comma segment

    if (lookupModeFlag == '=') {
      elmsFound--;
    } else {
      elmsFound = 0;
    }

    if (varSlot > -1) return (VARS[varSlot] = elmsFound) || 1;
    return provideArrayReturnAll (assign, elmSectionLength, elmsFound);

  }//end if reverse lookup?
  unsigned int indexNeeded = Number(indDelim, VARS);

  if (ptr[1] == '&' && ptr[3] == ';') { // fixed width/custom delim flag?
    if ( isdigit(ptr[2]) ) { // fixed width mode
      int width = ptr[2] - 48;
      ptr += 4;
      ptr += (width * indexNeeded);
      char endCap = ptr[width];
      ptr[width] = '\0'; // cap off so Number will parse

      unsigned long val = Number(ptr, VARS);
      ptr[width] = endCap;

      if (varSlot > -1) return (VARS[varSlot] = val) || 1;
      return provideArrayReturnAll (assign, elmSectionLength, val);

    } else {//end fixed width, begin custom delim
      delim = ptr[2];
      ptr += 3;
      elmSectionLength -= 3;
    }//end if
  }//end if static array or custom delim?

  // chop off index segment, making last option look like middle to simplify element finding
  ptr[elmSectionLength] = delim;
  ptr[elmSectionLength + 1] = '\0';

  // ratchet between commas, inclrementing ptr as needed
  unsigned int elmLength, elmsFound = 0;

  while (ptr) {
    if (elmsFound++ == indexNeeded) {
      elmLength =  (strchr(ptr + 1, delim) - ptr) - 1;
      break;
    }
    ptr = strchr(ptr + 2, delim);  // skip commas until count == index
  }//wend comma segment

  if (ptr) {
    if (varSlot > -1) return (VARS[varSlot] =  Number(ptr + 1, VARS)) || 1;

    // special text return instead of numbers like reverse and compares use
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

    return false;
  }

  if (varSlot > -1) return (VARS[varSlot] = 0) || 1;
  provideArrayReturnAll (assign, elmSectionLength, 0);

  return false;
}//end processArray()
bool evalMath(char * s, LATER_ENVIRON * script, int DMA) {
  char * ptr = strchr(s, '(');
  if (!ptr) return 0;

  HRT_START

  char * ptrOrig = ptr + 0;
  ptr++; // skip past open paren

  unsigned long * VARS = script->VARS;
  bool hasFunc = 0;
  char * ptrCmd = ptr;

  char funcLocalSlot = 0;
  char * leftPadPtr = s;
  while (leftPadPtr[0] == ' ')leftPadPtr++;
  int prefixLen = (ptr - leftPadPtr);

  if ( prefixLen > 2 ) { // && isupper(s[prefixLen - 2])  // prefix content long enough to be a command?
    ptrCmd = laterUtil::copyUntilChar(leftPadPtr, '(');

    char * pxptr = strchr(ptrCmd, '>');
    if (pxptr) ptrCmd = pxptr += 2;
    if (ptrCmd[0] == '@') ptrCmd += 3;
#ifndef LATER_DISABLE_OPTIMIZATIONS
    if (ptrCmd[0] == '#') { //function shortcut?
      funcLocalSlot = ptrCmd[1];
      hasFunc = true;
    } else { // function name
#endif

      if (ptrCmd[0] == '@') ptrCmd += 2;
      for (unsigned int i = 0, mx = strlen(ptrCmd); i < mx; i++) {
        if (!isupper(ptrCmd[0])  && (ptrCmd[0] != '.') ) {
          ptrCmd++;
          // break;
        }// endif upper?
      }//next i
      hasFunc = strlen(ptrCmd) > 2;
#ifndef LATER_DISABLE_OPTIMIZATIONS
    }//end if shortcut function pointer?
#endif
  } //end if any prefix content?
  if (DMA > -1) { // can't use DMA if in an array, since presumably that array wants dma as well.
    char * inArr = strchr(leftPadPtr, ']');
    if (inArr && inArr[1] == '[') DMA = -1;
  }
  while (ptr[0] == ' ') ptr++; // trim left
  char * rp = strchr(ptr, ')');
  if (!rp) return 0;

  char OVERRIDE = 0;
  char ops[8]; // list of match operators to use
  const char * MATCH_CHARS = hasFunc ? ",)" : (strchr(ptr, '.') ? "." : ")+*-/%<>=!&?:,|");
  static unsigned long nums[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // numbers to be mathed upon
  unsigned int i = 0,
               len = rp - ptr, //strlen(ptr),
               pos = strcspn (ptr, MATCH_CHARS);

  if (!hasFunc) {
    if (pos == len) return 0; // nothing to do, default to zero
    if (pos == 0) { // lisp-style operand first and data to follow?
      OVERRIDE = ptr[0];
      ptr++;
      pos = strcspn (ptr, MATCH_CHARS);
    }
  }
  unsigned long arity = 1;//         ","

  while (pos) {//put num/term into stack, slide string, try to grab next

    if (ptr[pos] == '.') {
      pos += 1;
    }

    nums[i] = Number(ptr, VARS);

    if ( (ops[i++] = ptr[pos])  == ')') break;
    if (i > 7) break;

    arity++;
    ptr += pos + 1;
    pos = strcspn (ptr , MATCH_CHARS);

  }//wend pos

  unsigned long varCache = nums[0], tempInt;
  /*
    Serial.println("varCache\t:" + String( varCache));
    Serial.println("prefixLen\t:" + String( prefixLen));
    Serial.println("hasFunc\t:" + String( hasFunc));
    Serial.println("i\t:" + String( i));
    Serial.println("arity\t:" + String( arity));

    Serial.println("s\t:" + String( s));

    Serial.println("ptrCmd\t:" + String( ptrCmd));
    Serial.println("leftPadPtr\t:" + String( leftPadPtr));

    Serial.println("hasFunc\t:" + String( hasFunc));
    Serial.println("funcLocalSlot\t:" + String( funcLocalSlot ));
    Serial.println("nums.0\t:" + String( nums[0]));
    Serial.println("nums.1\t:" + String( nums[1]));
    Serial.println("nums.2\t:" + String( nums[2]));

  */

  if (hasFunc) { // has function
    varCache = 666; // make parse errors stick out with mark of the beast
#ifndef LATER_DISABLE_OPTIMIZATIONS
    auto cb = funcLocalSlot ? script->FUNCS[funcLocalSlot - 65] : FUNCS[ptrCmd];
#else
    auto cb = FUNCS[ptrCmd];
#endif

    if (cb) {
      switch (arity) {
        case 1: varCache = cb( nums[0], -1, -1 ); break;
        case 2: varCache = cb( nums[0], nums[1], -1 ); break;
        default:  varCache = cb( nums[0], nums[1], nums[2] ); break;
      } //end switch arity
    } else {
      varCache = 404;
    }//end if cb?
  } else { // calc

    for (unsigned int ii = 1; ii < i; ii++) {
      tempInt = nums[ii];
      if (OVERRIDE) ops[ii - 1] = OVERRIDE;

      switch ( ops[ii - 1]) {
        case '+': varCache += tempInt; break;
        case ')': break;
        case '*': varCache *= tempInt; break;
        case '-': varCache = varCache -  tempInt; break;

        case ':': break; // do nothing, this is peeked by the ? operation
        case '?': varCache = varCache > 0 ? tempInt : nums[ii + 1] ; break;
        case '/': if (tempInt) varCache /= tempInt; break;
        case '|': varCache = varCache ? varCache : tempInt; break;
        case '!': varCache = varCache == tempInt ? 0 : 1; break;

        // these will work lisp-style
        case '&': varCache = varCache && tempInt ? 1 : 0; break;

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
        default: break;

          //case ',': break;
          //case ')': break;

      }//end operation switch
    }//next ii
  }//end if function or expression?

  /*
    unsigned long et = micros();
    Serial.println("\nexpression:"+String(s));
    Serial.println("cleanup and func name\t:"+String( at - st));
    Serial.println("parse terms\t:"+String( bt - xt));
    Serial.println("harvest terms\t:"+String( bt - at));
    Serial.println("calculate\t:"+String( et - bt));
    Serial.println("total\t:"+String( et - st)+"\n");
  */
  if (DMA > -1) {
    VARS[DMA] = varCache;
    HRT_TIME(math)
    return 1;
  }

  /*
    char * arrow = strstr(s, "->"); // optimize pixels
    if (arrow) {
      ptrCmd = arrow + 3;
      ptrCmd[0] = '@';
      char symb = getConstantNumber(NULL, script, varCache) + 65;
      ptrCmd[1] = symb;
      ptrCmd[2] = '\0';
      return 0;
    }
  */

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

  HRT_TIME(math)
  return 0;
} // end evalMath
bool evalConditionalExpression(char * string_condition, LATER_ENVIRON * s) {
  HRT_START

  char * ptr = string_condition;
  char * opPtr;

  char op, opHint, term1Slot;

  unsigned long term1 = 0,
                term2 = 0; // the values to compare

  bool ifConditionTrue = false,
       shouldInvert = false;

  // setup line cache:
  LATER_LINE * l = &s->lines[s->i];
  char * CACHE =  l->exprCache;
  unsigned long * VARS = s->VARS;
  char * funcName;

  //  exprCache map:
  //  0:shouldInvert
  //  1:op code
  //  2:op hint - basicaly is zero to indicate boolean single-term conditional ex: if $x
  //  3:term1 slot
  //  4:opPtr - string_condition offset
  //  5:term2 type :  1=var slot, 0=everything else. allows var slot 0 to be used instead of reflecting !!used
  //  6: term2 slot
  //  7:disble chained compare mode - 3+ terms

  if (!l->data) {

    memset(CACHE, '\0', 11);
    if (ptr[0] == '!') {
      shouldInvert = true;
      ptr++;
      while (ptr[0] == ' ') ptr++; // trim left
      CACHE[0] = 1;
    }///end if invert?
    opPtr = strpbrk (ptr, "=!<>%&|");

    op = opPtr ? opPtr[0] : 0;
    opHint = opPtr ? opPtr[1] : 0;

    CACHE[1] = op;
    CACHE[2] = opHint;
    if (ptr[0] == '@') {
      term1Slot = ptr[1] - 65;
      term1 = VARS[(int)term1Slot] ;
    } else {
      term1Slot = getConstantNumber(ptr, s);
      term1 = VARS[(int) term1Slot] ;
    }

    CACHE[3] = term1Slot;
    CACHE[4] = opPtr - string_condition;
    if (opHint) { //2nd term?
      char * t2 = strchr(opPtr + 1, '@');
      if (t2) {
        t2++;
        CACHE[5] = 1;
        CACHE[6] = t2[0] - 65;
        term2 = VARS[(int)CACHE[6]];
      } else {
        term2 =  Number(opPtr + 1, VARS);
      }
    }//end if

    l->data = 1;
    /*
      //////////////////////////////////// this is all experimental ///////////////////////////////////////////////
      // try to find a function to replace the logic. make a local copy, save func slot to CACHE[8]
      if (CACHE[5] && CACHE[6] && CACHE[2]) { // && CACHE[7]){
        char * nxtPtr = strpbrk (opPtr + 1, "=!<>%&|");
        if (!nxtPtr) {

          //  exprCache map:
          //  0:shouldInvert
          //  1:op code
          //  2:op hint - basicaly is zero to indicate boolean single-term conditional ex: if $x
          //  3:term1 slot
          //  4:opPtr - string_condition offset
          //  5:term2 type :  1=var slot, 0=everything else. allows var slot 0 to be used instead of reflecting !!used
          //  6: term2 slot
          //  7:disble chained compare mode - 3+ terms
          //  8:local function cache slot

          //char * funcName;
          char lut[] = "-DIFF +SUM *MULT /DIV <LT >GT =EQ !NEQ %MOD ";
          char * opPtr = strchr(lut, CACHE[1]);
          if (opPtr) {
            strchr(opPtr, ' ')[0] = '\0';
            funcName = opPtr + 1;
          }

          //  case '=': funcName= "EQ"; break;
          //  case '!': funcName= "NEQ"; break;
          //  case '>': funcName= "GT"; break;
          //  case '<': funcName= "LT"; break;
          //  case '%': funcName= "MOD"; break;
          //  }
          // this isn't wrong, it works, but i want to see if i can get apply to work instead,
          //becasue it can avoid template calling and interpolation, and prevent flag processessing
          // it could be a lot faster, i dunno. let's see.

          ////////////////////////
            if(funcName){
            auto callback = FUNCS[funcName];
            if(callback){
              int index = -1;
              // look for existing copy of cacched function to re-use:
              for (unsigned int i = 0; i < s->FUNC_COUNT; i++) {
                if (callback == s->FUNCS[i]) {
                index = i;
                break;
                }//end if callback found?
              }//next

              if (index == -1) index = s->FUNC_COUNT++;
              if (index < LATER_FUNCTION_CACHE_LENGTH){
                s->FUNCS[index] = callback; // cache locally

                DUMP("\ncallback cached:", index);
                DUMP("callback:", funcName);
                DUMP(">>>:", string_condition);
                DUMP("CACHE[5]:", CACHE[5]*1);
                DUMP("shouldInvert:", CACHE[0]*1);
                DUMP("term1:", (char)(CACHE[3]+65));
                DUMP("term2:", (char)(CACHE[6]+65));
                CACHE[8] = index;
                CACHE[9] = 1;
                l->data = 2;

              }//end if enough local func cache room?
            }//end if callback found?
            }//end if valid function name?

      //////////////////////// dd666 experitment
        }//end if no further operation?
      }//end if enough cache to try to make a function call?
      //////////////////////////////////// END OF  this is all experimental ///////////////////////////////////////////////

    */

  } else { // has line.data: restor state from last time:
    shouldInvert = CACHE[0];
    op = CACHE[1];
    opHint = CACHE[2];
    term1 =  VARS[(int) CACHE[3]];
    opPtr = string_condition + CACHE[4];
    term2 = CACHE[5] ? VARS[(int)CACHE[6]] : Number(opPtr + 1, VARS);
    if (CACHE[9]) { // dd666 could be badd
      ifConditionTrue = s->FUNCS[(uint8_t)CACHE[8]](term1, term2, 0);

      /*
        DUMP("callback rez:", ifConditionTrue);
          DUMP("shouldInvert:",shouldInvert);
          DUMP("term1:", term1);
          DUMP("term2:", term2);
      */
      return  shouldInvert ? (!ifConditionTrue) : ifConditionTrue;
    }
  }//end if first time or cache?


  if (op == '%'  && opHint == 0) { // random % syntax: if 10 %
    ifConditionTrue = term1 > (randomReg() % 100);
    HRT_TIME(cond)
    return ifConditionTrue;
  }//end if random change conditional?

  if (!op) { // if asking for truthyness of a single term, compare to zero and leave:  if $x
    ifConditionTrue = term1 > 0;
    if (shouldInvert) ifConditionTrue = !ifConditionTrue;
    HRT_TIME(cond)
    return ifConditionTrue;
  } // end if boolean self-compareto true?

  int opCount = 0;

  while (opPtr) {
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
    if (CACHE[7]) break; // known no further processing needed

    opCount++;
    term1 = term2;
    opPtr = strpbrk (opPtr + 1, "=!<>%&|"); // preumably, this breaks away

    if (opPtr) {
      op = opPtr[0];
      term2 =  Number(opPtr + 1, VARS); // atoi( opPtr + 1 ); RHS
    } else {
      if (opCount == 1) CACHE[7] = 1; // tried again and missed 1st time, don't check anymore
    }

  }//wend
  if (shouldInvert) ifConditionTrue = !ifConditionTrue;

  HRT_TIME(cond)

  return ifConditionTrue;
} // end evalConditionalExpression()
//#ifdef ESP8266HTTPClient_H_
#if defined(ESP8266HTTPClient_H_) || defined(HTTPClient_H_)
void popHttpResponse() {
  if (Later.httpResponseTextBuffer[0]) return;
  if (http.getSize() == 0) return;


  if (http.getSize() > LATER_HTTP_CACHE) {
    strncpy(Later.httpResponseTextBuffer, (char*) http.getString().c_str(), LATER_HTTP_CACHE - 1);
    Later.httpResponseTextBuffer[LATER_HTTP_CACHE - 1] = '\0';
  } else {
    strcpy(Later.httpResponseTextBuffer, (char*) http.getString().c_str());
  }
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
void processStringFormats(char* s , int index ) { // finds format flags in form of <#flag string#>, replacing between <##> with result
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
      ltoa( strtoul(out, NULL, 10), out, 16 );
      more = 0;
    }//end hex

    if (more && !strcmp(flagName, "lower")) {
      for (; i < slen; i++) out[i] = tolower(out[i]);
      more = 0;
    }//end lower
    if (more && !strcmp(flagName, "def")) {
      auto search = DEFINES[index].find(out);
      if ( (search != DEFINES[index].end()) && search->second && strlen(search->second) ) strcpy(out, search->second );
      more = 0;
    }//end def
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
    if (strchr(s, '<')) processStringFormats(s, index);
  }

  /*
    <escape
     <hex
     <upper
     <lower
     <pad1..9
     <trim
    <json
    <def key
  */

}//end processStringFormats()

void handleEval() {
  char linebuff[160];
  LATER_ENVIRON * s = LATER_SERVER_NAME.hasArg("name") ? Later.getByName(LATER_SERVER_NAME.arg("name").c_str()) : getCurrent();

  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);
  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.send ( 200, LATER_PLAIN, " ");
  strcpy(linebuff, LATER_SERVER_NAME.arg("code").c_str());
  if (strlen(linebuff) < 2) {
    LATER_SERVER_NAME.sendContent("Error: missing code GET param.");
  } else {
    laterCMD::runEval(linebuff, s);
  }

  LATER_SERVER_NAME.sendContent("");//ends and closes response
}//end handleEval()

#ifdef ESP8266WEBSERVER_H

void outputPaddedNumber(unsigned long value, const char * suffix, int width) {

  char respbuff[20];
  char pad[12] = "           ";
  char * ppad = pad;
  const char * ptrSuffix = suffix;

  if (value > 99999 ) {
    value = value / 1000;
    ptrSuffix++;
  }

  if (value > 99999 ) {
    value = value / 1000;
    ptrSuffix++;
  }

  itoa(value, respbuff, 10);

  ppad += strlen(respbuff) + (12 - width);

  if (strlen(ppad)) LATER_SERVER_NAME.sendContent(ppad);
  LATER_SERVER_NAME.sendContent(respbuff);
  pad[0] = ptrSuffix[0];
  pad[1] = ' ';
  pad[2] = '\0';
  LATER_SERVER_NAME.sendContent(pad);
} // end outputPaddedNumber()

#endif
void finishRun(LATER_ENVIRON * s) {
  s->runTime = micros() -  s->startedAt;
  s->duration += s->runTime;
  s->resumeLineNumber = s->startLineNumber;
  s->storeDirty = 0;
  s->calledFromWeb = 0;
  if (s->interval > 0) {
    s->resumeMillis = (s->interval - 1) + (millis() - ( s->runTime / 1000));
  } else {
    s->resumeMillis = 0;
  }
#ifdef HIGH_RES_TIMING
  HR_PERF.report();
#endif

}//end finishRun()
//

#line 1 "docs.ino"
//@TAKE

#line 1 "http.ino"

File fsUploadFile;
byte mac[6];  // the bytes of the station MAC address
const char *const RST_REASONS[] = {
  "REASON_DEFAULT_RST",
  "REASON_WDT_RST",
  "REASON_EXCEPTION_RST",
  "REASON_SOFT_WDT_RST",
  "REASON_SOFT_RESTART",
  "REASON_DEEP_SLEEP_AWAKE",
  "REASON_EXT_SYS_RST"
};
const char *const FLASH_SIZE_MAP_NAMES[] = {
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
std::map<std::string, std::string> PATHS;
std::map<std::string, std::string> BLURBS;

void handleGenericHttpRun(String fn) {
  const char *empty = "";
  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);
  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");

  LATER_ENVIRON *s = Later.load((char *)fn.c_str());  //dd666, move this somewhere better:
  if (!s) {
    LATER_SERVER_NAME.send(504, LATER_PLAIN, "504 - refused to load");
    LATER_SERVER_NAME.sendContent("");
    return;
  }

  if (!s->options.noget) {
    // load vars from url into script enviroment:
    String key, value, banned = ",$name,$content-type";
    for (uint8_t i = 0; i < LATER_SERVER_NAME.args(); i++) {
      key = "$" + LATER_SERVER_NAME.argName(i);
      value = LATER_SERVER_NAME.arg(i);
      if (banned.indexOf(',' + key + ',') > -1) continue;
      char slot = getVarNameNumber((char *)key.c_str(), s->index);
      s->VARS[(int)slot] = value.toInt();
    }
  }
  LATER_SERVER_NAME.send(200, (const char *)s->contentType, empty);  // start response
  s->calledFromWeb = 1;
  Later.run((char *)fn.c_str());         // execute em!
  LATER_SERVER_NAME.sendContent(empty);  // finish response
  /*
      if (LATER_SERVER_NAME.hasArg("persist")) return;
    if (s->options.persist) return;

    if (  !strchr(fnp, '~') ) {
      Later.unload(fnp);
    } else {
      s->options.persist = true;
    }
  */
}  //end handleGenericHttpRun();

void handleAPI() {  // break in here and look for default.bat or index.bat
  String fn = "/index.bat";
  if (SPIFFS.exists(fn) && !LATER_SERVER_NAME.hasArg("default")) {
    handleGenericHttpRun(fn);
    return;
  }  //end if bat file found?

  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);
  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");

  char TAGLINE[25] = "Later";

#ifdef LATER_PROJECT
  strcpy(TAGLINE, LATER_PROJECT);
#endif
  LATER_SERVER_NAME.send(200, "text/html", F("<html><body><title>"));

  LATER_SERVER_NAME.sendContent(TAGLINE);

  LATER_SERVER_NAME.sendContent(F("</title><style>*{font: 26px monospace;background:#222; color: #ccc; }a{text-decoration:none;color:#77a;}li>a:first-child:visited{color: #aaf;font-weight:bold;}li{list-style:none;padding-bottom: 0.5em;}small{font-size: 80%;white-space:pre; color:#777;}li>a:first-child{width: 7em;display: inline-block;}li:first-child small,li:first-child a{color:#fff}aside{font-size: 20px;opacity:0.8;}h1{font-size: 32px;}</style><h1>"));

  LATER_SERVER_NAME.sendContent(TAGLINE);

  LATER_SERVER_NAME.sendContent(F("</h1><big><big><ul><li>\n<a href=#>Endpoint </a> <small> Kind  Type  Params/Description</small></b>\n<li><a href=/autoexec.bat>/autoexec.bat</a> <small> API TXT View startup script</small>\n<li><a href=/config/>/config</a> <small> UI  HTML  Config options interface</small>\n"));
  delay(5);

  char line[64];
  //char blurb[160];
  for (const auto &x : PATHS) {

    Serial.print(x.first.c_str());
    Serial.print(" - ");

    int len = strlen(BLURBS[x.first.c_str()].c_str()) - 1;
    strncpy(TEMP_BUFFER, BLURBS[x.first.c_str()].c_str(), len);
    TEMP_BUFFER[len] = '\0';
    if (strlen(TEMP_BUFFER) < 5) strcpy(TEMP_BUFFER, "missin");
    //TEMP_BUFFER = "teeee";


    delay(1);

    LATER_SERVER_NAME.sendContent(sprintf(line, "<li><a href=%s>%s</a> ", x.first.c_str(), x.first.c_str()) ? line : line);
    LATER_SERVER_NAME.sendContent(" <small> ");
    LATER_SERVER_NAME.sendContent(TEMP_BUFFER + 1);
    LATER_SERVER_NAME.sendContent("</small>\n");
  }
  delay(5);

  LATER_SERVER_NAME.sendContent("\n<li><a href=/update>/update</a> <small> UI HTML  OTA update interface</small>\n");

  LATER_SERVER_NAME.sendContent("<br><br><aside>Built on ");
  LATER_SERVER_NAME.sendContent(__DATE__);
  LATER_SERVER_NAME.sendContent(" for ");

#ifdef ARDUINO_BOARD
  LATER_SERVER_NAME.sendContent(ARDUINO_BOARD);
#else
  LATER_SERVER_NAME.sendContent("Unknown Board");
#endif
  LATER_SERVER_NAME.sendContent(" w/ ");

#ifdef ESP8266
  itoa(ESP.getFlashChipRealSize() / 1024, line, 10);
#else
  itoa(ESP.getFlashChipSize() / 1024, line, 10);
#endif

  LATER_SERVER_NAME.sendContent(line);
  LATER_SERVER_NAME.sendContent("k flash ");

  LATER_SERVER_NAME.sendContent(" as ");
#ifdef LATER_PROJECT
  LATER_SERVER_NAME.sendContent(LATER_SKETCH);  //manual name
#else
#ifdef ESP8266
  LATER_SERVER_NAME.sendContent(WiFi.hostname());  //esp32
#else
  LATER_SERVER_NAME.sendContent(WiFi.getHostname());  //esp32
#endif
#endif

  LATER_SERVER_NAME.sendContent("<br>");
  LATER_SERVER_NAME.sendContent(WiFi.macAddress());

  LATER_SERVER_NAME.sendContent(" at ");
  LATER_SERVER_NAME.sendContent(WiFi.localIP().toString());
  LATER_SERVER_NAME.sendContent("</aside>");
  LATER_SERVER_NAME.sendContent(F(" <form id=f1 method=post action=/upload enctype=multipart/form-data target=_blank><label>Upload File <input onchange='setTimeout(function(){f2.click()},222);' accept='application/*'  type=file name=file></label><input type=submit value=Upload id=f2 ></form></body></html>"));
  LATER_SERVER_NAME.sendContent("");
}

void handleDelete() {
  String fn = LATER_SERVER_NAME.arg("name");

  if (!LATER_SERVER_NAME.hasArg("name")) {
    LATER_SERVER_NAME.send(404, "text/json", F("false"));
    return;
  }

  if (fn[0] != '/') fn = "/" + fn;  // optionalize preceding slash

  if (SPIFFS.exists(fn)) {
    SPIFFS.remove(fn);
    LATER_SERVER_NAME.send(200, "text/json", F("true"));
    return;
  }  //end if bat file found?

  // should not make it this far, file not found:
  LATER_SERVER_NAME.send(402, "text/json", F("false"));
}

void (*resetFunc)(void) = 0;  //declare reset function at address 0

void handleReboot() {
  String message = F("<body><h1>Rebooting. Allowing 7 seconds.</h1> <progress></progress> <script> setTimeout(function(){ location.href= localStorage.dest || '/';  },7300);</script></body> ");
  LATER_SERVER_NAME.send(200, "text/html", message);
  LATER_SERVER_NAME.close();
  delay(250);
  yield();
  resetFunc();
}
void handleResume() {

  char resp[10] = "false";
  bool status = false;
  const char *fn = LATER_SERVER_NAME.arg("name").c_str();
  status = Later.resume(fn);
  if (status) strcpy(resp, "true");

  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.send(200, "text/plain", resp);
}
void handleSuspend() {

  char resp[10] = "false";
  bool status = false;

  unsigned int ms = LATER_SERVER_NAME.arg("ms").toInt();
  const char *fn = LATER_SERVER_NAME.arg("name").c_str();
  if (fn[0] == '/') status = Later.suspend(fn, ms);
  if (status) strcpy(resp, "true");

  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.send(200, "text/plain", resp);
}
#ifdef ESP32
const char *serverIndex =
  "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
  "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
  "<input type='file' name='update'>"
  "<input type='submit' value='Update'>"
  "</form>"
  "<div id='prg'>progress: 0%</div>"
  "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')"
  "},"
  "error: function (a, b, c) {"
  "}"
  "});"
  "});"
  "</script>";

#endif
void bindServerMethods() {
#ifdef ESP32
  LATER_SERVER_NAME.on("/update", HTTP_GET, []() {
    LATER_SERVER_NAME.sendHeader("Connection", "close");
    LATER_SERVER_NAME.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  LATER_SERVER_NAME.on(
  "/update", HTTP_POST, []() {
    LATER_SERVER_NAME.sendHeader("Connection", "close");
    LATER_SERVER_NAME.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  },
  []() {
    HTTPUpload &upload = LATER_SERVER_NAME.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {  //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) {  //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });

#endif
  LATER_SERVER_NAME.on("/", handleAPI);  // this style of sub won't be listed
  // subscript public GET endpoints:
  //@TAKE

  // subscribe public GET endpoints:
  SUB_PATH(run, handleRun, "API  TXT @name Runs a script by filename");
  //@TAKE
  SUB_PATH(scripts, handleScripts, "API  JSON  Details of running scripts");
  SUB_PATH(log, handleLog, F("API  TXT View logged messages. See <a target=_blank href=https://github.com/rndme/later/blob/master/docs/api.md#log>docs</a> for GET options. "));
  SUB_PATH(dir, handleFileList, "API JSON  Lists stored files w/ details");

  SUB_PATH(resume, handleResume, F("API JSON  @name Resumes a suspended script file by name. "));
  SUB_PATH(suspend, handleSuspend, F("API JSON  @name @ms Suspends and unloads a script file by name. "));

  SUB_PATH(ls, handleLS, "UI HTML  File manager interface - allows deletes and uploads");
  SUB_PATH(delete, handleDelete, "API  JSON  @name Deletes a script by filename");
  SUB_PATH(reboot, handleReboot, "API  HTML  Reboots the ESP");
  SUB_PATH(editor, handleEditor, "UI HTML  Script editor interface");


  SUB_PATH(store, handleStore, F("API TSV Stored vars. See <a target=_blank href=https://github.com/rndme/later/blob/master/docs/api.md#store>docs</a> for GET options. "));
  SUB_PATH(unload, handleUnload, "API  JSON  @name Unloads a running Script by filename");
  SUB_PATH(test, handleDump, F("API  TXT @name Get debug information of a running script by script filename"));

  SUB_PATH(step, handleStep, F("API  TXT @name Step to next line of step option script by filename"));

  SUB_PATH(eval, handleEval, "API  TXT @name Runs a Script by filename");
  SUB_PATH(help, handleCommandList, F("API TXT List available commands and functions and templates"));

  LATER_SERVER_NAME.on(
  "/upload", HTTP_POST, []() {
    LATER_SERVER_NAME.send(200, LATER_PLAIN, "ok");
  },
  handleFileUpload);
  LATER_SERVER_NAME.onNotFound([]() {
    String fn = LATER_SERVER_NAME.uri() + ".bat";
    if (SPIFFS.exists(fn)) {
      handleGenericHttpRun(fn);
      return;
    }  //end if bat file found?
    if (!handleFileRead(LATER_SERVER_NAME.uri()))
      LATER_SERVER_NAME.send(404, LATER_PLAIN, "FileNotFound: " + LATER_SERVER_NAME.uri());
  });
}  //end bindServerMethods()
#ifdef ESP8266

#else

#endif
void handleLS() {  // replace with non-string non-crap:

  String path = LATER_SERVER_NAME.arg("dir");
  if (path == "") path = "/";
#ifdef ESP8266
  Dir dir = SPIFFS.openDir(path);
#else
  File dir = SPIFFS.open(path);
#endif
  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);
  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.send(200, "text/html", "");

  LATER_SERVER_NAME.sendContent(F("<html><head><title>"));
  LATER_SERVER_NAME.sendContent(path);
  LATER_SERVER_NAME.sendContent(F("</title><style>@import 'https://maxcdn.bootstrapcdn.com/bootswatch/3.3.7/cyborg/bootstrap.min.css';\n  a,b,small { display: inline-block; min-width: 11em;}"));
  LATER_SERVER_NAME.sendContent(F(" ol li { margin-top: 0.25em; font-size: 125%; }</style></title></head><body class=container> <h1>"));
  LATER_SERVER_NAME.sendContent(path);
  LATER_SERVER_NAME.sendContent(F("</h1> <ol id=list></ol><script>["));

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
      LATER_SERVER_NAME.sendContent(",\n{\"type\":\"");
      LATER_SERVER_NAME.sendContent((isDir) ? "dir" : "file");
      LATER_SERVER_NAME.sendContent("\",\"name\":\"");
#ifdef ESP8266
      LATER_SERVER_NAME.sendContent(entry.name() + 1);
#else
      LATER_SERVER_NAME.sendContent(entry.name());  // Ignore '/' prefix
#endif
#ifdef ESP8266
      LATER_SERVER_NAME.sendContent("\",\"size\":\"");
      LATER_SERVER_NAME.sendContent(laterUtil::formatBytes(dir.fileSize()));
#endif
#ifdef ESP32
      LATER_SERVER_NAME.sendContent("\",\"size\":\"");
      LATER_SERVER_NAME.sendContent(laterUtil::formatBytes(dir.size()));
#endif

      LATER_SERVER_NAME.sendContent("\",\"mime\":\"");
      LATER_SERVER_NAME.sendContent(getContentType(entry.name()));
      LATER_SERVER_NAME.sendContent("\"}");
      entry.close();

    }  //end if name long?

#ifdef ESP32
    entry = dir.openNextFile();
#endif
  }

  LATER_SERVER_NAME.sendContent(F("].filter(Boolean).map(function(a){list.appendChild(document.createElement('li')).innerHTML='<input type=button onclick=\"doDel(nextElementSibling.href)\" value=X > '+a.name.link('/'+a.name)+' '+'run'.link('/run/?name='+encodeURIComponent(a.name))+'  ' +'edit'.link('/editor/#'+a.name)+' ' + a.size.bold()+' ' + a.mime.small(); });function doDel(fn){if(!confirm('ERASING FILE: '+fn+'\\n\\nThis CANNOT be undone !!!'))return; var path = '/' + fn.split('/').pop(); fetch('/delete/?name='+encodeURIComponent(path)).then(function(){location.reload();});return false;}</script>"));
  LATER_SERVER_NAME.sendContent(F("<hr><form id=f1 method=post action=/upload enctype=multipart/form-data target=_blank><label>Upload Embeded File <input onchange='setTimeout(function(){f2.click()},222);' accept='application/*'  type=file name=file></label><input type=submit value=Upload id=f2 ></form></body>"));
  LATER_SERVER_NAME.sendContent("");
}
//25968 > 26268 > 26772
void handleEditor() {


  // move this to a multipart response, print most of it, then print define path to script, then print html page closer/footer.

  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);
  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.send(200, "text/html", "");

  LATER_SERVER_NAME.sendContent(F("<!doctype html><html><head>\n    <meta charset=\"ISO-8859-1\">    <title>later editor</title>\n<link rel=icon href=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAAFiUAABYlAUlSJPAAAAAcSURBVDhPY/hr+fc/JXjUgFEDQHjUgGFgwN//AJBjMi73juieAAAAAElFTkSuQmCC> \n<link rel=stylesheet type=text/css href='//maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css' />\n<style>\tbody {background:#000;color:#888;padding-top:5px; } #files{ width: 7em; }  #val {overflow: scroll;width: 99%; height: 85vh; font: 24px monospace; } div#stats {position: fixed;top: 1em;right: 3em;width: 40%;background: #111;padding: 1em;overflow: auto;height: 90vh;border: 1px solid #888;font: 20px monospace;}\n</style>\n</head>\n<body class=container-fixed><a href='/docs/'>Home</a>\n   <select id=files onchange='loadme(value)'>\n  <option value=\"\">Load File...<option>\n  </select>  &nbsp; \n <label>Filename: \n  <input type=text id=inpname size=32>\n</label>\n    &nbsp;   &nbsp; \n   <input type=button class='btn btn-success btn-sm' value=Save id=btnsave onclick='saveIt(inpname.value, val.value)'>\n&nbsp;   &nbsp; \n   <input type=button class='btn btn-warning btn-sm' value=Run id=btnrun onclick='runme(inpname.value)'> \n&nbsp;   &nbsp; \n   <input type=button class='btn btn-info btn-sm' value=Test id=btntest onclick='test()'> \n&nbsp;   &nbsp; <label> auto-test <input type=checkbox id=chkauto></label>\n\n&nbsp;   &nbsp;\n&nbsp;   &nbsp; <label> URL Params <input type=input id=inpqs value=\"&reload=true\" size=24></label>\n\n   <input type=button class='btn btn-xs btn-info pull-right btn-sm' value=\"?\" id=btnhelp onclick='showHelp()'> \n\n<br> \n<div id=edwrap>\n<textarea id=val rows=40 cols=90></textarea></div>\n\n<div id=stats></div>\n<form method='POST' action='/update' target=_blank enctype='multipart/form-data' onsubmit='setTimeout(function(){file11.value=null}, 25000)' >\n                  <input id=file11 type='file' accept='application/*' name='update'>\n                  <input type='submit' value='Update'>\n               </form>\n\n\n<script>\nvar url = '/';\n\nfunction saveIt(name, value) {\n\tif(!name) return alert('filename blank, try again');\n\tvar dbs = document.body.style,\n\t\tfile = new File([value], name, {\n\t\t\ttype: \"text/plain\",\n\t\t}),\n\t\tform = new FormData();\n\tdbs.opacity = 0.5;\n\tform.append('file', file, name);\n\tfetch(url + 'upload', {\n\t\tbody: form,\n\t\tmethod: 'POST',\n\t\tmode: 'cors'\n\t}).then(x => {\n\t\tdbs.opacity = 1;\n\t\tdir();\n\t\tlocation.hash = name;\n\t\tdocument.title=\"@\"+name;\n\t});\n}\n\nfunction dir() {\n\tfetch(url + 'dir').then(x => x.json()).then(x => {\n\t\tfiles.options.length = 1;\n\t\tx.sort(function(a,b){return a.name>b.name?1:-1;}).map(function(a, i) {\n\t\t\tfiles.appendChild(new Option(a.name + \" : \" + a.size, a.name));\n\t\t});\n\t})\n}\n\n \nfunction test() {\n\tfetch(url + 'test').then(x => x.text()).then(x=>{\n\t\t stats.innerText= x;\t\n\t});\n}\n\n\nfunction loadme(file) {\n        var dbs = document.body.style;\n\tdbs.opacity = 0.3;\n\tfetch(url + file).then(x => x.text()).then(x => {\n\t\tval.value = x;\n\t\tinpname.value = file;\n\t\tval.focus();\n\t\tdbs.opacity = 1;\n\t\tlocation.hash = file;\n\t\tdocument.title=\"@\"+file;\n\t});\n\n}\nvar cache;\nfunction showHelp(){\n  var done = x=>{\n   var s = x.split(/<\\/?pre/i)[1].slice(1).trim();\n   cache = x;\n   stats.innerText = s;\n  };\n  if(cache) return done(cache);\n  fetch(\"/docs/\").then(x=>x.text()).then(done);\n}\n\nfunction runme(file) {\n\tif(!file) return alert(\"no file chosen\");\n\tvar dbs = document.body.style;\n\tdbs.opacity = 0.3;\n\tfetch(url + \"run?name=\" + encodeURIComponent(file) + inpqs.value ).then(x => x.text()).then(x => {\n\t\tval.focus();stats.title=x;\n\t\tdbs.opacity = 1;\n\t\tif(chkauto.checked) setTimeout(test, 500);\n\t});\n}\nif(location.hash) loadme(location.hash.slice(1));\nsetTimeout(dir, 140);\n</script>"));

  LATER_SERVER_NAME.sendContent("<script src=");
  LATER_SERVER_NAME.sendContent(LATER_EDITOR_URL);
  LATER_SERVER_NAME.sendContent("></script>");
  LATER_SERVER_NAME.sendContent("\n</body>\n</html>");
  LATER_SERVER_NAME.sendContent("");
}  //end handle editor
String getContentType(String filename) {
  if (LATER_SERVER_NAME.hasArg("download")) return "application/octet-stream";
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
    LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
    LATER_SERVER_NAME.streamFile(file, contentType);
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
  message += " \"req_uri\":\t\"" + String(LATER_SERVER_NAME.uri()) + "\",\n";
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
  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.send(200, "application/json", message);
  #endif
  }
*/
void handleFileUpload() {
  static String filename;


  HTTPUpload &upload = LATER_SERVER_NAME.upload();
  if (upload.status == UPLOAD_FILE_START) {
    filename = upload.filename;
    if (!filename.startsWith("/")) filename = "/" + filename;
#ifdef DEBUG_WEBSERVER
    Serial.printf("handleFileUpload Name: %s\n", filename.c_str());
#endif  // DEBUG_WEBSERVER
    fsUploadFile = SPIFFS.open(filename, "w");
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile) {
      fsUploadFile.close();
      if ((!LATER_SERVER_NAME.hasArg("reload")) && Later.getByName((char *)filename.c_str())) Later.unload((char *)filename.c_str());
      if ((LATER_SERVER_NAME.hasArg("reload")) && Later.getByName((char *)filename.c_str())) Later.run((char *)filename.c_str());

      // handleSetFileLastFileName = ""; // bust any batch file caches
      LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
      LATER_SERVER_NAME.send(200, "text/html", F("<html><title>Done Uploading...</title><h1>Done</h1><script>location.replace('/ls');</script></html>"));
    }
#ifdef DEBUG_WEBSERVER
    Serial.printf(F("handleFileUpload Size: %u\n"), upload.totalSize);
#endif  // DEBUG_WEBSERVER
  }
}  //end handleFileUpload()
void handleFileList() {

  String path = LATER_SERVER_NAME.arg("dir");
  if (path == "") path = "/";

#ifdef ESP8266
  Dir dir = SPIFFS.openDir(path);
#else
  File dir = SPIFFS.open(path);
#endif

  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);
  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.send(200, "text/json", "[{}");

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
      LATER_SERVER_NAME.sendContent(",\n{\"name\":\"");

#ifdef ESP8266
      LATER_SERVER_NAME.sendContent(entry.name() + 1);
#else
      LATER_SERVER_NAME.sendContent(entry.name());  // Ignore '/' prefix
#endif
#ifdef ESP8266
      LATER_SERVER_NAME.sendContent("\",\"size\":\"");
      LATER_SERVER_NAME.sendContent(laterUtil::formatBytes(dir.fileSize()));
#endif
#ifdef ESP32
      LATER_SERVER_NAME.sendContent("\",\"size\":\"");
      LATER_SERVER_NAME.sendContent(laterUtil::formatBytes(entry.size()));
#endif
      LATER_SERVER_NAME.sendContent("\",\"mime\":\"");
      LATER_SERVER_NAME.sendContent(getContentType(entry.name()));
      LATER_SERVER_NAME.sendContent("\"}");
      entry.close();
    }

#ifdef ESP32
    entry = dir.openNextFile();
#endif
  }

  LATER_SERVER_NAME.sendContent("]");
  LATER_SERVER_NAME.sendContent("");
  /*

    String path = LATER_SERVER_NAME.arg("dir");

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
    LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
    LATER_SERVER_NAME.send(200, "text/json", output);

  */
}  //end handFileList()
void handleUnload() {
  char fnb[32] = { '/' };
  char *fnp = fnb + 1;
  memset(fnp, '\0', 31);
  strcpy(fnp, LATER_SERVER_NAME.arg("name").c_str());
  if (fnp[0] == '*') {
    for (int i = 0, mx = Later.loadedScripts; i < mx; i++) {
      fnp = SCRIPTS[i].fileName;
      Later.unload(fnp);
    }

  } else {
    if (fnp[0] != '/') fnp = fnb;
    Later.unload(fnp);
  }

  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.send(200, "text/json", "true");
}
void handleRun() {

  char fnb[44] = { '/' };
  char *fnp = fnb + 1;
  memset(fnp, '\0', 43);
  strcpy(fnp, LATER_SERVER_NAME.arg("name").c_str());
  if (fnp[0] != '/') fnp = fnb;

  if (SPIFFS.exists(fnp)) {
    handleGenericHttpRun(fnp);
    /*
        LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);
        LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");

        LATER_ENVIRON * s = Later.load(fnp);
        if (!s) {
          LATER_SERVER_NAME.send ( 503, LATER_PLAIN, "503 - refused to load");
          LATER_SERVER_NAME.sendContent("");
          return;
        }

        // load vars from url into script enviroment:
        String key, value, banned = ",$reload,$name,$content-type";
        for (uint8_t i = 0; i < LATER_SERVER_NAME.args(); i++) {
          key =  "$" + LATER_SERVER_NAME.argName(i);
          value = LATER_SERVER_NAME.arg(i);
          if (!isdigit(value[0])) continue;
          if (banned.indexOf(',' + key + ',') > -1) continue;
          char slot = getVarNameNumber((char*)key.c_str(), s->index);
          s->VARS[(int)slot] = value.toInt();
        }
        if (LATER_SERVER_NAME.hasArg("content-type")) {
          LATER_SERVER_NAME.send ( 200, LATER_SERVER_NAME.arg("content-type"), "");
        } else {
          LATER_SERVER_NAME.send ( 200,  s->contentType, "");
        }

        s->calledFromWeb = 1;
        Later.run(fnp);
        LATER_SERVER_NAME.sendContent("");
        if (LATER_SERVER_NAME.hasArg("persist")) return;
        if (s->options.persist) return;

        if (  !strchr(fnp, '~') ) {
          Later.unload(fnp);
        } else {
          s->options.persist = true;
        }

    */

    //LATER_INSTANCES
    return;
  }  //end if bat file found?

  LATER_SERVER_NAME.send(404, LATER_PLAIN, "404 - batch not found");

}  //end handleRun()
void handleLog() {

  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");

  if (LATER_SERVER_NAME.hasArg("tail")) {
    int count = LATER_SERVER_NAME.arg("tail").toInt();

    if (count < 1) {  // passed in url w/o value or zero, grab just the last line:
      LATER_SERVER_NAME.send(200, LATER_PLAIN, strrchr(setRunLog, '\n') + 1);
      return;
    }

    // grab tails chars specified by tail arg:
    int pos = strlen(setRunLog) - count;
    if (pos < 0) pos = 0;
    char *ret = setRunLog + pos;
    LATER_SERVER_NAME.send(200, LATER_PLAIN, ret);
    return;
  }  //end if tail arg?
  //////////////////////////////////////////////////////////////
  // processed results  - chunked line-by-line results:
  if (LATER_SERVER_NAME.args() > 0) {
    LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);  //Enable Chunked Transfer
    LATER_SERVER_NAME.send(200, LATER_PLAIN, LATER_LOG_HEADER);  //Send first part WITH header

    int pos = strcspn(setRunLog + 1, "\n");

    // take, skip, larger, smaller, after, before, filter, exclude, count

    char *rest = setRunLog;
    char line[64];
    char termBuffer[24];
    char excludeBuffer[24];

    bool is_filter = LATER_SERVER_NAME.hasArg("filter");

    bool is_after = LATER_SERVER_NAME.hasArg("after");
    bool is_before = LATER_SERVER_NAME.hasArg("before");
    bool is_larger = LATER_SERVER_NAME.hasArg("larger");
    bool is_smaller = LATER_SERVER_NAME.hasArg("smaller");
    bool is_exclude = LATER_SERVER_NAME.hasArg("exclude");
    bool is_take = LATER_SERVER_NAME.hasArg("take");
    bool is_skip = LATER_SERVER_NAME.hasArg("skip");
    bool is_count = LATER_SERVER_NAME.hasArg("count");
    unsigned long afterTime = strtoul(LATER_SERVER_NAME.arg("after").c_str(), NULL, 0);
    unsigned long beforeTime = strtoul(LATER_SERVER_NAME.arg("before").c_str(), NULL, 0);

    unsigned int largerThan = LATER_SERVER_NAME.arg("larger").toInt();
    unsigned int smallerThan = LATER_SERVER_NAME.arg("smaller").toInt();

    int takeLeft = LATER_SERVER_NAME.arg("take").toInt();
    int skipLeft = LATER_SERVER_NAME.arg("skip").toInt();
    int countOfResults = 0;
    unsigned long lineTime;
    char lineTimeString[16];

    if (is_filter) strcpy(termBuffer, LATER_SERVER_NAME.arg("filter").c_str());
    if (is_exclude) strcpy(excludeBuffer, LATER_SERVER_NAME.arg("exclude").c_str());

    bool is_wanted;

    int logLeft = strlen(rest);

    while ((logLeft - pos) > 1) {
      // copy line from string to buffer:
      strncpy(line, rest + 1, pos);
      line[pos] = '\n';
      line[pos + 1] = '\0';

      // now filter by making sure line contains term

      is_wanted = 1;
      if (is_filter && is_wanted) is_wanted = strstr(line, termBuffer);
      if (is_exclude && is_wanted) is_wanted = !strstr(line, excludeBuffer);

      if (is_larger && is_wanted) is_wanted = strlen(line) > largerThan;
      if (is_smaller && is_wanted) is_wanted = strlen(line) < smallerThan;
      if (is_after && is_wanted) {
        // parse a time from log line
        int delimPos = strcspn(line, "\t: ");
        strncpy(lineTimeString, line, delimPos);
        lineTime = strtoul(lineTimeString, NULL, 0);
        is_wanted = (lineTime > afterTime);
      }
      if (is_before && is_wanted) {
        // parse a time from log line
        int delimPos = strcspn(line, "\t: ");
        strncpy(lineTimeString, line, delimPos);
        lineTime = strtoul(lineTimeString, NULL, 0);
        is_wanted = (lineTime < beforeTime);
      }
      if (is_skip && is_wanted) is_wanted = skipLeft-- < 1;
      if (is_take && is_wanted) {
        is_wanted = takeLeft-- > 0;
        if (takeLeft < 0) break;  // early bail optomize if no more results wanted
      }                           //end if take?
      // based on the guantlet above, do we still want the line in the results?
      if (is_wanted) {
        if (is_count) {
          countOfResults++;
        } else {
          LATER_SERVER_NAME.sendContent(line);
        }
      }
      // find next line, if any
      if (rest[0]) {
        rest = strchr(rest + 1, '\n');
        pos = strcspn(rest + 1, "\n");
      } else {
        rest[0] = '\0';
        break;
      }

      logLeft = strlen(rest);

    }  // wend rest
    if (is_count) {
      LATER_SERVER_NAME.sendContent(String(countOfResults));
    }

    LATER_SERVER_NAME.sendContent(F(""));  // this tells web client that transfer is done
    LATER_SERVER_NAME.client().stop();
    //Tell browser no more content is coming
    return;
  }  //end if params?
  //////////////////////////////////////////////////////////////
  // END processed results
  // serve whole log:
  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);  //Enable Chunked Transfer
  LATER_SERVER_NAME.send(200, LATER_PLAIN, LATER_LOG_HEADER);
  LATER_SERVER_NAME.sendContent(strchr(setRunLog, '\n') + 1);
  LATER_SERVER_NAME.sendContent(F(""));

}  //end handleLog()
// before log api

// after log api:
void handleCommandList2() {

  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);                                                  //Enable Chunked Transfer
  LATER_SERVER_NAME.send(200, LATER_PLAIN, "COMMAND LISTING (duplicate keys are aliases)\n\nKey\tCommand\n");  //Send first part WITH header

  char c[2] = { 0, 0 };
  for (auto const &x : LATER_CMDS) {
    c[0] = x.second;
    if (!c[0]) continue;
    LATER_SERVER_NAME.sendContent(c);
    LATER_SERVER_NAME.sendContent("\t");
    LATER_SERVER_NAME.sendContent(x.first);
    LATER_SERVER_NAME.sendContent("\n");
  }
  LATER_SERVER_NAME.sendContent("");
}  //end handleCommandList()
// a 100-line or fewer key:value store with smart api for managing it. file backed peristent storage.

void handleStore() {

  if (LATER_SERVER_NAME.hasArg("value")) {
    if (LATER_SERVER_NAME.hasArg("ram")) {
      LATER_STORE.update(LATER_SERVER_NAME.arg("key").c_str(), LATER_SERVER_NAME.arg("value").toInt());
    } else {
      LATER_STORE.set(LATER_SERVER_NAME.arg("key").c_str(), LATER_SERVER_NAME.arg("value").toInt());
    }
    getCurrent()->storeDirty = 1;
  } else if (LATER_SERVER_NAME.hasArg("key")) {
    LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
    LATER_SERVER_NAME.send(200, LATER_PLAIN, String(LATER_STORE.get(LATER_SERVER_NAME.arg("key").c_str())));
    return;
  }

  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);
  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.send(200, LATER_PLAIN, "key  \ttimestamp\tver\tvalue\n");
  for (int i = 0; i < LATER_STORE.length; i++) {
    LATER_SERVER_NAME.sendContent(LATER_STORE.stringify(i));
    LATER_SERVER_NAME.sendContent("\n");
  }  //next

  LATER_SERVER_NAME.sendContent("");

  // serve whole log:

}  // handleStore()
int INDENT_LEVEL = 0;

void addJSON(char *buff, const char *key, unsigned long value) {
  char liner[52] = { '\t', '\t', '\t', '\t', '\t', '\t' };
  char *line = liner;
  line += INDENT_LEVEL;
  sprintf(line, "\"%s\": %lu,\n", key, value);
  strcat(buff, liner);
}

void addJSON(char *buff, const char *key, const char *value) {
  char liner[52] = { '\t', '\t', '\t', '\t', '\t', '\t' };
  char *line = liner;
  line += INDENT_LEVEL;

  sprintf(line, "\"%s\": \"%s\",\n", key, value);
  strcat(buff, liner);
}

void backtrack(char *buff) {
  buff[strlen(buff) - 2] = '\0';
}

void handleScripts() {

  int mx = Later.scriptCount;
  //char out[2048] = {'{', '\n'};
  char *out = FILE_BUFF;
  out[0] = '{';
  out[1] = '\n';
  memset(out + 2, '\0', 2045);

  INDENT_LEVEL = 1;

  addJSON(out, "count", Later.loadedScripts);
  addJSON(out, "current", Later.currentScript);
  addJSON(out, "ms", millis());
  addJSON(out, "ram", ESP.getFreeHeap());
  addJSON(out, "bootram", Later.bootRam);
  strcat(out, "\t\"scripts\":[  \n");  // start scripts:
  INDENT_LEVEL = 2;
  // iterate scripts:
  for (int i = 0; i < mx; i++) {
    if (!SCRIPTS[i].lineCount) continue;
    unsigned long runTime = (millis() - SCRIPTS[i].loadedAt) * (unsigned long)1000;
    strcat(out, "\t{\n");

    addJSON(out, "fileName", SCRIPTS[i].fileName);
    addJSON(out, "index", SCRIPTS[i].index);
    addJSON(out, "frozen", SCRIPTS[i].resumeLineNumber ? 1 : 0);
    addJSON(out, "interval", SCRIPTS[i].interval);
    addJSON(out, "persist", SCRIPTS[i].options.persist);
    addJSON(out, "step", SCRIPTS[i].options.step);
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
    addJSON(out, "cpuUtil", (SCRIPTS[i].duration * 100) / runTime);
    addJSON(out, "lifeTime", runTime);
    addJSON(out, "runs", SCRIPTS[i].runs);
    backtrack(out);
    strcat(out, "\n\t},\n");
  }

  INDENT_LEVEL = 0;

  if (mx) backtrack(out);

  strcat(out, "\n\t\t]\n}");  //end scripts


  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.send(200, "text/json", out);
}
#endif

#line 1 "loader.ino"
int loadScript(const char * scriptFileName) { //dd666 make this a class method
  unsigned long st = micros();
  TIMER(scriptFileName);
  char * fileBuff = laterUtil::fileToBuff(scriptFileName);
  char clean[LATER_PROGRAM_SIZE];
  char * outptr = clean;
  char * cleanptr = clean;
  char * lb = fileBuff; //strstr(buff, "\n");

  // stuff for lines:
  char * line = LINE_BUFF; //[LATER_LINE_BUFFER];
  memset(line, '\0', 16);
  char cmd[16];
  char consts[17] = "0000000000000000";

  //char * macroRep = TEMPLATE_BUFFER;

  int lineCount = 0;
  int endpos = strcspn( fileBuff, "\n");
  int lineLen = 0;
  bool isPrintBlock = 0;
  bool isStaticPrintBlock = 0;
  bool isConstant = false;
  unsigned long lineData = 0;
  int scriptIndex = 0;
  // find empty slot index:
  for (; scriptIndex < LATER_INSTANCES; scriptIndex++) {
    if (SCRIPTS[scriptIndex].lineCount == 0) break;
  }

  LATER_ENVIRON * SCRIPT = &SCRIPTS[scriptIndex];
  SCRIPT->loadedAt = millis();
  SCRIPT->i = 0;
  strcpy(SCRIPT->fileName, scriptFileName);
  laterUtil::trimLeft(fileBuff, true);

  // replace #includes
  replaceIncludes(fileBuff);

  // replace special macros like __FILENAME__ and __SKETCH_FILE__
  replaceSpecialMacros(fileBuff, scriptFileName);

  // look for #type special macro
  sniffContentType( fileBuff,  SCRIPT );

  // parse out #define calls and populate replacement mappings
  populateDefines( fileBuff,  scriptIndex);

  // de-inline multiple var assignments
  if (strstr(fileBuff, ", $") || strstr(fileBuff, ",$")) {
    deInlineVarAssignments(fileBuff);
  }

  removeMultiLineComments(fileBuff);
  removeDoubleLines(fileBuff);
  ///////////////////////////////////////////////////////
  //    Parse program into lines
  while (strlen(lb) > 1) {
#ifdef LATER_LINE_PROFILING
    unsigned long profileStart = micros();
#endif
    lineData = 0;
    isConstant = 0;
    memset(consts, '\0', 17);

    // copy program code into line buffer so we can mess it up
    strncpy( line, lb, endpos);
    line[endpos] = '\0';

    if (!endpos && !isPrintBlock) {
      line[endpos] = ' ';
      strcpy(line, "' ");
    }

    if (!endpos && isPrintBlock) {
      line[endpos] = ' ';
      line[endpos + 1] = '\0';
    }

    if (!isPrintBlock) laterUtil::trimRight(line);
    // convert IIF commands into 2-line operations:
    endpos = convertIIFs(line, lb, endpos);
    lb += endpos + 1; // rejigger line endings
    endpos = strcspn( lb, "\n");
    if (!isPrintBlock) { // trim left spaces and tabs on line
      int pos = 0;
      while (isblank(line[pos++])) {  };
      strcpy(line, line + (pos - 1));
    }

    removeSingleLineComments(line, cmd);
    if (!isStaticPrintBlock) laterUtil::trimRight(line);
    lineLen = strlen(line);
    ///////////////////////////////////////////
    if (lineLen || isStaticPrintBlock) { // filter empty lines

      harvestMacros(line, scriptIndex);
      cleanupVarDeclarations(line);
      if (line[0] == ':') {
        if (lineLen == 1) {
          lb++;
          continue;
        }
        laterUtil::replace(line, ":", "noop=:"); // turn lables into noops
      }
      expandRangeOperators(line, SCRIPT);
      if (line[0] == '&' && laterUtil::startsWith(line, "&RESPONSE->")) laterUtil::replace(line, "&RESPONSE->", "res=&RESPONSE->");
      replaceEndCommands(line);// handle block endings like end if, }, etc

      lineLen = strlen(line);

      if (line[0] == '<' && line[1] == '?') {
        isPrintBlock = 1;
        if (line[2] == '=') {
          line[2] = ' ';
          isStaticPrintBlock = 1;
        }
        line[0] = '_';
        line[1] = '=';
        continue;
      }

      if (line[0] == '?' && line[1] == '>') {
        isPrintBlock = isStaticPrintBlock = 0;
        line[0] = '_';
        line[1] = '=';
        continue;
      }
#ifndef LATER_DISABLE_OPTIMIZATIONS
      if (!isPrintBlock && line[4] == '$') {

        if (strstr(line, "={micros}")) {
          laterUtil::replace(line, "{micros}", "2");
          lineData = 10;
        }
        if (strstr(line, "={cycle}")) {
          laterUtil::replace(line, "{cycle}", "2");
          lineData = 11;
        }
      }
#endif

      if (!isPrintBlock) autoEqualsInsert(line);
      if (!isStaticPrintBlock) {
        isConstant = embedVariables(line, isConstant, SCRIPT);
#ifndef LATER_DISABLE_OPTIMIZATIONS
        embedTemplates(line, SCRIPT);
#endif
      }//end if !SPB
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
        if (linePtr[0] == '=') linePtr++;
        laterUtil::trimLeft(linePtr);
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

#ifndef LATER_DISABLE_OPTIMIZATIONS
      if (strchr(COMMANDS_ENDING_WITH_LITERALS, cmdChar)) replaceEndingLiterals(linePtr, SCRIPT);
      if (strchr(COMMANDS_STARTING_WITH_LITERALS, cmdChar) && isdigit(linePtr[0])) replaceStartingLiterals(linePtr,  SCRIPT);
#endif

      // look for var usage, minding var commands themselves
      if (cmdChar == LATER_var || cmdChar == LATER_static || cmdChar == LATER_apply ) { // look only after first equal for this
        lineData = parseVarCommands(line, linePtr, lineData, SCRIPT); // despace, optomize, fix syntax like *= > =*
        if (strchr(strchr(linePtr, '='), '@')  && !lineData ) flag += 2;// vars after assign
      } else { // non var command, but uses var, flag for var processing
        if (strchr(linePtr, '@')) flag += 2;// vars
      }
#ifndef LATER_DISABLE_OPTIMIZATIONS
#ifdef ADAFRUIT_NEOPIXEL_H
      if (cmdChar == LATER_solid) {
        if (strstr(linePtr, "0,0,0")) lineData = 1;
        if (strstr(linePtr, "#000")) lineData = 1;

        if (!strchr(linePtr, '{') && !strchr(linePtr, '@') ) {
          unsigned long parsedColor =  laterUtil::parseColor(linePtr, getCurrent() );

          lineData = 0;
          itoa(parsedColor, linePtr, 10);
          char symb = getConstantNumber(linePtr, getCurrent()) + 65;

          linePtr[0] = '@';
          linePtr[1] = symb;
          //  linePtr[2] = '_';
          linePtr[2] = '\0';
          lineLen = strlen(linePtr);
        }//end if literal color def?

      }
#endif
#endif

      if (cmdChar == LATER_option) {
        if (strstr(linePtr, "noget!") )SCRIPT->options.noget = true;
      }

      if (strchr(linePtr, '(') && strchr(linePtr, ')') && !isStaticPrintBlock ) flag += 4;
      //////////  [x,y][arrays] ?  8s
      if (strstr(linePtr, "][") && !isStaticPrintBlock ) flag += 8;

#ifdef ESP8266HTTPClient_H_
      if (strstr(linePtr, "&RESPONSE->") && !isStaticPrintBlock) flag += 32;
#endif
#ifdef HTTPClient_H_
      if (strstr(linePtr, "&RESPONSE->") && !isStaticPrintBlock) flag += 32;
#endif

      if (isConstant) flag += 64;


      //|| Later.addons[cmdChar]

      ////////// output ?  16s - interpolate var and %templates% in code line itself?
      if (  strchr(COMMANDS_NEEDING_OUTPUT, cmdChar)   ) {
        flag += 16;
      } else { // don't need whitespace in any other command, right. asume and let's try iy
        // collapse whitespace here
        if ( (!isPrintBlock) && strchr(line, ' ') && !strchr(COMMANDS_NEEDING_WHITESPACE, cmdChar) && (!strstr(linePtr, "][")) &&  (!Later.addons[cmdChar])  ) {
          while (strchr(linePtr, ' ')) laterUtil::replace(linePtr, " ", "");
        }
      }//end if non-output command?
      // wipe out existing processing for math commands:

      // populate script line object with accumulated data:
      LATER_LINE * sLine = &SCRIPT->lines[lineCount];
      sLine->cmd = cmdChar;
      sLine->data = lineData;
      sLine->flags = flag;

      if ( cmdChar == LATER_apply ||  cmdChar == LATER_var ) parseApply(linePtr, sLine, SCRIPT );
#ifdef ADAFRUIT_NEOPIXEL_H
      if ( cmdChar == LATER_pixel ) parsePixel(linePtr, sLine, SCRIPT );
#endif

      if ( cmdChar == LATER_math ) {
        replaceAllLiterals(linePtr, SCRIPT);
        laterUtil::replace(linePtr, " ", "");
      }

#ifdef LATER_CSV
      if ( cmdChar == LATER_csv ) {
        replaceAllLiterals(linePtr, SCRIPT);
        getCSV(linePtr, SCRIPT);
      }
#endif

      if (cmdChar == LATER_do) {
        char hint = linePtr[0];
        if (hint == 'w' || hint == 'u') {

          replaceAllLiterals(linePtr, SCRIPT);

          laterUtil::replace(linePtr, "while", "@A=(");
          laterUtil::replace(linePtr, "until", "@A=(");
          strcat(linePtr, ")");
          parseApply(linePtr, sLine, SCRIPT );

          if (cmdChar != sLine->cmd) {
            sLine->cmd = cmdChar;
            linePtr += 2;

            linePtr[0] = hint;
            sLine->exprCache[0] = (hint == 'u') ? 1 : 0;
            sLine->data = 2;
          }//end if changed?

        }//end if while/until or just _plain DO?
      }//end if do?
      if ( (cmdChar == LATER_if || cmdChar == LATER_iif) && !strchr(linePtr, '(')) {
        replaceAllLiterals(linePtr, SCRIPT);
        char op[2] = {linePtr[0], 0};
        laterUtil::replace(linePtr, op, "@A=( ");
        laterUtil::replace(linePtr, " ", op);
        strcat(linePtr, ")");
        parseApply(linePtr, sLine, SCRIPT );
        linePtr += 3;
        sLine->data = 2;
        sLine->flags = 0;
        sLine->cmd = cmdChar;
      }//end if if?
      lineLen = strlen(linePtr);
      sLine->len = lineLen; // how many chars is line?
      sLine->start = (outptr - cleanptr); // first line byte in clean buffer
      sLine->stop  = (outptr - cleanptr) + lineLen;// last line byte in clean buffer
      // copy to clean:
      strncpy (outptr, linePtr, lineLen );
      outptr[lineLen] = '\n';
      outptr += lineLen + 1;
#ifdef LATER_LINE_PROFILING
      sLine->profile.parse = micros() - profileStart;
#endif
      if (lineCount++ > LATER_LINE_LIMIT) break; // failsafe here, remove for prod?
    }//end if line not empty?
  } // wend endpos > 0

  outptr[0] = '\0';

  //iterate defines here, adding null terms to define linebreaks
  for (auto const & x : DEFINES[scriptIndex])   {
    if (x.second && strlen(x.second)) {
      char * endCap = strchr(x.second, '\n');
      if (endCap) endCap[0] = '\0';
    }
  }//next define

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
void replaceIncludes(char * fileBuff) {
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
}//end replaceIncludes()

void replaceSpecialMacros(char * fileBuff, const char * scriptFileName) {
  char * fil = strstr(fileBuff, "__FILENAME__");
  while (fil) {
    strncpy(fil, scriptFileName + 1, 12);
    unsigned int len = strlen(scriptFileName + 1);;
    if ( len < 12) memset(fil + 12, ' ', len - 12);
    fil = strstr(fileBuff, "__FILENAME__");
  }

  char * ino = strstr(fileBuff, "__SKETCH_FILE__");
  while (ino) {
    const char * mySketchName = LATER_SKETCH;
    strncpy(ino, mySketchName, 15);
    unsigned int len = strlen(mySketchName);
    if ( len < 15) memset(ino + 15, ' ', len - 15);
    ino = strstr(fileBuff, "__SKETCH_FILE__");
  }
}// end replaceSpecialMacros()
void sniffContentType( char * fileBuff, LATER_ENVIRON * SCRIPT ) {
  char * contentType = strstr(fileBuff, "#type=");
  while (contentType) {
    strncpy(SCRIPT->contentType, contentType + 6, 31);
    size_t ctend = strcspn(SCRIPT->contentType, "\n ;\t");
    SCRIPT->contentType[ctend] = '\0';
    contentType[0] = '\'';
    contentType = strstr(fileBuff, "#type=");
  }//wend contentType
}//end sniffContentType()
void populateDefines(char * fileBuff, int scriptIndex) {

  //#define TABLE_SIZE 100
  char * dec = strstr(fileBuff, "#define=");
  if (dec) DEFINES[scriptIndex].clear();
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

    DEFINES[scriptIndex][decName] = defValp;
    dec = strstr(fileBuff, "#define="); // grab next one (if any)
  }//wend define
}//end populateDefines()

void deInlineVarAssignments(char * buff) {
  char * p = buff;
  while ( (p = strstr(p, "\nvar "))) {

    //

    char * com = p + 2;
    char * linebreak = strchr(p + 2, '\n');

    while ((com = strchr(com + 1, ','))) {
      // make sure it's before a line break
      if (com < linebreak) {
        com[0] = '\n';
        DUMP("deinline:", String(com).substring(0, 8));
      } else { //end if before linebreak?
        break;
      }

    }//wend comma
    p += 4;
  }//wend
}// end deInlineVarAssignments();

int convertIIFs(char * line, char * lb, int endpos) {

  char * iifPtr  = strstr(line, "iif");
  char * cmtPtr = strstr(line, "//");

  if (iifPtr && (!cmtPtr || (cmtPtr > iifPtr)) ) {

    int colpos =  strcspn( line, ":");
    if (colpos > 0 && line[colpos - 1] == ' ' && line[colpos + 1] == ' ') {
      endpos = colpos;
      line[colpos] = '\0';
      lb[colpos] = '\n';
      laterUtil::trimRight(line);
    }
  }
  return endpos;
} //end convertIIFs()
void removeSingleLineComments(char * line, char * cmd) {
  // remove comments -- needs to chill a bit for later, check if print, log, fetch, etc.
  int commentPos = laterUtil::indexOf(line, "//");
  if (commentPos == -1 ) commentPos = laterUtil::indexOf(line, "'");
  if (commentPos > -1 ) {

    if (commentPos == 0) {
      line[0] = '\0';
    } else {
      int cmdLen = strcspn(line, " =");
      strncpy(cmd, line, cmdLen);
      cmd[cmdLen] = '\0';
      if (!strstr(",_,log,print,println,fetch,ping,timer,", cmd)) line[commentPos] = '\0'; // zap line at comment unless used by command
      // dd666       ^^^ this ^^^ needs to be an attrib of something rather than a britle string of unparsed command names

    }//end if not whole line comment?
  }//end if has comment?

  if (line[0] == '\'') line[0] = '\0'; // skip VB-style comment line, also used internally by multi-line comments to curtail buffer resizing
}//end removeSingleLineComments()
void harvestMacros(char * line, int scriptIndex) {
  char macro[16];
  char * macroRep = TEMPLATE_BUFFER;

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
    char buffKey2 [ 32 ] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char * macroRepPtr = DEFINES[scriptIndex][macroBuffPtr];
    // check GET params for match if no pre-defined macro exists under the name:
    if (!macroRepPtr || !strlen(macroRepPtr)) {
      if (LATER_SERVER_NAME.hasArg(macroBuffPtr)) {
        strcpy(buffKey2, LATER_SERVER_NAME.arg(macroBuffPtr).c_str());
        macroRepPtr = buffKey2;
      }
    }

    if (macroRepPtr) {
      size_t macroRepLen = strcspn(macroRepPtr, "\n");
      if (macroRepLen < 1) macroRepLen = strlen(macroRepPtr);

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
}//end harvestMacros()
void cleanupVarDeclarations(char * line) {

  int lineLen = strlen(line);

  // inject var= into plain var declarations; $x=1 into var=$x=1
  if (line[0] == '$') {
    if ( strchr(line, '{') && strchr(line, ':') && line[lineLen - 1] == '}') {
      laterUtil::replace(line, "$", "define=$");
    } else {
      laterUtil::replace(line, "$", "var=$");
      laterUtil::replace(line, "++", "=+1");
      laterUtil::replace(line, "--", "=-1");
    }

    laterUtil::replace(line, " =", "=");
    laterUtil::replace(line, "= ", "=");
  }//end if plain syntax var declaration line?

} //end cleanupVarDeclarations();
void expandRangeOperators(char * line, LATER_ENVIRON * SCRIPT) {
  char * rangeBuffer = TEMP_BUFFER;
  char temp[12];

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
}//end expandRangeOperators()
void replaceEndCommands(char * line) {
  if (laterUtil::startsWith(line, "end")) {
    laterUtil::replace(line, "end sub", "endsub=}");
    laterUtil::replace(line, "end if", "fi=end if");
    laterUtil::replace(line, "end do", "loop=loop");
    laterUtil::replace(line, "end switch", "end=end switch");
  }//end if end

  if (line[0] == '}') {
    laterUtil::replace(line, "}", "endsub=}");
  }//end if close sub brace?

} // end  replaceEndCommands()
bool embedVariables(char *  line, bool isConstant, LATER_ENVIRON * SCRIPT) {
  char * varPtr = strchr(line, '$');
  if (varPtr) {
    varPtr--;
    if (varPtr[0] == '=' && isupper(varPtr[2])) isConstant = true;
    varPtr++;
    replaceVarNames(varPtr, SCRIPT->index);
    if (isConstant && strstr(line, "var=@"))  SCRIPT->VARS[varPtr[1] - 65] = 420420420;
  }
  return isConstant;
}//end embedVariables()
int parseVarCommands(char * line, char * linePtr, int lineData, LATER_ENVIRON * s) {

#ifndef LATER_DISABLE_OPTIMIZATIONS
  if (strchr(linePtr, '('))  embedFunctions(strchr(linePtr, '='), s);
#endif

  // clean up all spaces they are not needed.
  char * ptrSpace = strchr(linePtr, ' ');
  while (ptrSpace) {
    strcpy(ptrSpace, ptrSpace + 1);
    ptrSpace = strchr(ptrSpace, ' ');
  }

  if (strpbrk (line, "*/-+")) {
    laterUtil::replace(line, "+=", "=+");
    laterUtil::replace(line, "-=", "=-");
    laterUtil::replace(line, "*=", "=*");
    laterUtil::replace(line, "/=", "=/");

#ifndef LATER_DISABLE_OPTIMIZATIONS
    if (strstr(line, "=+1")) lineData = 1;
    if (strstr(line, "=-1")) lineData = 2;
    if (strstr(line, "=+@") || strstr(line, "=+{#")) lineData = 3;
    if (strstr(line, "=-@") || strstr(line, "=-{#")) lineData = 4;
    if (strstr(line, "=/2")) lineData = 8;
    if (strstr(line, "=*2")) lineData = 9;
#endif
    // remove space to the left of =
    int eqPos = laterUtil::indexOf(linePtr, "=");
    if (eqPos > 3)  strcpy(linePtr + 3, strchr(linePtr, '='));
  } // end if line has  math symbols?

  if (strstr(linePtr, "=@") || strstr(linePtr, "={#") ) lineData = 5;
  if (strstr(linePtr, "=0")) lineData = 6;
  return lineData;
}//end parseVarCommands()
bool isStaticValue(char * str) {
  return (!strchr(str, '{')) && (!strchr(str, '@')) && (!strchr(str, '(')) && (!strchr(str, '[')) ;
}

#ifdef ADAFRUIT_NEOPIXEL_H
void parsePixel(char * lb, LATER_LINE * l, LATER_ENVIRON * s ) {

  //support literals: #ABC or #abc or #AABBCC or #aabbcc, or r,g,b, ints, functions
  // char * ptr = lb;
  char * assign = strstr(lb, "->");
  if (!assign) return;

  char * afterAssign = assign + 2;
  char * comma = strstr(lb, ",");
  bool hasParen = strchr(assign, '(');
  assign[0] = 'z';
  assign[1] = '=';
  char * paren = strchr(assign, '(');
  if (paren) embedFunctions(assign, s);
  assign[0] = '-';
  assign[1] = '>';
  char colorBuff[32];
  strcpy(colorBuff, assign + 2);
  char * ptrColorBuff = colorBuff;
  char startBuff[16] = {0};
  char spanBuff[16] = {0};
  bool staticIndex = 0;
  bool staticSpan  = 0;
  bool staticColor = 0;
  long start, span;

  //char * CACHE = l->exprCache;
  uint32_t color = 0;
  if (comma && comma < assign) {
    strncpy(spanBuff, comma + 1, (assign - comma) - 1);
    strncpy(startBuff, lb, comma - lb);
  } else {
    strcpy(spanBuff, "1");
    strncpy(startBuff, lb, assign - lb);
  }

  staticIndex = isStaticValue(startBuff);
  staticSpan = isStaticValue(spanBuff);
  char * pflag = strchr("+-<>*&", afterAssign[0]);
  char flag;
  if (!pflag) {
    flag = '_';
  } else {
    flag = pflag[0];
    afterAssign++;
    ptrColorBuff++;
  }
  while (ptrColorBuff[0] == ' ') ptrColorBuff++;

  staticColor = isStaticValue(ptrColorBuff);
  if (!strchr(assign, '(') && hasParen) staticColor = 1;

  if (staticColor) color = laterUtil::parseColor(ptrColorBuff, s);
  RGB_PIXEL.value = color;

  char * cursor = lb;
  start =  Number( startBuff, s->VARS);
  if (staticIndex) {
    l->exprCache[0] = 1;
    l->exprCache[1] = start;
    itoa(start, cursor, 10);
  } else {
    strcpy(cursor, startBuff);
  }

  cursor += strlen(cursor) - 1;
  strcat(cursor, ", ");
  cursor = strchr(cursor, ',') + 1;
  span =  Number( spanBuff, s->VARS);
  if (staticSpan) {
    l->exprCache[2] = 1;
    l->exprCache[3] = span;
    itoa(span, cursor, 10);
  } else {
    strcpy(cursor, spanBuff);
  }
  strcat(cursor, "->_");
  cursor = strchr(cursor, '_');

  cursor[0] = flag;
  l->exprCache[4] = flag;
  cursor++;

  if (staticColor) {
    l->exprCache[5] = 1;
    l->exprCache[6] =  RGB_PIXEL.chan[2];
    l->exprCache[7] =  RGB_PIXEL.chan[1];
    l->exprCache[8] =  RGB_PIXEL.chan[0];

    memset(cursor, '.', 7);
    cursor[0] = '#';
    cursor++;
    itoa(RGB_PIXEL.chan[2], cursor, 16);
    if (!cursor[1]) {
      cursor[1] = cursor[0];
      cursor[0] = '0';
    }
    cursor += 2;
    itoa(RGB_PIXEL.chan[1], cursor, 16);
    if (!cursor[1]) {
      cursor[1] = cursor[0];
      cursor[0] = '0';
    }
    cursor += 2;
    itoa(RGB_PIXEL.chan[0], cursor, 16);
    if (!cursor[1]) {
      cursor[1] = cursor[0];
      cursor[0] = '0';
    }
    cursor[2] = '\0';
  } else {
    strcpy(cursor, ptrColorBuff);
  }

  if (((l->flags >> 2) & 0x01) == 1) { // remove inlined expressions' flag
    if (!strchr(lb, '(')) l->flags -= 4;
  };
  if (((l->flags >> 1) & 0x01) == 1) { // remove var flags
    l->flags -= 2;
  };

}//end parsePixel();
#endif

unsigned long applyArgs(  LATER_LINE * l, LATER_ENVIRON * s  ) {
  APPLY_ARGS[2] = 0;
  for (int i = 0, index = 2, mx = 8; index < mx;  index++) {
    switch ( l->exprCache[index++]) {
      case '@': APPLY_ARGS[i++] = s->VARS[ (int) l->exprCache[index]  ]  ; break;
      case '{':  APPLY_ARGS[i++] =  s->TEMPS[(int)   l->exprCache[index]  ](); break;
      case 'D': APPLY_ARGS[i++] =  l->exprCache[index]; break;
    }//end switch hint
  }// next arg pair

  // run function and assign return to destination:
  return s->FUNCS[  (int) l->exprCache[1]    ] (
           APPLY_ARGS[0],
           APPLY_ARGS[1],
           APPLY_ARGS[2]
         );

  //return ret;
}
void parseArgsForApply(char * lb,  char * CACHE  ) {

  uint8_t i = 2;
  char * ptrLine = strchr(lb, '(') + 1;
  memset(CACHE, '\0', 11);

  while (ptrLine[0]) {
    if (ptrLine[0] == '@') {
      CACHE[i++] = '@';
      CACHE[i++] = ptrLine[1] - 65;
      ptrLine += 1;
    } else if (ptrLine[0] == '{') {
      CACHE[i++] = '{';
      CACHE[i++] = ptrLine[2] - 65;
      ptrLine += 2;
    } else if (isdigit(ptrLine[0])) {
      CACHE[i++] = 'D';
      CACHE[i++] = ptrLine[0] - 48;
    }
    ptrLine++;
  }//wend ptrline

}
void parseApply(char * lb, LATER_LINE * l, LATER_ENVIRON * s ) {

  char * olb = lb;


  if (lb[3] == '#' && lb[5] == '(' && strchr(lb, ',')) {
    l->cmd = LATER_apply;
    l->flags = 0; // cancel line preproc
    l->data = 0; // cancel optimizations

    parseArgsForApply( lb,   l->exprCache  );

    l->exprCache[0] = lb[1] - 65; // dest
    l->exprCache[1] = strchr(lb, '#')[1] - 65; // cb

  } else { // not ready to go, but can it be converted inline?

    l->cmd = LATER_var; // until proven innocent

    // look for convertable expressions:
    if (lb[3] == '(' ) {
      lb += 3;

      uint8_t opPos1 =  strcspn( lb, "+/-*|<>=!");
      char op1 = lb[opPos1];

      if (!op1) return;

      uint8_t opPos2 =  strcspn( lb + opPos1 + 1, "+/-*|<>=!");
      if (opPos2 == strlen(lb + opPos1 + 1)) opPos2 = 0;

      if (opPos2) {
        char op2 = lb[opPos2 + opPos1 + 1];
        if (op2 && op2 != op1)  return;
      }

      // check for opPos3, and abort if present
      uint8_t opPos3 =  strcspn( lb + opPos1 + opPos2 + 2, "+/-*|<>=!");
      if (!opPos2)opPos3 = 0;
      if (opPos3) return;
      char nameBuffer[8] = {0, 0, 0, 0,  0, 0, 0, 0};

      char lut[] = "-DIFF +SUM *MULT /DIV <LT >GT =EQ !NEQ %MOD ";
      char * opPtr = strchr(lut, op1);
      if (!opPtr) return;
      strchr(opPtr, ' ')[0] = '\0';
      strcpy(nameBuffer, opPtr + 1);
      /*
        switch (op1) {
        case '-': strcpy(nameBuffer, "DIFF"); break;
        case '+': strcpy(nameBuffer, "SUM"); break;
        case '*': strcpy(nameBuffer, "MULT"); break;
        case '/': strcpy(nameBuffer, "DIV"); break;
        default:          return;          break;
        }
      */
      if (!strlen(nameBuffer )) return;
      auto callback = FUNCS[nameBuffer];
      if (!callback) return;
      int index = -1;
      // look for existing copy of cacched function to re-use:
      for (unsigned int i = 0; i < s->FUNC_COUNT; i++) {
        if (callback == s->FUNCS[i])    index = i;
      }
      if (index == -1) {
        index = s->FUNC_COUNT++;
      }

      if (index == LATER_FUNCTION_CACHE_LENGTH) return;
      s->FUNCS[index] = callback;

      l->cmd = LATER_apply;
      l->flags = 0; // cancel line preproc
      l->data = 0; // cancel optimizations
      parseArgsForApply( lb,   l->exprCache  );
      l->exprCache[0] = olb[1] - 65; // dest
      l->exprCache[1] = index;

    } else { //give up and make/leave it a var
      l->cmd = LATER_var;
    }
  }//end if ready to go for apply?
}//end parseApply()

#line 1 "mod.ino"
//#ifdef ESP8266HTTPClient_H_
#if defined(ESP8266HTTPClient_H_) || defined(HTTPClient_H_)

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

#line 1 "runner.ino"

void runScript() {
  unsigned int loopLimit = 32700;
  LATER_ENVIRON * s = getCurrent();
  LATER_LINE * l;
  static char linebuff[LATER_LINE_BUFFER]; // holds a copy of the code line to alter as needed to run, keeps orig intact
  char * lp = s->program; // start point of master line
  if (s->options.debug)  loopLimit = 1000;
  s->startedAt = micros();
  s->runs++;

  unsigned int hits = 0; // used for runaway code detection
  char * k, * v; // used by hard-coded commands to parse thier own lines
  char * lb; // line buffer pointer to used for line selection and processing
  unsigned long varCache = 0, tempInt = 0, varTemp = 0; // used by hard-coded commands to store numbers insde raw (scopeless) switch
  int varSlot = 0; // used by DMA
  bool usedDMA = false; // dma needed? (since varSlot 0 is legit, this ride-along flag is needed)
  char varChar; // used by hard-coded commands to cache a char
  int pinCache;
  if (!s->exitLineNumber) s->exitLineNumber = s->lineCount;
#ifdef HIGH_RES_TIMING
  unsigned long st = 0;
  HR_PERF.reset();
#endif
#ifdef LATER_LINE_PROFILING
  unsigned long profileStart = micros();
  unsigned long profileDone = profileStart;
#endif
  l = &s->lines[s->resumeLineNumber];
  for (s->i = s->resumeLineNumber; s->i < s->exitLineNumber; s->i++) {

    if (s->options.step) {
      if (!s->stepReady) {
        s->stepReady = true;
      } else {
        s->stepReady = false;
        s->i--;
        s->freeze(99999);
        return;
      }
    }//end if line step mode?

#ifdef HIGH_RES_TIMING
    if (st > 0) {
      HR_PERF.loop.total += micros() - st;
      HR_PERF.loop.count++;
    }
#endif

#ifdef LATER_LINE_PROFILING
    profileStart = micros();
    l->profile.total += (profileStart - profileDone);
    profileDone = profileStart;
    l->profile.count++;
#endif

    l = &s->lines[s->i]; //    parsed line struct, members: [start, stop, data, len, flags, cmd]
    // pop temp line buffer:
    lp = s->program + l->start;
    strncpy(linebuff, lp, l->len);
    linebuff[l->len] = '\0';
    lb = linebuff;

    usedDMA = 0;

    ////////////////////////////////////
    // line buffer formed, process line:

    // skip over all flag handling if no flag at all is set:
    if (l->flags) { // T=0, V=1, E=2, A=3, O=4, H=5;

      if (l->flags == 128) continue; //dead command, no pre-processing done. used by static/define et al.

      //#ifdef ESP8266HTTPClient_H_
#if defined(ESP8266HTTPClient_H_) || defined(HTTPClient_H_)
      // if ajax response operation, do that:
      if (l->flags & FLAGS.H) {
        if (l->cmd == LATER_var || l->cmd == LATER_static || l->cmd == LATER_store || l->cmd == LATER_global ) { // assign ret to a vary:
          processResponseEmbeds(strchr(linebuff, '=') + 1, s);
        } else { // template result into line:
          processResponseEmbeds(linebuff, s);
        } // end if var or other cmd?
      }//handle response access
#endif
      if (l->flags & FLAGS.T) {
        processTemplateExpressions2(linebuff, s);
      } // end if templates?
      if (l->flags & FLAGS.O) { //
        processVariableExpressions(linebuff, s->VARS);
      }//end if output-needing vars?

      //evaluate paren expressions into numbers
      if (l->flags & FLAGS.E) {
        // } else {
        evalMath(linebuff, s, -1); // replace usedDMA with  var dma: @A
        // } // end if var or other cmd?
      }//end if parens flag?
      // detect arrays and process:
      if (l->flags & FLAGS.A) {
        //  } else {
        usedDMA = processArray(linebuff, s, -1); // todo: replace usedDMA with  var dma: @A
        // } // end if var or other cmd?
      }//end if array?

    }//end if flags?
    if (hits++ > loopLimit) {
      uniPrintln("runaway loop detected, aborting");
      break;
    }

    if (s->options.debug) {
      static char tempbuff[LATER_LINE_BUFFER]; // for DEBUGGING output
      strcpy(tempbuff, "           ");
      char * tb = tempbuff;
      itoa (s->i, tb, 10);
      strcat(tb, ">");
      itoa (l->exit, tb + strlen(tb), 10);
      strcat(tb, "\t");
      char tiny[4] = {l->cmd, 0};
      strcat(tb, tiny);
      strcat(tb, " =");
      strcat(tb, linebuff);
      uniPrintln(tempbuff);
    }

#ifdef HIGH_RES_TIMING
    st = micros();
#endif
    ////////////////////////////////////
    ////////////////////////////////////
    // linebuff has been pre-processed by flag and is ready to feed to commands
    switch (l->cmd) { // do command-y stuff with value by cmd, see COMMANDS:

      case LATER_noop: l->flags = 128;  continue; // do nothing. res (removed) still fired line prep, noop doesn't case LATER_res:

      //  not needed because IFs will always come out line after fi or else, which is co-incidently IF's line.exit
      case LATER_else: // ELSE
        s->i = l->exit;
        continue;
        break;

      case LATER_var: case LATER_static: case LATER_store: case LATER_global: // init variable to value

        if (l->cmd == LATER_static  ) {// never come back here again
          l->cmd = LATER_noop;
          l->flags = 128;

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
            //char * pname = varName;
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

          // look for array literals
          if (strchr(linebuff, ',') && strchr(linebuff, '[') && strchr(linebuff, ']')) { // defining a json literal?
            unsigned int b = linebuff[1] - 65;
            char varName[24];
            char varNameTemp[24];
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

            // array routine, using numbers to name vars as index
            char * p = strchr(linebuff, '[');
            //char * pcomma;
            //char * pname = varName;
            int slot = 0;
            int keyCount = 0;
            while (p) { // dig through json literal to define vars:

              p++;
              while (p[0] == ' ') p++; // trimleft


              varName[baseLen] = '\0'; // reset composite var name holder
              std::sprintf(varNameTemp, "%d", keyCount);
              strncat(varName, varNameTemp, baseLen);

              slot = getVarNameNumber(varName, s->index); // use composite to get/make allocated slot
              s->VARS[slot] = Number(p, s->VARS); // set var value from literal

              /*
                uniPrint("varName:");
                uniPrintln(String(varName));

                uniPrint("keyCount:");
                uniPrintln(String(keyCount));

                uniPrint("p:");
                uniPrintln(String(p));

                uniPrint("baseLen:");
                uniPrintln(String(baseLen));
              */

              keyCount++;
              p = strchr(p, ','); // next k:v pair
              if (!p) break; //p = strchr(p, ']'); // last pair?

            }//wend , array values
            // now set root object to a count of properties:
            varName[baseLen - 1] = '\0';
            slot = getVarNameNumber(varName, s->index); // use composite to get/make allocated slot
            s->VARS[slot] = keyCount;
            continue;
          }//end if "array" literal?

          if (1) { // look out for url-inserted values
            unsigned int b = linebuff[1] - 65;
            char varName[24];
            //  reflect human var names from shortcut char to use for adding .prop names to base var name.
            for (auto const & x : LATER_VAR_NAMES[s->index])   {
              if (x.second == b ) {
                strcpy(varName, x.first.c_str());
                break;
              }//end if matching var?
            }//next var name
            if (server.hasArg(varName + 1)) continue;
          }

        }//end if static/define?

        if (usedDMA) continue;
        varSlot = linebuff[1] - 65;

        if (   (((l->flags >> 6) & 0x01) == 1)   && (s->VARS[varSlot] != 420420420)   ) {
          l->cmd = LATER_noop;
          continue;
        }
        // split on equal, get name and value
        v = strchr(linebuff, '=') + 1;

#ifndef LATER_DISABLE_OPTIMIZATIONS
        if (l->data) { // look for logical perf-improving shortcuts found in parsing

          switch (l->data) {
            case 1: s->VARS[varSlot]++; continue; // increment 1
            case 2: s->VARS[varSlot]--; continue; // decrement 1
            case 3: s->VARS[varSlot] += s->VARS[linebuff[5] - 65]; continue; // increment var
            case 4: s->VARS[varSlot] -= s->VARS[linebuff[5] - 65]; continue; // decrement var
            case 5: s->VARS[varSlot] = s->VARS[linebuff[4] - 65]; continue; // copy var
            case 6: s->VARS[varSlot] = 0; continue; // reset var
            case 7: l->data = 0; continue; // do nothing (uses implied DMA, var set out of loop)
            case 8: s->VARS[varSlot] = s->VARS[varSlot] >> 1; continue; // fast bitshift divide
            case 9: s->VARS[varSlot] = s->VARS[varSlot] << 1; continue; // fast bitshift double

            case 10: s->VARS[varSlot] = micros(); continue; // fast microsecond capture
#ifdef ESP8266
            case 11: s->VARS[varSlot] = esp_get_cycle_count(); continue; // fast cpu ticks capture
#endif

            default: break;
          }
        }//end if data shortcuts?
#endif
        while (v[0] == ' ') v++; // trim lef, right of compare operator char
        if (isdigit(v[0])) {
          varCache = Number(v, s->VARS); // atol(v);
        } else {
          //setup mathy bits:
          varCache =  s->VARS[varSlot];

          if (l->cmd == LATER_store || l->cmd == LATER_global) {
            k = laterUtil::trimRight(laterUtil::copyUntilChar(linebuff, '='));
            varCache = LATER_STORE.get(k);
          }
          tempInt = Number(v + 1, s->VARS); // atol(v + 1);

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

        if (l->cmd == LATER_var) {
          s->VARS[varSlot] = varCache;
        } else { // static, global, or store
          if (l->cmd == LATER_store) {
            k = laterUtil::trimRight(laterUtil::copyUntilChar(linebuff, '='));
            LATER_STORE.set(k, varCache);
          } else {
            if (l->cmd == LATER_global) {
              k = laterUtil::trimRight(laterUtil::copyUntilChar(linebuff, '='));
              LATER_STORE.update(k, varCache);
            } else { // static:
              s->VARS[varSlot] = varCache;
            }//end if global?
          }//end if store?
        }//end if var?
        continue;
        break;

      case LATER_goto: // quick jump command for home-made flow control. use wisely.

        if (l->exit) { // handle pre-processed conditionals

          switch (s->jumpIfOperator) {
            case '>':
              if ( s->VARS[l->data] > s->jumpIfOperand) {
                s->i = l->exit - 1;
                continue;
              }
              break;

            case '<':
              if ( s->VARS[l->data] < s->jumpIfOperand) {
                s->i = l->exit - 1;
                continue;
              }
              break;

            case '=':
              if ( s->VARS[l->data] == s->jumpIfOperand) {
                s->i = l->exit - 1;
                continue;
              }
              break;

            case '!':
              if ( s->VARS[l->data] != s->jumpIfOperand) {
                s->i = l->exit - 1;
                continue;
              }
              break;

            default: s->i++; continue;

          }//end operation switch

        }//end if pre-processed?

        // parse conditional expressions and store :
        if (strlen(linebuff) > 4) { // conditional, parse it
          /*
            goto 6 if $x < $mx
            becomes   6if@A_<@B_
          */

          // set goto destination
          if (linebuff[0] == '-') { // relative line count
            l->exit = s->i - strtoul(linebuff + 1, NULL, 10);
          } else { // absolute line index
            l->exit = strtoul(linebuff, NULL, 10) + 1;
          }//end if neg line ref?
          char * ptr = strstr(linebuff, "if@") + 3;

          if (l->exit == 1  &&  linebuff[0] != '0'  ) { // find label/landmark

            // find subroutine matching name named here
            // set sub end line exit  to goto line

            char labelCache[20];
            strncpy(labelCache, linebuff, (ptr - 3) - linebuff);

            // find non-label navpoints:
            if (labelCache[0] != ':') { // find pre-defined nav points in program

              if ( !strcmp ( labelCache, "TOP" )) {
                l->exit = 1;
              } else if ( !strcmp ( labelCache, "FINISH" )) {
                l->exit = s->exitLineNumber + 1;
              } else if ( !strcmp ( labelCache, "END" )) {
                l->exit = s->lineCount;
              } else if ( !strcmp ( labelCache, "BOTTOM" )) {
                l->exit = s->lineCount;
              } else if ( !strcmp ( labelCache, "START" )) {
                l->exit = s->startLineNumber + 1;
              }

            } else { // find labels by matching text

              auto * whole = s->lines;
              for (int i = 0; i < s->lineCount; i++) {
                LATER_LINE * currentLine = &whole[i];
                if (currentLine->cmd == LATER_noop) {
                  char * tLine =  s->program + currentLine->start;
                  if (  laterUtil::startsWith(tLine, labelCache)  ) {
                    l->exit = i + 1;
                    break;
                  }
                }//end if sub dec line?
              }//next

            }
            if (!l->exit) l->exit = s->i + 1;
          }//end if subroutine name?

          l->data = ptr[0] - 65; // left-side var ref

          // handle default>0
          if (strlen(ptr) < 4) {
            s->jumpIfOperator = '>';
            s->jumpIfOperand  = 0;
          } else {
            ptr += 2;
            s->jumpIfOperator = ptr[0];
            ptr++;
            if (ptr[0] == '@') { //eval var:
              s->jumpIfOperand  = s->VARS[ptr[1] - 65];
            } else { // parse literal
              s->jumpIfOperand  =  strtoul(ptr, NULL, 10);
            }

          }

          switch (s->jumpIfOperator) {
            case '>':
              if ( s->VARS[l->data] > s->jumpIfOperand) {
                s->i = l->exit - 1;
                continue;
              }
              break;

            case '<':
              if ( s->VARS[l->data] < s->jumpIfOperand) {
                s->i = l->exit - 1;
                continue;
              }
              break;

            case '=':
              if ( s->VARS[l->data] == s->jumpIfOperand) {
                s->i = l->exit - 1;
                continue;
              }
              break;

            case '!':
              if ( s->VARS[l->data] != s->jumpIfOperand) {
                s->i = l->exit - 1;
                continue;
              }
              break;

            default:
              s->i++;
              continue;

          }//end operation switch
        } else { // just a number mode, mutate to LATER_else, since it does what we need

          varCache = strtoul(linebuff, NULL, 10);
          if (varCache) {
            varCache = varCache - 1;
            l->exit = varCache;
            l->cmd = LATER_else;
            s->i = varCache;
          }
        }

        continue;
        break;

      case LATER_fi: // end if
        continue;
        break;

      case LATER_if: case LATER_iif: // If/Iff

        if (l->data == 2) {
          /*  String j="";
            for(int i=0; i<10; i++){
              j+=String( l->exprCache[i] * 1)+"|";
              if(i==4) j+=" ";
            }
            Serial.println(j);
            delay(11);
          */
          if (!applyArgs(l, s)) s->i = l->exit;
        } else {
          if (!evalConditionalExpression(linebuff, s)) s->i = l->exit;
        }
        continue;
        break;
#ifdef LATER_CSV
      case LATER_csv: {
          // make this update the params better, maybe on save or load. switch to [instante][line]?
          uint8_t col = 0;
          bool shouldExit = false;
          char* nextColumn;
          int slot = 0, usedSlots = 0;
          CsvState* csv = getCSV(linebuff, s);


          if (csv->morePointer) s->VARS[csv->morePointer] = 1;
          if (!csv->fn) shouldExit = true;

          char* lineCursor = shouldExit ? NULL : laterUtil::getFileLine(csv->fn, csv->lineNeeded);
          if (!lineCursor) shouldExit = true;
          if (shouldExit) {
            if (csv->morePointer) s->VARS[csv->morePointer] = 0;
            if (csv->blockSize) s->i += csv->blockSize;
            csv->lineNeeded = 0;
            continue;
          }

          strcat(lineCursor, csv->delimStr);
          while ((nextColumn = strchr(lineCursor, csv->delim))) {
            if ((++col) >= csv->skip) {
              slot = csv->varSlots[usedSlots++];
              if (!slot) break;
              s->VARS[slot] = Number(lineCursor, s->VARS);
            }
            lineCursor = nextColumn + 1;
          }  //wend nextColumn

          if (!col) {
            if (csv->morePointer) s->VARS[csv->morePointer] = 0;
            if (csv->blockSize) s->i += csv->blockSize;
            csv->lineNeeded = 0;
            continue;
          } else {

            if (csv->filter) {
              uint16_t  rez = evalLite(csv->filter, s);
              if (!rez) {
                s->i++;
                continue; // non-destructive exit
              }//end if rez?
            }//end if filter?
          }//end if !col?
        }  //end scope
        continue;
        break;

#endif
      case LATER_math:
        varSlot = lb[1] - 65;
        tempInt = evalLite(lb + 3, s);
        s->VARS[varSlot] = tempInt;

        continue;
        break;
      case LATER_apply: // fast expression execution engine
        /*
                APPLY_ARGS[2] = 0;
                for (int i = 0, index = 2, mx = 8; index < mx;  index++) {
                  switch ( l->exprCache[index++]) {
                    case '@': APPLY_ARGS[i++] = s->VARS[ (int) l->exprCache[index]  ]  ; break;
                    case '{':  APPLY_ARGS[i++] =  s->TEMPS[(int)   l->exprCache[index]  ](); break;
                    case 'D': APPLY_ARGS[i++] =  l->exprCache[index]; break;
                  }//end switch hint
                }// next arg pair

                // run function and assign return to destination:
                s->VARS[  (int) l->exprCache[0]  ] =
                  s->FUNCS[  (int) l->exprCache[1]    ] (
                    APPLY_ARGS[0],
                    APPLY_ARGS[1],
                    APPLY_ARGS[2]
                  );
        */
        s->VARS[  (int) l->exprCache[0]  ] = applyArgs(l, s);

        continue;
        break;
      case LATER_end: //end switch might need to become LATER_end_switch, if other ends are needed
        s->switchTerm[0] = '\0';
        continue;
        break;
#ifdef __INC_FASTSPI_LED2_H
      case LATER_pixel: // paint rgb leds
        laterCMD::runSetPixel(lb, s);
        continue;
        break;
      case LATER_render: // update painted rgb leds
        FastLED.show();
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
        if (l->data == 1) {
          FastLED.showColor(0);
          continue;
        }
        k = lb + 0;

        FastLED.showColor( LATER_PIXEL_TYPE(laterUtil::parseColor(k, s)) );

        continue;
        break;

#endif
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
        if (l->data == 1) {
          LATER_PIXEL_NAME.fill(0, LATER_PIXEL_NAME.numPixels());
          LATER_PIXEL_NAME.show();
          continue;
        }
        k = lb + 0;
        LATER_PIXEL_NAME.fill( laterUtil::parseColor(k, s), 0, LATER_PIXEL_NAME.numPixels() );
        LATER_PIXEL_NAME.show();

        continue;
        break;

#endif
      case LATER_sub: //sub routine
        if (!s->subReturnLine) {
          s->i = l->exit;
          continue;
        }
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

      case LATER_print: case LATER_println:// print value
        laterUtil::replace(linebuff, "\\n", " \n");
        laterUtil::replace(linebuff, "\\t", " \t");
        laterUtil::replace(linebuff, "\\s", " ");
        processStringFormats(linebuff, s->index);

        // look for input redirects
        if ( (v = strstr(linebuff, "<<")) ) {
          char * tempFileName = strstr(linebuff, "<<") + 2;
          while (tempFileName[0] == ' ') tempFileName++;
          laterUtil::trimRight(tempFileName);
          uniPrintln(laterUtil::fileToBuff(tempFileName));
          continue;
        }

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


          if (v[0] == '%' && v[1] == 'R' && v[4] == '%') {
            char * fileBuff = laterUtil::fileToBuff(v);
            if (tempInt) {
              strcat (fileBuff, linebuff);
            } else {
              strcpy(fileBuff, linebuff);
            }

          } else {
            s->writes++;
            laterUtil::buffToFile(v, linebuff, tempInt);
          }
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

      case LATER_start:
        if (lb[0] == '0' && lb[1] == '0') { // default 00
          s->startLineNumber = s->i + 1; // next line is new top
        } else {
          s->startLineNumber = Number(lb, s->VARS); // top specified
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

      case LATER_option:
        //bool debug; // print debug info to the console?
        //bool perf; // print perf info to the console?
        //bool strict; // disable legacy handlers and slower features?
        if (strstr(lb, "debug")) s->options.debug = true;
        if (strstr(lb, "perf")) s->options.perf = true;
        if (strstr(lb, "strict")) s->options.strict = true;
        if (strstr(lb, "persist")) s->options.persist = true;
        if (strstr(lb, "socket")) s->options.socket = true;
        if (strstr(lb, "noget")) s->options.noget = true;
        if (strstr(lb, "step")) s->options.step = true;

        if ((k = strstr(lb, "interval"))) {
          // find next digits
          v = strpbrk(k + 8, "0123456789"); // locate first digit(s) after "interval"
          s->interval = Number(v, s->VARS);
          s->options.persist = true;
        }
        l->flags = 128;
        continue;
        break;
      case LATER_interval: //interval sub call

        // find interval, compare to lastFire
        k = linebuff;

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

      case LATER_exit: // aka finish
        s->exitLineNumber = s->i;
        finishRun(s);
        return;
        break;
      case LATER_pinMode: // setPinMode
        laterCMD::runPinMode(lb);
        continue;
        break;

      case LATER_log: // log value
        processStringFormats(linebuff, s->index);
        laterCMD::logMe(linebuff);
        continue;
        break;

      case LATER_switch: // sWitch
        strcpy(s->switchTerm, linebuff);
        s->switchTerm[strlen(linebuff)] = '\0';
        s->switchExit = l->exit;
        continue;
        break;

#if defined(ESP8266HTTPClient_H_) || defined(HTTPClient_H_)
      case LATER_ping: //  http request url
        yield();
        Later.httpResponseTextBuffer[0] = '\0';
        s->status = HTTPRequest(linebuff);
        yield();

        Later.httpResponseText = Later.httpResponseTextBuffer;

        //Later.httpResponseText = Later.httpResponseTextBuffer;

        continue;
        break;
#endif

      case LATER_do: // do

        if (l->data) {
          // do an apply things here
          bool resp = applyArgs(l, s);
          if (l->exprCache[0]) resp = !resp;
          if (!resp) s->i = l->exit;
          continue;
        } else {

          if (linebuff[0] == ' ') continue;
          if (linebuff[0] == 'w') {
            if (!evalConditionalExpression(linebuff + 5, s)) s->i = l->exit;
          }//end if while

          if (linebuff[0] == 'u') { //blah
            if (evalLite(linebuff + 5, s)) s->i = l->exit;
          }//end if until
        }
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

      case LATER_call: //call call
        // look for arguments, populate as needed
        if (l->data) {
          k = linebuff;
          k += l->data;
          while (isSpace(k[0])) k++;
          laterUtil::splitStringByChar(k, ',');
          int i = 0;
          for (i = 0; i < laterUtil::split_count; i++)    s->subArgs[i] = Number(laterUtil::splits[i], s->VARS);
          s->arity = i;
        }//end if args?

        s->subReturnValue = linebuff[1] - 65;
        s->subReturnLine = s->i;
        s->i = l->exit;
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
      case LATER_flash: // persist list of variables to flash memory, if changed, or load vars

        if (1) {
          bool isRead = strchr(linebuff, '>') ? 1 : 0;
          char fileName[32] = {'/'};
          char * args = strchr(linebuff, '<');
          char valbuff [18];
          char fileBuffer[48];
          char keyBuff[8];
          std::map<char,  bool> VAR_MAPPING;
          if (!args) args = strchr(linebuff, '>');
          if (!args) continue; // nothing to do

          strcat(fileName, linebuff);
          fileName[(args - linebuff) + 1] = '\0';
          strcat(fileName, ".var");
          args++; // hop over <>
          while (args[0] == ' ') args++; // trim left

          laterUtil::splitStringByChar(args, ',');

          File file5;
          if (isRead && !strstr(fileName, "RTC") ) file5 = SPIFFS.open( fileName, "r");
          if (!isRead && !strstr(fileName, "RTC") ) file5 = SPIFFS.open( fileName, "w");


          for (int i = 0; i < laterUtil::split_count; i++) {
            char * arg = laterUtil::splits[i];
            while (arg[0] == ' ') arg++;

            // find comma delim:
            char * ptr = strchr(arg, ',');
            if (ptr) ptr[0] = '\0'; // chop at first comma

            // trim :
            ptr = strchr(arg, ' ');
            if (ptr) ptr[0] = '\0'; // chop at first space

            char* slot;
            char key[16] = {'$'};

            strcpy(key + 1, arg);
            slot = getVarName(key, s->index); // use composite to get/make allocated slot

            if (isRead) { // add key:value pair of arg:slot[1] to mapping
              VAR_MAPPING[slot[1]] = true;
            } else { // print file right here and now.
              file5.print(arg);
              file5.print("=");
              itoa (s->VARS[slot[1] - 65], valbuff, 10);
              file5.println(valbuff);
            }

          }//next arg

          if (isRead) {
            //iterate file and look for mappings, update inplace if found

            while (file5.available()) {

              int l = file5.readBytesUntil('\n', fileBuffer, sizeof(fileBuffer));
              fileBuffer[l] = '\0';
              char * delim = strchr(fileBuffer, '=');
              delim[0] = '\0';

              // reset key buffer
              keyBuff[0] = '$';
              keyBuff[1] = '\0';
              strcat(keyBuff, fileBuffer);

              char * savedValue = delim + 1;
              char * slot = getVarName(keyBuff, s->index);
              if (VAR_MAPPING[slot[1]]) s->VARS[slot[1] - 65] = strtoul(savedValue, NULL, 10);
            }
          }

          if (file5) file5.close();


          //s->status =
        }
        continue;
        break;

      case LATER_type: // print file by name to "stdout"
        uniPrintln(laterUtil::fileToBuff(linebuff));
        continue;
        break;

      case LATER_clear: // clear log value
        setRunLog[0] = '\n';
        setRunLog[1] = '\0';
        continue;
        break;
      case LATER_delete: // delete variable

        continue;
        break;
      case LATER_freeze: // suspend operation for given MS
        s->freeze(Number(lb, s->VARS));
        return;
        continue;
        break;
      case LATER_on: // subscript pin change and other events
        //on= pin, sub[, FALLING|RISING|CHANGE|EDGE]
        // we have exit to sub top, and data of edge type pre-set
        pinCache = Number(lb, s->VARS); // pin
        varSlot = -1; // known handler? if so, grab event slot #
        for (int i = 0; i < LATER_EVENT_COUNT; i++) {
          if (pinCache == EVENT[i].pin) { // stop on first non-set slot, since -1 is default and matches varSlot
            varSlot = i;
            break;
          }
        }//next


        if (varSlot > -1) { // known? run sub
          // compare sub with event object and parsed params

          tempInt = digitalRead(pinCache);

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
          for (int i = 0; i < LATER_EVENT_COUNT; i++) {
            if (EVENT[i].pin == -1) {
              varSlot = i;
              break;
            }
          }//next
          EVENT[varSlot].pin = pinCache;
          EVENT[varSlot].value = digitalRead(pinCache);
          EVENT[varSlot].msNext = millis();
        }//end if known handler?

        s->eventSlot = varSlot;
        EVENT[varSlot].programSlot = s->index;

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

      case LATER_suspend: // suspend operation for given MS, unload script
        varCache = Number(lb, s->VARS);
        if ( varCache > 0 ) { // number passed, suspend current script for ms
          s->resumeLineNumber = s->i + 1;
          s->duration = (micros() -  s->startedAt) / 1000;
          Later.suspend(s->fileName, varCache);
          return;
        } else { // file name passed , suspend other script asap, no resume period
          Later.suspend(lb, 0);
        }

        continue;
        break;
      case LATER_resume: // resumes a script by file name, can't resume self, but could pretend they meant suspend
        Later.resume(lb);
        continue;
        break;
      case LATER_assert:
        laterCMD::runAssert(lb, l, s);
        continue;
        break;

      case LATER_cgi:
        laterCMD::runCGI(lb, s);
        continue;
        break;
      case LATER_json:
        laterUtil::splitStringByChar(lb, ',');
        if (laterUtil::split_count > 1) {

          uniPrintln("{");

          char valbuff [18];

          for (int i = 0; i < laterUtil::split_count; i++) {
            // trim left:
            while (laterUtil::splits[i][0] == ' ')laterUtil::splits[i]++;

            // find comma delim:
            char * ptr = strchr(laterUtil::splits[i], ',');
            if (ptr) ptr[0] = '\0'; // chop at first comma

            // trim right:
            ptr = strchr(laterUtil::splits[i], ' ');
            if (ptr) ptr[0] = '\0'; // chop at first space

            char* slot;
            char key[16];
            key[0] = '$';

            strcpy(key + 1, laterUtil::splits[i]);
            slot = getVarName(key, s->index); // use composite to get/make allocated slot
            uniPrint(" \"");

            char * colon = strchr(key, ':');
            if (!colon) {
              uniPrint(key + 1);
            } else {
              colon[0] = '\0';
              uniPrint(key + 1);
              uniPrint("\":\t");
              uniPrint( colon + 1 );
              if ( i + 1 < laterUtil::split_count) uniPrint(",");
              uniPrintln(" ");
              continue;
            }
            uniPrint("\":\t");
            itoa (s->VARS[slot[1] - 65], valbuff, 10);
            uniPrint( valbuff );
            if ( i + 1 < laterUtil::split_count) uniPrint(",");
            uniPrintln(" ");

          }//next var
          uniPrintln("} ");
        }//end if vars passed?

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

#line 1 "templates.ino"
#ifdef ESP32
extern "C" {
  uint8_t temprature_sens_read();
}
uint64_t macAddress = ESP.getEfuseMac();
uint64_t macAddressTrunc = macAddress << 40;
unsigned long chipID = macAddressTrunc >> 40;
#endif
#define SIZER(_expr) LATER_SERVER_NAME.sendContent("\n" #_expr ":\t"); LATER_SERVER_NAME.sendContent(itoa(sizeof( _expr ), TEMPLATE_BUFFER, 10));
#define SIZER_SUB(_name, _expr, _qty) LATER_SERVER_NAME.sendContent("\n  "  #_name ":\t"); \
  LATER_SERVER_NAME.sendContent(itoa(sizeof( _expr ), TEMPLATE_BUFFER, 10)); \
  LATER_SERVER_NAME.sendContent("b\t X "); \
  LATER_SERVER_NAME.sendContent(itoa( _qty , TEMPLATE_BUFFER, 10)); \
  LATER_SERVER_NAME.sendContent(" = "); \
  LATER_SERVER_NAME.sendContent(itoa(sizeof( _expr )*_qty, TEMPLATE_BUFFER, 10)); \
  LATER_SERVER_NAME.sendContent("b total ");
#ifdef NTP_DEFAULT_LOCAL_PORT

unsigned int DATES[4];
const char * MONTHNAMES =  "JanFebMarArpMayJunJulAugSepOctNovDec";
const char * DAYNAMES =  "SunMonTueWedThuFriSat";

void getDate(unsigned long epoc) {
  if (!epoc) epoc = timeClient.getEpochTime();
  epoc += (24 * 60 * 60);
  unsigned long since2024 = epoc - 1704002400;
  unsigned int monthLengths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30 , 31, 30, 31};
  //var monthNames="JanFebMarArpMayJunJulAugSepOctNovDec";
  unsigned int  days = (since2024 / 86400);
  unsigned int  monthsSince = 0;
  unsigned int  counted = 0;
  unsigned int  month = 0;
  unsigned int  year = 2023;

  while (counted < days) {
    month = (monthsSince++ % 12);
    if (month == 0) year++;
    if (month == 1 && !(year % 4)) counted++; // leap days
    counted += monthLengths[month];
  }

  monthsSince--;
  unsigned int day = monthLengths[month] - (counted - days);
  DATES[0] = year;
  DATES[1] = month + 1;
  DATES[2] = day;
  DATES[3] = days % 7;
}
#endif

std::map < const char *, unsigned long(*)(), cmp_str > TEMPLATES2 = {
  REPRAW("{timer}", millis()),
  REPRAW("{rnd}", randomReg() % 1024),
  REPRAW("{rnd2}", randomReg() % 2),
  REPRAW("{rnd8}", randomReg() % 256),
  REPRAW("{rnd16}", randomReg() % 65536),
  REPRAW("{rnd_digit}", randomReg() % 10),
  REPRAW("{rnd_reg}", randomReg()),
  REPRAW("{web}", getCurrent()->calledFromWeb ? 1 : 0),
  REPRAW("{store}", getCurrent()->storeDirty ? 1 : 0),
  REPRAW("{counter}", getCurrent()->counter++),
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

  {"{time.date}", []()->unsigned long {getDate(0); return DATES[2];}},
  {"{time.month}", []()->unsigned long {getDate(0); return DATES[1];}},
  {"{time.year}", []()->unsigned long {getDate(0); return DATES[0];}},

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
#ifdef __INC_FASTSPI_LED2_H
  REPRAW("{leds}", FastLED.size()),
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


  // replacements for 8266 versions:
  REPRAW("{cpu}", getCpuFrequencyMhz()),
  REPRAW("{mac}", chipID),
  REPRAW("{flash}", ESP.getFlashChipSize()),
  REPRAW("{micros64}", xTaskGetTickCount()),


#endif

  REPRAW("{E.pin}", EVENT[Later.lastEventSlot].pin),
  REPRAW("{E.value}", EVENT[Later.lastEventSlot].value),
  REPRAW("{E.time}", EVENT[Later.lastEventSlot].ms),
  REPRAW("{E.ms}", EVENT[Later.lastEventSlot].msNext - EVENT[Later.lastEventSlot].ms ),
  REPRAW("{E.program}", EVENT[Later.lastEventSlot].programSlot),
  REPRAW("{args}", LATER_SERVER_NAME.args()),
  REPRAW("{arity}", getCurrent()->arity),
  REPRAW("{arg0}", getCurrent()->subArgs[0]),
  REPRAW("{arg1}", getCurrent()->subArgs[1]),
  REPRAW("{arg2}", getCurrent()->subArgs[2]),
  REPRAW("{arg3}", getCurrent()->subArgs[3]),

  REPRAW("{self.index}", getCurrent()->index  ),
  REPRAW("{self.interval}", getCurrent()->interval  ),
  REPRAW("{self.runTime}", getCurrent()->runTime  ),
  REPRAW("{self.duration}", getCurrent()->duration  ),
  REPRAW("{self.loadTime}", getCurrent()->loadedAt  ),
  REPRAW("{self.parseTime}", getCurrent()->parseTime  ),
  REPRAW("{self.runs}", getCurrent()->runs  ),
  REPRAW("{self.lines}", getCurrent()->lineCount  ),

#ifdef SAMPLER_ENABLED
  REPRAW( "{data.total}", Sampler.total  ),
  REPRAW( "{data.avg}", Sampler.avg  ),
  REPRAW( "{data.min}", Sampler.min  ),
  REPRAW( "{data.max}", Sampler.max  ),
  REPRAW( "{data.minTime}", Sampler.minTime  ),
  REPRAW( "{data.maxTime}", Sampler.maxTime  ),
  REPRAW( "{data.lastValue}", Sampler.lastValue  ),
  REPRAW( "{data.lastTime}", Sampler.lastTime  ),
  REPRAW( "{data.length}", Sampler.length  ),
  REPRAW( "{data.total}", Sampler.total  ),
  REPRAW( "{data.total}", Sampler.total  ),
  REPRAW( "{data.total}", Sampler.total  ),
#endif
};//end map

std::map < const char *, unsigned long(*)(), cmp_str > * getTemplates() {
  return &TEMPLATES2;
}

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
#ifndef LATER_DISABLE_OPTIMIZATIONS
void embedTemplates(char * line, LATER_ENVIRON * s) {

  char nameBuffer[32];

  char * ptrLeft = strchr(line, '{');
  if (!ptrLeft) return;

  char * ptrRight = strchr(line, '}');
  if (!ptrRight) return;

  // skip over special templates
  if ( ptrLeft[1] == '&' || ptrLeft[1] == '@' || ptrLeft[1] == '%') {
    embedTemplates(ptrRight + 1, s);
    return;
  }

  ptrRight++;
  unsigned int nameLength = ptrRight - ptrLeft;

  strncpy(nameBuffer, ptrLeft, nameLength);
  nameBuffer[nameLength] = '\0';

  auto callback = TEMPLATES2[nameBuffer];
  unsigned int index;
  if (callback) {
    index = s->TEMP_COUNT++;

    if (index == LATER_TEMPLATE_CACHE_LENGTH) return;

    s->TEMPS[index] = callback;
    // now replace text of template embed with shortcut:
    if (nameLength == 3) { //resize the string to hold 4-char symbnol:
      laterUtil::replace(ptrLeft, "}", " }");
    }
    memset(ptrLeft + 1, ' ', nameLength - 2);
    ptrLeft[1] = '#';
    ptrLeft[2] = index + 65;
  }
  if (strchr(ptrRight, '{')) embedTemplates(ptrRight + 1, s);

}// end embedTemplates()
void embedFunctions(char * line, LATER_ENVIRON * s) {
  // if all literals, replace function call with actual result

  // bool isFunc = true;
  char * ptrDblSpace = strstr(line, "  ");
  if (ptrDblSpace) {
    while (ptrDblSpace) {
      strcpy(ptrDblSpace, ptrDblSpace + 1);
      ptrDblSpace = strstr(line, "  ");
    }
  }

  // step on string to make processing downstream much easier:
  char * ptrParts = strchr(line, '(');
  const char * MATCH_CHARS = ")+*-/%<>=!&?:|";
  ptrParts --;
  if (!isupper(ptrParts[0])) { //not a function call, but math expression, inject . before each operator
    //  isFunc = false;
    ptrParts += 2;
    int pos = strcspn (ptrParts , MATCH_CHARS);
    while (pos) {//put num/term into stack, slide string, try to grab next

      //if already a space, use that
      if (ptrParts[pos - 1] == ' ') {
        ptrParts[pos - 1] = '.';
      }
      if ( ptrParts[pos]  == ')') break;

      ptrParts += pos + 1;
      pos = strcspn (ptrParts , MATCH_CHARS);
    }//wend pos

  }//end if math or function?
  char * lp = line;
  char nameBuffer[32];

  while (lp[0] && lp[0] != ')' && !isupper(lp[0])) lp++;
  char * ptrRight = strchr(lp, '(');
  int nameLen = 0;

  if (!ptrRight) {
    memset(nameBuffer, ' ', 8);
    //return; //not a function call
  } else {
    // found function call, parse it to var-ize, cache it locally, and shortcut the function name to the local copy:

    // build name of function in stand-alone buff
    nameLen = ptrRight - lp;
    strncpy(nameBuffer, lp, nameLen);
    nameBuffer[nameLen] = '\0';
  }

  char * ptr;

  auto callback = FUNCS[nameBuffer];
  if (callback) {

    // fn found, cache:
    int index = -1;
    // look for existing copy of cacched function to re-use:
    for (unsigned int i = 0; i < s->FUNC_COUNT; i++) {
      if (callback == s->FUNCS[i]) {
        index = i;
      }
    }
    if (index == -1) {
      index = s->FUNC_COUNT++;
    }

    if (index == LATER_FUNCTION_CACHE_LENGTH) return;
    s->FUNCS[index] = callback; // cache locally
    // now replace text of fn handle embed with shortcut:
    memset(lp, ' ', nameLen);
    lp += nameLen - 2;
    lp[0] = '#';
    lp[1] = index + 65;
    // pre-pop literals in function calls:
    unsigned int terms[3] = {0, 0, 0};
    int termCount = 0;

    ptr = strchr(line, '(') + 1;

    while (ptr && ptr[0]) {
      if (ptr[0] == '\0') break;

      while (ptr[0] == ' ') ptr++;

      while (ptr[0] && !isdigit(ptr[0])) ptr++;
      if (!ptr || ptr[0] == '\0') break;

      //chomp number and count up:
      int i = 0;
      for (; i < 6; i++) {
        if (!isdigit(ptr[i])) {
          i--;
          if (ptr[0] != '@') terms[termCount++] = strtoul(ptr, NULL, 10);
          ptr += i;
          break;
        }
      }

      ptr++;
    }//wend;

    if (termCount == 3) { // all literals, inline function calling results:
      unsigned long rez = callback(terms[0], terms[1], terms[2]);
      // replace whol darn thing with shortcut var
      char symb = getConstantNumber(ptr, s, rez) + 65;
      ptr = strchr(line, '=') + 1;
      memset(ptr, ' ', strlen(ptr));
      ptr[0] = '@';
      ptr[1] = symb;
      //ptr[2] = '_';
      return;
    }//end if 3 arg function found?

  }//end if callback?

  ptr = strchr(line, '(') + 1;

  while (ptr && ptr[0]) {
    if (ptr[0] == '\0') break;
    //the de-literization routine for semi-literal function args and expressions
    char * startPos = ptr;
    while (isdigit(ptr[0])) ptr++;
    int span = ptr - startPos;
    if (span > 1) {
      char symb = getConstantNumber(startPos, s) + 65;
      memset(startPos, ' ', span);
      startPos[0] = '@';
      startPos[1] = symb;
      //startPos[2] = '_';
    }

    /*
      if ( ptr[0] &&  isdigit(ptr[0]) && isdigit(ptr[1]) && isdigit(ptr[2]) ) { // foun 2+digits of literals
      char symb = getConstantNumber(ptr, s) + 65;
      ptr[0] = '@';
      ptr[1] = symb;
      //ptr[2] = '_';

      ptr+=3;
      }
    */
    ptr++;
    while (ptr[0] == ' ') ptr++;
  }//wend
}// end embedFunctions()

#endif
unsigned int lineTemplateCount = 0;
void processTemplateExpressions2(char * line, LATER_ENVIRON * s) { // also accept line.single flag or bool here

  HRT_START

  char * ptrLeft = strchr(line, '{');
  if (!ptrLeft) return;

  char * ptrRight = strchr(ptrLeft + 2, '}');
  if (!ptrRight) return;

  bool isConstant = false;

  if (ptrLeft[1] == '*') {
    isConstant = true;
    ptrLeft[0] = ' ';
    ptrLeft[1] = '{';
    ptrLeft++;
  }//ed if star constant?
  char * TEMPLATE_KEY_BUFF2 = ptrLeft;
  char rightSideCap = ptrRight[1];

  char * nam;

  unsigned long val = 0;

  ptrRight[1] = '\0';

#ifndef LATER_DISABLE_OPTIMIZATIONS
  if (ptrLeft[1] == '#') {

    //@E_={#B }
    //@D_={#Ad}

    auto * cb = s->TEMPS[ptrLeft[2] - 65];
    //auto cb = TEMPLATES2["{runs}"];
    val = cb();

    s->VARS[lineTemplateCount] = val;
    ptrRight[0] = ' ';
    ptrRight[1] = rightSideCap;
    ptrLeft[0] = '@';
    ptrLeft[1] = lineTemplateCount++ + 65; //line[1];
    //ptrLeft[2] = '_';
    strcpy(ptrLeft + 2, ptrRight + 1);

    // s->lines[s->i].data = 5;
    //lineTemplateCount++;
    if (strrchr ( ptrLeft + 2, '{' )) {
      processTemplateExpressions2(ptrLeft + 2, s);
    }
    lineTemplateCount = 0;
    return;
  }
#endif

  bool storeCall = ptrLeft[1] == '&';
  bool varCall = ptrLeft[1] == '@';
  int len = (ptrRight - ptrLeft) + 1;
  if (TEMPLATE_KEY_BUFF2[1] == '%') { //{%RAM%}

    if (strstr(TEMPLATE_KEY_BUFF2, "%RAM%")) { // was  nsLATER::laterUtil  ddns
      laterUtil::replace(line, TEMPLATE_KEY_BUFF2, laterUtil::fileToBuff("%RAM%"));
      ptrRight[1] = rightSideCap;
      HRT_TIME(templates)
      return;
    }//end if RAM?

#ifdef NTP_DEFAULT_LOCAL_PORT
    if (strstr(TEMPLATE_KEY_BUFF2, "%TIME%")) {
      laterUtil::replace(line, TEMPLATE_KEY_BUFF2, timeClient.getFormattedTime().c_str());
      ptrRight[1] = rightSideCap;
      processTemplateExpressions2(line, s);
      return;
    }//end if RAM?

    getDate(0);

    if (strstr(TEMPLATE_KEY_BUFF2, "%DATE%")) {
      String ds = String(DATES[0]) + "/" + String(DATES[1]) + "/" + String(DATES[2]);
      laterUtil::replace(line, TEMPLATE_KEY_BUFF2, ds.c_str());
      ptrRight[1] = rightSideCap;
      processTemplateExpressions2(line, s);
      return;
    }//end if DATE?

    if (strstr(TEMPLATE_KEY_BUFF2, "%MONTH%")) {
      int offset = (DATES[1] - 1) * 3;
      char mn[4];
      strncpy(mn, MONTHNAMES + offset, 3);
      mn[3] = '\0';
      laterUtil::replace(line, TEMPLATE_KEY_BUFF2, mn  );
      ptrRight[1] = rightSideCap;
      processTemplateExpressions2(line, s);
      return;
    }//end if MONTH?

    if (strstr(TEMPLATE_KEY_BUFF2, "%DAY%")) {
      int offset = (DATES[3]) * 3;
      char dn[4];
      strncpy(dn, DAYNAMES + offset, 3);
      dn[3] = '\0';
      laterUtil::replace(line, TEMPLATE_KEY_BUFF2, dn  );
      ptrRight[1] = rightSideCap;
      processTemplateExpressions2(line, s);
      return;
    }//end if DATE?
#endif
  }//end if [0]=='%' ?

  auto callback = isConstant ? 0 : TEMPLATES2[TEMPLATE_KEY_BUFF2];
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
  if (isConstant) { // replace val if known value already computed
    //CONSTANTS[s->index][ptrLeft]
    auto search = CONSTANTS[s->index].find(TEMPLATE_KEY_BUFF2);
    if (search != CONSTANTS[s->index].end()) {
      val = search->second;
    } else {
      val = CONSTANTS[s->index][TEMPLATE_KEY_BUFF2] = TEMPLATES2[TEMPLATE_KEY_BUFF2]();
    }
  }//end if constant?
  if (val) {
    bool varUsed = false;

    if (!varCall) { // vars will get literally embded instead of aliasing the var for no reason:

      nam = getVarName(TEMPLATE_KEY_BUFF2, s->index);
      s->VARS[nam[1] - 65] = val;
      varUsed = true;
      //if output needed. build interpolated replacement buffer
      if ( ((s->lines[s->i].flags >> 4) & 0x01) == 1   ) {
        int varLen = strlen(nam);
        memset ( TEMPLATE_BUFFER, ' ', 63);
        strncpy(TEMPLATE_BUFFER, nam, varLen);
        TEMPLATE_BUFFER[varLen] = '\0';
      }

    } else {
      itoa(val, TEMPLATE_BUFFER, 10);
    }
    if (varUsed &&  ((s->lines[s->i].flags >> 4) & 0x01) != 1  ) { //if not output and var used, inject var marker w/o resizing string
      ptrRight[1] = rightSideCap;
      ptrLeft[0] = '@';
      ptrLeft[1] = nam[1];
      // ptrLeft[2] = '_';
      for (int i = 0; i < (len - 2); i++) ptrLeft[2 + i] = ' '; // fill rest of line with space
    } else {
      strcpy(TEMPLATE_KEY_BUFF, TEMPLATE_KEY_BUFF2);
      ptrRight[1] = rightSideCap;
      laterUtil::replace(line, TEMPLATE_KEY_BUFF, TEMPLATE_BUFFER);
    }

  } else {
    strcpy(TEMPLATE_KEY_BUFF, TEMPLATE_KEY_BUFF2);
    ptrRight[1] = rightSideCap;
    laterUtil::replace(line, TEMPLATE_KEY_BUFF, "0"); // prevent re-process attempts on unknown keys
  }//end if val?
  HRT_TIME(templates)

  // look for additional template expressions:
  ptrLeft = strchr(line, '{');
  if (!ptrLeft) return;

  // found more, process:
  if (strrchr ( ptrLeft + 1, '}' )) processTemplateExpressions2(line, s);
  lineTemplateCount = 0;
}//end processTemplateExpressions2()
uint8_t parseByteFromChars(char * ptr) {
  //  }else
  if (ptr[1]) {
    return ((ptr[0] - 48) * 10) + (ptr[1] - 48);
  } else {
    return ptr[0] && (ptr[0] - 48);
  }
}
void handleCommandList() {

  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);   //Enable Chunked Transfer
  LATER_SERVER_NAME.send(200, LATER_PLAIN, "COMMAND LISTING (duplicate keys are aliases)\n\nKey\tCommand\n");                      //Send first part WITH header

  char c[2] = {0, 0};
  for (auto const & x : LATER_CMDS)   {
    c[0] = x.second;
    if (!c[0]) continue;
    LATER_SERVER_NAME.sendContent(c);
    LATER_SERVER_NAME.sendContent("\t");
    LATER_SERVER_NAME.sendContent(x.first);
    LATER_SERVER_NAME.sendContent("\n");
  }
  LATER_SERVER_NAME.sendContent("\n\nFUNCTIONS:\n\n");
  for (auto const & x : FUNCS)   {
    if (strlen(x.first)) {
      LATER_SERVER_NAME.sendContent(x.first);
      LATER_SERVER_NAME.sendContent("\n");
    }//end if something to send?
  }
  LATER_SERVER_NAME.sendContent("\n\nTEMPLATES:\n\n");
  unsigned long val;

  for (auto const & x : TEMPLATES2)   {
    if (strlen(x.first)) {
      LATER_SERVER_NAME.sendContent(x.first);
      if ( strstr(x.first, "[pop") || strstr(x.first, "[shift") ) { // prevent destructive reads
        LATER_SERVER_NAME.sendContent("\t  n/a in help\n");
        continue;
      }
      auto callback = TEMPLATES2[x.first];
      val = 0;
      if (callback) val = callback();
      LATER_SERVER_NAME.sendContent("\t");

      memset ( TEMPLATE_BUFFER, ' ', 63);
      itoa(val, TEMPLATE_BUFFER, 10);
      LATER_SERVER_NAME.sendContent(TEMPLATE_BUFFER);
      LATER_SERVER_NAME.sendContent("\n");
    }//end if something to send?
  }
  LATER_SERVER_NAME.sendContent("\nRAM USAGES:\n");
  int baseSize = 52; // measured by commenting out 10 funcs, lowering ram by 527b
  baseSize *= FUNCS.size();
  baseSize += sizeof(FUNCS);

  LATER_SERVER_NAME.sendContent("\nFUNCS:\t");
  LATER_SERVER_NAME.sendContent(itoa(baseSize, TEMPLATE_BUFFER, 10));

  LATER_SERVER_NAME.sendContent("\nTEMPLATES:\t");
  LATER_SERVER_NAME.sendContent(itoa(TEMPLATES2.size() * 8, TEMPLATE_BUFFER, 10));

  LATER_SERVER_NAME.sendContent("\nCOMMANDS:\t");
  LATER_SERVER_NAME.sendContent(itoa(LATER_CMDS.size() * 5, TEMPLATE_BUFFER, 10));
  SIZER(FILE_BUFF);
  SIZER(TEMPLATE_BUFFER);
  SIZER(INCLUDE_BUFFER);
  SIZER(TEMP_BUFFER);
  SIZER(LINE_BUFF);

  LATER_SERVER_NAME.sendContent("\nLATER_HTTP_CACHE:\t");
  LATER_SERVER_NAME.sendContent(itoa(LATER_HTTP_CACHE, TEMPLATE_BUFFER, 10));

  SIZER(setRunLog);
  SIZER(CMDCHARS);
  SIZER(VARCHARS );
  SIZER(VARLIST);

  SIZER(LaterClass);
  SIZER(LATER_ENVIRON);
  SIZER_SUB("Lines", LATER_LINE, LATER_LINE_LIMIT);
  SIZER_SUB("Program", char, LATER_PROGRAM_SIZE);
  SIZER_SUB("Vars", unsigned long, LATER_VARS_LENGTH);
  SIZER_SUB("Event", LATER_EVENT, 1);
  SIZER_SUB("Options", LATER_OPTIONS, 1);
  SIZER_SUB("Intervals",   unsigned long, 8);
  SIZER_SUB("Sub Args",   unsigned long, 8);
  SIZER_SUB("fileName",   char, 32);
  SIZER_SUB("contentType",   char, 32);
  SIZER_SUB("FUNCS", threeArgFunc, LATER_FUNCTION_CACHE_LENGTH);
  SIZER_SUB("TEMPS", noArgFunc, LATER_TEMPLATE_CACHE_LENGTH);
  LATER_SERVER_NAME.sendContent("");
}//end handleCommandList()
#ifdef ESP8266WEBSERVER_H
void handleStep() {

  LATER_ENVIRON * s = LATER_SERVER_NAME.hasArg("name") ? Later.getByName(LATER_SERVER_NAME.arg("name").c_str()) : getCurrent();
  if (!s) s = getCurrent();
  //char linebuff[LATER_LINE_BUFFER];
  char * linebuff = LINE_BUFF;
  memset(linebuff, '\0', 16);

  s->resumeMillis = millis() - 4;

  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");
  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);
  LATER_SERVER_NAME.send ( 200, LATER_PLAIN, " ");
  LATER_SERVER_NAME.sendContent(itoa(s->i, linebuff, 10));
  LATER_SERVER_NAME.sendContent("\n");

  if (strlen(SYSTEM_OUTPUT_BUFFER)) {
    LATER_SERVER_NAME.sendContent(SYSTEM_OUTPUT_BUFFER);
    memset(SYSTEM_OUTPUT_BUFFER, '\0', 2);
  }

  LATER_SERVER_NAME.sendContent("\n");

  int varNameMisses = 0;

  //\nVALUE REGISTERS:\n#  \tSYM\tval\texpr\n");
  for (unsigned int i = 0;  i < LATER_VARS_LENGTH; i++) {
    if ( i > 25 && i < 32) continue;

    if (varNameMisses  && ! s->VARS[i]) continue; // skip "empty" lines

    LATER_SERVER_NAME.sendContent(itoa(i, linebuff, 10));

    linebuff[0] = '\0';
    strcpy(linebuff, ".\t@ \t");
    linebuff[3] = (char) (i + 65);

    //linebuff[1] = '\t';
    //linebuff[2] = '\0';

    LATER_SERVER_NAME.sendContent(linebuff);

    LATER_SERVER_NAME.sendContent(itoa(s->VARS[i], linebuff, 10));
    LATER_SERVER_NAME.sendContent("\t");
    bool foundVarName = false;

    if (varNameMisses < 2) {
      for (auto const & x : LATER_VAR_NAMES[s->index])   {
        if (x.second == i) {
          foundVarName = true;
          LATER_SERVER_NAME.sendContent(x.first.c_str());
          break;
        }//if match?
      }//next varName
    }//if not struck out finding var names yet?

    //}else{
    if (!foundVarName) {
      varNameMisses++;
      LATER_SERVER_NAME.sendContent("#");
      LATER_SERVER_NAME.sendContent(itoa(s->VARS[i], linebuff, 10));
    }
    LATER_SERVER_NAME.sendContent("\n");

  }//next local var

  LATER_SERVER_NAME.sendContent("");


}//end handleStep()
void handleDump() {
  LATER_ENVIRON * s = LATER_SERVER_NAME.hasArg("name") ? Later.getByName(LATER_SERVER_NAME.arg("name").c_str()) : getCurrent();
  if (!s) s = getCurrent();
  LATER_LINE * l;
  //char linebuff[LATER_LINE_BUFFER];
  char * linebuff = LINE_BUFF;
  memset(linebuff, '\0', 16);

  char respbuff[26];
  char * lp;
  //char dbg[ 8 8 ];
  char * dbg = TEMP_BUFFER;
  memset(dbg, '\0', 16);
  char flagList[] = "CHOAEVT";

  LATER_SERVER_NAME.sendHeader(LATER_CORS, "*");

  LATER_SERVER_NAME.setContentLength(CONTENT_LENGTH_UNKNOWN);
  LATER_SERVER_NAME.send ( 200, LATER_PLAIN, "\n");

  sprintf(dbg, "%ld lines in %db file:", s->lineCount, strlen(s->program) );
  LATER_SERVER_NAME.sendContent(dbg);
  LATER_SERVER_NAME.sendContent(s->fileName);

  sprintf(dbg, "\nRAM:%u  runs:%lu  start:%d at:%lu exit:%d\n", ESP.getFreeHeap(), s->runs, s->startLineNumber, s->i,  s->exitLineNumber );
  LATER_SERVER_NAME.sendContent(dbg);

  unsigned long avg = s->runTime;
  if (s->runs) avg = s->duration / s->runs;
  sprintf(dbg, "resume:%d run:%ld parse:%ld avg:%ld",
          s->resumeLineNumber, s->runTime, s->parseTime, avg);
  LATER_SERVER_NAME.sendContent(dbg);
  //String bonus = " ";
  bool bonus = true;

#ifdef LATER_LINE_PROFILING
  LATER_SERVER_NAME.sendContent("\n\nLINES:\n # ex    CHOAEVT OP data  runs    ptime    mean  parse    code\n");
#else
  LATER_SERVER_NAME.sendContent("\n\nLINES:\n # ex    CHOAEVT OP dat   code\n");
#endif

  for (int i = 0, mx = s->lineCount; i < mx; i++) {
    l = &s->lines[i];
    lp = s->program + l->start;
    strncpy(linebuff, lp, l->len);
    linebuff[l->len] = '\0';
    if (i > 9) bonus = false;
    if (bonus) LATER_SERVER_NAME.sendContent(" ");
    LATER_SERVER_NAME.sendContent(itoa(i, respbuff, 10));
    LATER_SERVER_NAME.sendContent("->");
    LATER_SERVER_NAME.sendContent(itoa(l->exit, respbuff, 10));
    LATER_SERVER_NAME.sendContent(" \t[");
    itoa(l->flags + 256, respbuff, 2);
    lp = respbuff;
    lp += 2;  // print out any active flags with abbr in the slot, else empty space:
    for (int f = 0; f < 7; f++)  lp[f] = (lp[f] == '1') ? flagList[f] : ' ';

    LATER_SERVER_NAME.sendContent(lp);
    LATER_SERVER_NAME.sendContent("] ");
    /*
        // exprCache:

        char * rb = respbuff;
        int cachepos = 0;
        memset(rb, '\0', 11);

        for (int i = 0; i < 10; i++) {

          if (l->exprCache[i] < 15) {
            strcat(rb, "o");
            rb++;
            itoa(l->exprCache[i], rb, 16);
            rb++;
          } else {
            itoa(l->exprCache[i], rb, 16);
            rb += 2;
          }

          if (i == 5) {
            strcat(rb, " ");
            rb++;
          }

        }
        LATER_SERVER_NAME.sendContent(respbuff);
        LATER_SERVER_NAME.sendContent(" ");
    */
    respbuff[0] = l->cmd ? l->cmd : '?';
    respbuff[1] = '\0';
    LATER_SERVER_NAME.sendContent(respbuff);
    LATER_SERVER_NAME.sendContent(" ");

    itoa(l->data, respbuff, 16);
    if (l->data < 16)  LATER_SERVER_NAME.sendContent("0");
    LATER_SERVER_NAME.sendContent(respbuff);

    LATER_SERVER_NAME.sendContent("  ");
#ifndef LATER_LINE_PROFILING
    LATER_SERVER_NAME.sendContent("| ");
#endif

    // cut in profile info here:
#ifdef LATER_LINE_PROFILING
    outputPaddedNumber(l->profile.count, "xkm", 6);
    outputPaddedNumber(l->profile.total, "ums", 8);
    unsigned long tot = l->profile.total;
    if (l->profile.count) tot = l->profile.total / l->profile.count;
    outputPaddedNumber(tot, "ums", 7);
    outputPaddedNumber(l->profile.parse, "ums", 6);
    LATER_SERVER_NAME.sendContent(" | ");
#endif

    LATER_SERVER_NAME.sendContent(linebuff);
    LATER_SERVER_NAME.sendContent("\n");
  }//next line

#ifdef LATER_LINE_PROFILING
  LATER_SERVER_NAME.sendContent(" # ex    CHOAEVT OP data  runs    ptime    mean  parse  code\n");
#else
  LATER_SERVER_NAME.sendContent(" # ex    CHOAEVT OP dat code\n");
#endif
#ifndef LATER_DISABLE_OPTIMIZATIONS

  // optimization report:
  LATER_SERVER_NAME.sendContent("\nVALUE REGISTERS:\n#  \tsymb\tvalue\texpr\n");
  int varNameMisses = 0;

  //\nVALUE REGISTERS:\n#  \tSYM\tval\texpr\n");
  for (unsigned int i = 0;  i < LATER_VARS_LENGTH; i++) {
    if ( i > 25 && i < 32) continue;

    if (varNameMisses  && ! s->VARS[i]) continue; // skip "empty" lines

    LATER_SERVER_NAME.sendContent(itoa(i, linebuff, 10));
    LATER_SERVER_NAME.sendContent( ".\t@");
    linebuff[0] = (char) (i + 65);

    linebuff[1] = '\0';

    LATER_SERVER_NAME.sendContent(linebuff);
    LATER_SERVER_NAME.sendContent("\t");

    LATER_SERVER_NAME.sendContent(itoa(s->VARS[i], linebuff, 10));
    LATER_SERVER_NAME.sendContent("\t");
    bool foundVarName = false;

    if (varNameMisses < 2) {
      for (auto const & x : LATER_VAR_NAMES[s->index])   {
        if (x.second == i) {
          foundVarName = true;
          LATER_SERVER_NAME.sendContent(x.first.c_str());
          break;
        }//if match?
      }//next varName
    }//if not struck out finding var names yet?

    //}else{
    if (!foundVarName) {
      varNameMisses++;
      LATER_SERVER_NAME.sendContent("#");
      LATER_SERVER_NAME.sendContent(itoa(s->VARS[i], linebuff, 10));
    }
    LATER_SERVER_NAME.sendContent("\n");

  }//next local var
  LATER_SERVER_NAME.sendContent("\nCACHED FUNCTIONS:\n#  \tsymb\tname\n");

  for (unsigned int i = 0; i < s->FUNC_COUNT; i++) {
    LATER_SERVER_NAME.sendContent(itoa(i, linebuff, 10));
    LATER_SERVER_NAME.sendContent( ".\t#");

    auto cachedFunc = s->FUNCS[i];
    for (auto const & x : FUNCS)   {
      if (x.second == cachedFunc ) {

        // symb:
        linebuff[0] = 65 + i;
        linebuff[1] = '\0';
        LATER_SERVER_NAME.sendContent(linebuff);

        // name:
        LATER_SERVER_NAME.sendContent("\t");
        LATER_SERVER_NAME.sendContent(x.first);
        LATER_SERVER_NAME.sendContent("\n");
        break;
      }//end if match?
    }//next global function
  }//next local func
  LATER_SERVER_NAME.sendContent("\nCACHED TEMPLATES:\n#  \tsymb\tvalue\texpr\n");

  for (unsigned int i = 0; i < s->TEMP_COUNT; i++) {
    LATER_SERVER_NAME.sendContent(itoa(i, linebuff, 10));
    LATER_SERVER_NAME.sendContent( ".\t#");

    auto cachedFunc = s->TEMPS[i];

    for (auto const & x : TEMPLATES2)   {
      if (x.second == cachedFunc ) {
        linebuff[0] = 65 + i;
        linebuff[1] = '\t';
        linebuff[2] = '\0';
        LATER_SERVER_NAME.sendContent(linebuff);
        LATER_SERVER_NAME.sendContent(itoa( cachedFunc(), linebuff, 10));
        LATER_SERVER_NAME.sendContent( "\t");
        LATER_SERVER_NAME.sendContent(x.first);
        LATER_SERVER_NAME.sendContent("\n");
        break;
      }
    }

  }//next temp
#endif
  LATER_SERVER_NAME.sendContent("\n-------- SYSTEM LOG -----------\n");
  LATER_SERVER_NAME.sendContent(setRunLog);
  LATER_SERVER_NAME.sendContent("\n-------- END PROGRAM DEBUG -----------\n");
  LATER_SERVER_NAME.sendContent("");//ends and closes response
} // end handle dump()
#endif







//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
}
using nsLATER::Later;
using nsLATER::LATER_LINE;
using nsLATER::LATER_ENVIRON;

#endif
