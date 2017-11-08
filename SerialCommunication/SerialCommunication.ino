/* Simple test of the functionality of the photo resistor

Connect the photoresistor one leg to pin 0, and pin to +5V
Connect a resistor (around 10k is a good value, higher
values gives higher readings) from pin 0 to GND. (see appendix of arduino notebook page 37 for schematics).

----------------------------------------------------

           PhotoR     10K
 +5    o---/\/\/--.--/\/\/---o GND
                  |
 Pin 0 o-----------

----------------------------------------------------
*/

const int lightPin = A0;  //define a pin for Photo resistor
const int buttonPin = 2;

void setup()
{
  Serial.begin(9600);  //Begin serial communcation
  pinMode(buttonPin, INPUT);
}

void loop()
{
  // read analog input pin 0
  int val = analogRead(lightPin);    
  int buttonState = digitalRead(buttonPin); 
  
  int outputValue = map(val, 300, 850, 0, 255);  
//Serial.println(val);
  sendToIsadora(1,constrain(outputValue, 0, 100));
  sendToIsadora(2,buttonState);

  delay(1);
}

void sendToIsadora(int route, int value)
{
  Serial.print(route);
  Serial.print('|');
  Serial.print(value);
  Serial.print(' ');
}

