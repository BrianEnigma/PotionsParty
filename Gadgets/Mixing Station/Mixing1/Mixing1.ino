#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
    #include <avr/power.h>
#endif
#include <Bounce2.h>

#define MAGNET_PIN          4
#define NEOPIXEL_LENGTH     19
#define NEOPIXEL_PIN        2
#define TEST_LED_PIN        13

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOPIXEL_LENGTH, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
Bounce debouncer = Bounce(); 

#define ANIMATE_DELAY 50
#define WHITE_BRIGHTNESS 64
#define BRIGHTNESS1 255
#define BRIGHTNESS2 192
#define BRIGHTNESS3 128
#define BRIGHTNESS4  64

// Shades (brightnesses) of the colors to use in the stir animation.
const uint32_t COLORS[][] = {
    {strip.Color(BRIGHTNESS1, 0, 0), strip.Color(BRIGHTNESS2, 0, 0), strip.Color(BRIGHTNESS3, 0, 0), strip.Color(BRIGHTNESS4, 0, 0)}, // Shades of red
    {strip.Color(0, BRIGHTNESS1, 0), strip.Color(0, BRIGHTNESS2, 0), strip.Color(0, BRIGHTNESS3, 0), strip.Color(0, BRIGHTNESS4, 0)}, // Shades of green
    {strip.Color(0, 0, BRIGHTNESS1), strip.Color(0, 0, BRIGHTNESS2), strip.Color(0, 0, BRIGHTNESS3), strip.Color(0, 0, BRIGHTNESS4)}, // Shades of blue
    {strip.Color(BRIGHTNESS1, BRIGHTNESS1, 0), strip.Color(BRIGHTNESS2, BRIGHTNESS2, 0), strip.Color(BRIGHTNESS3, BRIGHTNESS3, 0), strip.Color(BRIGHTNESS4, BRIGHTNESS4, 0)}  // Shades of yellow
}
const uint32_t WHITE = strip.Color(WHITE_BRIGHTNESS, WHITE_BRIGHTNESS, WHITE_BRIGHTNESS);

unsigned char stirPosition = 0;  // Where in the strip/wheel we are with the stir animation.
unsigned char selectedColor = 0; // Which primary index in the COLORS[][] array we're using for the animation

void setup() 
{
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
    #if defined (__AVR_ATtiny85__)
        if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif
    // End of trinket special code

    pinMode(TEST_LED_PIN, OUTPUT);
    pinMode(MAGNET_PIN, INPUT);
    debouncer.attach(MAGNET_PIN);
    debouncer.interval(100);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    strandTest();
}

bool oldState = false;
bool newState = false;
bool isAnimating = false;
void loop() 
{
    debouncer.update();
    int value = debouncer.read();
    if (value == HIGH) 
    {
        digitalWrite(TEST_LED_PIN, HIGH);
        newState = false;
    } else {
        digitalWrite(TEST_LED_PIN, LOW);
        newState = true;
    }
    
    if (oldState != newState) // State change
    {
        oldState = newState;
        isAnimating = !isAnimating;
        animateStartStop(isAnimating);
    } else { // Continue with the current state of animating or not
        if (isAnimating)
            animateStep();
    }
}

void animateStartStop(bool doStart)
{
    if (doStart)
    {
        stirPosition = 0;
        selectedColor = 0; // TODO: randomize this to a house color, once stable
        // TODO: fade in
        showColor(WHITE);
    } else {
        // TODO: fade out
        showColor(0x000000);
    }
}

void animateStep()
{
    for (uint8_t pos = 0; pos < NEOPIXEL_LENGTH; pos++)
        strip.setPixelColor(pos, WHITE);
    for (int8_t offset = -3; offset <= 3; offset++)
    {
        int8_t pos = stirPosition + offset; // Find the position for the color offset (this could be negative).
        uint32_t color = COLOR[selectedColor][abs(offset)]; // Find the color for this offset.
        pos = (pos + NEOPIXEL_LENGTH) % NEOPIXEL_LENGTH; // Find the real-world position (this must be positive)
        // Set the color of "this" pixel.
        strip.setPixelColor(pos, color);
        // Set the color of pixel across from it in the circle
        pos = (pos + (NEOPIXEL_LENGTH / 2)) % NEOPIXEL_LENGTH;
        strip.setPixelColor(pos, color);
    }
    strip.show();

    delay(ANIMATE_DELAY);
    stirPosition = (stirPosition + 1) % NEOPIXEL_LENGTH;
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

