// BETA later script interpreter for JavaScript, ported from the C++ source by dandavis with some use of Gemini AI for pure functions and class convertions.
// this is an in-progress project for development work, not a stable end-product. Initial release will provide modules, APIs, and browser/nodejs hooks. stay tuned.
// CCBY3: dandavis.  begin hybrid js/html testbed file: /////////////////
//<script>window.onerror=function(e,x,y,z){console.info(e,x,y,z); document.write("<h2 style='max-width: 100vw;overflow: auto'>"+e.split(':').join(':<br>').fontcolor('brick')+("<br><h2>Line <a onclick='top.jumpToLine(innerHTML-1)'>"+y+"</a> pos: " + z).big());};</script><pre style="font-size: 1.5rem;background:#ddd;" id=stats><style>.pix{display: inline-block; height: 2.9vw; width: 1vw;}body,html{margin:0;padding:0;}</style><script>
// later emulator: converted js from c++ later library

//////////////////////////////////////////////
// RUNTIME and NATIVE FUNCTION SUPPORT:


// simple mutable string object. string methods mutate. cons: s+="fd" yeilds string as s
function String5(val){
  var data = val.split(""), odf = (k,v)=>Object.defineProperty(data, k, {value: v});
  Object.getOwnPropertyNames(String.prototype).forEach(function(method, index){ 
         if(/\b((length)|(valueOf)|(toString)|(constructor))\b/.test(method)) return;
          odf(method, (function(){
                var buff = ""[method].apply(data.join(""), arguments);  
                data.length = 0;
                data.push.apply(data, buff.split(""));
                return data; 
         }));
   }, data);

 odf("toJSON", x=>data.join(""));
 odf("valueOf", x=>data.join(""));
 odf("toString", x=>data.join(""));

 return data;
}

function strpbrk(hay, chars){
   var rx = new RegExp(`[${ chars.replace(/[/\-\\^$*+?.()|[\]{}]/g, '\\$&') }]`);
   var ind = hay.search(rx);
  return hay.slice(ind > -1 ? ind : hay.length);
}


function strcspn(hay, needles){
 var rx = new RegExp(`[${ needles.replace(/[/\-\\^$*+?.()|[\]{}]/g, '\\$&') }]`);
 return hay.search(rx)+1;
}


function strchr(s,c){
  var p = s.indexOf(c);
  return s.slice(p>-1?p : 9e9);//.join("");
}

function strstr(s,c){
 var ind = s.indexOf(c);
 if(ind==-1) return "";
  return s.slice(ind);//.join("");
}


function strlen(s){
  return String(s).length;
}



const Serial={
 print: console.log,
 println: console.log
};

function _Dir(path){
 var entries = Object.entries(SPIFFS.files),
 	 cursor= 0;
 function next(){
     var o = entries[cursor++];
     if(!o) return null;
	 return {
	 	name: x=>o[0],
		size: x=>o[1].length,
	 };
  }
  return {
	openNextFile: next,
		openFile: next
  };
}

function _File(val){
	var cursor = 0, len = val.length;
	//readBytes seek close
	return {
		  seek: n=>cursor=n,
	 readBytes: n=>val.substr(cursor, n, cursor+=n),
	 	 close: Boolean.bind(1,1)
	}
}

const ESP = {getFreeHeap: x=>12345 };

const SPIFFS= {
   files: {
   	"/autoexec.lnk": "/main.bat",
"/test.bat": "#define=x 777\n$dan = 66\nprintln this is a test {rnd}\nif $dan > 55 \n println big dan\nelse\nprintln lil dan\nfi\nprintln Done! ",	

"/data.csv":`age,year,sig
0,2025,318697
1,2024,318697
2,2023,318697
3,2022,318698
4,2021,318698
5,2020,318698
6,2019,318698
7,2018,318698
8,2017,318698
9,2016,318699
10,2015,318699
11,2014,318699
12,2013,318699`,
	"/store.ini": 'myKey1\t1678886400000\t1\t123\nanotherKey\t1678886460000\t3\t456\ntestKey\t1678886520000\t2\t789'
	
	},
  exists: strName=> !!SPIFFS.files[strName],
  remove: strName=> delete SPIFFS.files[strName],
    open: strName=> _File(SPIFFS.files[strName]),
 openDir: strName=> _Dir(strName),
_readAll: strName=> SPIFFS.files[strName]||"",
 _write: (strName, strValue)=> SPIFFS.files[strName]=strValue||"",
    info: strName=>({
			usedBytes: JSON.stringify(SPIFFS.files).length, 
			totalBytes: 5e6
			}),	
};//end SPIFFS



var PINS=new Array(40).fill(0).map((x,i)=>({
  pin: i, value: 0, mode: 0
}));
function pinMode(pin, mode){
 PINS[pin].mode = mode;
}
function digitalWrite(pin, value){
 PINS[pin].value = +(!!value);
}
function analogWrite(pin, value){
 PINS[pin].value =  value % 1023;
}
function digitalRead(pin){
 return +(!!PINS[pin].value);
}
function analogRead(pin){
 return PINS[pin].value;
}


function millis(){
 return Math.floor(performance.now());
}


function micros(){
 return Math.floor(performance.now() * 1000);
}

var LATER_HTTP_BUFFER="";

var LATER_SERVER_NAME={
  send: (status, type, content)=>LATER_HTTP_BUFFER=content,
  sendContent: x=>LATER_HTTP_BUFFER+=x,  
  setContentLength: x=>1,
  sendHeader: (key, val)=>{},  
  hasArg: (key)=>!!LATER_SERVER_NAME.args[key],
  arg: (key)=>LATER_SERVER_NAME.args[key],
  args: {a: 777},  
};


//LATER_SERVER_NAME.hasArg(macroBuffPtr)



///////////////////////////////////////
///////////// BEGIN TRANSPILED SOURCE:
// config defines:
const later_h = 1;
const LATER_INSTANCES=4;
const LATER_PROGRAM_SIZE=1024;
const LATER_LOG_SIZE=4096;
const LATER_LINE_BUFFER=96;
const LATER_LINE_LIMIT=128;
const LATER_RESUME_LIMIT=5;
const LATER_HTTP_CACHE=1400;
const LATER_EVENT_COUNT=5;
//const LATER_PIXEL_NAME="strip";
//const LATER_SERVER_NAME="server";
const LATER_PLAIN="text/plain";
const LATER_CORS="Access-Control-Allow-Origin";
const DANOS_EDITOR_URL="https://pagedemos.com/later/js/";
const SAMPLER_LENGTH=100;
const SAMPLER_TYPE="unsigned lon";
const LATER_VARS_LENGTH=95;
const LATER_FUNCTION_CACHE_LENGTH=10;
const LATER_TEMPLATE_CACHE_LENGTH=28;
const LATER_SKETCH = "MyProject.ino";


function DUMP(lab, val) { Serial.println(lab + String(val)); }



class RGB_COLOR {
  constructor(initialValue = 0) {
    var chan = this.chan = new ArrayBuffer(4);
    var x=new DataView(chan);
     for(var i=0; i<4;i++) Object.defineProperty(chan, i, {set:x.setUint8.bind(x, i), get: x.getUint8.bind(x, i) });
     Object.defineProperty(this, "value", {set:x.setUint32.bind(x, 0), get: x.getUint32.bind(x, 0)});
     this.value = initialValue;
  }
}//end RGB_COLOR()


/*
class RGB_COLOR {
  constructor(initialValue = 0) {
    var that = this;
    this.value = initialValue; 
    var chan = [0,0,0,0];
    chan._0 = this.chan[0];
    chan._1 = this.chan[1];
    chan._2 = this.chan[2];
    chan._3 = this.chan[3];
   
    Object.defineProperty(chan, "0", {set: function(v){ chan._0 = v; that._updateValue();}, get:x=>chan_0 });
    Object.defineProperty(chan, "1", {set: function(v){ chan._1 = v; that._updateValue();}, get:x=>chan_1  });
    Object.defineProperty(chan, "2", {set: function(v){ chan._2 = v; that._updateValue();}, get:x=>chan_2  });
    Object.defineProperty(chan, "3", {set: function(v){ chan._3 = v; that._updateValue();}, get:x=>chan_3  });
    this._chan = chan;

  }

  get chan() {
return [
   (this.value >> 24) & 0xFF,
   (this.value >> 16) & 0xFF,
   (this.value >> 8) & 0xFF,
   (this.value & 0xFF),
]
  }
  // Internal method to update the value from the channel array
  _updateValue() { 
    this.value = (this._chan._0<< 24) |
                   (this._chan._1<< 16) |
                   (this._chan._2<< 8)  |
                   (this._chan._3);
  }
}//end RGB_COLOR()
*/
RGB_PIXEL = new RGB_COLOR;
OLD_PIXEL = new RGB_COLOR;
NEW_PIXEL = new RGB_COLOR;





// reusable buffers:
var TEMPLATE_BUFFER = (new Array(64).fill(""));
var TEMPLATE_KEY_BUFF = (new Array(24).fill(""));
var INCLUDE_BUFFER = (new Array(1024).fill(""));
var TEMP_BUFFER = (new Array(128).fill(""));
var FILENAME_BUFFER = (new Array(32).fill(""));
var FILE_BUFF = (new Array(2048).fill(""));
var LINE_BUFF = (new Array(LATER_LINE_BUFFER).fill(""));


const VARCHARS = Object.freeze(["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","_","$","1","2","3","4","5","6","7","8","9","0","."]);
const VARLIST = Object.freeze(["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","_"]);
const CMDCHARS = Object.freeze(["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","1","2","3","4","5","6","7","8","9","0","!","@","#","$","%","^","&","*","(",")","_","+","=","-","`","~",",",".","<",">","{","}","[","]",";",":","'","?","/","|"]);

class FLAGS {
  static T = 1;
  static V = 2;
  static E = 4;
  static A = 8;
  static O = 16;
  static H = 32;
  static N = 64;
}



  
var LATER_VAR_NAMES=new Array(LATER_INSTANCES).fill({});
var VAR_NAME_COUNT=new Array(LATER_INSTANCES).fill(3);
var DEFINES=new Array(LATER_INSTANCES).fill({x:999});
var LOG_CURSOR= 0; // moved here from commands
var setRunLog="\n";
var CONSTANTS=new Array(LATER_INSTANCES).fill({});
var lastFileName = "ahriglf6456343455"; // fileLoader cache
var APPLY_ARGS = [0, 0, 0, 0];






class LATER_EVENT {
    constructor() {
        this.pin = -1;
        this.value = 0;
        this.ms = 0;
        this.msNext = 0;
        this.programSlot = -1;
    }
}

const EVENT = new Array(LATER_EVENT_COUNT).fill(null).map(() => new LATER_EVENT());

class LATER_OPTIONS {
    constructor() {
        this.debug = false;
        this.perf = false;
        this.strict = false;
        this.persist = false;
        this.socket = false;
        this.noget = false;
        this.step = false;
    }
}

class LATER_RESUME {
    constructor() {
        this.timestamp = 0;
        this.fileName = new Array(32).fill('\0');
    }
}

class LATER_LINE {
    constructor() {
        this.start = 0;
        this.stop = 0;
        this.data = 0;
        this.len = 0;
        this.flags = 0;
        this.exit = 0;
        this.profile = null; // Assuming LINE_PROFILE is defined elsewhere
        this.cmd = '';
		this.hits = 0;
        this.exprCache = new Array(11).fill('\0');
    }
}

class CsvState {
  constructor() {
    this.hasLineParam = false;
    this.delim = ',';
    this.skip = 0;
    this.blockSize = 0;
    this.morePointer = 0;
    this.varSlots = new Array(12).fill(0);
    this.delimStr = ",";
    this.lineNeeded = 1;
    this.fn = "";
    this.filter = "";
  }
}


class LATER_ENVIRON {
    constructor() {
        this.index = 0;
        this.i = 0;
        this.lines = new Array(LATER_LINE_LIMIT).fill(null).map(() => new LATER_LINE());
        this.program = new Array(LATER_PROGRAM_SIZE).fill('');
        this.fileName = new Array(32).fill('');
        this.switchTerm = new Array(16).fill('');
        this.contentType = new Array(32).fill('');
        this.eventSlot = -1;
        this.status = 0;
        this.lastLineNumber = 0;
        this.lastLinePtr = null;
        this.TEMPS = new Array(LATER_TEMPLATE_CACHE_LENGTH).fill(null); // Assuming noArgFunc is defined elsewhere
        this.FUNCS = new Array(LATER_FUNCTION_CACHE_LENGTH).fill(null); // Assuming threeArgFunc is defined elsewhere
        this.lineCount = 0;
        this.forTop = new Array(4).fill(0);
        this.forStep = new Array(4).fill(0);
        this.forIndex = new Array(4).fill(0);
        this.forStart = new Array(4).fill(0);
        this.forEnd = new Array(4).fill(0);
        this.forLevel = 0;
        this.switchExit = 0;
        this.counter = 0;
        this.intervals = new Array(8).fill(0);
        this.loadedAt = 0;
        this.startedAt = 0;
        this.runs = 0;
        this.duration = 0;
        this.runTime = 0;
        this.parseTime = 0;
        this.reads = 0;
        this.writes = 0;
        this.interval = 0;
        this.VARS = new Array(LATER_VARS_LENGTH).fill(0);
        this.TEMP_COUNT = 0;
        this.FUNC_COUNT = 0;
        this.LITS_COUNT = 2;
        this.subArgs = new Array(8).fill(0);
        this.jumpIfOperand = 0;
        this.resumeMillis = 0;
        this.timer = 0;
        this.subReturnValue = 99;
        this.intervalCount = 0;
        this.jumpIfOperator = 0;
        this.subReturnLine = 0;
        this.resumeLineNumber = 0;
        this.arity = 0;
        this.startLineNumber = 0;
        this.exitLineNumber = 0;
        this.calledFromWeb = false;
        this.storeDirty = false;
        this.isSuspended = false;
        this.stepReady = false;
        this.csv = new CsvState();
        this.options = new LATER_OPTIONS();
    }

    freeze(duration) {
        this.resumeLineNumber = this.i + 1;
        this.resumeMillis = Date.now() + duration; // Assuming millis() is equivalent to Date.now()
        this.duration = (performance.now() - this.startedAt) / 1000; // Assuming micros() is equivalent to performance.now()
    }
	
	Number(lb){
	  return NumberJS(lb, this.VARS);
	}
}

var SCRIPTS=new Array(LATER_INSTANCES).fill(0).map(x=>new LATER_ENVIRON());




