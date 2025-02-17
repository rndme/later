#include "Arduino.h"

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
//Global variables use 52416 bytes (63%) of dynamic memory, leaving 29504 bytes for local variables. Maximum is 81920 bytes.
// USING LATER, see https://github.com/rndme/later
/////////////////////////////////////
// top-line later config:
#define LATER_PROJECT "My Project"
#define LATER_SERVER_NAME server
#define LATER_UART_PORT Serial
#define LATER_EDITOR_URL "http://pagedemos.com/je6x6mwhvgbn/js"

// options disabled by default:
//#define LATER_ARRAY 1 // uncomment to enable (esp32 only) +256b
//#define LATER_UART_PORT_DISABLE 1
//#define SAMPLER_ENABLED 1  // +984b
//#define HIGH_RES_TIMING Serial


// boiler plate:
const char LATER_SKETCH[128] = __FILE__;

// Prefrences definitions:
struct Prefs {
	String wifi_ssid;   // wifi network name to connect to
	String wifi_pw;     // wifi password
	bool wifi_sockets;  // enable websockets?
	bool wifi_http;     // enable http API?
	bool wifi_update;   // enable http over the air firmware upgrades?
	String wifi_ip;     // optional hard-coded IP to use instead of waiting for DHCP
};
Prefs PREFS = {
	/* wifi */ "the good one", "ffffffffffff", true, true, true, ""
};
Prefs oldPREFS;


/////////////////////////////////////////////////////////////
// per device class configs, taking advantage of ram and speed:
#ifdef ESP8266

// instead of 4, allow 3 scripts:
#define LATER_INSTANCES 3
// chop log size by half to 2kb from 4kb:
#define LATER_LOG_SIZE 1678
// allow larger programs 1.4k instead of 1k:
#define LATER_PROGRAM_SIZE 1024
#define LATER_LINE_BUFFER 128
#define LATER_LINE_LIMIT 96
#define LATER_HTTP_CACHE 900

//52940 bytes (64%) of dynamic memory, leaving 28980 with 128/96 x3
//54596 bytes (66%) of dynamic memory, leaving 27324 with 128/96 x4
//49852 bytes (60%) of dynamic memory, leaving 32068 with 80/64 x3
//52500 bytes (64%) of dynamic memory, leaving 29420 with 80/64 x4
// with newer festures: 51676 bytes (63%) of dynamic memory, leaving 30244 128/96 x 3
// ESP8266
extern "C" {
#include "user_interface.h"
}

#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
#include <ESP8266HTTPUpdateServer.h>
ESP8266HTTPUpdateServer httpUpdater;
#include <ESP8266HTTPClient.h>
HTTPClient http;  // poin
#include <core_esp8266_waveform.h>

//#pragma GCC optimize ("O3")
#pragma GCC optimize("Ofast")


//53312 bytes (65%) of dynamic memory, leaving 28608  O3
//53328 bytes (65%) of dynamic memory, leaving 28592  O2
//53328 bytes (65%) of dynamic memory, leaving 28592  O1
//53312 bytes (65%) of dynamic memory, leaving 28608  Ofast
#else
///////////////////////////////////////
// ESP32

// with more beef:
// instead of 4, allow 5 scripts:
#define LATER_INSTANCES 5
// bump up log size from 4kb from 16kb:
#define LATER_LOG_SIZE 16384
// allow larger programs 2k instead of 1k:
#define LATER_PROGRAM_SIZE 2048
#define LATER_LINE_BUFFER 160
#define LATER_LINE_LIMIT 256
#define LATER_HTTP_CACHE 2400

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WebServer.h>
WebServer server(80);
#include "SPIFFS.h"
#include <HTTPClient.h>
HTTPClient http;
#include <Update.h>

#include <WebSocketsServer.h>
WebSocketsServer webSocket = WebSocketsServer(81);

#endif
/////////////////////////////////////////////////////////
//end ESP 8266 / 32 split
///////////////////////////////////
unsigned long loops = 0;  // handy for sever things, increments in loop()

// dht temp stuff
//#include <DHT.h>
//DHT dht(5, DHT11);

#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "time.nist.gov", 18000, 960000); // 6 hours behind gmt
NTPClient timeClient(ntpUDP, "time.nist.gov", -21600, 960000);  // 5 hours behind gmt

//NTPClient timeClient(ntpUDP, "time.nist.gov", 0, 960000);
//setTimeOffset(int timeOffset)
//setUpdateInterval(unsigned long updateInterval)
//



#include <later.h>

#ifdef LATER_ARRAY
unsigned long ARRAY_LENGTH = 0;
const unsigned long ARRAY_LIMIT = 64;
unsigned long ARRAY[ARRAY_LIMIT];
char numArg[5];
#endif



