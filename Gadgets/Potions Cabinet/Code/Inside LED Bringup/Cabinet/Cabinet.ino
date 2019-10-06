#include <Adafruit_NeoPixel.h>

#define SOLENOID_PIN 2
#define LED_PIN 3
#define MAGNET_PIN 4
#define SOUND_PIN 5
#define INSIDE_LED_PIN 6

#define LED_COUNT 8

#define INSIDE_LED_COUNT 8

#define WHITE_BRIGHTNESS 192
#define COLOR_BRIGHTNESS 192

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel insideStrip = Adafruit_NeoPixel(INSIDE_LED_COUNT, INSIDE_LED_PIN, NEO_GRBW + NEO_KHZ800);

const uint32_t COLORS[] = {
    strip.Color(COLOR_BRIGHTNESS, 0, 0), // red
    strip.Color(0, COLOR_BRIGHTNESS, 0), // green
    strip.Color(0, 0, COLOR_BRIGHTNESS), // blue
    strip.Color(COLOR_BRIGHTNESS / 2, COLOR_BRIGHTNESS / 2, 0) // yellow
};
const uint32_t WHITE = strip.Color(WHITE_BRIGHTNESS, WHITE_BRIGHTNESS, WHITE_BRIGHTNESS);

unsigned char selectedColor = 0; // Which primary index in the COLORS[][] array we're using for the animation

void setColor(uint32_t c) 
{
    for(uint16_t i = 0; i < LED_COUNT; i++) 
    {
        strip.setPixelColor(i, c);
    }
}

void colorTest()
{
    setColor(strip.Color(255, 0, 0));
    strip.show();
    delay(200);
    setColor(strip.Color(0, 255, 0));
    strip.show();
    delay(200);
    setColor(strip.Color(0, 0, 255));
    strip.show();
    delay(200);
    setColor(strip.Color(128, 128, 128)); // NOTE: The current board design doesn't have enough current for a full 0xFFFFFF white.
    strip.show();
    delay(200);
    setColor(strip.Color(0, 0, 0));
    strip.show();
}

void setSolenoid(bool energized)
{
    digitalWrite(SOLENOID_PIN, energized ? HIGH : LOW);
    digitalWrite(LED_BUILTIN, energized? HIGH : LOW);
}

void makeNoise()
{
    digitalWrite(SOUND_PIN, LOW);
    delay(250);
    digitalWrite(SOUND_PIN, HIGH);
}

void insideLightsOn()
{
    for (int i = 0; i < 0xFF; i += 5)
    {
        for(int j = 0; j < INSIDE_LED_COUNT; j++) 
            insideStrip.setPixelColor(j, i, i, 0x00, i);
        insideStrip.show();
        delay(15);
    }
    for(int j = 0; j < INSIDE_LED_COUNT; j++) 
        insideStrip.setPixelColor(j, 0xFF, 0xFF, 0x00, 0xFF);
    insideStrip.show();
}

void insideLightsOff()
{
    for (int i = 0xFF; i > 0; i -= 5)
    {
        for(int j = 0; j < INSIDE_LED_COUNT; j++) 
            insideStrip.setPixelColor(j, i, i, 0x00, i);
        insideStrip.show();
        delay(15);
    }
    for(int j = 0; j < INSIDE_LED_COUNT; j++) 
        insideStrip.setPixelColor(j, 0x00, 0x00, 0x00, 0x00);
    insideStrip.show();
}

void setup() 
{
    pinMode(SOLENOID_PIN, OUTPUT);
    pinMode(MAGNET_PIN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(SOUND_PIN, OUTPUT);
    pinMode(INSIDE_LED_PIN, OUTPUT);
    pinMode(A0, INPUT);
    randomSeed(analogRead(0));
    setSolenoid(false);
    digitalWrite(SOUND_PIN, HIGH);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    insideStrip.begin();
    insideStrip.show();
    colorTest();
}

void doAnimateUnlock()
{
    makeNoise();
    insideLightsOn();
    for (int i = 0; i < 10; i++)
        delay(1000);
    insideLightsOff();
}

bool oldState = false;
bool newState = false;
void loop() 
{
    doAnimateUnlock();
    while (1)
    {
        delay(1000);
    }
}
