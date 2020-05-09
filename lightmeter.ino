int led = A5; // LED to give us immediate feedback (usefull for debugging)
int photosensor = A0; // This is where your photoresistor or phototransistor is plugged in. The other side goes to the "power" pin (below).
int lightReading; // Here we are declaring the integer variable analogvalue, which we will use later to store the value of the photoresistor or phototransistor.
int lastReading; // Previous reading so we can track the changes not the reading.

void setup() {
	Serial.begin(9600);
	pinMode(led, OUTPUT); // Our LED pin is output (lighting up the LED)
	pinMode(photosensor, INPUT);
	lastReading = 0;
}


// Next is the loop function...
void loop() {

	lightReading = analogRead(photosensor);
	Serial.printlnf("%d", lightReading);
	// If the light reading is under 15 turn the the light on.
	if ((lightReading > 90) && (lastReading <= 90)) {
	    digitalWrite(led,HIGH);
	    String measurements = String(lightReading);
	    Particle.publish("light-level-changed", "in sunlight", PRIVATE);
	    lastReading = lightReading;
	} else if ((lightReading <= 90) && (lastReading > 90)) {
	    digitalWrite(led,LOW);
	    Particle.publish("light-level-changed", "out of sunlight", PRIVATE);
	    lastReading = lightReading;
	}

	// Some delay required to prevent overflowing the serial buffer
	delay(60000);
}