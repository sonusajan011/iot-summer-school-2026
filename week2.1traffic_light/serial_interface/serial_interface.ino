/**
 * @file serial_interface.ino
 * @author [Your Name]
 * @date July 2026
 * @brief Robust Serial Command Processing Interface with Input Validation
 * Assignment submission for IIT Jammu Summer School 2026.
 */

const int TARGET_LED = LED_BUILTIN; // Maps directly to Pin 13 on Arduino Uno
int operationalBlinkCount = 0;

void setup() {
  pinMode(TARGET_LED, OUTPUT);
  Serial.begin(9600);
  
  // Clear any residual buffer data and signal system ready
  while(Serial.available() > 0) { Serial.read(); }
  Serial.println("SYSTEM INITIALIZED. ENTER COMMANDS:");
}

void loop() {
  // Check if bytes are waiting to be read from the serial hardware cache
  if (Serial.available() > 0) {
    // Read string until newline character '\n'
    String inputCommand = Serial.readStringUntil('\n');
    
    // Sanitize string data: strip tracking carriage returns or whitespace variations
    inputCommand.trim();
    
    // Ignore accidental completely empty inputs
    if (inputCommand.length() == 0) return;

    // Command Parser Evaluation Engine
    if (inputCommand.equals("LED_ON")) {
      digitalWrite(TARGET_LED, HIGH);
      Serial.println("SUCCESS: LED is turned ON");
      
    } else if (inputCommand.equals("LED_OFF")) {
      digitalWrite(TARGET_LED, LOW);
      Serial.println("SUCCESS: LED is turned OFF");
      
    } else if (inputCommand.startsWith("BLINK_")) {
      // Extract the 'X' character position
      String countValueStr = inputCommand.substring(6); 
      int blinkRequested = countValueStr.toInt();
      
      // Validation Check: Must be a singular digit between 1 and 9
      if (countValueStr.length() == 1 && blinkRequested >= 1 && blinkRequested <= 9) {
        Serial.print("SUCCESS: Executing blink cycle ");
        Serial.print(blinkRequested);
        Serial.println(" times.");
        
        for (int i = 0; i < blinkRequested; i++) {
          digitalWrite(TARGET_LED, HIGH);
          delay(250);
          digitalWrite(TARGET_LED, LOW);
          delay(250);
          operationalBlinkCount++;
        }
      } else {
        Serial.println("ERROR: Unknown command");
      }
      
    } else if (inputCommand.equals("STATUS")) {
      int currentPinState = digitalRead(TARGET_LED);
      Serial.println("--- SYSTEM STATUS ---");
      Serial.print("Built-in LED Pin State: ");
      Serial.println(currentPinState == HIGH ? "HIGH (ON)" : "LOW (OFF)");
      Serial.print("Total Cumulative Blinks Executed: ");
      Serial.println(operationalBlinkCount);
      Serial.println("---------------------");
      
    } else if (inputCommand.equals("RESET")) {
      operationalBlinkCount = 0;
      Serial.println("SUCCESS: Cumulative blink counter reset to zero");
      
    } else {
      // Fallback input validation default
      Serial.println("ERROR: Unknown command");
    }
  }
}
