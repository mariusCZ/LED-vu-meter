#include "FastLED.h"

// Define the LED constants
#define NUM_LEDS 60
#define DATA_PIN 3
#define CHIPSET WS2812
#define BRIGHTNESS 255
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];


int k;

void setup() {
  // Init serial
  Serial.begin(115200);
  delay(3000);
  // Init LEDs
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}
void loop() {
  int n = Serial.available();
  // If serial comm is available, read
  if (n > 0) {
    k = Serial.parseInt();
  }
  // If data legit, light up the LEDs
  if (k > 0 && k <= 30 ) {
    Serial.println(k);
    showVUtwo(k);
  }
}

// Pattern from sides to center
void showVUone(int k) {
  int r = 0, g = 255, b = 0;
  for (int i = k; i < NUM_LEDS - 30; i++)
    leds[i] = CRGB::Black;
  for (int i = 0; i < k; i++) {
    leds[i].setRGB(r, g, b);
    r += 15;
    g -= 25;
    if (r > 255) r = 255;
    if (g < 0) g = 0;
  }
  FastLED.show();
  r = 0;
  g = 255; 
  for (int i = NUM_LEDS; i > NUM_LEDS - k - 1; i--) {
    leds[i].setRGB(r, g, b);
    r += 15;
    g -= 25;
    if (r > 255) r = 255;
    if (g < 0) g = 0;
  }
  for (int i = NUM_LEDS - k - 1; i > NUM_LEDS - 30; i--)
    leds[i] = CRGB::Black;
  FastLED.show();
}

// Patern from center to sides
void showVUtwo(int k) {
  int r = 0, g = 255, b = 0;
  for (int i = NUM_LEDS/2 - k; i >= 0; i--)
    leds[i] = CRGB::Black;
  for (int i = NUM_LEDS/2; i >= NUM_LEDS/2 - k - 1; i--) {
    leds[i].setRGB(r, g, b);
    r += 15;
    g -= 25;
    if (r > 255) r = 255;
    if (g < 0) g = 0;
  }
  FastLED.show();
  r = 0;
  g = 255; 
  for (int i = NUM_LEDS/2; i <= NUM_LEDS/2 + k + 1; i++) {
    leds[i].setRGB(r, g, b);
    r += 15;
    g -= 25;
    if (r > 255) r = 255;
    if (g < 0) g = 0;
  }
  for (int i = NUM_LEDS/2 + k; i <= NUM_LEDS; i++)
    leds[i] = CRGB::Black;
  FastLED.show();
}