char s1[64] = "now is the time for all good men";
char s2[64] = "now is the time for all good men";

unsigned long VARS2[57] = { 11, 22, 33, 44, 55, 66, 77 };  // holds variable values

unsigned long Number2(const char* str, const unsigned long* VARS) {
	while (str[0] == ' ') str++;  // fast left-side trim
	if (str[0] == '@') {          // && str[2] == '_') {
		return VARS2[str[1] - 65];
	} else {
		return strtoul(str, NULL, 10);  // atoi(str);
	}
}  //end Number2()

///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void setup() {

#ifdef ESP8266
	SPIFFS.begin();
#else
	SPIFFS.begin(true);
#endif

	pinMode(0, INPUT_PULLUP);

	// default analog read/write to 10 bit at 2khz to avoid flicker
#ifdef ESP8266
	system_update_cpu_freq(SYS_CPU_160MHZ);
	wifi_set_sleep_type(NONE_SLEEP_T);
	analogWriteRange(1023);
	analogWriteFreq(2048);
#else
	//	analogWriteFrequency(2048);
	//	analogWriteResolution(10);
	analogReadResolution(10);
#endif

	Serial.begin(115200);

	loadConfig();

	server.on("/cfg/", handleConfig);
	server.on("/config/", handleConfigInterface);
	server.on("/lang/", handleConfigLang);
	server.on("/lang", handleConfigLang);

	WiFi.disconnect();
	WiFi.mode(WIFI_STA);
#ifdef ESP8266
	WiFi.hostname(LATER_PROJECT);  //esp8266
#else
	WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
	WiFi.setHostname(LATER_PROJECT);  //esp32
#endif

	Serial.println("\n");


	Serial.println("C++:" + String(__cplusplus));

	//WiFi.begin(ssid, password);
	WiFi.begin(PREFS.wifi_ssid, PREFS.wifi_pw);


	while (WiFi.status() != WL_CONNECTED) {
		delay(150);
		Serial.print(".");
	}

	Serial.print("\nOnline at http://");
	Serial.print(WiFi.localIP());
	Serial.print("/\nWifi MAC: ");
	Serial.println(WiFi.macAddress());

	server.begin();
	timeClient.begin();

#ifdef ESP8266
	httpUpdater.setup(&server);
#endif

	// later expansions and config
	/////////////////////////////////////////////////////
	if (!digitalRead(0)) {
		Serial.println(F("Later - SAFE MODE ENABLED (no autoexec)"));
	} else {

#ifdef LATER_ARRAY
		addLaterArrays();
#endif

#ifdef LATER_PORT
		Later.addCommand("config", [](char* v, LATER_LINE* ln, LATER_ENVIRON* scr) -> bool {
			// parse name from line or v buffer
			char keyBuffer[32];
			char valueBuffer[32];

			while (isSpace(v[0])) v++;  // trim whole line left

			// copy key into buffer and cleanup:
			strcpy(keyBuffer, v);
			char* eqSlot = strchr(v, '=') + 1;
			int keyLen = (eqSlot - 1) - v;
			while (isSpace(keyBuffer[keyLen])) keyLen--;  // trim buffer right
			keyBuffer[keyLen - 1] = '\0';

			// find where the value starts
			while (isSpace(eqSlot[0])) eqSlot++;

			// find length of value
			int i = strcspn(eqSlot, " ;,");

			// copy value to valueBuffer
			strncpy(valueBuffer, eqSlot, i + 1);

			eqSlot += i;
			setConfig(keyBuffer, valueBuffer);
			if (strstr(eqSlot, "SAVE")) saveConfig();
			if (strstr(eqSlot, "APPLY")) APPLY_CONFIG();

			return true;
		});  // using lambda
#endif

		Later.addCommand("wipe", [](char* v, LATER_LINE* ln, LATER_ENVIRON* scr) -> bool {
			return (nsLATER::setRunLog[0] = '\0');
		});                                           // using lambda
		Later.addTemplate("{zip}", TEMPLATE(90210));  // using TEMPLATE MACRO
		Later.addTemplate("{loops}", TEMPLATE(loops));

		Later.addCommand("serial", [](char* v, LATER_LINE* ln, LATER_ENVIRON* scr) -> bool {
			nsLATER::uniPrintln(v);
			return 1;
		});  // using lambda

		Later.addFunction("LOOPOPT", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0) [[gnu::pure]] noexcept -> unsigned long {
			a = esp_get_cycle_count();
			long x = 0;
			//for(int i=0;i<1000; i++) x = x + 1;
			while (x < 500000) x += esp_get_cycle_count() % 4;
			if (x % 2) a++;
			return esp_get_cycle_count() - a;
		});






