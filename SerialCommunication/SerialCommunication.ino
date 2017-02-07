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
}

void loop()
{
  // read analog input pin 0
  int val = analogRead(lightPin);    
  int buttonState = digitalRead(buttonPin); 
  
  int outputValue = map(val, 800, 875, 0, 255);

  // print a '1', this character will be
  // used as a parsing character
  Serial.print(1, DEC); 
  // prints the value read from the
  // button   
  Serial.print(buttonState, DEC);
  
  Serial.print(2, DEC); 
  // prints the value read from the
  // sensor in analog pin 0   
  Serial.println(constrain(outputValue, 0, 100), DEC);                     
  delay(1);
}
