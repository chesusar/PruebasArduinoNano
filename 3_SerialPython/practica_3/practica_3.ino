
void setup() {
  Serial.begin(9600);
}

void loop() {
  float r = random(-20, 20)*0.1;
  Serial.print(r);
  Serial.print(";");
  Serial.print(r);
  Serial.print(";");
  Serial.print(r);
  Serial.println();
  delay(100);
}
