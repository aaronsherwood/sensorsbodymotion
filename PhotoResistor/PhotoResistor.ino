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

int lightPin = A0;  //define a pin for Photo resistor
int ledPin = 9;     //define a pin for LED
int smoothed = 0;

void setup()
{
    Serial.begin(9600);  //Begin serial communcation
    pinMode( ledPin, OUTPUT );
}

void loop()
{
    int val = analogRead(lightPin);
    Serial.println(val); //Write the value of the photoresistor to the serial monitor.
//    int mapped = map(val, 740, 892, 255, 0);
//    int constrained = constrain(mapped, 0, 255);
//    analogWrite(ledPin, constrained); 
//    delay(1); 
}
