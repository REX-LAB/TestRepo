
#include <Servo.h>

Servo myservo;

// this is a comment
const boolean DEBUG = false;

const int panelButtonPin = 2;
const int panelInPin = 3;

const int panelNobPin = A0;
const int remoteNobPin = A1;  // the one connected through "CONTROL"

const int servoPin = 6;
const int servoShut = 10;
const int servoOpen = 100;

int panelButtonState = 0;
int panelInState = 0;
int panelNobVal = 0;
int remoteNobVal = 0;

int angle = 0;


void setup() {
	// define input pin, use internal pullup resistor
	// this means button needs to go from input pin to GND
	pinMode(panelButtonPin, INPUT);
	pinMode(panelInPin, INPUT);
	digitalWrite(panelButtonPin, HIGH);  // enable pull-up resistor
	digitalWrite(panelInPin, HIGH);  // enable pull-up resistor
	// init servo
	myservo.attach(servoPin);
	myservo.write(servoShut);

	if (DEBUG) {
		Serial.begin(9600);
	}
}


void loop() {
	panelButtonState = !digitalRead(panelButtonPin);
	panelInState = digitalRead(panelInPin);
	panelNobVal = analogRead(panelNobPin);
	remoteNobVal = analogRead(remoteNobPin);

	if (panelButtonState == HIGH && panelInState == HIGH) {
		// open serve to the higher value of the two nobs
		if (panelNobVal > remoteNobVal) {
			angle = map(1023-panelNobVal, 0, 1023, servoShut, servoOpen);
		} else {
			angle = map(1023-remoteNobVal, 0, 1023, servoShut, servoOpen);
		}

		if (DEBUG) {
			Serial.println(panelButtonState);
			Serial.println(panelInState);
			Serial.println(panelNobVal);
			Serial.println(remoteNobVal);
			Serial.println(angle);
			Serial.println("---");
			delay(600);
		}
	} else {
		angle = servoOpen;
	}

	myservo.write(angle);
	delay(50);
}
