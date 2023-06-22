
#define LED 19

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  Serial.println("LED is on");
  delay(2000);
  digitalWrite(LED, LOW);
  Serial.println("LED is off");
  delay(2000);
}