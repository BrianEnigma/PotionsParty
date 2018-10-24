#include <Adafruit_NeoPixel.h>

#define SOLENOID_PIN 2
#define LED_PIN 3
#define MAGNET_PIN 4

#define LED_COUNT 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void colorSet(uint32_t c) 
{
    for(uint16_t i = 0; i < LED_COUNT; i++) 
    {
        strip.setPixelColor(i, c);
    }
    strip.show();
}

void colorTest()
{
    colorSet(strip.Color(255, 0, 0));
    delay(200);
    colorSet(strip.Color(0, 255, 0));
    delay(200);
    colorSet(strip.Color(0, 0, 255));
    delay(200);
    colorSet(strip.Color(128, 128, 128)); // NOTE: The current board design doesn't have enough current for a full 0xFFFFFF white.
    delay(200);
    colorSet(strip.Color(0, 0, 0));
}

void setup() 
{
    pinMode(SOLENOID_PIN, OUTPUT);
    pinMode(MAGNET_PIN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    colorTest();
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
        colorSet(newState ? strip.Color(255, 0, 0) : strip.Color(0, 0, 0));
        oldState = newState;
    }
}
