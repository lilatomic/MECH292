/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
#include <Servo.h> 


Servo claw_servo;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);		 // Initialize the LED_BUILTIN pin as an output
	pinMode(D1, OUTPUT);
	pinMode(D2, OUTPUT);
	pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	claw_servo.attach(D0);
}

// the loop function runs over and over again forever
void loop() {
	delay(2000);											// Wait for two seconds (to demonstrate the active low LED)
	int pos;

	for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
	{																	// in steps of 1 degree 
		claw_servo.write(pos);							// tell servo to go to position in variable 'pos' 
		delay(15);											 // waits 15ms for the servo to reach the position 
	} 
	for(pos = 180; pos>=0; pos-=1)		 // goes from 180 degrees to 0 degrees 
	{																
		claw_servo.write(pos);							// tell servo to go to position in variable 'pos' 
		delay(15);											 // waits 15ms for the servo to reach the position 
	}
	digitalWrite(D1,HIGH);
		delay(1000);
	digitalWrite(D2,HIGH);
		delay(1000); 
	digitalWrite(D3,HIGH); 
		delay(1000);
	digitalWrite(D4,HIGH); 
		delay(1000);
	digitalWrite(D1,LOW); 
		delay(1000);
	digitalWrite(D2,LOW); 
		delay(1000);
	digitalWrite(D3,LOW); 
		delay(1000);
	digitalWrite(D4,LOW); 
		delay(1000);
	
}
