/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
int r = 6; // Range Argument of your input move
int e1s = 0;int e1e=r;
int e2s = e1e+1;int e2e=e1e+r;
int e3s = e2e+1;int e3e=e2e+r;
int e4s = e3e+1;int e4e=e3e+r;

// defines pins numbers
const int trigPin = 3;
const int echoPin = 2;
// defines variables
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;

//@STCgoal Generating events in a  string for distance range
char evn = 'n';
if (distance > e1s && distance < e1e) evn = 'a';
else 
if (distance > e2s && distance < e2e) evn = 'b';
else 
if (distance > e3s && distance < e3e) evn = 'c';
else 
if (distance > e4s && distance < e4e) evn = 'd';
else evn = 'n';

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.print(distance);
if (evn != 'n'){
Serial.print(" Event: ");
Serial.println(evn);
}else Serial.println("");
}
