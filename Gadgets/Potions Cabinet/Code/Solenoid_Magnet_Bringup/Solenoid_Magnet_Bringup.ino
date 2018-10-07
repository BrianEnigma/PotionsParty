#define SOLENOID_PIN 2
#define MAGNET_PIN 4

void setup() 
{
    pinMode(SOLENOID_PIN, OUTPUT);
    pinMode(MAGNET_PIN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void setSolenoid(bool energized)
{
    digitalWrite(SOLENOID_PIN, energized ? HIGH : LOW);
    digitalWrite(LED_BUILTIN, energized? HIGH : LOW);
}

bool oldState = false;
bool newState = false;
void loop() 
{
    if (digitalRead(MAGNET_PIN) == HIGH) 
    {
        newState = false;
    } else {
        newState = true;
    }
    if (oldState != newState)
    {
        setSolenoid(newState);
        oldState = newState;
    }
}
