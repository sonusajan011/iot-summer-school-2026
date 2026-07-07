/**
 * @file digital_piano.ino
 * @brief 4-Key Digital Piano with Scale Toggle and Chord Substitutes
 * Assignment submission for IIT Jammu Summer School 2026.
 */

// Pin Definitions
const int BTN_DO = 2;
const int BTN_RE = 3;
const int BTN_MI = 4;
const int BTN_FA = 5;
const int BTN_TOGGLE = 6; // 5th Button for Mode Toggle
const int BUZZER_PIN = 9;

// Frequencies
const int NOTE_SOL = 392;

// Scale Configurations [Do, Re, Mi, Fa]
const int majorScale[] = {262, 294, 330, 349}; // Standard C Major
const int minorScale[] = {262, 294, 311, 349}; // C Natural Minor (Eb/311Hz replaces E/330Hz)

bool isMinorMode = false;
bool lastToggleState = HIGH;

void setup() {
  pinMode(BTN_DO, INPUT_PULLUP);
  pinMode(BTN_RE, INPUT_PULLUP);
  pinMode(BTN_MI, INPUT_PULLUP);
  pinMode(BTN_FA, INPUT_PULLUP);
  pinMode(BTN_TOGGLE, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Read scale toggle button (with state-change detection logic)
  bool currentToggleState = digitalRead(BTN_TOGGLE);
  if (currentToggleState == LOW && lastToggleState == HIGH) {
    isMinorMode = !isMinorMode; // Switch modes
    delay(50); // Software debounce handling
  }
  lastToggleState = currentToggleState;

  // Read piano keys
  bool pressDo = (digitalRead(BTN_DO) == LOW);
  bool pressRe = (digitalRead(BTN_RE) == LOW);
  bool pressMi = (digitalRead(BTN_MI) == LOW);
  bool pressFa = (digitalRead(BTN_FA) == LOW);

  int totalPressed = pressDo + pressRe + pressMi + pressFa;

  // Pointer selection based on system mode flag
  const int* currentScale = isMinorMode ? minorScale : majorScale;

  // Execution Logic
  if (totalPressed >= 2) {
    tone(BUZZER_PIN, NOTE_SOL);
  } else if (pressDo) {
    tone(BUZZER_PIN, currentScale[0]);
  } else if (pressRe) {
    tone(BUZZER_PIN, currentScale[1]);
  } else if (pressMi) {
    tone(BUZZER_PIN, currentScale[2]);
  } else if (pressFa) {
    tone(BUZZER_PIN, currentScale[3]);
  } else {
    noTone(BUZZER_PIN);
  }
}