// char cmd name constants
const LATER_apply='6';
const LATER_noop='n';
const LATER_else='E';
const LATER_var='V';
const LATER_store='g';
const LATER_global='m';
const LATER_static='d';
const LATER_goto='4';
const LATER_fi='F';
const LATER_if='I';
const LATER_math='7';
const LATER_csv='8';
const LATER_end='X';
const LATER_pixel='A';
const LATER_solid='s';
const LATER_render='r';
const LATER_rotate='o';
const LATER_sub='J';
const LATER_digitalWrite='G';
const LATER_analogWrite='w';
const LATER_print='T';
const LATER_println='l';
const LATER_for='R';
const LATER_next='N';
const LATER_start='z';
const LATER_gosub='Y';
const LATER_timer='t';
const LATER_case='K';
const LATER_option='c';
const LATER_interval='i';
const LATER_sleep='S';
const LATER_pinMode='M';
const LATER_log='L';
const LATER_switch='W';
const LATER_ping='H';
const LATER_assert='k';
const LATER_break='B';
const LATER_call='h';
const LATER_cgi='j';
const LATER_clear='C';
const LATER_continue='O';
const LATER_default='U';
const LATER_delete='e';
const LATER_do='D';
const LATER_endsub='Q';
const LATER_exit='x';
const LATER_flash='3';
const LATER_freeze='f';
const LATER_grad='a';
const LATER_iif='b';
const LATER_json='5';
const LATER_loop='P';
const LATER_on='v';
const LATER_resume='1';
const LATER_return='Z';
const LATER_run='u';
const LATER_suspend='2';
const LATER_type='p';
const LATER_unload='q';


const COMMANDS_ENDING_WITH_LITERALS = [LATER_if, LATER_do, LATER_iif, LATER_freeze, LATER_sleep, LATER_goto, LATER_rotate, LATER_suspend, LATER_analogWrite, LATER_var, 0];

const COMMANDS_STARTING_WITH_LITERALS = [ LATER_interval, LATER_digitalWrite, LATER_analogWrite, LATER_for, LATER_sleep, 0];

const COMMANDS_NEEDING_OUTPUT = [ LATER_log, LATER_switch, LATER_print, LATER_println, LATER_ping, LATER_timer, LATER_assert, LATER_run, 0];

const COMMANDS_NEEDING_WHITESPACE = [LATER_gosub, LATER_call, LATER_interval, LATER_flash, LATER_option, LATER_json, LATER_csv,  0];



var LATER_CMDS =  {
  "_": 'l',
  "__": 'l',
  "analogWrite": 'w',
  "apply": '6',
  "assert": 'k',
  "attachInterrupt": 'v', // alias: on
  "break": 'B',
  "call": 'h',
  "case": 'K',
  "cgi": 'j',
  "clear": 'C',
  "continue": 'O',
  "csv": '8',
  "default": 'U',
  "define": 'd',
  "delete": 'e',
  "del": 'e',
  "delay": 'S',// alias: sleep
  "digitalWrite": 'G',
  "do": 'D',
  "else": 'E',
  "end": 'X',
  "endsub": 'Q',
  "erase": 'e',// alias: delete
  "exit": 'x',
  "fetch": 'H', //alias: ping
  "fi": 'F',
  "finish": 'x',
  "flash": '3',
  "for": 'R',
  "freeze": 'f',
  "global": 'm',
  "gosub": 'Y',
  "goto": '4',
  "gpio": 'G',// alias: digitalWrite
  "grad": 'a',
  "if": 'I',
  "iif": 'b',
  "int": 'V', // alias: var
  "interval": 'i',
  "json": '5',
  "log": 'L',
  "loop": 'P',
  "math": '7',
  "next": 'N',
  "noop": 'n',
  "on": 'v',
  "option": 'c',
  "ping": 'H',
  "pinMode": 'M',
  "print": 'T',
  "println": 'l',
  "pixel": 'A',
  "render": 'r',
  "resume": '1',
  "return": 'Z',
  "rotate": 'o',
  "run": 'u',
  "set": 'G',// alias: digitalWrite
  "show": 'r',
  "sleep": 'S',
  "solid": 's',
  "start": 'z',
  "static": 'd',
  "store": 'g',
  "sub": 'J',
  "suspend": '2',
  "switch": 'W',
  "timer": 't',
  "type": 'p',
  "unlink": 'e',// alias: delete
  "unload": 'q',
  "var": 'V',
  "wend": 'P',// alias: loop
  "write": 'G'// alias: digitalWrite
};



function clamp(a) {
  return a > 0 ? (a < 255 ? a : 255) : 0;
}





const FUNCS = {
  "SUM": (a, b, c=0) => a + b + c,
  "DIFF": (a, b, c=0) => a - b - c,
  "MULT": (a, b, c=1) => a * b * c,
  "DIV": (a, b, c=1) => a / b,
  "AND": (a, b, c=1) => a && b && c,
  "OR": (a, b, c=0) => a || b || c,
  "MIN": (a, b, c) => Math.min(a, b),
  "MAX": (a, b, c) => Math.max(a, b),
  "SQRT": (a, b, c) => Math.sqrt(a),
  "CBRT": (a, b, c) => Math.cbrt(a),
  "SIN": (a, b, c) => Math.sin(a),
  "TAN": (a, b, c) => Math.tan(a),
  "COS": (a, b, c) => Math.cos(a),
  "GPIO": (a, b, c) => digitalRead(a), // Assuming digitalRead is a defined JS function
  "ADC": (a, b, c) => analogRead(a),   // Assuming analogRead is a defined JS function
  "MED": (a, b, c) => (a > b ? ((a < c) ? a : (b < c ? c : b)) : ((b < c) ? b : (c < a ? a : c))),
  "MODE": (a, b, c) => (a == b ? a : (b == c ? b : a == c ? a : b)),
  "AVG": (a, b, c) => (a + b + (c || 0)) / 3,
  "CLAMP": (a, b, c) => (a > 0 ? (a < 255 ? a : 255) : 0),
  "POW": (a, b, c) => Math.pow(a, b),
  "MAP": (a, b, c) => (b / c) * a,
  "EQ": (a, b, c) => a == b,
  "NEQ": (a, b, c) => a != b,
  "MOD": (a, b, c) => a % b,
  "GT": (a, b, c) => a > b,
  "LT": (a, b, c) => a < b,
  "GTE": (a, b, c) => a >= b,
  "LTE": (a, b, c) => a <= b,
  "ID": (a, b, c) => a,
  "IIF": (a, b, c) => (a ? b : c),
  "ELSE": (a, b, c) => (a ? a : b),
  "AtBeC": (a, b, c) => (a ? b : c),
  "AtAeB": (a, b, c) => (a ? a : b),
  "AoBtAeC": (a, b, c) => ((a || b) ? a : c),
  "AoBtBeC": (a, b, c) => ((a || b) ? b : c),
  "AnBtAeC": (a, b, c) => (a && b ? a : c),
  "AnBtBeC": (a, b, c) => (a && b ? b : c),
  "NAND": (a, b, c) => !a || !b,
  "NOT": (a, b, c) => !a,
  "RGB": (a, b, c) => Adafruit_NeoPixel.Color(a, b, c), // Assuming Adafruit_NeoPixel is available
  "CRGB": (a, b, c) => Adafruit_NeoPixel.Color(clamp(a), clamp(b), clamp(c)), // Assuming Adafruit_NeoPixel and clamp are available
  "HSV": (a, b, c) => Adafruit_NeoPixel.ColorHSV(a, b, c), // Assuming Adafruit_NeoPixel is available
  "CSPRNG": (a, b, c) => (((randomReg()) % ((a + 1) - b)) + b), // Assuming randomReg is available
  "PRNG": (a, b, c) => ((Math.random() * ((a + 1) - b)) + b)
};



const Later = {
  debug: false,
  scriptCount: LATER_INSTANCES, // Assuming LATER_INSTANCES is defined
  currentScript: 0,
  loadedScripts: 0,
  lastEventSlot: -1,
  resumes: new Array(LATER_RESUME_LIMIT).fill(x=>new LATER_RESUME), // Assuming LATER_RESUME_LIMIT is defined
  started: false,
  httpResponseTextBuffer: new Array(LATER_HTTP_CACHE).fill(""), // Assuming LATER_HTTP_CACHE is defined
  httpResponseText: null,
  bootRam: 16666,
  addons: {}
};


function getCurrent() {
  return SCRIPTS[Later.currentScript];
} //end getCurrent()
function randomReg() {
  return Math.floor(Math.random() * Number.MAX_SAFE_INTEGER);
} // end randomReg()




Later.setup = function(){

  this.started = true;

  setRunLog[LATER_LOG_SIZE + 14] = '#';
  setRunLog[LATER_LOG_SIZE + 15] = '\0';

  bindServerMethods();

  this.bootRam = ESP.getFreeHeap();

  for (var i = 0; i < this.scriptCount; i++) {
    VAR_NAME_COUNT[i] = 3;
    SCRIPTS[i].index = i;
  }//next script
 
 
  loadStoredValuesForStore();

  if (this.debug) LATER_PRINTLN("Later - Setup()");
  /// this has to be added here so that it can use function prototype defined after the rest of the Functions
  Later.addFunction("DMA", function(a,b,c){return  getCurrent().VARS[a] = b;}); // using FUNCTION MACRO
  
  // run autoexec.bat if available
  if (SPIFFS.exists("/autoexec.bat")) {
    if (this.debug) LATER_PRINTLN("Later - Autoexec.bat will run");
    this.run("/autoexec.bat");
    if (this.debug) LATER_PRINTLN("Later - Autoexec.bat ran");
    this.unload("/autoexec.bat");
  }
  // run autoexec.lnk if available

  if (SPIFFS.exists("/autoexec.lnk")) {
    if (this.debug) LATER_PRINTLN("Later - Autoexec.lnk will run");
		
	 SPIFFS._readAll("/autoexec.lnk")
	     .trim().split(/\n/).filter(String)
		 .filter(/./.test, /\.bat$/)
		 .map(this.run);

    if (this.debug) LATER_PRINTLN("Later - Autoexec.lnk ran");
  }//end if autoexec.lnk?
}//end later setup()



Later.loop = function() {


 var ms = millis();

  for (var i = 0; i < Later.scriptCount; i++) {
    if (ms > SCRIPTS[i].resumeMillis) {
      // look for interval processes:
      if ( SCRIPTS[i].interval > 0) this.run(SCRIPTS[i].fileName);

      // look for frozen processes
      if (SCRIPTS[i].resumeMillis  ) this.run(SCRIPTS[i].fileName);
    }

  }//next i
  // look for suspended processes ready to resume:
  for (var i = 0; i < LATER_RESUME_LIMIT; i++) {
    if (Later.resumes[i].timestamp && (ms > Later.resumes[i].timestamp) ) {
      this.resume(Later.resumes[i].fileName);
    }
  }//next i

  // roll these loops

  // look for interupts here, from a table or something.
  for (var i = 0; i < LATER_EVENT_COUNT; i++) {
    var e = EVENT[i];
    if (e.pin != -1 && digitalRead(e.pin) != e.value) {
      // run script here and now, if loaded.
      this.run( SCRIPTS[e.programSlot].fileName  );
    }

  }//next i
};//end later loop()



Later.getByName = function(fileName){
 return SCRIPTS.find(x=>fileName==x.fileName && x.lineCount) || null;
};


Later.resume = x=>new Error("resume not implimented. yet?");
Later.suspend = x=>new Error("suspend not implimented. yet?");


Later.unload = function (fileName) {
  const s = this.getByName(fileName); // Assuming 'this' refers to an instance of a class with a 'getByName' method
  if (!s) return;

  this.lastFileName = ""; // Assuming 'this' has 'lastFileName' property

  if (s.lineCount != s.exitLineNumber && !s.isSuspended) {
    const oldScript = this.currentScript; // Assuming 'this' has 'currentScript' property
    this.currentScript = s.index;

    s.resumeLineNumber = s.exitLineNumber + 1;
    s.exitLineNumber = 0;
    this.runScript(); // Assuming 'this' has 'runScript' method
    this.currentScript = oldScript;
  }

  for (let i = 0; i < s.lineCount; i++) {
    s.lines[i].exit = 0;
    s.lines[i].data = 0;
    for (let j = 0; j < 11; j++) { 
      s.lines[i].exprCache[j] = 0;
    }
    
	if(typeof LATER_LINE_PROFILING !="undefined") {
    s.lines[i].profile = { count: 0, totalTime: 0, averageTime: 0 }; // Assuming profile is an object
	}
    
  }

  
  if(typeof LATER_CSV !="undefined")  s.csv.fn = "";
  
  this.loadedScripts--;
  s.fileName = "";
  s.program="";
  s.i = 0;
  s.resumeMillis = 0;
  s.interval = 0;
  s.counter = 0;
  s.TEMP_COUNT = 0;
  s.FUNC_COUNT = 0;
  s.LITS_COUNT = 2;
  s.startLineNumber = 0;
  s.resumeLineNumber = 0;
  s.exitLineNumber = 0;
  s.lineCount = 0;
  s.options.noget = 0;
  s.options.debug = 0;
  s.options.socket = 0;
  s.options.persist = 0;
  s.options.perf = 0;
  s.options.step = 0;
  s.options.strict = 0;
  s.forLevel = 0;
  s.intervalCount = 0;
  s.duration = 0;
  s.contentType = LATER_PLAIN; // Assuming LATER_PLAIN is a defined constant

  if (s.eventSlot > -1) {
    EVENT[s.eventSlot].pin = -1; // Assuming 'this' has 'EVENT' property (likely an array)
    EVENT[s.eventSlot].value = 0;
    EVENT[s.eventSlot].msNext = 0;
    EVENT[s.eventSlot].ms = 0;
    EVENT[s.eventSlot].programSlot = -1;
  }

  for (let i = 0; i < LATER_VARS_LENGTH; i++) { // Assuming LATER_VARS_LENGTH is a defined constant
    s.VARS[i] = 0;
  }

  CONSTANTS[s.index] = []; // Simulate clear for an array
  LATER_VAR_NAMES[s.index] = []; // Simulate clear for an array
  VAR_NAME_COUNT[s.index] = 3;
  
  
  if (this.debug) { // Assuming 'this' has 'debug' property
    console.log("Later - unloaded " + fileName); // Using console.log for LATER_PRINTLN
  }
};//end Later.unload()


Later.load = function (fileName) {
  let s = this.getByName(fileName); // Assuming 'this' refers to an instance of a class with a 'getByName' method
  if (s) return s;

//console.warn(s);


  const rez = loadScript(fileName); // Assuming 'this' has a 'loadScript' method
  if (!rez) {
    if (this.debug) { // Assuming 'this' has a 'debug' property
      console.log("Later - load failed1: " + fileName); // Using console.log for LATER_PRINTLN
    }
    return null;
  }

  s = this.getByName(fileName); // try again to get active script now that it's loaded
  if (!s) {
    if (this.debug) {
      console.log("Later - load failed2: " + fileName);
    }
    return null;
  }

  this.loadedScripts++; // Assuming 'this' has 'loadedScripts' property

  //VAR_NAME_COUNT[s.index] = 3; // Assuming 'this' has 'VAR_NAME_COUNT' property (likely an array)
  LATER_VAR_NAMES[s.index]["$DMA0"] = 0; // Assuming 'this' has 'LATER_VAR_NAMES' property (likely an array of objects/maps)
  LATER_VAR_NAMES[s.index]["$DMA1"] = 1;
  LATER_VAR_NAMES[s.index]["$DMA2"] = 2;

  s.duration = 0;
  s.calledFromWeb = 0;
  s.runs = 0;
  s.resumeLineNumber = 0;
  if (this.debug) {
    console.log("Later - loaded " + fileName);
  }
  return s;
};//end Later.load()


