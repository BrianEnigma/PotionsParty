#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
    #include <avr/power.h>
#endif

#define MAGNET_PIN          4
#define NEOPIXEL_LENGTH     19
#define NEOPIXEL_PIN        2
#define TEST_LED_PIN        13

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOPIXEL_LENGTH, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
    #if defined (__AVR_ATtiny85__)
        if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif
    // End of trinket special code

    pinMode(TEST_LED_PIN, OUTPUT);
    pinMode(MAGNET_PIN, INPUT);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    strandTest();
}

bool oldState = false;
bool newState = false;
void loop() 
{
    if (digitalRead(MAGNET_PIN) == HIGH) 
    {
        digitalWrite(TEST_LED_PIN, HIGH);
        newState = false;
    } else {
        digitalWrite(TEST_LED_PIN, LOW);
        newState = true;
    }
    if (oldState != newState)
    {
        showColor(newState ? 0xff0000 : 0x000000);
        oldState = newState;
    }
}

void strandTest()
{
    uint32_t COLORS[] = {0xff0000, 0x00ff00, 0x0000ff, 0xffffff, 0x000000};
    for (uint8_t color = 0; color < 5; color++)
    {
        for (uint8_t pos = 0; pos < NEOPIXEL_LENGTH; pos++)
            strip.setPixelColor(pos, COLORS[color]);
        strip.show();
        delay(250);
    }
}

void showColor(uint32_t color)
{
    for (uint8_t pos = 0; pos < NEOPIXEL_LENGTH; pos++)
        strip.setPixelColor(pos, color);
    strip.show();
}

