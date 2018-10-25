bool ledState = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0){
    int x =Serial.read();
    //x is storing a number
    //if we write that number to the serial monitor
    //the monitor inteprets that number as ascii
    Serial.write(x);
    //if we Serial.print that number, 
    //we print out the actual number, again as ascii
    Serial.println(x);

    if (x==104) //ascii number for h
      ledState = HIGH;
    if (x==108) //ascii number for l
      ledState = LOW;
      
    digitalWrite(2,ledState);
  }
}
