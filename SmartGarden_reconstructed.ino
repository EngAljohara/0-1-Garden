// 0/1 Garden (2023) — reconstructed and normalized from presentation slide 8.
// This is NOT a verified copy of the original sketch. Pin mapping and thresholds
// must be checked against the original circuit before connecting hardware.
const int moisturePin = A0;
const int pumpRelayPin = 3;
const int fanPin = 9;
int moisture = 0;

void setup() {
  pinMode(pumpRelayPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(pumpRelayPin, LOW);
  analogWrite(fanPin, 0);
}

void loop() {
  const int raw = analogRead(moisturePin);
  moisture = constrain(map(raw, 1017, 100, 0, 100), 0, 100);

  if (moisture < 20) {
    analogWrite(fanPin, 0);
    digitalWrite(pumpRelayPin, HIGH);
    Serial.println("The plants need water");
    Serial.println("PUMP ON");
  } else if (moisture > 70) {
    analogWrite(fanPin, 255);
    digitalWrite(pumpRelayPin, LOW);
    Serial.println("Plants have been watered");
    Serial.println("PUMP OFF");
  } else {
    // Safety-oriented reconstruction: turn both outputs off between thresholds.
    analogWrite(fanPin, 0);
    digitalWrite(pumpRelayPin, LOW);
  }

  Serial.print("Soil Moisture % = ");
  Serial.println(moisture);
  delay(1000);
}
