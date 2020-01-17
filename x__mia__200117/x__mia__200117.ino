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

int r = 9; // Range Argument of your input move
int e1s = 1;
int e1e = r;
int e1p = 5;
int e2s = e1e + 1;
int e2e = e2s + r;
int e2p = 6;
int e3s = e2e + 1;
int e3e = e3s + r;
int e3p = 7;
int e4s = e3e + 1;
int e4e = e4s + r;
int e4p = 9;

// defines pins numbers
const int trigPin = 3;
const int echoPin = 2;
// defines variables
long duration;
int distance;
void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input

  //turning lights when event occurs
  pinMode(e1p, OUTPUT);
  pinMode(e2p, OUTPUT);
  pinMode(e3p, OUTPUT);
  pinMode(e4p, OUTPUT);

  Serial.begin(9600); // Starts the serial communication
}
void loop()
{
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

  //@STCgoal Generating events in a  string for distance range
  char evn = 'n';
  if (distance > e1s && distance < e1e)
  {
    evn = 'a';
    digitalWrite(e1p, HIGH);
  }
  else if (distance > e2s && distance < e2e)
  {
    evn = 'b';
    digitalWrite(e2p, HIGH);
  }
  else if (distance > e3s && distance < e3e)
  {
    evn = 'c';
    digitalWrite(e3p, HIGH);
  }
  else if (distance > e4s && distance < e4e)
  {
    evn = 'd';
    digitalWrite(e4p, HIGH);
  }
  else
  {
    evn = 'n';
  }

  // Prints the distance on the Serial Monitor

  if (evn != 'n')
  {  
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" Event: ");
    Serial.println(evn);
  }
  // else
  //   Serial.println("");

  delay(100);
  digitalWrite(e1p, LOW);
  digitalWrite(e2p, LOW);
  digitalWrite(e3p, LOW);
  digitalWrite(e4p, LOW);
}
