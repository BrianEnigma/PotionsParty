#include <Adafruit_NeoPixel.h>

#define SOLENOID_PIN 2
#define LED_PIN 3
#define MAGNET_PIN 4
#define SOUND_PIN 5
#define INSIDE_LED_PIN 6

#define LED_COUNT 8

#define INSIDE_LED_COUNT 6

#define WHITE_BRIGHTNESS 192
#define COLOR_BRIGHTNESS 192

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel insideStrip = Adafruit_NeoPixel(INSIDE_LED_COUNT, INSIDE_LED_PIN, NEO_GRB + NEO_KHZ800);

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
    uint16_t i;
    for(i = 0; i < INSIDE_LED_COUNT; i++) 
        insideStrip.setPixelColor(i, 0x202020);
    insideStrip.show();
}

void insideLightsOff()
{
    for(int i = 0; i < INSIDE_LED_COUNT; i++) 
        insideStrip.setPixelColor(i, 0x000000);
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

void randomAnimation(uint32_t c)
{
    for(uint16_t i = 0; i < LED_COUNT; i++) 
    {
        if (i % 2)
        {
            strip.setPixelColor(i, c);
        } else {
            uint32_t randC = 0;
            for (int shade = 0; shade <= 4; shade++)
                randC = (randC << 8) | random(0x00, 0x60);
            strip.setPixelColor(i, randC);
        }
    }
    strip.show();
}

void doAnimateUnlock()
{
    makeNoise();
    selectedColor = random(0, 4);
    // Fade up
    for (int brightness = 0; brightness <= 255; brightness += 10)
    {
        strip.setBrightness(brightness);
        setColor(COLORS[selectedColor]);
        strip.show();
        delay(30);
    }
    strip.setBrightness(255);
    setColor(COLORS[selectedColor]);
    strip.show();

    // Blinkeys
    for (unsigned int counter = 0; counter < 20; counter++)
    {
        randomAnimation(COLORS[selectedColor]);
        delay(100);
    }

    insideLightsOn();
    for (int i = 0; i < 2; i++)
    {
        randomAnimation(COLORS[selectedColor]);
        setSolenoid(true);
        delay(100);
        randomAnimation(COLORS[selectedColor]);
        setSolenoid(false);
        delay(100);
    }
    setSolenoid(true);
    for (unsigned int counter = 0; counter < 40; counter++)
    {
        randomAnimation(COLORS[selectedColor]);
        delay(100);
    }
    setSolenoid(false);

    // Fade out
    setColor(COLORS[selectedColor]);
    strip.show();
    for (int brightness = 255; brightness >= 0; brightness -= 10)
    {
        strip.setBrightness(brightness);
        setColor(COLORS[selectedColor]);
        strip.show();
        delay(30);
    }
    strip.setBrightness(255);
    setColor(0x000000);
    strip.show();
    for (int i = 0; i < 10; i++)
        delay(1000);
    insideLightsOff();
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
        if (LOW == newState)
            doAnimateUnlock();
        oldState = newState;
    }
}
