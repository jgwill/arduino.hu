/*

 Simple in/out connection from
 Arduino Duemilanove to TouchDesigner
 created Jan 2010
 Rob Bairos
 support@derivative.ca
 www.derivative.ca
 This example code is in the public domain.

 Measure the light falling on a photocell, 
 and the value of a potentiometer, send it through the serial port.
 Control the state of an LED through the serial port.
 
 Be sure to turn off Active parameter in the TouchDesigner Serial In DAT
 while uploading new sketches to the board.  Otherwise uploading is disabled
 as the serial connection is in use.
 
 The circuit:
 * LED:  short side connected to 330 ohm resistor, other side of resistor connected to ground,
         long side connected to pin 23.
         Value of the resistor dependent on LED type. (Some may not require resistor).
         If you dont have an LED, use the onboard Arduino Duemilanove LED and set ledPin=13
         
 * Photocell:
         Used a Cadmium Sulfide Photo resistor, but not crucial.
         One leg connected to 5v
         Other leg connected to Analog0
         10K resistor connected from Analog0 to ground, to form a simple voltage divider network
         
 * Potentiometer
         100K pot
         Outside leg connected to 5v
         Other outside leg connected to Gnd
         Middle leg connected to Analog1
 */

// constants won't change. Used here to 
// set pin numbers:
const int ledPin =  12;      // LED pin number (use pin 13 for builtin LED)
const int analogInPin1 = A0;
const int analogInPin2 = A1;


void setup() 
{  
  Serial.begin(9600);  // match default TouchDesigner Serial In DAT baudrate.
  
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);      
  
  // flash the LED to signal its working properly..
  for (int i=0; i<3; i++)
  {
    digitalWrite(ledPin, 1);  // turn on
    delay(200);
    digitalWrite(ledPin, 0);  // turn off
    delay(200);
  }
  
}

void loop()
{
  int  sensorValue1, sensorValue2;
  
  // read both analog inputs.
  
  sensorValue1 = analogRead(analogInPin1);
  sensorValue2 = analogRead(analogInPin2);

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
      digitalWrite(ledPin, 1);  // turn on
    else if (c == '0')
      digitalWrite(ledPin, 0);  // turn off
  }
}
