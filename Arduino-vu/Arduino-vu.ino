#include "FastLED.h"

#define NUM_LEDS 60
#define DATA_PIN 3
#define CHIPSET WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];


int k;

void setup() { 
  Serial.begin(115200);
  delay(3000);
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  // Initialize serial port 
}
void loop() {
  int n = Serial.available();
  if (n > 0) {
    k = Serial.parseInt();
  }
  if (k > 0 && k <= 30 ) 
    Serial.println(k);
    showVU(k);
  }
}

void showVU(int k) {
  for (int i = k; i < NUM_LEDS - 30; i++)
    leds[i] = CRGB::Black;
  for (int i = 0; i < NUM_LEDS - 60 + k; i++)
    leds[i] = CRGB::HotPink;
  for (int i = NUM_LEDS - 1; i > NUM_LEDS - k; i--)
    leds[i] = CRGB::HotPink;
  for (int i = NUM_LEDS - k; i > NUM_LEDS - 30; i--)
    leds[i] = CRGB::Black;
  FastLED.show();
}

