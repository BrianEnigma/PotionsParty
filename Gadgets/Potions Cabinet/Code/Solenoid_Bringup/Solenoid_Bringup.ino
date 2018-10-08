#define SOLENOID_PIN 2
void setup() 
{
    pinMode(SOLENOID_PIN, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
    digitalWrite(SOLENOID_PIN, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(SOLENOID_PIN, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delay(4000);
}