Later.run = function (fileName) {
  // find script in POOL, run, or load if not found;
  let s = this.getByName(fileName); 
  //
  
  if (!s)  s = this.load(fileName); // Assuming 'this' has a 'load' method
  if (!s) return null;

  this.currentScript = s.index; // Assuming 'this' has 'currentScript' property
  s.timer = 0; // Assuming 's' has 'timer' property
  runScript(); 

  if (!s.options.persist) { // Assuming 's' has 'options' property with 'persist'
  //  this.unload(s.fileName); // Assuming 'this' has 'unload' method
  }
}; // end Later.run()



Later.addFunction = function(commandName, callBack) {
  FUNCS[commandName] = callBack;
  return 1;
}; //end Later.addFunction()




function laterClassAddCommand(commandName, callBack) {
  if (this.started) { // Assuming 'this' refers to an instance of LaterClass with a 'started' property
    if (this.debug) { // Assuming 'this' has a 'debug' property
      console.log("ERROR!  .addCommand() cannot be called after .setup()"); // Using console.log for LATER_PRINTLN
    }
    return false;
  }

  const cmdChar = CMDCHARS.filter(x=>!LATER_CMDS[x])[0];
  console.log(`adding command [${cmdChar}:${commandName}] to known commands`); 
  LATER_CMDS[commandName] = cmdChar;
  this.addons[cmdChar] = callBack; // Assuming 'this' has an 'addons' property (likely an object/map)
  return true;
}//end Later.addCommand()


//#line 1 "commands.ino"


const laterUtil = {
  splits: new Array(24).fill(null),
  split_count: 0,
  indexedFileName: null,
  linePos: [],
  
  getFileLine: function(fn, line){
  	return SPIFFS._readAll(fn).split("\n")[line];  
  },

  intFromHexChar: function(c) {
    if (c >= '0' && c <= '9') return c.charCodeAt(0) - 48;
    if (c >= 'A' && c <= 'F') return (c.charCodeAt(0) - 64) + 10;
    if (c >= 'a' && c <= 'f') return (c.charCodeAt(0) - 96) + 10;
    return NaN; // Or handle invalid characters as needed
  },

  isTheSame: function(data, term) {
    if (!data || !term || data[0] !== term[0]) return false;
    return data === term; // Direct string comparison in JS
  },

  splitStringByChar: function(hay, term) {
    this.splits = hay.split(term);
    this.split_count = this.splits.length;
  },

  afterSubstring: function(str, needle) {
    if (!str || !needle) return null;
    const index = str.indexOf(needle);
    if (index === -1) return null;
    return str.substring(index + needle.length);
  },

  copyUntilChar: function(str, of) {
    if (!str) return "";
    const index = str.indexOf(of);
    if (index === -1) return str;
    return str.substring(0, index);
  },

  trimRight: function(str) {
    if (!str) return "";
    let i = str.length - 1;
    while (i >= 0 && str[i] === ' ') {
      i--;
    }
    return str.substring(0, i + 1);
  },

  trimLeft: function(str, aggressive = false) {
    if (!str) return "";
    let i = 0;
    if (!aggressive) {
      while (i < str.length && str[i] === ' ') {
        i++;
      }
    } else {
      while (i < str.length && /\s/.test(str[i])) {
        i++;
      }
    }
    return str.substring(i);
  },

  startsWith: function(hay, needle) {
    if (!hay || !needle) return false;
    return hay.startsWith(needle);
  },

  indexOf: function(base, term) {
    if (!base || !term) return -1;
    return base.indexOf(term);
  },

  replace: function(str, term, rep) {
    if (!str || !term || !rep) return str || "";
    return str.split(term).join(rep);
  },

  formatBytes: function(bytes) {
    if (bytes < 1024) {
      return bytes + "B";
    } else if (bytes < (1024 * 1024)) {
      return (bytes / 1024.0).toFixed(2) + "KB";
    } else if (bytes < (1024 * 1024 * 1024)) {
      return (bytes / 1024.0 / 1024.0).toFixed(2) + "MB";
    } else {
      return (bytes / 1024.0 / 1024.0 / 1024.0).toFixed(2) + "GB";
    }
  },

  fileToBuff: function(fileName) {
    return SPIFFS._readAll(fileName);
  },

  fileToBuffInclude: function(fileName) {
    return SPIFFS._readAll(fileName);
  },

  buffToFile: function(fileName, value, append) {
   SPIFFS._write(fileName, append ?  ( SPIFFS._readAll(fileName) + value)  : value);
  },

parseColor: function(ptr, s) {
  ptr = ptr.trim();
  const colorLength = ptr.length;
  let color;

  if (ptr[0] === '#') { // #ABC or #aabbcc or #AABBCC or #aabbcc
    if (colorLength === 4) {
      RGB_PIXEL.chan[1] = parseInt(ptr[1], 16) * 16;
      RGB_PIXEL.chan[2] = parseInt(ptr[2], 16) * 16;
      RGB_PIXEL.chan[3] = parseInt(ptr[3], 16) * 16;
      color = RGB_PIXEL.value;
    } else { // #AABBCC
      color = parseInt(ptr.substring(1), 16);
    }
  } else { // number or r,g,b
    const commaPos = ptr.indexOf(",");
    if (commaPos > 0) { // $r, $g, $b
	  let c=ptr.split(",");
      RGB_PIXEL.chan[1] = s.Number(c[0]);
      RGB_PIXEL.chan[2] = s.Number(c[1]);
      RGB_PIXEL.chan[3] = s.Number(c[2]);
      color = RGB_PIXEL.value; //LATER_PIXEL_NAME.Color(r, g, b);
    } else { // no comma, just a big long
      color = s.Number(ptr);
    }
  }
  return color;
}

};// end laterUtil namepsace




const laterCMD = {


  runPinMode: function(line) {
    const parts = line.split(',');
    if (parts.length < 2) return;

    const pinStr = parts[0].trim();
    let modeStr = parts[1].trim();
    const spaceIndex = modeStr.indexOf(' ');
    if (spaceIndex !== -1) {
1
    }

    const pin = parseInt(pinStr, 10);

    if (modeStr === "OUTPUT") {
      pinMode(pin, OUTPUT); // Assuming pinMode and OUTPUT are defined
      return;
    }
    if (modeStr === "INPUT") {
      pinMode(pin, INPUT); // Assuming INPUT is defined
      return;
    }
    if (modeStr === "INPUT_PULLUP") {
      pinMode(pin, INPUT_PULLUP); // Assuming INPUT_PULLUP is defined
      return;
    }
  },

  runPortWrite: function(line, VARS, isDigital) {
    const parts = line.split(',');
    if (parts.length < 2) return;

    const pinStr = parts[0].trim();
    const valueStr = parts[1].trim();

    const pin = NumberJS(pinStr, VARS);
    const value = NumberJS(valueStr, VARS);

    if (isDigital) {
      digitalWrite(pin, value); // Assuming digitalWrite and Number are defined
    } else {
      analogWrite(pin, value); // Assuming analogWrite and Number are defined
    }
  },

  compositeLine: function(linebuff, s) {
    linebuff= replaceVarNames(linebuff, s.index); 
    linebuff=processTemplateExpressions2(linebuff, s); 
    linebuff=processVariableExpressions(linebuff, s.VARS); 
    linebuff=evalMath(linebuff, s, -1);
	return linebuff;
  },

  runCGI: function(lb, s) {
    const buff = laterUtil.fileToBuff(lb); // Assuming laterUtil is defined
    let p = buff;
    let len = 0;
    const linebuff = this.LINE_BUFF || new Array(16).fill('\0').join(''); // Assuming LINE_BUFF is a property or constant
    let nextLine;

    while ((nextLine = p.indexOf('\n')) !== -1) {
      len = nextLine - p;
      const currentLine = p.substring(0, len);
      // Simulate strncpy
      let tempLinebuff = '';
      for (let i = 0; i < Math.min(len, linebuff.length - 1); i++) {
        tempLinebuff += currentLine[i];
      }
      while (tempLinebuff.length < linebuff.length) {
        tempLinebuff += '\0';
      }
      this.compositeLine(tempLinebuff, s);
      if (tempLinebuff.trim().length > 0) {
        uniPrintln(tempLinebuff); // Assuming 'this' has uniPrintln
      }
      p = buff.substring(nextLine + 1);
    }
  },


//$x =555
//assert  ($x = 555) -> var assign literal

  runAssert: function(lb, l, s) {
  
  
    const rez = NumberJS(lb, s.VARS); // Assuming 'this' has Number
	console.info("assert:", lb, rez);
	
	
	
    uniPrint(rez ? "PASS: " : "FAIL: "); // Assuming 'this' has uniPrint
    let p2 = lb.indexOf("->");
    if (p2 !== -1) {
      p2 += 2;
      while (p2 < lb.length && lb[p2] === ' ') {
        p2++;
      }
      uniPrint(lb.substring(p2));
    }
    uniPrint(" :: ");

    if (!rez) {
      let lp;
      const linebuff = this.LINE_BUFF || new Array(36).fill('\0').join(''); // Assuming LINE_BUFF
      const programLine = s.program.substring(l.start, l.start + l.len);
      // Simulate strncpy
      let tempLinebuff = '';
      for (let i = 0; i < Math.min(l.len, linebuff.length - 1); i++) {
        tempLinebuff += programLine[i];
      }
      while (tempLinebuff.length < linebuff.length) {
        tempLinebuff += '\0';
      }

      lp = tempLinebuff.indexOf("->");
      if (lp !== -1) tempLinebuff = tempLinebuff.substring(0, lp);
      if (tempLinebuff.length > 0 && tempLinebuff[tempLinebuff.length - 1] === '-') {
        tempLinebuff = tempLinebuff.substring(0, tempLinebuff.length - 1);
      }
      tempLinebuff += "=";

      const arrowIndex = lb.indexOf("->");
      let assertValue = lb;
      if (arrowIndex !== -1) {
        assertValue = lb.substring(0, arrowIndex);
      }
      assertValue = assertValue.trim();
      tempLinebuff += assertValue;
      let len = tempLinebuff.length;
      if (len > 0 && tempLinebuff[len - 1] === ' ') tempLinebuff = tempLinebuff.substring(0, len - 1);

      const varPtrIndex = tempLinebuff.indexOf('@');
      if (varPtrIndex !== -1) {
        tempLinebuff += "; @";
        len = tempLinebuff.length;
        const varName = tempLinebuff[varPtrIndex + 1];
        const varIndex = varName.charCodeAt(0) - 65; // Assuming A=0, B=1, etc.
        tempLinebuff += varName + "=" + (s.VARS[varIndex] || 0);
      }
      uniPrintln(tempLinebuff);
    } else {
      uniPrintln("-");
    }
	

  },

  logMe: function(line) {
   if (setRunLog.length  > LATER_LOG_SIZE) setRunLog = setRunLog.slice(200) + "\n";
   setRunLog+= `${millis()}\t${line}\n`;
  },

};


function uniPrintln(text){
  var s = getCurrent();  
  if (s.calledFromWeb) {
    LATER_SERVER_NAME.sendContent(text);
    LATER_SERVER_NAME.sendContent("\n");
  } else {
    console.log(text);
	stats.innerHTML+=text + "<br>";
  }  
}

function uniPrint(text){
  var s = getCurrent();  
  if (s.calledFromWeb) {
    LATER_SERVER_NAME.sendContent(text);
  } else {
    console.log(text);
	stats.innerHTML+= text;
  }  
}



const LATER_STORE = {
  fileName: "/store.ini",
  items: Array(24).fill(null).map(() => ({ dt: 0, value: 0, ver: 0, key: Array(16).fill('\0').join('') })),
  time: 0,
  length: 0,
  loaded: false,

  getIndex: function(key) {
    if (!this.loaded) this.load();
    for (let i = 0; i < this.length; i++) {
      if (this.items[i].key === key) return i;
    }
    return -1;
  },

  get: function(key) {
    const index = this.getIndex(key);
    if (index === -1) return 0;
    return this.items[index].value;
  },

  match: function(key) {
    // Placeholder - functionality not fully defined in C++
    return 0;
  },

  set: function(key, value) {
    let index = this.getIndex(key);
    if (index === -1) {
      index = this.length++;
    }
    if (index > 23) return false;
    this.items[index].value = value;
    this.items[index].dt = this.time = this.getTime(); // Assuming getTime() provides the current time
    this.items[index].ver++;
    this.items[index].key = key;
    this.save();
    return true;
  },

  update: function(key, value) {
    let index = this.getIndex(key);
    if (index === -1) {
      index = this.length++;
    }
    if (index > 23) return false;
    this.items[index].value = value;
    this.items[index].dt = this.time = this.getTime(); // Assuming getTime() provides the current time
    this.items[index].ver++;
    this.items[index].key = key;
    return true;
  },

  unset: function(key) {
    const index = this.getIndex(key);
    if (index === -1) return false;
    this.length--;
    this.items[index].value = 0;
    this.items[index].dt = 0;
    this.items[index].ver = 0;
    this.save();
    return true;
  },

  stringify: function(index) {
    const it = this.items[index];
    return `${it.key}\t${it.dt}\t${it.ver}\t${it.value}`;
  },

  save: function() {
    let output = "";
    for (let i = 0; i < 24; i++) {
      const it = this.items[i];
      if (it.ver > 0) {
        output += this.stringify(i) + "\n";
      }
    }
	SPIFFS._write(this.fileName, output);
    return true;
  },

  load: function() {
    if (this.loaded) return false;
    this.loaded = true;
    this.length = 0;
    this.items = Array(24).fill(null).map(() => ({ dt: 0, value: 0, ver: 0, key: "" })); // Reset items

    const mockData =SPIFFS._readAll(this.fileName).split("\n");

    for (const line of mockData) {
      const parts = line.split('\t');
      if (parts.length === 4) {
        const it = this.items[this.length++];
        it.key = parts[0];
        it.dt = parseInt(parts[1], 10);
        it.ver = parseInt(parts[2], 10);
        it.value = parseInt(parts[3], 10);
      }
      if (this.length >= 24) break;
    }

    return true;
  },

  // Helper function to simulate getting the current time (you might replace this)
  getTime: function() {
    return Date.now();
  }
};

function loadStoredValuesForStore() {
  LATER_STORE.load();
}

function evalLite(lb, s) {
  lb=lb.replace(/\s+/g,"");
  
  //console.warn("evalLite:", lb);
  
  var r = lb.split(/([+\-\/\*%^\|&=\!<>])/g);
  
  let varChar;
  let tempInt = s.Number(r[0]);
  let varCache;
  let i = 1;
  
  while (i < r.length && varCache !== tempInt) {
    varCache = tempInt;
    varChar = r[i++];
	
    const varTemp = s.Number(r[i++] || "");

//console.info({lb, varTemp, nextNumStr, varChar, varCache, tempInt});

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
      case '!': tempInt = (tempInt != varTemp) ? 1 : 0; break;
      case '<': tempInt = (tempInt < varTemp) ? 1 : 0; break;
      case '>': tempInt = (tempInt > varTemp) ? 1 : 0; break;
    }
  }
  return tempInt;
}


