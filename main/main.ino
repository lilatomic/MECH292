
#include <ESP8266WiFi.h>
#include <Servo.h>
#include "FS.h"

const char WiFiAPPSK[] = "mech292";
const char* jquery_string = "";
const char* page = R"(<!DOCTYPE HTML>
<html>
<style type="text/css">
form,table {
 display:inline;
  margin:px;
  padding:px;
}
</style>
<head>
<script
  src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>

<script>
$(document).keypress(function(e){
    var checkWebkitandIE=(e.which==97 ? 1 : 0);
    var checkMoz=(e.which==97 ? 1 : 0);
    if (checkWebkitandIE || checkMoz) $.post("/go/l");
});
</script>
<script>
$(document).keypress(function(e){
    var checkWebkitandIE=(e.which==115 ? 1 : 0);
    var checkMoz=(e.which==115 ? 1 : 0);
    if (checkWebkitandIE || checkMoz) $.post("/go/b");
});
</script>
<script>
$(document).keypress(function(e){
    var checkWebkitandIE=(e.which==100 ? 1 : 0);
    var checkMoz=(e.which==100 ? 1 : 0);
    if (checkWebkitandIE || checkMoz) $.post("/go/r");
});
</script>
<script>
$(document).keypress(function(e){
    var checkWebkitandIE=(e.which==119 ? 1 : 0);
    var checkMoz=(e.which==119 ? 1 : 0);
    if (checkWebkitandIE || checkMoz) $.post("/go/f"));
});
</script>
<script>
$(document).keypress(function(e){
    var checkWebkitandIE=(e.which==120 ? 1 : 0);
    var checkMoz=(e.which==120 ? 1 : 0);
    if (checkWebkitandIE || checkMoz) $.post("/go/s");
});
</script>
  
</head>

Led pin is now: On
<br>
<form action = "/go/f" method = "get">
  <input type="submit" value="forward" />
</form>
<br>
<form action = "/go/l" method = "post">
  <input type="submit" value="go/l" />
</form>
<form action = "/go/s" method = "post">
  <input type="submit" value="go/s" />
</form>
<form action = "/go/r" method = "post">
  <input type="submit" value="go/r" />
</form>
<br>
<form action = "/go/b" method = "post">
  <input type="submit" value="Backwards" />
</form>
<br>

<br>
Click <a href="/LED=ON">here</a> turn the LED on pin 5 ON<br>
</html>
 )";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

int ledPin = LED_BUILTIN;
Servo claw_servo;
int leftPinA = D1;
int leftPinB = D2;
int rightPinA = D3;
int rightPinB = D4;
 
void setupWiFi()
{
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESP8266 Thing " + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);

//  SPIFFS.begin();
//  Dir dir =SPIFFS.openDir("/data");
//  server.serverStatic("/jquery-3.2.1.min.js", SPIFFS, "/data/jquery-3.2.1.min.js");
}

void initHardware()
{
  Serial.begin(115200);
  delay(10);

  // sets up pins
  pinMode(LED_BUILTIN, OUTPUT);		 // Initialize the LED_BUILTIN pin as an output
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  claw_servo.attach(D0);
  
  
  digitalWrite(ledPin, 0);
}
  
void setup()
{
    initHardware();
    setupWiFi();
    server.begin();
}

void loop() {
	// Check if a client has connected
	WiFiClient client = server.available();
	if (!client) {
		return;
	}
	
	// Wait until the client sends some data
//	Serial.println("new client");
	while(!client.available()){
		delay(1);
	}
	
	// Read the first line of the request
	String req = client.readStringUntil('\r');
	Serial.println(req);
	client.flush();
	
	// Match the request
	if (req.indexOf("/led/0") != -1)
		digitalWrite(ledPin, 0);
	else if (req.indexOf("/led/1") != -1)
		digitalWrite(ledPin, 1);
    else if (req.indexOf("/go/f") != -1)
    {
    	digitalWrite(leftPinA, 1);
        digitalWrite(leftPinB, 0);
        digitalWrite(rightPinA, 1);
        digitalWrite(rightPinB, 0);
    }
    else if (req.indexOf("/go/b") != -1)
    {
    	digitalWrite(leftPinA, 0);
        digitalWrite(leftPinB, 1);
        digitalWrite(rightPinA, 0);
        digitalWrite(rightPinB, 1);
    }
    else if (req.indexOf("/go/r") != -1)
    {
    	digitalWrite(leftPinA, 0);
        digitalWrite(leftPinB, 1);
        digitalWrite(rightPinA, 1);
        digitalWrite(rightPinB, 0);
    }
    else if (req.indexOf("/go/l") != -1)
    {
    	digitalWrite(leftPinA, 1);
        digitalWrite(leftPinB, 0);
        digitalWrite(rightPinA, 0);
        digitalWrite(rightPinB, 1);
    }
    else if (req.indexOf("/go/s") != -1)
    {
    	digitalWrite(leftPinA, 0);
        digitalWrite(leftPinB, 0);
        digitalWrite(rightPinA, 0);
        digitalWrite(rightPinB, 0);
    }
    else if (req.indexOf("/grip/1") != -1)
    {
        for(int pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees
        {																	// in steps of 1 degree
            claw_servo.write(pos);							// tell servo to go to position in variable 'pos'
            delay(15);											 // waits 15ms for the servo to reach the position
        }

    }
    else if (req.indexOf("/grip/0") != -1)
    {
        for(int pos = 180; pos>=0; pos-=1)		 // goes from 180 degrees to 0 degrees
    	{
    		claw_servo.write(pos);							// tell servo to go to position in variable 'pos'
    		delay(15);											 // waits 15ms for the servo to reach the position
    	}
    }
	else if (req.indexOf("/home") != -1)
	{
		client.println(page);
	}
 else if (req.indexOf("/jquery") != -1)
 {
   client.println(jquery_string);
 }
	else {
		Serial.println("invalid request");
		client.stop();
		return;
	}
	
	client.flush();

	// Prepare the response
//	String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
//	s += (val)?"high":"low";
//	s += "</html>\n";
	

	// Send the response to the client
  client.println(page);
	client.print("HTTP/1.1 200 OK\r\n");
	delay(1);
//	Serial.println("Client disonnected");

	// The client will actually be disconnected
	// when the function returns and 'client' object is detroyed

	client.stop();
}

