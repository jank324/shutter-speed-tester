const int SENSOR_PIN = 3;
long t1, t2 = 0;
bool is_open = false;
bool has_fired = false;

void setup() {
    Serial.begin(9600);
    pinMode(SENSOR_PIN, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), shutter_action, CHANGE);
    Serial.println("Ready!");
}

void loop() {
    if (has_fired) {
        long microseconds = t2 - t1;
        float fraction = 1000000 / (float)microseconds;
        Serial.print("Measured shutter speed: 1/");
        Serial.print(fraction);
        Serial.print(" s (");
        Serial.print(microseconds);
        Serial.println(" microseconds)");
        has_fired = false;
    }
    digitalWrite(LED_BUILTIN, digitalRead(SENSOR_PIN));
}

void shutter_action() {
    if (!is_open) {
        Serial.print("shutter opened ... ");
        is_open = true;
        t1 = micros();
    } else if (is_open) {
        Serial.println("and closed!");
        is_open = false;
        t2 = micros();
        has_fired = true;
    }
}
