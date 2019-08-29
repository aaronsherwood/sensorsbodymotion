/*
 * Wiring for IR range finder in kit is:
 * Black VCC
 * Red GND
 * Blue GND
 * Yellow VCC
 * Green A0 (data)
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A1));
  delay(1);
}
