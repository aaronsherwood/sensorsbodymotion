// just arbitrary values to test
int val1 = 1;
int val2 = 1;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 1;
int val7 = 0;
int val8 = 1;
int val9 = 0;
int val10 = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int val = 0;
  if (Serial.available() > 0) {
    val = Serial.read();
  }
  if (val == '!') {
    unsigned char byte1Send = (val1 << 7) | 
    (val2 << 6) | 
    (val3 << 5) | 
    (val4 << 4) | 
    (val5 << 3) | 
    (val6 << 2) | 
    (val7 << 1) | 
    (val8 & 0x01);
  
    unsigned char byte2Send = (val9 << 1) | (val10 & 0x01);
  
    Serial.write(byte1Send);
    Serial.write(byte2Send);
  }
  
}
