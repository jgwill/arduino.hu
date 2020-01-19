int v = 0; //verbose level
/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
* Deeply altered to becoming the Arduino module of Mia's X200117 - Talking with Touch Designer
* By J.Guillaume D.Isabelle
* www.guillaumeisabelle.com/r/mia
*/

int r =6; // Range Argument of your input move
int dmin = 150; //distance min to interact

double edv = 1;
double e1v = 2;
double e2v = 3;
double e3v = 4;
double e4v = 5;
int e1s = 1;
int e1e = r;
int e1p = 6; //PIN light to validate.. might be removed
int e2s = e1e + 1;
int e2e = e2s + r;
int e2p = 7;
int e3s = e2e + 1;
int e3e = e3s + r;
int e3p = 8;
int e4s = e3e + 1;
int e4e = e4s + r;
int e4p = 9;


//-----------------------------IO
const int ledPin = 12; // LED pin number (use pin 13 for builtin LED)
const int analogInPin1 = A0; //@STCGoal Potentiometer
const int analogInPin2 = A1; //@STCGoal ???

//---------------------------
// defines pins numbers
const int trigPin = 3;// First Distance
const int echoPin = 2;
const int trigPin2 = 5; // Second Distance
const int echoPin2 = 4;
// defines variables
long duration;
int distance;
long duration2;
int distance2;
void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT);  // Sets the echoPin as an Input

  //turning lights when event occurs
  pinMode(e1p, OUTPUT);
  pinMode(e2p, OUTPUT);
  pinMode(e3p, OUTPUT);
  pinMode(e4p, OUTPUT);

  Serial.begin(9600); // Starts the serial communication

  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);

  // flash the LED to signal its working properly..
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(ledPin, 1); // turn on
    delay(100);
    digitalWrite(ledPin, 0); // turn off
    delay(100);
  }
}
void loop()
{

  int sensorValue1, sensorValue2;

  // read both analog inputs.

  sensorValue1 = analogRead(analogInPin1);
  sensorValue2 = analogRead(analogInPin2);

  //--------------------------------------------------
  //-----------------------------Distance reading---
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
  distance = duration * 0.034 / 2;

// Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2;

  //@STCgoal Generating events in a  string for distance range

  //char evn = 'n';

  double evn = 1;

  if (distance > e1s && distance < e1e)
  {
    evn = e1v;
    digitalWrite(e1p, HIGH);
  }
  else if (distance > e2s && distance < e2e)
  {
    evn = e2v;
    digitalWrite(e2p, HIGH);
  }
  else if (distance > e3s && distance < e3e)
  {
    evn = e3v;
    digitalWrite(e3p, HIGH);
  }
  else if (distance > e4s && distance < e4e)
  {
    evn = e4v;
    digitalWrite(e4p, HIGH);
  }
  else
  {
    evn = edv;
  }

  // Prints the distance on the Serial Monitor

  if (evn != 'n')
  {
    if (v > 0)
    {
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print(" Event: ");
    }

    //  Serial.print(evn);
  }
  // else
  //   Serial.println("");
if (distance > dmin) distance = dmin;

  sensorValue1 =  distance;// evn;
  sensorValue2 = distance2;


  //delay(80);
  digitalWrite(e1p, LOW);
  digitalWrite(e2p, LOW);
  digitalWrite(e3p, LOW);
  digitalWrite(e4p, LOW);

  //----------------------------------------------------
  // output values to serial.
  // Each value is prepended by a name label
  // for easier identification on the receiving side.
  Serial.print("A1=");
  Serial.print(sensorValue1);
  Serial.print(" ");
  Serial.print("A2=");
  Serial.print(sensorValue2);
  Serial.print("\n"); // use this instead of println to output only one delimiter
                      // println outputs \r\n

  // monitor incoming bytes.
  // in the case of '1' or '0' set LED output accordingly

  if (Serial.available())
  {
    char c = Serial.read();
    if (c == '1')
      digitalWrite(ledPin, 1); // turn on
    else if (c == '0')
      digitalWrite(ledPin, 0); // turn off
  }

  delay(20);
}
