//Con el siguiente link se producira el blink de led
#define LED 19
int tiempo=4000;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  Serial.println("LED is on");
  delay(tiempo);
  digitalWrite(LED, LOW);
  Serial.println("LED is off");
  delay(tiempo);
}