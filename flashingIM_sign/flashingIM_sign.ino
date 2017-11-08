const int buttonPin = 2;     // the number of the pushbutton pin

//Need these for sign flashing
const int signPin =  13;
int counter = 0;
bool signOnOff = true;
bool flashing = false;
long flashCounter = 0;
long pMillis =0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(signPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  //pass in on off here
  flash_IM_Sign(buttonState);
}

void flash_IM_Sign(int onOff) {
  //adjust numbers for counter and flashCounter modulo to adjust speed
  //printing things out to serial will effect this greatly
  if (onOff == HIGH) {
    flashing = true;
    counter = 20000;
  }
  else if (flashing) {
    counter--;
  }
  if (flashing) {
    if (flashCounter % 1000 == 0)
      signOnOff = !signOnOff;
  }
  if (counter <= 0) {
    flashing = false;
    signOnOff = true;
  }

  digitalWrite(signPin, signOnOff);
  flashCounter++;

  if (flashCounter == 100000) flashCounter = 0;
}