let currentCsvState = null;

function getCSV(codeLine, s) {
  let state = currentCsvState || new CsvState();
  let varPtr;



  if (state.fn) { // Re-call, just re-assign line number:
    if (state.hasLineParam) {
      varPtr = laterUtil.afterSubstring(codeLine, "line=");
      if (varPtr) state.lineNeeded = Number(varPtr, s.VARS);
    } else {
      state.lineNeeded++;
    }
    currentCsvState = state;
    return state;
  }

  // Init:
  varPtr = laterUtil.afterSubstring(codeLine, "line=");
  
  
if (varPtr) {

    state.lineNeeded = s.Number(varPtr);
    state.hasLineParam = true;
  }
  varPtr = laterUtil.afterSubstring(codeLine, "file=");
  if (varPtr) state.fn = varPtr.substring(0, 35);
  varPtr = laterUtil.afterSubstring(codeLine, "filter=");
  if (varPtr) state.filter = varPtr.substring(0, 35);
  varPtr = laterUtil.afterSubstring(codeLine, "delim=");
  if (varPtr) state.delim = varPtr[0];
  varPtr = laterUtil.afterSubstring(codeLine, "skip=");
  if (varPtr) state.skip = Number(varPtr, s.VARS);
  varPtr = laterUtil.afterSubstring(codeLine, "block=");
  if (varPtr) state.blockSize = Number(varPtr, s.VARS);
  varPtr = laterUtil.afterSubstring(codeLine, "more=@");
  if (varPtr) state.morePointer = varPtr.charCodeAt(0) - 65;

  if (!state.hasLineParam) state.blockSize = 2; // Auto mode

  state.delimStr = state.delim;
  state.varSlots.fill(0);

  let spcPtrIndex = state.fn.indexOf(' ');
  if (spcPtrIndex !== -1) state.fn = state.fn.substring(0, spcPtrIndex);

  spcPtrIndex = state.filter.indexOf(' ');
  if (spcPtrIndex !== -1) state.filter = state.filter.substring(0, spcPtrIndex);

  let slotNumber = 0;
  varPtr = laterUtil.afterSubstring(codeLine, "vars=");
  if (!varPtr) varPtr = "AUTO";

  if (varPtr === "AUTO") { // Pull var names from data source for templating
    varPtr = laterUtil.getFileLine(state.fn, 0);
    const nameBuffer = ['$', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '']; // Simulate char array

    while (varPtr) { // Find comma, and copy before it into buffer, trimming as needed and adding a $
      if (varPtr[0] === state.delim) varPtr = varPtr.substring(1);
      while (varPtr[0] === ' ') varPtr = varPtr.substring(1);

      let len = varPtr.indexOf(state.delimStr);
      if (len === -1) len = varPtr.length;
      const segment = varPtr.substring(0, len);
      nameBuffer[1] = segment;
      nameBuffer.length = segment.length + 2; // Adjust length

      state.varSlots[slotNumber] = getVarNameNumber(nameBuffer.join(''), s.index);
	  
      slotNumber++;
      let nextDelimIndex = varPtr.indexOf(state.delim);
      if (nextDelimIndex === -1) {
        varPtr = null;
      } else {
        varPtr = varPtr.substring(nextDelimIndex + 1);
      }
    }

    // Handle the last one (if any) after the loop
    const lastVarPtr = laterUtil.getFileLine(state.fn, 0);
    if (lastVarPtr && lastVarPtr.lastIndexOf(state.delim) !== lastVarPtr.length - 1) {
      const parts = lastVarPtr.split(state.delim);
      if (parts.length > slotNumber) {
        const lastPart = parts[slotNumber].trim();
        if (lastPart) {
          nameBuffer[1] = lastPart;
          nameBuffer.length = lastPart.length + 2;
          state.varSlots[slotNumber] = getVarNameNumber(nameBuffer.join(''), s.index);
        }
      }
    }

  } else { // Hard-coded vars for templating
    let spacePtrIndex = varPtr.indexOf(' ');

    while (varPtr) {
      if (varPtr[0] === '@' && varPtr.length > 1) {
        state.varSlots[slotNumber] = varPtr.charCodeAt(1) - 65;
        slotNumber++;
      }
      let nextAtIndex = varPtr.indexOf('@', 1);
      if (nextAtIndex === -1) {
        varPtr = null;
      } else {
        varPtr = varPtr.substring(nextAtIndex);
        if (spacePtrIndex !== -1 && nextAtIndex > spacePtrIndex) break;
      }
    }
  }

  currentCsvState = state;
  return state;
} //end getCSV()





// #line 1 "core.ino"
function NumberJS( str="", VARS) {
  //unsigned long theNumber;
  str=str.trimLeft();

  if (str[0] == '@' ) { //&& str[2] == '_') {
    return  VARS[str[1].charCodeAt(0) - 65];
  } else {
    if (str[0] == '{') {
      return processTemplateExpressionsNumber(str);
    } else {
      return parseInt(str, 10); // atoi(str);
    }
  }// end if var format?
  return 0; // failsafe
}//end NumberJS()

function getVarName(longName, scriptIndex) {

  var buffer = "";  
  var  hit  = LATER_VAR_NAMES[scriptIndex][longName] ;

  if (hit != null) {
    buffer = "@" + String.fromCharCode(hit + 65);
  } else {
    if ( VAR_NAME_COUNT[scriptIndex] >= LATER_VARS_LENGTH) {
      VAR_NAME_COUNT[scriptIndex] = LATER_VARS_LENGTH;
    } else {
      if (VAR_NAME_COUNT[scriptIndex] > 25 && VAR_NAME_COUNT[scriptIndex] < 31) {
        VAR_NAME_COUNT[scriptIndex] = 32;
      }
      buffer  ="@" + String.fromCharCode((LATER_VAR_NAMES[scriptIndex][longName] = VAR_NAME_COUNT[scriptIndex]++ ) + 65);
    }

  }
  //console.info("assigning ", [longName], " to ", buffer ); 
  return buffer;
}

function getConstantNumber(valueString,  s, res = -1) {
  var slot = LATER_VARS_LENGTH - s.LITS_COUNT++;
  var value = res != -1 ? res :  parseInt(valueString, 10);
  if (value == 0) return LATER_VARS_LENGTH - 1;

  for (var i = slot; i < LATER_VARS_LENGTH; i++) {
    if (s.VARS[i] == value) {
      s.LITS_COUNT--;
      slot = i;
      break;
    }
  }
  s.VARS[slot] = value;
  return slot;
}

function getVarNameNumber(longName, scriptIndex) {
  var hit = LATER_VAR_NAMES[scriptIndex][longName];
  if (hit != null) return hit;
  return LATER_VAR_NAMES[scriptIndex][longName] = ++VAR_NAME_COUNT[scriptIndex];
}


function getVarLongname(symb, scriptIndex) {
  if(/[a-z]/i.test(symb)) symb = symb.charCodeAt(0) - 65;
  
  var o = Object.entries(LATER_VAR_NAMES[scriptIndex]);
  
  var hit = o.find(x=>x[1]==symb);
  if (hit) return hit[0];
  return "";
}



function removeDoubleLines(buff) {
  // replace double lines with single, repeat if needed
  return buff.replace(/\n\n/g,"\n");
}//end removeDoubleLines()

function removeMultiLineComments(buff) { // remove multi line comments by turning span into single-line comments w/o re-sizing buffer
  var mlcPos = buff.indexOf("/*");
  if (mlcPos > -1) {
    var mlcEndPos = buff.indexOf("*/");
    if (mlcEndPos > -1) {
		buff= buff.slice(0,mlcPos )+buff.slice(mlcEndPos+2);
    }//end if closing comment?
  }//end if multi-line comment?
  return buff;
}

function replaceEndingLiterals(line, s) {
  return line.replace(/(\d{2,})\s*$/g, function(j,n){
  	var symb = getConstantNumber(n, s) + 65;
      return '@' + String.fromCharCode(symb);	  
  });
}// end replaceEndingLiterals()


function replaceAllLiterals(line, s) {
  return line.replace(/(\d{2,})/g, function(j,n){
  	var symb = getConstantNumber(n, s) + 65;
      return '@' + String.fromCharCode(symb);	  
  });
}// end replaceAllLiterals()

function replaceVarNames(line, scriptIndex) { // turns $fancyName into @a, 
  return line.replace(/(\$[\w\.]+)/g, function(j,n){
  	var symb = getVarName(n, scriptIndex);
      return symb;  
  });
}//end replaceVarNames()




function autoEqualsInsert (line) { // inserts '=' into any line not having one after the command (first "word" in line)
  return line.trimLeft().replace(/^(\w+)\s*=?/,"$1=");
}//end autoEqualsInsert()


function buildExitPoints(SCRIPT) {
  const whole = SCRIPT.lines;
  const mx = SCRIPT.lineCount;
  let k, v, c;
  c = SCRIPT.program || ""; // prevent un-init error

  // compute Exit points for each line:
  for (let index = 0; index < mx; index++) {
    const line = whole[index];
    switch (line.cmd) {
      case LATER_if: // if
        for (let i = index + 1, need = 1; i < mx; i++) {
          const x = whole[i];
          if (x.cmd === LATER_fi) need--;
          if (x.cmd === LATER_else && need === 1) need--;
          if (x.cmd === LATER_if) need++;
          if (need === 0) {
            line.exit = i;
            break;
          }
        }
        break;

      case LATER_iif: // iif
        line.exit = index + 1;
        break;

      case LATER_else: // else
        for (let i = index + 1, need = 1; i < mx; i++) {
          const x = whole[i];
          if (x.cmd === LATER_fi) need--;
          if (x.cmd === LATER_if) need++;
          if (need === 0) {
            line.exit = i;
            break;
          }
        }
        break;

      case LATER_for:
      case LATER_continue: // for
        for (let i = index + 1, need = 1; i < mx; i++) {
          const x = whole[i];
          if (x.cmd === LATER_next) need--;
          if (x.cmd === LATER_for) need++;
          if (need === 0) {
            line.exit = i;
            break;
          }
        }
        break;

      case LATER_do: // do
        for (let i = index + 1, need = 1; i < mx; i++) {
          const x = whole[i];
          if (x.cmd === LATER_loop) need--;
          if (need === 0) {
            line.exit = i;
            break;
          }
        }
        break;

      case LATER_switch: // switch
        for (let i = index + 1; i < mx; i++) {
          const x = whole[i];
          if (x.cmd === LATER_end) { // end
            line.exit = i;
            break;
          }
        }
        break;

      case LATER_case: // case
        for (let i = index + 1; i < mx; i++) {
          const x = whole[i];
          if (x.cmd === LATER_case || x.cmd === LATER_default || x.cmd === LATER_end) { // case, default, or end
            line.exit = i - 1;
            break;
          }
        }
        break;

      case LATER_break: // break, exits do loop (not needed w/ case since there's no fall-through)
        for (let i = index + 1, need = 1; i < mx; i++) {
          const x = whole[i];
          if (x.cmd === LATER_loop) need--;
          if (x.cmd === LATER_do) need++;
          if (need === 0) {
            line.exit = i;
            break;
          }
        }
        break;

      case LATER_next: // next, go to for
        for (let i = index - 1, need = 1; i > 0; i--) {
          const x = whole[i];
          if (x.cmd === LATER_next) need++;
          if (x.cmd === LATER_for) need--;
          if (need === 0) {
            line.exit = i;
            break;
          }
        }
        break;

      case LATER_loop: // loop
	  
        for (let i = index - 1, need = 1; i > 0; i--) {
          const x = whole[i];
          if (x.cmd === LATER_loop) need++;
          if (x.cmd === LATER_do) need--;
          if (need === 0) {
            line.exit = i - 1 ;
            break;
          }
        }
        break;

      case LATER_sub:
      case LATER_return: // subroutine
        for (let i = index + 1, need = 1; i < mx; i++) {
          const x = whole[i];
          if (x.cmd === LATER_endsub) need--;
          if (need === 0) {
            line.exit = i;
            break;
          }
        }
        break;

      case LATER_gosub:
      case LATER_on:
      case LATER_interval: // sub finder by name
        k = SCRIPT.program.substring(line.start);
        let varCache = 0;

        //cut in here and scoot k down if it's an on call instead of gosub
        if (line.cmd === LATER_on) { // set line.data to edge type, and line.exit to subroutine start
          k = k.substring(k.indexOf(',') + 1).trimStart(); // find 1st comma, 2nd arg (sub name)
          while (k[0] && !/[a-zA-Z0-9]/.test(k[0])) k = k.substring(1); // advance to subname start
          line.data = 0;
          let vIndex = k.indexOf(','); // 3rd argument (event type)?
          if (vIndex !== -1) {
            varCache = 1; // flag as spoilt with 3rd arg, or maybe used line.data, duh
            c = k[vIndex];
            v = k.substring(vIndex + 1).trimStart();
            while (v[0] && !/[a-zA-Z0-9]/.test(v[0])) v = v.substring(1);
            // set line.data with type of interrupt
            if (v.startsWith("RISING")) line.data = 1;
            if (v.startsWith("FALLING")) line.data = 2;
            k = SCRIPT.program.substring(line.start).substring(SCRIPT.program.substring(line.start).indexOf(',') + 1);
          }
        } //end if on?

        // if it's an interval call instead of gosub, to set line.data to intervals count
        if (line.cmd === LATER_interval) {
          line.data = SCRIPT.intervalCount++;
          k = SCRIPT.program.substring(line.start).substring(SCRIPT.program.substring(line.start).indexOf(',') + 1).trimStart();
          while (k[0] && !/[a-zA-Z0-9]/.test(k[0])) k = k.substring(1); // trim?
        }

        v = k;
        while (v[0] && /[a-zA-Z0-9]/.test(v[0])) v = v.substring(1);
        const ind = v.length ? k.length - v.length : k.length;

        for (let i = index - 1; i > 0; i--) {
          const x = whole[i];
          if (x.cmd === LATER_sub) {
            const subName = SCRIPT.program.substring(x.start);
            if (k.startsWith(subName) && k.substring(subName.length).length === 0) {
              line.exit = i;
              break;
            }
          } //end if sub dec line?
        } //next

        // cleanup injected null terminator (not really needed in JS)
        break;

      case LATER_call: // sub finder by name
        k = SCRIPT.program.slice(line.start, line.stop);
		var ok = k;
        k = k.substring(k.indexOf('=') + 1).trimStart(); // find 1st '=', 2nd arg (sub name)
        while (k[0] && !/[a-zA-Z0-9]/.test(k[0])) k = k.substring(1); // advance to subname start
        v = k;
        while (v[0] && /[a-zA-Z0-9]/.test(v[0])) v = v.substring(1); // v is end of sub name
        const varCacheCall = v[0];
        const indCall = v.length ? k.length - v.length : k.length;

       if (varCacheCall === ' ' || varCacheCall === ',') line.data = ok.indexOf(v); // Approximate argument count

        const subNameToFind = k.substring(0, indCall);

        for (let i = index - 1; i > 0; i--) {
          const x = whole[i];
          if (x.cmd === LATER_sub) {
            const subName = SCRIPT.program.substring(x.start);
            if (subNameToFind === subName) {
              line.exit = i;
              break;
            }
          } //end if sub dec line?
        } //next
        break;
    } //end switch()
  } //next line
} //end buildExitPoints()

