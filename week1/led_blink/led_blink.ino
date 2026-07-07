/**
 * @file led_blink.ino
 * @author [Your Name]
 * @date July 2026
 * @brief Dynamic IoT LED blink tracking system with potentiometer speed control.
 * Assignment submission for IIT Jammu Summer School 2026.
 */

int blinkCount = 0;
int potPin = A0;
int delayTime = 500;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  delayTime = analogRead(potPin); 

  digitalWrite(13, HIGH);
  delay(delayTime);
  digitalWrite(13, LOW);
  delay(delayTime);
  
  blinkCount++;
  Serial.print("Blink count: ");
  Serial.print(blinkCount);
  Serial.print(" | Delay: ");
  Serial.println(delayTime);
}
