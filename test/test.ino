#include <Servo.h> 


Servo claw_servo;

void setup() {
	pinMode(D1, OUTPUT);
	pinMode(D2, OUTPUT);
	pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	claw_servo.attach(D0);
}

void loop() {
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
