/*
 *	This sketch demonstrates how to set up a simple HTTP-like server.
 *	The server will set a GPIO pin depending on the request
 *		http://server_ip/gpio/0 will set the GPIO2 low,
 *		http://server_ip/gpio/1 will set the GPIO2 high
 *	server_ip is the IP address of the ESP8266 module, will be
 *	printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

const char* ssid = "";
const char* password = "";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

int ledPin = LED_BUILTIN;
WiFiClient client;
 
void setup() {
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
	
	// Connect to WiFi network
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
	
	WiFi.begin(ssid, password);
	
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
	
	// Start the server
	server.begin();
	Serial.println("Server started");
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
//	Serial.println(req);
	client.flush();
	
	// Match the request
	if (req.indexOf("/led/0") != -1)
		digitalWrite(ledPin, 0);
	else if (req.indexOf("/led/1") != -1)
		digitalWrite(ledPin, 1);
    else if (req.indexOf("/go/f") != -1)
    	digitalWrite(l, );
    else if (req.indexOf("/go/b") != -1)
    	digitalWrite(l, );
    else if (req.indexOf("/go/r") != -1)
    	digitalWrite(l, );
    else if (req.indexOf("/go/l") != -1)
    	digitalWrite(l, );
    else if (req.indexOf("/go/s") != -1)
    	digitalWrite(l, );
    else if (req.indexOf("/grip/1") != -1)
    	digitalWrite(l, );
    else if (req.indexOf("/grip/0") != -1)
    	digitalWrite(l, );
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
	client.print("HTTP/1.1 200 OK\r\n");
	delay(1);
//	Serial.println("Client disonnected");

	// The client will actually be disconnected
	// when the function returns and 'client' object is detroyed

	client.stop();
}