//var symbol:	47,665, literal:	791,437 @ 10000 reps, static code
//var symbol:	656615, literal:	4378385   var is faster by:	6x // with char rep each line
//var symbol:	229415, literal:	3948361   var is faster by:	17x // with bare code, no reps
//var symbol:	188058, literal:	3908867   var is faster by:	20x // with bare code, no reps, no leading space



		Later.addFunction("RUNNUM", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0) [[gnu::pure]] noexcept -> unsigned long {
			unsigned long tot;
			long mx = 5000;
			//char bs = 1;
			char exp1[] = "@b_  and some more text ";
			char exp2[] = "14  and some more text ";

			a = esp_get_cycle_count();
			for (int i = 0; i < mx; i++) {
				//	bs = (i % 20) + 65;
				//	exp1[8] = bs;
				tot += Number2(exp1, VARS2);
			}
			b = esp_get_cycle_count();
			for (int i = 0; i < mx; i++) {
				//	bs = (i % 20) + 65;
				//	exp2[8] = bs;
				tot += Number2(exp2, VARS2);
			}
			c = esp_get_cycle_count();
			Serial.println("var symbol:\t" + String(b - a) + ", literal:\t" + String(c - b));
			Serial.println("symbol is faster by:\t" + String((c - b) / (b - a)) + "x");

			//		Serial.println("s1:" + String(s1));
			//		Serial.println("s2:" + String(s2));
			return c - a;
		});





  Later.addTemplate("{test}", TEMPLATE(RANDOM_REG32 % 8));

	Later.addFunction("TST", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0) -> unsigned long {
		return (RANDOM_REG32 % 8);
	});





		Later.addFunction("DUMPEV", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0) -> unsigned long {
			nsLATER::uniPrintln("lasteventslot:" + String(Later.lastEventSlot));
			for (int i = 0; i < 3; i++) {

				nsLATER::uniPrintln("\ne slot:" + String(i));
				nsLATER::uniPrintln("program:" + String(nsLATER::EVENT[i].programSlot));
				nsLATER::uniPrintln("value:" + String(nsLATER::EVENT[i].value));
				nsLATER::uniPrintln("ms:" + String(nsLATER::EVENT[i].ms));
				nsLATER::uniPrintln("msnext:" + String(nsLATER::EVENT[i].msNext));
				nsLATER::uniPrintln("pin:" + String(nsLATER::EVENT[i].pin));
			}

			return 666;
		});



#ifdef ESP8266
		Later.addFunction("WAVE", [](unsigned long pin = 0, unsigned long duty = 0, unsigned long freq = 0) -> unsigned long {
			duty = duty % 1023;
			if (freq == 0) freq = 1000;
			unsigned long period = 1000000 / freq;
			unsigned long on = (period * duty) / 1023;
			Serial.println("WAVE on:" + String(on) + ", duty:" + String(duty) + ", off:" + String(period - on) + ", period:" + String(period));
			if (duty == 0) {
				stopWaveform(pin);
				digitalWrite(pin, 0);
				return 0;
			} else {
				return startWaveform(pin, on, period - on, 0);
			}
		});
#endif
		/*
      #ifdef ESP32
      Later.addFunction("WAVE", [](unsigned long pin = 0, unsigned long duty = 0, unsigned long freq = 0)->unsigned long {
      duty = duty % 1023;
      if (freq == 0) freq = 1000;
      Serial.println("WAVE duty:" + String(duty) + ", pin:" + String(pin) + ", freq:" + String(freq));
      if (duty == 0) {
        ledcDetachPin(pin);
        digitalWrite(pin, 0);
        return 0;
      } else{
        ledcSetup(0, freq, 10); // Configure the LEDC channel with a starting frequency of 1000 Hz
        ledcAttachPin(pin, 0); // Assign the pin to the LEDC channel
        ledcWriteTone(0, freq); // Sets the frequency of the LEDC channel
        ledcWrite(0, duty); // Set duty cycle to 50% (128 of 256 for 8-bit resolution)
      }
      return 1;
      }); // using lambda
      #endif


    */



#ifdef ESP32
		Later.addFunction("RNDCH", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0) -> unsigned long {
			return esp_random();
		});
		Later.addTemplate("{tempEsp}", TEMPLATE(temperatureRead()));
#endif
		Later.setup();
	}  // end if gpio 0 grounded just after startup? don't load dan scripts (safe mode)
	   /////////////////////////////////////////////////////

}  //end setup()

void loop() {
	if ((loops % 1533) == 0) timeClient.update();
	server.handleClient();
	Later.loop();
	delay(0);
	loops++;
}
