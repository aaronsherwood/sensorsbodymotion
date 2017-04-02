const int ledPin1 = 9;
const int ledPin2 = 6;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int inputs[]={0,0,0,0,0,0,0,0,0};
int index=0;
void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  //write first LED based on first input  
  analogWrite(ledPin1,inputs[0]);
  //write second LED based on first input 
  analogWrite(ledPin2,inputs[1]);
}

//this will automatically call whenever serial information comes in
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    //if a new line, start over at  index 0 (input 0)
    if (inChar == '\n') {
      index=0;
    } else if (inChar == ','){ //if a comma add the current string to the current input
      inputs[index]=inputString.toInt();
      index++;
      inputString = "";
    }else{
      inputString += inChar;//otherwise keep adding chars to the string
    }
  }
}
