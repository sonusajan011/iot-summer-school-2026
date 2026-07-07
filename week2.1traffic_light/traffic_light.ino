/**
 * @file traffic_light.ino
 * @author [Your Name]
 * @date July 2026
 * @brief Traffic Light Controller with Immediate Pedestrian Override
 * Assignment submission for IIT Jammu Summer School 2026.
 */

// Pin Definitions
const int RED_LED = 11;
const int YELLOW_LED = 12;
const int GREEN_LED = 13;
const int BUTTON_PIN = 7;

// State Enumeration
enum TrafficState { STATE_RED, STATE_YELLOW, STATE_GREEN, STATE_PEDESTRIAN };
TrafficState currentState = STATE_RED;

// Timing Variables (in milliseconds)
unsigned long stateStartTime = 0;
unsigned long currentInterval = 5000; // Start with 5s for Red

void setup() {
  // Initialize LED Pins as outputs
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  // Initialize Button with Internal Pull-up Resistor
  // Button unpressed = HIGH, pressed = LOW
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize Serial Telemetry
  Serial.begin(9600);
  
  // Initial state execution
  setLightState(STATE_RED, 5000, "SYSTEM START: RED LIGHT ACTIVE");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // 1. Instantaneous Polling for Pedestrian Override
  // Active-LOW logic due to INPUT_PULLUP
  if (digitalRead(BUTTON_PIN) == LOW && currentState != STATE_PEDESTRIAN) {
    setLightState(STATE_PEDESTRIAN, 8000, "PEDESTRIAN OVERRIDE TRIGGERED");
    return; 
  }
  
  // 2. State Machine Time Tracking
  if (currentMillis - stateStartTime >= currentInterval) {
    switch (currentState) {
      case STATE_RED:
        setLightState(STATE_YELLOW, 2000, "TRANSITION: YELLOW LIGHT ACTIVE");
        break;
        
      case STATE_YELLOW:
        setLightState(STATE_GREEN, 4000, "TRANSITION: GREEN LIGHT ACTIVE");
        break;
        
      case STATE_GREEN:
      case STATE_PEDESTRIAN:
        // After Green or Pedestrian hold finishes, recycle back to normal Red
        setLightState(STATE_RED, 5000, "CYCLE RESTART: RED LIGHT ACTIVE");
        break;
    }
  }
}

/**
 * @brief Updates hardware pins, state indicators, variables, and outputs telemetry.
 */
void setLightState(TrafficState newState, unsigned long interval, String logMessage) {
  currentState = newState;
  currentInterval = interval;
  stateStartTime = millis();
  
  // Hardware Execution
  switch (currentState) {
    case STATE_RED:
    case STATE_PEDESTRIAN:
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      break;
    case STATE_YELLOW:
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      break;
    case STATE_GREEN:
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      break;
  }
  
  // Print Requirement: Current State Message + Timestamp
  Serial.print("[Timestamp: ");
  Serial.print(stateStartTime);
  Serial.print(" ms] -> ");
  Serial.println(logMessage);
}
