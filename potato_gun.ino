#define FIRE_BUTTON_PIN 5
#define SAFETY_BUTTON_PIN 6
#define SAFETY_LIGHT_PIN 7
#define VALVE_PIN 8

#define DEBOUNCE_TIME 50

#define VALVE_OPEN_DURATION 500


boolean safety_on = false;
int safety_button_state;
int last_safety_button_state = LOW;
int fire_button_state;
int last_fire_button_state = LOW;

unsigned long last_safety_debounce_time = 0;
unsigned long last_fire_debounce_time = 0;

void setup() {
  pinMode(FIRE_BUTTON_PIN, INPUT);
  pinMode(SAFETY_BUTTON_PIN, INPUT);
  pinMode(SAFETY_LIGHT_PIN, OUTPUT);
  pinMode(VALVE_PIN, OUTPUT);

  digitalWrite(SAFETY_LIGHT_PIN, LOW);
  digitalWrite(VALVE_PIN, LOW);
}


void loop() {
  // reading safety button state with debouncing
  int current_safety_state = digitalRead(SAFETY_BUTTON_PIN);
  if (current_safety_state != last_safety_button_state) {
    last_safety_debounce_time = millis();
  }

  if ((millis() - last_safety_debounce_time) > DEBOUNCE_TIME) {
    if (current_safety_state != safety_button_state) {
      safety_button_state = current_safety_state;

      if (safety_button_state == HIGH) {
        digitalWrite(SAFETY_BUTTON_PIN, HIGH);
        safety_on = true;
      } else {
        digitalWrite(SAFETY_BUTTON_PIN, LOW);
        safety_on = false;
      }
    }
  }
  last_safety_button_state = current_safety_state;

  // reading fire button state with debouncing
  int current_fire_state = digitalRead(FIRE_BUTTON_PIN);
  if (current_fire_state != last_fire_button_state) {
    last_fire_debounce_time = millis();
  }

  if ((millis() - last_fire_debounce_time) > DEBOUNCE_TIME) {
    if (current_fire_state != fire_button_state) {
      fire_button_state = current_fire_state;

      if (fire_button_state == HIGH && safety_on) {
        digitalWrite(VALVE_PIN, HIGH);
        delay(VALVE_OPEN_DURATION);
        digitalWrite(VALVE_PIN, LOW);
      }
    }
  }
  last_fire_button_state = current_fire_state;
}
