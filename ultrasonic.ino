#define LOOP_DELAY 1 // in ms
#define ECHO_PIN 7
#define TRIG_PIN 8
#define LED_PIN 13

#define PRE_PULSE_DURATION 2 // in us (microseconds)
#define PULSE_DURATION 10 // in us

#define MAX_RANGE 200 // in cm
#define MIN_RANGE 0 // in cm
#define OUT_OF_RANGE_MESSAGE "Out of range"

/*
Speed of sound is 340.29 m / s

So it goes 34.03 millimeters in 1 microsecond.
To find distance to object that "reflected" our sound pulse 
we need the time between sending a pulse and receiving the pulse (plus the pulse duration itself, btw)
divided by (34.03mm * 2) (because it goes forward and comes back)
so we get 68.06

1 us = 6.806 cm
x us = 1 cm

1 us * 1 cm = 6.806 cm * x
x = 1 / 6.806 (us * cm / cm)
x = 1 / 6.806 us

1 us / 6.806 cm = 0.1469 us/cm (is how much time it takes sound to go 1 cm)
e.g.: 1 us / 0.1469 us/cm = 6.8074 cm

*/
#define SPEED_OF_SOUND_QUOTIENT 0.1469 // in us/cm


long duration, distance; // Duration used to calculate distance

void setup() {
 Serial.begin (9600);
 pinMode(TRIG_PIN, OUTPUT);
 pinMode(ECHO_PIN, INPUT);
 pinMode(LED_PIN, OUTPUT);
}

void loop() {
 digitalWrite(TRIG_PIN, LOW); 
 delayMicroseconds(PRE_PULSE_DURATION); // Not really sure why we do this...

 digitalWrite(TRIG_PIN, HIGH);
 delayMicroseconds(PULSE_DURATION); 
 
 digitalWrite(TRIG_PIN, LOW);
 // Listen to the echo of the 10 microsecond 40k sound pulse we've just sent.
 duration = pulseIn(ECHO_PIN, HIGH);
 
 //Calculate the distance based on the speed of sound.
 distance = (duration - PULSE_DURATION) * SPEED_OF_SOUND_QUOTIENT;
 
 if (distance >= MAX_RANGE || distance <= MIN_RANGE){
  /* Send a negative number to the computer and Turn LED ON to indicate "out of range" */
   Serial.println(OUT_OF_RANGE_MESSAGE);
   digitalWrite(LED_PIN, HIGH);
 }
 else {
   /* Send the distance to the computer using Serial protocol, and turn LED OFF to indicate successful reading. */
   Serial.println(distance);
   digitalWrite(LED_PIN, LOW); 
 }
 
 //Delay before next reading.
 delay(LOOP_DELAY);
}
