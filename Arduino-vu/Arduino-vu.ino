#include "FastLED.h"

// Define the LED constants
#define NUM_LEDS 60
#define DATA_PIN 3
#define CHIPSET WS2812
#define BRIGHTNESS 255
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void showVUone(int k);
void showVUtwo(int k);
void showVUthree(int k);
void musicMode();
void readColors(byte val[3][3]);

void setup() {
  // Init serial
  Serial.begin(115200);
  delay(3000);
  // Init LEDs
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  //showVUone(1);
  //readColors(NULL);
}
void loop() {
  int k;
  // If serial comm is available, read
  if (Serial.available()) {
    k = Serial.read();
  }
  Serial.println("shit");
  // If data legit, light up the LEDs
  switch(k) {
    case 'm':
    musicMode();
    break;
  }
}

void musicMode() {
  byte k, val[3][3];
  char c;
  while (c != 'C') {
    Serial.println("shit woks");
    while(c != 'P') {
      Serial.println("stuck");
      c = (char)Serial.read();
    }
    k = Serial.parseInt();
    
    while (true) {
      byte l;
      if (Serial.available()) {
        l = Serial.peek();
        if (l == 80) break;
        if (l == 67) readColors(val);
        l = Serial.parseInt();
      }
      if (l > 0 && l <= 30)
        switch(k) {
            case 0:
                showVUone(l);
                break;
            case 1:
                showVUtwo(l);
                break;
            case 2:
                showVUthree(l);
                break;
            default:
                Serial.println("Faulty input");
                break;
        }
  }
  c = (char)Serial.read();
  Serial.println("sometin wong");
}
}

/*
void musicMode() {
  int k;
  char c;
  byte val[3][3];
  while (c != 'C') {
    Serial.println("shit woks");
    while(c != 'P') {
      Serial.println("stuck");
      if (Serial.available())
        c = (char)Serial.read();
    }
    k = Serial.parseInt();
    switch(k) {
      case 0:
      {
        Serial.println("one");
        while (true) {
          if (Serial.available()) {
          k = Serial.peek();
          if (k == 80) break;
          if (k == 67) readColors(val);
          k = Serial.parseInt();
          if (k > 0 && k <= 30)
            showVUone(k);
          }
        }
      }
      break;
      case 1:
      {
        Serial.println("two");
        while (true) {
          if (Serial.available()) {
          k = Serial.peek();
          if (k == 80) break;
          k = Serial.parseInt();
          Serial.println(k);
          }
          if (k > 0 && k <= 30)
            showVUtwo(k);
        }
      }
      break;
      case 2:
      {
        Serial.println("three");
        while (true) {
          if (Serial.available()) {
          k = Serial.peek();
          if (k == 80) break;
          k = Serial.parseInt();
          Serial.println(k);
          if (k > 0 && k <= 30)
            showVUthree(k);
          }
        }
      }
      break;
    }
    c = (char)Serial.read();
  }
}
*/

void readColors(byte val[3][3]) {
  Serial.read();
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
      val[i][j] = Serial.parseInt();
      Serial.println(val[i][j]);
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

void showVUthree(int k) {
  int r = 0, g = 255, b = 0;
  for (int i = 0; i < k * 2; i++) {
    leds[i].setRGB(r, g, b);
    r += 15;
    g -= 15;
    if (r > 255) r = 255;
    if (g < 0) g = 0;
  }
  for (int i = k * 2; i < NUM_LEDS; i++)
    leds[i] = CRGB::Black;
  FastLED.show();
}

