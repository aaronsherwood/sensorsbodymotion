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

int lightPin = 0;  //define a pin for Photo resistor
int ledPin=11;     //define a pin for LED

void setup()
{
    Serial.begin(9600);  //Begin serial communcation
    pinMode( ledPin, OUTPUT );
}

void loop()
{
    int val = analogRead(lightPin);
    Serial.println(val); //Write the value of the photoresistor to the serial monitor.
    //send the value to the ledPin. Depending on value of resistor 
    //you have  to divide the value. for example, 
    //with a 10k resistor divide the value by 2, for 100k resistor divide by 4.
    analogWrite(ledPin, val/2);  
}