function processVariableExpressions(line, VARS) {// composites var values into literals for output
 return line.replace(/(@\w)/g, function(j,a){
  return NumberJS(a, VARS); 
 }); 
}//end processVariableExpressions()

function processArray(line,  s, varSlot){
  var p = line.split("][");
  var delim = ",";
  var rx = /\[.+\]/;
  p[0]=p[0].slice(p[0].indexOf("[")+1);
  
  if (p[0][0] == '&' && p[0][2] == ';') {
   delim = p[0][1];
   p[0]=p[0].slice(3);
  }

// handle lookup mode:
  var lookupMode = p[1][0].replace(/[^<>&=]/g,"") || "";
  if(lookupMode) p[1] = p[1].slice(lookupMode.length);

  var index = s.Number(p[1]);
  var elms = p[0].split(delim);
  if(delim-0.1) elms = p[0].match(RegExp(`.{${delim}}`, "g")); // fixed-width mode
  
  if(!lookupMode) return line.replace(rx, elms[index]);
  
  var ret;
  switch(lookupMode){
  	case ">": ret= elms.find(x=>x>index);break;
	case "<": ret= elms.find(x=>x<index);break;
	case "&": ret= elms.findIndex(x=>x==index)+1; break;
	case "=": ret= elms.filter(x=>x==index).length; break;	
  }
   return line.replace(rx, ret);   
}//end processArray()

function evalMath(lb, s, DMA){
   var rxfn= /(\w+)\(/, rxParens = /\(.+\)/;
   
   if(rxfn.test(lb)){ // handle function calls:
      let fn = lb.match(rxfn)[0].slice(0,-1);
	  fn = FUNCS[fn];
	  let args = String(lb.match(rxParens)).slice(1,-1).trim()
	               .split(/\s*,\s*/)
				   .filter(String)
				   .map(x=>s.Number(x));	  
	  if(fn) return lb.replace(rxfn, "(").replace(rxParens,  fn.apply(s, args  ));
	  return lb.replace(rxfn, "(").replace(rxParens, 0);
   }
  // return lb.replace(rxParens, evalLite(lb, s) || 0);
  
  
   return lb.replace(rxParens, function(j){
     j= j.slice(1,-1);
	 
     if(/^[+\-*\/%^]/.test(j)){
	 	return eval(   j.slice(1).trim().split(/\s*,\s*/)
		  .map(s.Number, s)
		  .join(j[0])    );
	 }   
   	 return evalLite(j, s) || 0;
	});
   
} // end evalMath()



function evalConditionalExpression(string_condition, s) {
 string_condition = string_condition.trim();
 var shouldInvert = string_condition[0] == '!';
 if(shouldInvert) string_condition = string_condition.slice(1);
 var ret = evalLite(string_condition, s);
 return shouldInvert ? !ret : ret;
} // end evalConditionalExpression()


// skip over a coupld http functions, TODO: implemetn http
function popHttpResponse(){}
function processResponseEmbeds(){}


function processStringFormats(str, index = 0){
    var rx = /<#(\w+)([\w\W]+?)#>/g;
	return str.replace(rx, function(w,tag, data){
		switch(tag){
		  case "escape": return escape(data) ;break;
		  case "upper": return data.toUpperCase();break;
		  case "lower": return data.toLowerCase();break;
		  case "trim": return data.trim();break;
		  case "hex": return SCRIPTS[index].Number(data).toString(16); break;
		  case "pad":
		  	    var amt = (tag[3] - 48) - data.length;
      			var filler = tag[4] || " ";
				return filler.repeat(amt) + data;
				break;
		  case "def": return DEFINES[index][data.trim()]; break;
		}
	});
}//end processStringFormats()


function outputPaddedNumber(){} // skpip for now, TODO: http report stuff

function finishRun(s) {
// s.startedAt = performance.now() * 1000; // micros()
  s.runTime = (performance.now() * 1000) - s.startedAt; // Convert ms to microseconds
  s.duration += s.runTime;
  s.resumeLineNumber = s.startLineNumber;
  s.storeDirty = 0;
  s.calledFromWeb = 0;
  if (s.interval > 0) {
    s.resumeMillis = (s.interval - 1) + millis();
  } else {
    s.resumeMillis = 0;
  }
}//ennd finishRun()

//#line 1 "docs.ino"
//#line 1 "http.ino"
// skipping ALL the HTTP server methods, for now. TODO: http server methods?
//#line 1 "loader.ino"














var parserLinesTried = 0;



function loadScript(scriptFileName) { // dd666 make this a class method
  const st = micros(); 
  
    var fileBuff = " \n"+laterUtil.fileToBuff(scriptFileName);
    var clean = ""; //new Array(LATER_PROGRAM_SIZE).fill('\0').join('');
    let outptr = 0;
    let cleanptr = 0;
    let lb = fileBuff;

    // stuff for lines:
    var line = "";// new Array(LATER_LINE_BUFFER).fill('\0').join('');
    var cmd = ""; //new Array(16).fill('\0').join('');
    var consts = "0000000000000000";

    let lineCount = 0;
    let endpos = lb.indexOf('\n');
    if (endpos === -1) endpos = lb.length;
    let lineLen = 0;
    let isPrintBlock = false;
    let isStaticPrintBlock = false;
    let isConstant = false;
    let lineData = 0;
    let scriptIndex = -1;

    // find empty slot index:
    for (let i = 0; i < LATER_INSTANCES; i++) {
      if (SCRIPTS[i].lineCount === 0) {
        scriptIndex = i;
        break;
      }
    }

    if (scriptIndex === -1) {
      console.error("No empty script slot available.");
      return 0;
    }

    const SCRIPT = SCRIPTS[scriptIndex];
    SCRIPT.loadedAt = Date.now(); // millis() equivalent
    SCRIPT.i = 0;
    SCRIPT.fileName = scriptFileName;
    laterUtil.trimLeft(fileBuff, true);



    // replace #includes
    fileBuff = replaceIncludes(fileBuff);

    // replace special macros like __FILENAME__ and __SKETCH_FILE__
    fileBuff = replaceSpecialMacros(fileBuff, scriptFileName);

    // look for #type special macro
    fileBuff = sniffContentType(fileBuff, SCRIPT);

    // parse out #define calls and populate replacement mappings
   
	fileBuff = populateDefines(fileBuff, scriptIndex);
	
	
    // de-inline multiple var assignments
    if (fileBuff.includes(", $") || fileBuff.includes(",$")) {
   //   fileBuff = deInlineVarAssignments(fileBuff);
    }

    removeMultiLineComments(fileBuff);
    removeDoubleLines(fileBuff);
    ///////////////////////////////////////////////////////
    //    Parse program into lines
	
	lb = fileBuff;
	endpos = lb.indexOf('\n');
	
    while (lb.length > 1) {
      const profileStart = performance.now() * 1000; // LATER_LINE_PROFILING

	if(parserLinesTried++ > 133) throw "too many lines parsed";

      lineData = 0;
      isConstant = false;
      const currentConsts = consts.slice(); // Create a copy

      // copy program code into line buffer so we can mess it up
      let currentLine = lb.substring(0, endpos);
      //while (currentLine.length < line.length - 1) currentLine += '\0';



      if (endpos === 0 && !isPrintBlock) {
        currentLine = "' ";
      }

      if (endpos === 0 && isPrintBlock)  currentLine += ' ';

	if (!isPrintBlock) currentLine = laterUtil.trimRight(currentLine);
      





	  // convert IIF commands into 2-line operations:
      //var ret = convertIIFs(currentLine, lb, endpos);
	  //lb = ret.lb;
	  //currentLine = ret.line;      
	  
	  // still TODO: gix iif commands
	//  var ret = convertIIFs(currentLine, lb, endpos);
	  //  currentLine = ret.line;      
	  
	  
      endpos = lb.indexOf('\n');
      if (endpos === -1) endpos = lb.length;
		lb = lb.slice(endpos+1);

// dd adding this in here in js version,
endpos = lb.indexOf('\n');
      if (endpos === -1) endpos = lb.length;
currentLine = lb.substring(0, endpos);




      if (!isPrintBlock) { // trim left spaces and tabs on line
	  	currentLine = currentLine.trimLeft();
      }

	 cmd = currentLine.trim().split(/[=\s]/)[0];
	
      currentLine = removeSingleLineComments(currentLine, cmd);
	  
      if (!isStaticPrintBlock) currentLine = currentLine.trimRight();
      lineLen = currentLine.length;
      ///////
	  
///////////////////////////////////
	  
      if (lineLen > 0 || isStaticPrintBlock) { // filter empty lines

        currentLine = harvestMacros(currentLine, scriptIndex);
		
		
        currentLine = cleanupVarDeclarations(currentLine);
		
		
		
        if (currentLine[0] === ':') {
          if (lineLen === 1) {
            continue;
          }
          laterUtil.replace(currentLine, ":", "noop=:"); // turn labels into noops
        }
		
		


        currentLine = expandRangeOperators(currentLine, SCRIPT);
        if (currentLine[0] === '&' && laterUtil.startsWith(currentLine, "&RESPONSE->")) laterUtil.replace(currentLine, "&RESPONSE->", "res=&RESPONSE->");
        currentLine = replaceEndCommands(currentLine); // handle block endings like end if, , etc




        lineLen = currentLine.length;

        if (currentLine[0] === '<' && currentLine[1] === '?') {
          isPrintBlock = true;
          if (currentLine[2] === '=') {
            currentLine = currentLine.substring(0, 2) + ' ' + currentLine.substring(3);
            isStaticPrintBlock = true;
          }
          currentLine = '_' + '=' + currentLine.substring(2);
          continue;
        }

        if (currentLine[0] === '?' && currentLine[1] === '>') {
          isPrintBlock = false;
          isStaticPrintBlock = false;
          currentLine = '_' + '=' + currentLine.substring(2);
          continue;
        }

        if (!isPrintBlock && currentLine[4] === '$') {
          if (currentLine.includes("={micros}")) {
            laterUtil.replace(currentLine, "{micros}", "2");
            lineData = 10;
          }
          if (currentLine.includes("={cycle}")) {
            laterUtil.replace(currentLine, "{cycle}", "2");
            lineData = 11;
          }
        }

        if (!isPrintBlock) currentLine = autoEqualsInsert(currentLine);
        if (!isStaticPrintBlock) {
          var ret = embedVariables(currentLine, isConstant, SCRIPT);
		  isConstant = ret.isConstant;
		  currentLine = ret.line;
        //  embedTemplates(currentLine, SCRIPT); //dd666 needless?
        }
        lineLen = currentLine.length;



        ///////////////////////////////
        // deduce command:
        let cmdPos = currentLine.indexOf("=");
        if (cmdPos < 0) cmdPos = 0;
        const currentCmd = currentLine.substring(0, cmdPos);
        const cmdChar = LATER_CMDS[currentCmd] || 0; // Default to 0 if not found

        // cleanup value after command:
        let linePtr = currentLine;
        if (cmdPos > 0) linePtr = currentLine.substring(cmdPos + 1);
        if (!isPrintBlock) {
          if (linePtr[0] === '=') linePtr = linePtr.substring(1);
          linePtr = linePtr.trimLeft();
        } else {
          linePtr = currentLine;
          LATER_CMDS["_"] = LATER_println; // Ensure _= acts as println in print block
        }
        lineLen = linePtr.length;


//console.info({currentLine, linePtr});

		///////////////////////////////////////
        // FLAGS: set byte flag based on the value
        // b2          b1          b1
        // hasParens, hasVar, hasTemplate
        let flag = 0;

        //////////  %templates% ? LSB
        const tempPtr = linePtr.indexOf('{'); // look for opening template expression
        if (tempPtr !== -1 && tempPtr + 1 < linePtr.length && linePtr[tempPtr + 1] !== ' ' && linePtr.indexOf('}', tempPtr + 1) !== -1 && !isStaticPrintBlock) flag += 1; // also has later close template delim
        //////////  $vars ? 2s

        // look for var usage, minding var commands themselves
        if (cmdChar === LATER_var || cmdChar === LATER_static || cmdChar === LATER_apply) { // look only after first equal for this
          //lineData = parseVarCommands(currentLine, linePtr, lineData, SCRIPT); // despace, optimize, fix syntax like *= > =*
		 
		  currentLine=parseVarCommands(currentLine, linePtr, lineData, SCRIPT); 
		  linePtr = currentLine.split("=").slice(1).join("=");
		 
          const equalsIndex = currentLine.indexOf('=');
          if (equalsIndex !== -1 && currentLine.indexOf('@', equalsIndex) !== -1 && !lineData) flag += 2; // vars after assign
        } else { // non var command, but uses var, flag for var processing
          if (linePtr.includes('@')) flag += 2; // vars
        }

        if (cmdChar === LATER_option) {
          if (linePtr.includes("noget!")) SCRIPT.options.noget = true;
        }

        if (linePtr.includes('(') && linePtr.includes(')') && !isStaticPrintBlock) flag += 4;
        //////////  [x,y][arrays] ?  8s
        if (linePtr.includes("][") && !isStaticPrintBlock) flag += 8;

        if (isConstant) flag += 64;

        ////////// output ?  16s - interpolate var and %templates% in code line itself?
        if (COMMANDS_NEEDING_OUTPUT.includes(cmdChar)) {
          flag += 16;
        } else { // don't need whitespace in any other command
          // collapse whitespace here
          if (!isPrintBlock && currentLine.includes(' ') && !COMMANDS_NEEDING_WHITESPACE.includes(cmdChar) && (!currentLine.includes("][")) && (!Later.addons[cmdChar])) {
		  
		  console.log("zapping space", {currentLine, linePtr});
		  
            linePtr = linePtr.replace(/ /g, "");
            currentLine = currentLine.substring(0, cmdPos + 1 + linePtr);
          }
        }
        // wipe out existing processing for math commands:

        // populate script line object with accumulated data:
        const sLine = SCRIPT.lines[lineCount];
        sLine.cmd = cmdChar;
        sLine.data = lineData;
        sLine.flags = flag;

      //  if (cmdChar === LATER_apply || cmdChar === LATER_var) parseApply(linePtr, sLine, SCRIPT);

        if (cmdChar === LATER_math) {
          replaceAllLiterals(linePtr, SCRIPT);
          linePtr = linePtr.replace(/ /g, "");
          currentLine = currentLine.substring(0, cmdPos + 1) + linePtr;
        }

        lineLen = linePtr.length;
        sLine.len = lineLen; // how many chars is line?
        sLine.start = outptr; // first line byte in clean buffer
        sLine.stop = outptr + lineLen; // last line byte in clean buffer
        // copy to clean:
        const segment = linePtr;//.substring(0, lineLen);
        clean = clean.substring(0, outptr) + segment + clean.substring(outptr + segment.length);
        outptr += lineLen //+ 1;

        sLine.profile = { parse: (performance.now() * 1000) - profileStart }; // LATER_LINE_PROFILING

        lineCount++;
        if (lineCount > LATER_LINE_LIMIT) break; // failsafe here
      } //end if line not empty?
    } // wend endpos > 0

    // iterate defines here, adding null terms to define linebreaks
    for (const key in DEFINES[scriptIndex]) {
      if (DEFINES[scriptIndex].hasOwnProperty(key) && DEFINES[scriptIndex][key]) {
        const endCap = DEFINES[scriptIndex][key].indexOf('\n');
        if (endCap !== -1) {
          DEFINES[scriptIndex][key] = DEFINES[scriptIndex][key].substring(0, endCap);
        }
      }
    }


	

    // move clean buffer to script object
    SCRIPT.program = clean.substring(0, outptr);

    // populate SCRIPT object with parsed program meta and data:
    SCRIPT.lineCount = lineCount;
    SCRIPT.forTop[0] = -1;
    SCRIPT.runs = 0;

	SCRIPT.lines.length = lineCount;
    buildExitPoints(SCRIPT);
    SCRIPT.parseTime = (performance.now() * 1000) - st;
    //console.timeEnd(`loadScript-${scriptFileName}`);
    return 1; 
}//end loadScript()

function replaceIncludes(fileBuff) {
  // replace include(s)
  return fileBuff.replace(/#include\s*([\w\W]+?)\n/g, function(j,def){
    console.info("#include", def);  
	return laterUtil.fileToBuffInclude(def.trim());
  });
}//end replaceIncludes()

