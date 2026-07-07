int blinkCount = 0;
int potPin = A0;
int delayTime = 500;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read potentiometer value (0 to 1023)
  delayTime = analogRead(potPin); 

  digitalWrite(13, HIGH);
  delay(delayTime);
  digitalWrite(13, LOW);
  delay(delayTime);
  
  blinkCount++;
  Serial.print("Blink count: ");
  Serial.print(blinkCount);
  Serial.git checkoutprint(" | Delay: ");
  Serial.println(delayTime);
}