function replaceSpecialMacros(fileBuff, scriptFileName) {
  return fileBuff.replace(/__FILENAME__/g, scriptFileName)
  				 .replace(/__SKETCH_FILE__/g, LATER_SKETCH);
}// end replaceSpecialMacros()

function sniffContentType( fileBuff, s ) {
  return fileBuff.replace(/#type=([\w\W]+?)[\n\t ;]/g, function(j,def){
    SCRIPT.contentType = def;
	return "";
  });
}//end sniffContentType()

function populateDefines(fileBuff, scriptIndex) {
  DEFINES[scriptIndex] = {};
  return fileBuff.replace(/#define=([\w\W]+?)$/gm, function(j,def){
   	 var p=def.trim().split(" ");
     DEFINES[scriptIndex][p[0]] = p.slice(1).join(" ");
	return "";
  });
}//end populateDefines()


/*
void deInlineVarAssignments(char * buff) { // makes var x=1, y=2; into x=12\ny=2;
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
    //p=strstr(p+2, "\nvar ");
  }//wend
}// end deInlineVarAssignments();
*/

function convertIIFs(line, lb, endpos) {
  line = line.replace(/^iif ([\w\W]+?) : ([\w\W]+?)$/mg, function(j,con,bod){
    //   line=line.slice(line.indexOf(" : ")).trim();
	return "iif " + con +"\n" + bod;
  });
  return  {lb, line};
} //end convertIIFs()

function removeSingleLineComments(line, cmd) {
  // remove comments -- needs to chill a bit for later, check if print, log, fetch, etc.
  var commentPos = laterUtil.indexOf(line, "//");
  if (commentPos == -1 ) commentPos = laterUtil.indexOf(line, "'");
  if (commentPos > -1 ) {
    if (commentPos == 0) {
      line = "";
    } else {

      if (!strstr(",_,log,print,println,fetch,ping,timer,", cmd)) line = line.slice(0, commentPos);
	  
    }//end if not whole line comment?
  }//end if has comment?

  if (line[0] == '\'') line=""; // skip VB-style comment line, also used internally by multi-line comments to curtail buffer resizing
  return line;
}//end removeSingleLineComments()

function harvestMacros(line, scriptIndex) {
   return line.replace(/@([\w]+)/gm, function(j, key){
     return DEFINES[scriptIndex][key] || "";
  });
}//end harvestMacros()

function cleanupVarDeclarations(line) {
  var  lineLen = line.length;
  // inject var= into plain var declarations; $x=1 into var=$x=1
  if (line[0] == '$') {
    if ( strchr(line, '{') && strchr(line, ':') && line[lineLen - 1] == '}') {
      line = line.replace("$", "define=$");
    } else {
	  line = line.replace("$", "var=$");
	  line = line.replace("++", "=+1");
	  line = line.replace("--", "=-1");
    }
	  line = line.replace(/ ?= ?/, "=");
  }//end if plain syntax var declaration line?
  return line;
} //end cleanupVarDeclarations();

function expandRangeOperators(line, s) {
   //replace range operators with csv ints within the range bounds
  return line.replace(/(\d+)\.\.(\d+)/gm, function(j, l, r){
     l = s.Number(l);
	 r = s.Number(r);	 
	 var buff = [];	 	 
	 if(l<r){
	 	for (var i = l+1; i < r; i++) buff.push(i);
	 }else{
	   	for (var i = l-1; i > r; i--) buff.push(i);
	 }
	 return [l,buff,r]+"";
  });

}//end expandRangeOperators()

function replaceEndCommands(line) {
 if(line.startsWith("end")){
 	line = line.replace("end sub", "endsub=}")
	.replace("end if", "fi")
	.replace("end do", "loop")
	.replace("end switch", "end=switch");
 }
  if (line[0] == '}')  line=line.replace("}", "endsub=}");
  return line;
} // end  replaceEndCommands()

function embedVariables(line, isConstant, SCRIPT) {
   var isConstant = /\$[A-Z]/.test(line);
   line =  replaceVarNames(line, SCRIPT.index);
   if(isConstant) SCRIPT.VARS[line.charCodeAt(1) - 65] = 420420420;
  return {line, isConstant};
}//end embedVariables()


function parseVarCommands(line, linePtr, lineData, s) {
  // clean up all spaces they are not needed.
  return line.replace(/\s+/g, "")
  .replace( "+=", "=+")
  .replace("-=", "=-")
  .replace("*=", "=*")
  .replace("/=", "=/");  
}//end parseVarCommands()


/// jumping ahead to templates.ino:
function processTemplateExpressions2(line) {

  return line.replace(/(\{[\w#&%]+\})/gm,function(j,key){
   var flag = /^{\w/.test(key) ? "" : key[1];
   if(!flag)  return TEMPLATES2[key]?.call() || 0;
   if(flag=="@") return getCurrent().VARS[key.charCodeAt(2) - 65];
   if(flag=="&") return LATER_STORE.get(key.slice(2,-1));
   if(flag=="#") return getCurrent().TEMPS[key.charCodeAt(2)-65]?.call();
   
  if(flag=="*") return LATER_STORE.get(key.slice(2,-1));
  });
} // end processTemplateExpressions2()


/// jumping ahead to templates.ino:
function processTemplateExpressionsNumber(line) {

  var ptrLeft = strchr(line, '{');
  if (!ptrLeft) return 0;

  var storeCall = 0;
  var len = strcspn (ptrLeft, "}") + 2; //end param delim
  // unsigned long val;

  if (ptrLeft[1] == '&') {
    storeCall = 1;
    ptrLeft = ptrLeft.slice(2);
    len -= 3;
  }

  var TEMPLATE_KEY_BUFF =  ptrLeft.slice(0,len);

  if (storeCall) {
    return LATER_STORE.get(TEMPLATE_KEY_BUFF);
  } else {
    var callback = TEMPLATES2[TEMPLATE_KEY_BUFF];
    if (callback) return callback(); //this needs to capture value, a ulong then push in sting if line.single flag is not set
    if (ptrLeft[1] == '@') return getCurrent().VARS[ptrLeft[2] - 65];
  }
  return 0;
} // end processTemplateExpressionsNumber()


const TEMPLATES2 = {
  "{timer}": () => Date.now(), // Assuming millis() is equivalent to JS timestamp
  "{rnd}": () => Math.floor(Math.random() * 1024), // Assuming randomReg() % 1024
  "{rnd2}": () => Math.floor(Math.random() * 2),   // Assuming randomReg() % 2
  "{rnd8}": () => Math.floor(Math.random() * 256),  // Assuming randomReg() % 256
  "{rnd16}": () => Math.floor(Math.random() * 65536), // Assuming randomReg() % 65536
  "{rnd_digit}": () => Math.floor(Math.random() * 10), // Assuming randomReg() % 10
  "{rnd_reg}": () => Math.random(), // Assuming randomReg() returns a float [0, 1)
  "{web}": () => (getCurrent() && getCurrent().calledFromWeb) ? 1 : 0,
  "{store}": () => (getCurrent() && getCurrent().storeDirty) ? 1 : 0,
  "{counter}": () => getCurrent() ? getCurrent().counter++ : 0,
  "{i}": () => getCurrent() ? getCurrent().forIndex[getCurrent().forLevel] : 0,
  "{ii}": () => (getCurrent() && getCurrent().forLevel > 0) ? (getCurrent().forIndex[getCurrent().forLevel - 1]) : 0,
  "{iii}": () => (getCurrent() && getCurrent().forLevel > 1) ? (getCurrent().forIndex[getCurrent().forLevel - 2]) : 0,
  "{iiii}": () => (getCurrent() && getCurrent().forLevel > 2) ? (getCurrent().forIndex[getCurrent().forLevel - 3]) : 0,
  "{adc}": () => analogRead(0), // Assuming analogRead and A0 are defined
  "{a0}": () => analogRead(0),  // Assuming analogRead and A0 are defined
  "{runtime}": () => getCurrent() ? (performance.now() - getCurrent().startedAt) : 0, // Assuming micros() -> performance.now() in ms

  "{time.day}": () => timeClient ? timeClient.getDay() : 0,
  "{time.hour}": () => timeClient ? timeClient.getHours() : 0,
  "{time.minute}": () => timeClient ? timeClient.getMinutes() : 0,
  "{time.second}": () => timeClient ? timeClient.getSeconds() : 0,
  "{time.epoc}": () => timeClient ? timeClient.getEpochTime() : 0,

  "{time.date}": () => { getDate(0); return DATES ? DATES[2] : 0; }, // Assuming getDate and DATES are defined
  "{time.month}": () => { getDate(0); return DATES ? DATES[1] : 0; }, // Assuming getDate and DATES are defined
  "{time.year}": () => { getDate(0); return DATES ? DATES[0] : 0; },  // Assuming getDate and DATES are defined

  "{micros}": () => performance.now() * 1000, // Approximate micros() with performance.now() in ms

  "{micros64}": () => performance.now() * 1000, // Approximate micros64()
  "{cycle}": () => 0, // esp_get_cycle_count() has no direct JS equivalent
  "{frag}": () => 0,  // ESP.getHeapFragmentation() has no direct JS equivalent
  "{flash}": () => 0, // ESP.getFlashChipRealSize() has no direct JS equivalent
  "{mac}": () => 0,   // system_get_chip_id() has no direct JS equivalent
  "{chan}": () => 0,  // wifi_get_channel() has no direct JS equivalent
  "{cpu}": () => 0,   // system_get_cpu_freq() has no direct JS equivalent

  "{rssi}": () => (typeof WiFi !== 'undefined' && WiFi.RSSI) ? WiFi.RSSI() : 0,
  "{runs}": () => getCurrent() ? getCurrent().runs : 0,
  "{ip0}": () => (typeof WiFi !== 'undefined' && WiFi.localIP && WiFi.localIP()[0]) ? WiFi.localIP()[0] % 255 : 0,
  "{ip1}": () => (typeof WiFi !== 'undefined' && WiFi.localIP && WiFi.localIP()[1]) ? WiFi.localIP()[1] % 255 : 0,
  "{ip2}": () => (typeof WiFi !== 'undefined' && WiFi.localIP && WiFi.localIP()[2]) ? WiFi.localIP()[2] % 255 : 0,
  "{ip3}": () => (typeof WiFi !== 'undefined' && WiFi.localIP && WiFi.localIP()[3]) ? WiFi.localIP()[3] % 255 : 0,

  "{ip}": () => (typeof WiFi !== 'undefined' && WiFi.localIP && WiFi.localIP()[3]) ? WiFi.localIP()[3] % 255 : 0,
  "{net}": () => (typeof WiFi !== 'undefined' && WiFi.localIP && WiFi.localIP()[2]) ? WiFi.localIP()[2] % 255 : 0,
  "{ram}": () => (typeof ESP !== 'undefined' && ESP.getFreeHeap) ? ESP.getFreeHeap() : 0,

  "{leds}": () => (typeof strip !== 'undefined' && strip.numPixels) ? strip.numPixels() : 0,

  "{line}": () => getCurrent().i ,
  "{gpio0}": () => digitalRead(0),   // Assuming digitalRead is defined
  "{gpio2}": () => digitalRead(2),   // Assuming digitalRead is defined
  "{gpio3}": () => digitalRead(3),   // Assuming digitalRead is defined
  "{gpio4}": () => digitalRead(4),   // Assuming digitalRead is defined
  "{gpio5}": () => digitalRead(5),   // Assuming digitalRead is defined
  "{gpio12}": () => digitalRead(12), // Assuming digitalRead is defined
  "{gpio13}": () => digitalRead(13), // Assuming digitalRead is defined
  "{gpio14}": () => digitalRead(14), // Assuming digitalRead is defined
  "{gpio15}": () => digitalRead(15), // Assuming digitalRead is defined
  "{gpio16}": () => digitalRead(16), // Assuming digitalRead is defined
  "{E.pin}": () => EVENT[Later.lastEventSlot].pin,
  "{E.value}": () =>EVENT[Later.lastEventSlot].value,
  "{E.time}": () => EVENT[Later.lastEventSlot].ms,
  "{E.ms}": () => (EVENT[Later.lastEventSlot].msNext - EVENT[Later.lastEventSlot].ms),  
  "{E.program}": () =>EVENT[Later.lastEventSlot].programSlot,
  "{args}": () => (typeof server !== 'undefined' && server.args) ? server.args() : 0,
  "{arity}": () => getCurrent().arity,
  "{arg0}": () =>  getCurrent().subArgs[0] ,
  "{arg1}": () => getCurrent().subArgs[1] ,
  "{arg2}": () =>getCurrent().subArgs[2] ,
  "{arg3}": () =>  getCurrent().subArgs[3] ,

  "{self.index}": () =>  getCurrent().index ,
  "{self.interval}": () => getCurrent().interval ,
  "{self.runTime}": () => getCurrent().runTime ,
  "{self.duration}": () => getCurrent().duration ,
  "{self.loadTime}": () =>  getCurrent().loadedAt ,
  "{self.parseTime}": () =>  getCurrent().parseTime ,
  "{self.runs}": () =>  getCurrent().runs ,
  "{self.lines}": () =>  getCurrent().lineCount,
};//end TEMPLATES2



function Dump(){
  var s = getCurrent();
  var r = SCRIPTS[0].lines.map((x,i)=>{
    //return i+".\t" +  x.cmd+"::"+s.program.slice(x.start, x.stop);
	//return {ex: x.exit, data: x.data, flags: x.flags, hits: x.hits, cmd: x.cmd, line: s.program.slice(x.start, x.stop)};
	
	return { "edfhc":""+[ x.exit, x.data, x.flags, x.hits,x.cmd], line: s.program.slice(x.start, x.stop)};
	
	
  });
 console.table(r);
 console.dir(s.VARS);
}







// neopixel implimentation

function add(a, b) {
  return Math.min(a + b, 255);
}

function subtract(a, b) {
  return Math.max(b - a, 0);
}

function within(range, base) {
  const n = (randomReg() % (range * 2)) - range;
  return Math.min(255, Math.max(base + n, 0));
}

function rndSubtract(range, base) {
  const n = randomReg() % range;
  return Math.max(base - n, 0);
}

function rndAdd(range, base) {
  const n = randomReg() % range;
  return Math.min(base + n, 255);
}

function runSetPixel(line, s) {
  let ptr = line;
  let color;
  const indPos = line.indexOf("->");
  let commaPos = line.indexOf(",") + 1;
  const startPos = s.Number(line);
  let howMany = 1;

  if (commaPos && commaPos < indPos) howMany = s.Number(line.substring(commaPos));

  ptr = line.substring(indPos + 2);

  let flag = 0;
  if (ptr.match(/[+\-<>*&]/)) {
    flag = ptr[0];
    ptr = ptr.substring(1);
  }

  if (startPos + howMany > LATER_PIXEL_NAME.numPixels()) return;

  color = laterUtil.parseColor(ptr, s);

  if (flag) {
    const r1 = (color >> 16) & 0xFF;
    const g1 = (color >> 8) & 0xFF;
    const b1 = color % 256;
    let colorOld;

    for (let i = startPos, mx = startPos + howMany; i < mx; i++) {
      colorOld = LATER_PIXEL_NAME.getPixelColor(i);

      const r2 = (colorOld >> 16) & 0xFF;
      const g2 = (colorOld >> 8) & 0xFF;
      const b2 = colorOld % 256;

      switch (flag) {
        case '+':
          color = LATER_PIXEL_NAME.Color(add(r1, r2), add(g1, g2), add(b1, b2));
          break;

        case '-':
          color = LATER_PIXEL_NAME.Color(subtract(r1, r2), subtract(g1, g2), subtract(b1, b2));
          break;

        case '*':
          color = LATER_PIXEL_NAME.Color(within(r1, r2), within(g1, g2), within(b1, b2));
          break;

        case '>':
          color = LATER_PIXEL_NAME.Color(rndAdd(r1, r2), rndAdd(g1, g2), rndAdd(b1, b2));
          break;

        case '<':
          color = LATER_PIXEL_NAME.Color(rndSubtract(r1, r2), rndSubtract(g1, g2), rndSubtract(b1, b2));
          break;

        case '&':
          color = LATER_PIXEL_NAME.Color((r1 + r2) / 2, (g1 + g2) / 2, (b1 + b2) / 2);
          break;
      }

      LATER_PIXEL_NAME.fill(color, i, 1);
    }
    return;
  }

  LATER_PIXEL_NAME.fill(color, startPos, howMany);
  
}

function runRotate(dist) {
  const mx = LATER_PIXEL_NAME.numPixels() - 1;
  let i = 0;

  let last;
  last = LATER_PIXEL_NAME.getPixelColor(mx);
  for (i = mx; i > 0; i--) LATER_PIXEL_NAME.setPixelColor(i, LATER_PIXEL_NAME.getPixelColor(i - 1));
  LATER_PIXEL_NAME.setPixelColor(0, last);
  renderStrip();
}

function runGrad(line, s) {
  let ptr = line;
  let col, col2;
  const indPos = line.indexOf("->");
  let commaPos = line.indexOf(",") + 1;
  const startPos = s.Number(line);
  let howMany = LATER_PIXEL_NAME.numPixels();

  if (commaPos && commaPos < indPos) howMany = s.Number(line.substring(commaPos), s.VARS);

  ptr = line.substring(indPos + 2);

  let ptr2 = ptr.indexOf(",");
  const colStr = ptr.substring(0, ptr2);
  const col2Str = ptr.substring(ptr2 + 1)
  col = laterUtil.parseColor(colStr, s);
  col2 = laterUtil.parseColor(col2Str, s);

  const r1 = (col >> 16) & 0xFF;
  const g1 = (col >> 8) & 0xFF;
  const b1 = col % 256;
  const r2 = (col2 >> 16) & 0xFF;
  const g2 = (col2 >> 8) & 0xFF;
  const b2 = col2 % 256;

  const fhm = howMany;
  const rd = (r1 - r2) / fhm;
  const gd = (g1 - g2) / fhm;
  const bd = (b1 - b2) / fhm;

  LATER_PIXEL_NAME.setPixelColor(startPos, col);

  for (let i = 1, mx = howMany; i < mx; i++) {
    LATER_PIXEL_NAME.setPixelColor(
      startPos + i,
      r1 - (rd * i),
      g1 - (gd * i),
      b1 - (bd * i)
    );
  }
  LATER_PIXEL_NAME.setPixelColor(startPos + howMany, col2);
  renderStrip();
}


const LATER_PIXEL_NAME = { 
  pixels: Array(100).fill(0),
  asHex: function(){
   return this.pixels.map(x=>`#${`00${x.toString(16)}`.slice(-6)}`);
  },
  show: renderStrip,
  numPixels: () => 100, // Example
  getPixelColor: function(i){return this.pixels[i];}, // Example red
  setPixelColor: function(index, r, g=-1, b) {
   if(g==-1) return this.pixels[index] = r;
   this.pixels[index] =  (r << 16) | (g << 8) | b;
  },
  Color: (r, g, b) => {
    return (r << 16) | (g << 8) | b; // Example RGB to integer
  },
  fill: function (color, ind, howMany) {
      for(var i=ind,mx=ind+howMany;i<mx;i++) LATER_PIXEL_NAME.pixels[i]=color;
	//  renderStrip();
  }
};

var stripDiv = document.body.appendChild(document.createElement("div"));
stripDiv.innerHTML = "<span class=pix style='background-color:#000'></span>".repeat(100);
stripDiv._api =  [].slice.call(stripDiv.children).map(x=>x.style);

function renderStrip(){
 var colors = LATER_PIXEL_NAME.asHex();
 var r =stripDiv._api.forEach(function(sty, i){
  sty.backgroundColor = colors[i];
 });
}



























async function sleep(ms){
 return await new Promise(function(y,n){
   setTimeout(y, ms); 
 });
}






async function runScript() {
  let loopLimit = 29999;
  const s = getCurrent();
  let l;
  var linebuff = "";//new Array(LATER_LINE_BUFFER).fill('\0').join(''); // holds a copy
  let lp = s.program; // start point
  if (s.options.debug) loopLimit = 6000;
  s.startedAt = performance.now() * 1000; // micros()
  s.runs++;
//console.info("rs", s.VARS.slice(3,9)+'');
  let hits = 0; // runaway code detection
  let k, v; // for parsing
  let lb; // line buffer pointer
  let varCache = 0, tempInt = 0, varTemp = 0; // for numbers in switch
  let varSlot = 0; // for DMA
  let usedDMA = false; // DMA needed?
  let varChar; // cache char
  let pinCache;
  if (!s.exitLineNumber) s.exitLineNumber = s.lineCount;

  for (s.i = s.resumeLineNumber; s.i < s.exitLineNumber; s.i++) {
    if (s.options.step) {
      if (!s.stepReady) {
        s.stepReady = true;
      } else {
        s.stepReady = false;
        s.i--;
      //  await s.freeze(99999); // Assuming freeze is async
        return;
      }
    }

    l = s.lines[s.i];


	l.hits++;

    lp = s.program.substring(l.start, l.stop);
    let currentLinebuff = lp; // Use a local variable

    usedDMA = false;

    if (l.flags) {
	
	
      if (l.flags === 128) continue;

      if (l.flags & FLAGS.T) {
       currentLinebuff = processTemplateExpressions2(currentLinebuff, s);
      }
      if (l.flags & FLAGS.O) {
	     currentLinebuff = processVariableExpressions(currentLinebuff, s.VARS);
	
      }
      if (l.flags & FLAGS.E) {
	 // console.warn(	  currentLinebuff);
        currentLinebuff = evalMath(currentLinebuff, s, -1);
		//console.warn(	  currentLinebuff);
      }
      if (l.flags & FLAGS.A) {
        currentLinebuff = processArray(currentLinebuff, s, -1);
      }
    }

    if (hits++ > loopLimit) {
	s.hits = hits;
      uniPrintln("runaway loop detected, aborting");
      break;
    }

    if (s.options.debug) {
      const tempbuff = "                ";
      let tb = tempbuff;
      tb = s.i + ">" + l.exit + "\t" + String.fromCharCode(l.cmd) + " =" + currentLinebuff;
      uniPrintln(tb);
    }

	lb = linebuff = currentLinebuff;
	
	////////////////////////////////////////////////////////////////////////////
    switch (l.cmd) {/////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	
	
	
	case LATER_static:
//-static // static $z={ a:11, b:22, c:33 }
// -switch to noop/128
		l.cmd = LATER_noop;
		l.flags = 128;
 //-json? - def sub-vars
 if(/\w+\s?\:[\W\w]+\,/.test(lb)){ // json mode
  var r = lb.trim().split(/[{}]/)[1].split(/\s*,\s*/);
  var base = lb.charCodeAt(1) - 65;
  var baseName =getVarLongname(base, s.index);
  r.forEach(x=>{
  	  var p = x.trim().split(/\s*:\s*/);
  	  let slot = getVarNameNumber(baseName+"." + p[0], s.index); 
      s.VARS[slot] = s.Number(p[1]); 			  
  });
  s.VARS[base] = r.length; 
  continue;
 }
 
  //-array $x=[1,2,3] == $x.0=1;$x.1=2...
 if(/\[[\w\W]+\]/.test(lb)){ // json mode
  var r = lb.trim().split(/[\[\]]/)[1].split(/\s*,\s*/);
  var base = lb.charCodeAt(1) - 65;
  var baseName =getVarLongname(base, s.index);
  r.forEach((x,y)=>{
  	  var p = x.trim();
  	  let slot = getVarNameNumber(baseName+"." + y, s.index); 
      s.VARS[slot] = s.Number(p); 			  
  });
  s.VARS[base] = r.length; 
  continue;
 }
 
  //- look out for url-inserted values
  // eval op or jsut assign val as needed
  var base = lb.charCodeAt(1) - 65;
  var baseName =getVarLongname(base, s.index);
  if(!LATER_SERVER_NAME.hasArg(baseName.slice(1))){
  	s.VARS[base] = s.Number(lb.slice(3));
	continue;
  }else{
 	 
  	s.VARS[base] = s.Number(""+LATER_SERVER_NAME.arg(baseName.slice(1)));
	
  	continue;
  }
  
	break;
			
      case LATER_var:
	  case LATER_store:
	  case LATER_global:
       //console.warn("VAR", lb, lb[1].charCodeAt(0) - 65,s.Number(lb.slice(3)) );
	    varSlot = lb[1].charCodeAt(0) - 65,
	   	   
		   val = s.Number(lb.slice(3)) || 0;
		   
		   
		   
       if (l.cmd == LATER_store || l.cmd == LATER_global) {
         val = LATER_STORE.get(lb.split("=")[0].trim());
       }


//console.log("var", {c:lb[1], f:lb[3], varSlot,val, lb});
		   
		var newVal = +lb[3] ? val : s.VARS[varSlot];
		
	   switch(lb[3]){
	     case '+': newVal += val || 0; break;
		 case '-': newVal -= val|| 0; break;
		 case '*': newVal *= val|| 0; break;
		 case '/': newVal /= val|| 0; break;
		 case '%': newVal %= val|| 0; break;
		 default:  newVal =  val|| 0; break;
	   }
	   
	//   console.warn("var", {valstr: lb.slice(3), cur: s.VARS[varSlot] , varSlot, sig:lb[3], newVal, val , cmd: l.cmd==LATER_var })
	   
	   // if var:
		if(l.cmd == LATER_var){
	   		s.VARS[varSlot]  = newVal;
			continue;
		}
		
		if (l.cmd == LATER_store) {
			 LATER_STORE.set(lb.split("=")[0].trim(), newVal);
			continue;
		}
		
		if(l.cmd == LATER_global){
			LATER_STORE.update(lb.split("=")[0].trim(), newVal);
			continue;
		}
		
		
	   /*
	   things that var needs to do

find varslot

        if (   (((l->flags >> 6) & 0x01) == 1)   && (s->VARS[varSlot] != 420420420)   ) {
          l->cmd = LATER_noop;
          continue;
        } ????

shortcuts? 

parse value
if store, store.get buff
has operation?
 -eval op 

set dest 
 -varslot, store, etc
 
 
 */
	   
	   
	   
	   
	   
        continue;
		
	   case LATER_if: case LATER_iif: // If/Iff
	      if (!evalConditionalExpression(linebuff, s)) s.i = l.exit;
		  continue;
        break;
		
		case LATER_do: // do
		  if (linebuff[0] == ' ') continue;
          if (linebuff[0] == 'w') {
		  //console.info("while",linebuff.slice(5));
            //if (!evalConditionalExpression(linebuff.slice(5), s)) s.i = l.exit;
			if (!evalLite(linebuff.slice(5), s)) s.i = l.exit;
          } else if (linebuff[0] == 'u') { //blah
            if (evalLite(linebuff.slice(5), s)) s.i = l.exit;
          }//end if until

		continue;
        break;
		
      case LATER_exit: // aka finish
        s.exitLineNumber = s.i;
        finishRun(s);
        return;
        break;
		
      case LATER_loop:
        s.i = l.exit;
        continue;
		
	  case LATER_sleep:
         await sleep(s.Number(lb));
        continue;
		
		
		 
      case LATER_noop:
        l.flags = 128;
        continue;

      case LATER_else:
        s.i = l.exit;
        continue;

      case LATER_digitalWrite:
        laterCMD.runPortWrite(currentLinebuff, s.VARS, true);
        continue;

      case LATER_analogWrite:
        laterCMD.runPortWrite(currentLinebuff, s.VARS, false);
        continue;

      case LATER_print:
      case LATER_println:
        if (l.cmd === LATER_println) {
          uniPrintln(currentLinebuff);
        } else {
          uniPrint(currentLinebuff);
        }
        continue;
		
		
		case LATER_switch: // sWitch
        //s->switchTerm = atoi(linebuff);
        s.switchTerm=linebuff.trim();
        s.switchExit = l.exit;
        //LATER_PRINTLN("  SWITCH x " + String(s->switchExit) + "  |" + String(s->switchTerm) + "|");
        continue;
        break;
		
		
      case LATER_end: //end switch might need to become LATER_end_switch, if other ends are needed
        s.switchTerm = '';
        continue;
        break;
	
	
      case LATER_default: // switch default
        if (!s.switchTerm) {
          s.i = s.switchExit;
        } else {
          s.switchTerm = '\0';
        }
        continue;
        break;
		
		
      case LATER_case: // case (Kse)
        if (!s.switchTerm) {
          s.i = s.switchExit;
        } else {
          //if (s->switchTerm == atoi(linebuff)) {
          if (s.switchTerm == linebuff) { // match? yes:
            s.switchTerm = "";
          } else { // no match, go to next case statement to look for a match
            s.i = l.exit;
          }//end if case match?
        }//end if expired switch's case?
        continue;
        break;
		
  		case LATER_for: // forLoop
			

        if (s.forTop[s.forLevel] != -1) s.forLevel++; //  in loop? shift up a level
		s.forTop[s.forLevel] = s.i;

		var p = linebuff.split(/\s*;\s*/);

        s.forStart[s.forLevel] = s.Number(p[1] ? p[0] : 0); 
        s.forEnd[s.forLevel] = s.Number(p[1] ? p[1] : 0); 
        s.forStep[s.forLevel] = s.Number(p[2] ? p[2] : 1); 
		
        s.forIndex[s.forLevel] = s.forStart[s.forLevel];
        if (s.forEnd[s.forLevel] < s.forStart[s.forLevel]) { // hi-lo?
          if (s.forStep[s.forLevel] > 0) s.forStep[s.forLevel] *= -1;
        }//end if hi-low order?

//var o ={};
//["forStep", "forLevel", "forEnd", "forStart", "forIndex"].map(x=>o[x]=s[x][0]);
//console.warn("forrr", o);

        continue;
        break;

 		case LATER_next: // forLoop's Next
        s.forIndex[s.forLevel] += s.forStep[s.forLevel];

        if (s.forStep[s.forLevel] > 0) { // works
          if (s.forIndex[s.forLevel] >= s.forEnd[s.forLevel]) { // done
            s.forTop[s.forLevel] = -1;
            // shift down a level if not on zero
            if (s.forLevel) s.forLevel--;
          } else { // keep going
            s.i = l.exit;
          }

        } else { // counting down

          // LATER_PRINTLN("[forStart:" + String(s.forStart) + ", forTop:" + String(s.forTop) + ", forEnd:" + String(s.forEnd) + ", forStep:" + String(s.forStep) + ", forIndex:" + String(s.forIndex) + ", " + "]");
          if (s.forIndex[s.forLevel] <= s.forEnd[s.forLevel]) { //done
            s.forTop[s.forLevel] = -1;
            // shift down a level if not on zero
            if (s.forLevel) s.forLevel--;
          } else { // keep going
            s.i = l.exit;
          }

        }//end if count up or down?

        continue;
        break;
		
      case LATER_sub: //sub routine
        if (!s.subReturnLine) {
          s.i = l.exit;
          continue;
        }
        continue;
        break;
		
		
      case LATER_option:
        //bool debug; // print debug info to the console?
        //bool perf; // print perf info to the console?
        //bool strict; // disable legacy handlers and slower features?
        if (strstr(lb, "debug")) s.options.debug = true;
        if (strstr(lb, "perf")) s.options.perf = true;
        if (strstr(lb, "strict")) s.options.strict = true;
        if (strstr(lb, "persist")) s.options.persist = true;
        if (strstr(lb, "socket")) s.options.socket = true;
        if (strstr(lb, "noget")) s.options.noget = true;
        if (strstr(lb, "step")) s.options.step = true;
		var ok = strstr(lb, "interval");
        if (ok) {
          // find next digits
          v = strpbrk(ok.slice(8), "0123456789"); // locate first digit(s) after "interval"
          s.interval = s.Number(v);
          s.options.persist = true;
        }
		
        l.flags = 128;
        continue;
        break;
		
      case LATER_pinMode:
        laterCMD.runPinMode(currentLinebuff);
        continue;

      case LATER_log:
        processStringFormats(currentLinebuff, s.index);
        laterCMD.logMe(currentLinebuff);
        continue;

      case LATER_start:
        if (lb[0] == '0' ) { // default 00
          s.startLineNumber = s.i + 1; // next line is new top
        } else {
          s.startLineNumber = s.Number(lb||"0") ||  s.i + 1; // top specified
        }
        continue;
        break;
		
		
	    case LATER_sub: //sub routine
        if (!s.subReturnLine) {
          s.i = l.exit;
          continue;
        }
        continue;
        break;
	
      case LATER_gosub: //sub call
        // look for arguments, populate as needed
        let k = strchr(linebuff, ' ').trim();
        if (k) {          
          let p = k.split(/\s*\,\s*/);          
          for (let i = 0; i < p.length; i++) s.subArgs[i] = s.Number(p[i]);
        }//end if args?
        s.subReturnLine = s.i;
        s.i = l.exit;
        continue;
        break;		
	
      case LATER_interval: //interval sub call
        // find interval, compare to lastFire
        //k = strchr(linebuff, ' ');
        k = linebuff;
        if (k) {
          tempInt = s.Number(k);
          if (  (s.intervals[ l.data ] + tempInt) < millis()  ) { //ready?
            s.intervals[ l.data ] = millis();
            s.subReturnLine = s.i;
            s.i = l.exit;
          }//end if ready?
        }//end if interval

        continue;
        break;
				
      case LATER_endsub: //sub end
        if (s.subReturnLine) {
          s.i = s.subReturnLine;
          s.subReturnLine = 0;
          s.subArgs[0] = 0;
          s.subArgs[1] = 0;
          s.subArgs[2] = 0;
          s.subArgs[3] = 0;

        }
        continue;
        break;

      case LATER_call: //call call
        // look for arguments, populate as needed
        if (l.data) {
          let k = linebuff.slice(l.data).trim();
          //k += l.data;          		  
          let p = k.split(/\s*\,\s*/);          
          let i = 0;
          for (i = 0; i <p.length; i++) s.subArgs[i] = s.Number(p[i]);
          s.arity = i;
        }//end if args?
        s.subReturnValue = linebuff.charCodeAt(1) - 65;
        s.subReturnLine = s.i;
        s.i = l.exit;
        continue;
        break;

      case LATER_return: //sub return
        if (s.subReturnLine) {
          tempInt = s.Number(lb);
          if (s.subReturnValue < 99) s.VARS[s.subReturnValue] = tempInt;
          s.i = s.subReturnLine;
          s.subReturnLine = 0;
          s.subArgs[0] = 0;
          s.subArgs[1] = 0;
          s.subArgs[2] = 0;
          s.subArgs[3] = 0;
          continue;
        }
        continue;
        break;



      case LATER_timer: // print hi-res timestamp to
        tempInt = micros();
        if (!s.timer) {
          s.timer = tempInt;
        } else {
          uniPrintln( "T+" + (tempInt - s.timer) +":\t"+lb );
          s.timer =  micros();
        }
        continue;
        break;

      case LATER_type: // print file by name to "stdout"
        uniPrintln(laterUtil.fileToBuff(linebuff));
        // nsLATER::uniPrintln(nsLATER::laterUtil::fileToBuff(linebuff));       //ddns
        continue;
        break;
		
	    case LATER_clear: // clear log value
        setRunLog = '\n';
        continue;
        break;	
		
      case LATER_freeze: // suspend operation for given MS
        s.freeze(s.Number(lb));
        return;
        continue;
        break;

      case LATER_run:
        Later.run(lb.trim());
        continue;
        break;


      case LATER_unload:
        Later.unload(lb.trim());
        if (lb.trim() == s.fileName) return;
        continue;
        break;	


      case LATER_suspend: // suspend operation for given MS, unload script
        varCache = s.Number(lb);
        if ( varCache > 0 ) { // number passed, suspend current script for ms
          s.resumeLineNumber = s.i + 1;
          s.duration = (micros() -  s.startedAt) / 1000;
          Later.suspend(s.fileName, varCache);
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
        laterCMD.runAssert(lb, l, s);
        continue;
        break;

      case LATER_cgi:
        laterCMD.runCGI(lb, s);
        continue;
        break;
		
		
		
		
		
	   case LATER_json:
        var o={},  p = lb.trim().split(/\s*\,\s*/);
		p.forEach(a=> o[a] = s.VARS[getVarNameNumber("$" + a, s.index)]);
		uniPrintln(JSON.stringify(o, null, "\t"));
        continue;
        break;	


     case LATER_continue:
        s.i = l.exit - 1;
        continue;
        break;
		
      case LATER_delete: // delete variable
        continue;
        break;

      case LATER_break:
        s.i = l.exit;
        continue;
        break;


      case LATER_fi: // end if
        continue;
        break;
		
      case LATER_math:
        s.VARS[ lb[1]-65]= evalLite( lb.slice(3), s);
        continue;
        break;
		
	
      case LATER_ping: // fetch
	    Later.httpResponseTextBuffer = "";
        await fetch(linebuff).then(x=>{
			s.status = x.status;
			return x.text();
		}).then(x=>{
			return Later.httpResponseText = Later.httpResponseTextBuffer = x;
		});
        continue;
        break;
		
		


      case LATER_flash: // save/restore variables to file
	  	//flash mystate < a, b, c
	  	var p = lb.trim().split(/[\s<>,]+/);	   
	    var fn =  ("/" + p.shift() + ".var").replace(/^\/\//g, "/");		
		if(lb.includes(">")){ // read:
		     SPIFFS._readAll(fn).split("\n").forEach(x=>{
			    var r = x.trim().split("="),
				slot = getVarNameNumber(r[0], s.index);
				if(p.includes( r[0].slice(1) )) s.VARS[slot] = parseInt(r[1], 10);	
			 });		    
		}else{ // export vars:
			let buff = [];
			p.forEach(a=>buff.push("$"+a+"="+s.VARS[getVarNameNumber("$"+a,s.index)]));
			SPIFFS._write(fn, buff.join("\n"));						
		}	  
        continue;
        break;
				
	
	      case LATER_on: // subscript pin change and other events
        //on= pin, sub[, FALLING|RISING|CHANGE|EDGE]
        // we have exit to sub top, and data of edge type pre-set
        pinCache = Number(lb, s.VARS); // pin
        varSlot = -1; // known handler? if so, grab event slot #
        for (var i = 0; i < LATER_EVENT_COUNT; i++) {
          if (pinCache == EVENT[i].pin) { // stop on first non-set slot, since -1 is default and matches varSlot
            varSlot = i;
            break;
          }
        }//next

        // at this point, we have pin#(pinCache & event[varSlot].pin), event slot (varSlot)

        if (varSlot > -1) { // known? run sub
          // compare sub with event object and parsed params
          tempInt = digitalRead(pinCache);
          if ( EVENT[varSlot].value != tempInt ) {
            // update last value:
            EVENT[varSlot].value = tempInt;
            EVENT[varSlot].ms = EVENT[varSlot].msNext;
            EVENT[varSlot].msNext = millis();
            Later.lastEventSlot = varSlot;
            if (l.data == 1 && tempInt != 1) continue; // rising only
            if (l.data == 2 && tempInt == 1) continue; // falling only
            s.subReturnLine = s.i;
            s.i = l.exit;
          }//end if change?
        } else { // unknown event, subscribe it by populating first empty event slot
          // find first unused slot:
          for (var i = 0; i < LATER_EVENT_COUNT; i++) {
            if (EVENT[i].pin == -1) {
              varSlot = i;
              break;
            }
          }//next
          EVENT[varSlot].pin = pinCache;
          EVENT[varSlot].value = digitalRead(pinCache);
          EVENT[varSlot].msNext = millis();
        }//end if known handler?
        s.eventSlot = varSlot;
        EVENT[varSlot].programSlot = s.index;

        continue;
        break;
		
		
		case LATER_csv:
		 let col = 0;
  let shouldExit = false;
  let nextColumn;
  let slot = 0, usedSlots = 0;
  const csv =  getCSV(linebuff, s);

   console.info(csv, lb);

  if (csv.morePointer) s.VARS[csv.morePointer] = 1;
  if (!csv.fn) shouldExit = true;

  let lineCursor = shouldExit ? null : laterUtil.getFileLine(csv.fn, csv.lineNeeded);
  if (!lineCursor) shouldExit = true;
  if (shouldExit) {
    if (csv.morePointer) s.VARS[csv.morePointer] = 0;
    if (csv.blockSize) s.i += csv.blockSize;
    csv.lineNeeded = 0;
    currentCsvState = null; // Reset state on exit
    return;
  }

  lineCursor += csv.delimStr;
  let parts = lineCursor.split(csv.delim);
  for (let i = 0; i < parts.length; i++) {
    if ((++col) >= csv.skip) {
      slot = csv.varSlots[usedSlots++];
      if (slot === 0) break;
      s.VARS[slot] = Number(parts[i], s.VARS);
    }
  } //wend nextColumn

  if (col === 0) {
    if (csv.morePointer) s.VARS[csv.morePointer] = 0;
    if (csv.blockSize) s.i += csv.blockSize;
    csv.lineNeeded = 0;
    currentCsvState = null; // Reset state on exit
    return;
  } else {
    if (csv.filter) {
      const rez = evalLite(csv.filter, s);
      if (!rez) {
        s.i++;
        return; // Non-destructive exit
      } //end if rez?
    } //end if filter?
  } //end if !col?
  
  continue;
  break;
		
		
		
		
 case LATER_pixel: // paint rgb leds
        runSetPixel(lb, s);
        continue;
        break;
      case LATER_render: // update painted rgb leds
        LATER_PIXEL_NAME.show();
        continue;
        break;
      case LATER_rotate: // update painted rgb leds
        runRotate( s.Number(lb) );
        continue;
        break;
      case LATER_grad:
        runGrad(lb, s);
        continue;
        break;
      case LATER_solid: // paint all rgb leds
        if (l.data == 1) {
          LATER_PIXEL_NAME.fill(0, LATER_PIXEL_NAME.numPixels());
          LATER_PIXEL_NAME.show();
          continue;
        }
        k = lb + 0;
        LATER_PIXEL_NAME.fill( laterUtil.parseColor(k, s), 0, LATER_PIXEL_NAME.numPixels() );
        LATER_PIXEL_NAME.show();
        continue;
        break;
		

      default:
        if (Later.addons[l.cmd]) {
          Later.addons[l.cmd](currentLinebuff, l, s);
          continue;
        }
		
		if(l.exit) s.i = l.exit;
        continue;	
		
        //if (s.options.debug) uniPrint("Err: Unknown Command");
		
        break;
    }
  }

  finishRun(s);
}




//////////////////////////////////////
///////////////////////////////////////////////////////////
////////////////////////////////////////////////

setTimeout(x=>Later.run('/test.bat'), 500);

function init(){
  Later.load("/test.bat");
}

setInterval(Later.loop.bind(Later), 20);

if(window.document){
 document.write("<h4 style='color:#fff;background:#000'>	<br>&nbsp;It Works!<hr> " +Date()+"<br><br></h4><br>" +`<button type="button" id="" class="" onclick="Later.run('/test.bat');">run test</button>`	);
}
console.log("parsed ok");
//</script>

