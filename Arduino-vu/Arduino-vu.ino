#include "FastLED.h"

// Define the LED constants
#define NUM_LEDS 60
#define DATA_PIN 3
#define CHIPSET WS2812
#define BRIGHTNESS 255
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

// Music mode functions
void showVUone(int k, byte val[3][3]);
void showVUtwo(int k, byte val[3][3]);
void showVUthree(int k, byte val[3][3]);
void showVUfour(int k, byte val[3][3]);
void readColors(byte val[3][3]);
void musicMode();
// Manual control
void turnLED(unsigned long color, int minVal, int maxVal);
void rainbow(), confetti(), cylon(), juggle(), mood_light(), rain();
typedef void (*SimplePatternList[])();
SimplePatternList Patterns = { rainbow, confetti, cylon, juggle, mood_light, rain };
byte hue = 0;
byte pattern;
unsigned long color = 0xff0000;
int minVal = 0, maxVal = 59;
bool state = 0;

void setup() {
  // Init serial
  Serial.begin(115200);
  delay(3000);
  // Init LEDs
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}
void loop() {
  char k;
  // If serial comm is available, read
  if (Serial.available()) {
    k = Serial.read();
    //Serial.println(k);
  }
  //manualControl();
  // If data legit, light up the LEDs
  switch(k) {
    case 'L':
    {
      minVal = Serial.parseInt();
      maxVal = Serial.parseInt();
      turnLED(color, minVal, maxVal);
      state = 0;
    }
    break;
    case 'H':
    {
      String hex = Serial.readStringUntil('\n');
      const char *conv = hex.c_str();
      color = strtol(conv, NULL, 16);
      turnLED(color, minVal, maxVal);
      state = 0;
    }
    break;
    case 'R':
    {
      state = 1;
      pattern = Serial.parseInt();
    }
    break;
    case 'm':
    {
      musicMode();
    }
    break;
    default:
      //Serial.println("Shit's broken");
    break;
  }
  if (state == 1) {
    Patterns[pattern]();
    FastLED.delay(1000/120);
    FastLED.show();
    EVERY_N_MILLISECONDS( 80 ) { hue++; }
  }
  delay(1);
}

void musicMode() {
  byte k, val[3][3];
  char c;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
      val[i][j] = 0;
    }
  
  while (c != 'S') {
    while(c != 'P') {
      if (Serial.available())
        c = (char)Serial.read();
    }
    k = (char)Serial.parseInt();
    
    while (true) {
      byte l;
      if (Serial.available()) {
        l = Serial.peek();
        if (l == 80) break;
        if (l == 67) readColors(val);
        if (l == 83) break;
        else l = (char)Serial.parseInt();
      }
      if (l > 0 && l <= 30)
        switch(k) {
            case 0:
            {
                showVUone(l, val);
            }
                break;
            case 1:
            {
                showVUtwo(l, val);
            }
                break;
            case 2:
            {
                showVUthree(l, val);
            }
                break;
            case 3:
            {
              showVUfour(l, val);
            }
            default:
                break;
        }
  }
  c = (char)Serial.read();
  }
}

void turnLED(unsigned long color, int minVal, int maxVal) {
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB::Black;
  for (int i = minVal; i <= maxVal; i++)
    leds[i] = color;
  FastLED.show();
}

void rainbow() {
  fill_rainbow( leds, NUM_LEDS, hue, 4);
}

void confetti() {
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( hue + random8(64), 200, 255);
}

void cylon() {
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13,0,NUM_LEDS);
  leds[pos] += CHSV( hue, 255, 192);
}

void juggle() {
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void mood_light() {
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i].setHue(hue);
}

void rain () {
  
}

void readColors(byte val[3][3]) {
  Serial.read();
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
      val[i][j] = Serial.parseInt();
    }
}


void showVUone(int k, byte val[3][3]) {
  //Serial.println("one");
  int r = val[0][0], rd = val[0][1], g = val[1][0], gd = val[1][1], b = val[2][0], bd = val[2][1];
  bool rop = (bool)val[0][2], gop = (bool)val[1][2], bop = (bool)val[2][2];
  for (int i = NUM_LEDS - 1; i > NUM_LEDS - 1 - (k * 2); i--) {
    leds[i].setRGB(r, g, b);
    if (rop == 1) r += rd;
    else if (rop == 0) r -= rd;
    if (gop == 1) g += gd;
    else if (gop == 0) g -= gd;
    if (bop == 1) b += bd;
    else if (bop == 0) b -= bd;
    if (r > 255) r = 255;
    if (r < 0) r = 0;
    if (g > 255) g = 255;
    if (g < 0) g = 0;
    if (b > 255) b = 255;
    if (b < 0) b = 0;
  }
  for (int i = 0; i < NUM_LEDS - 1 - (k * 2); i++)
    leds[i] = CRGB::Black;
  FastLED.show();
}

// Patern from center to sides
void showVUthree(int k, byte val[3][3]) {
  //Serial.println("two");
  int r = val[0][0], rd = val[0][1], g = val[1][0], gd = val[1][1], b = val[2][0], bd = val[2][1];
  bool rop = (bool)val[0][2], gop = (bool)val[1][2], bop = (bool)val[2][2];
  for (int i = NUM_LEDS/2 - k; i >= 0; i--)
    leds[i] = CRGB::Black;
  for (int i = NUM_LEDS/2; i >= NUM_LEDS/2 - k - 1; i--) {
    leds[i].setRGB(r, g, b);
    if (rop == 1) r += rd;
    else if (rop == 0) r -= rd;
    if (gop == 1) g += gd;
    else if (gop == 0) g -= gd;
    if (bop == 1) b += bd;
    else if (bop == 0) b -= bd;
    if (r > 255) r = 255;
    if (r < 0) r = 0;
    if (g > 255) g = 255;
    if (g < 0) g = 0;
    if (b > 255) b = 255;
    if (b < 0) b = 0;
  }
  //FastLED.show();
  r = val[0][0], rd = val[0][1], g = val[1][0], gd = val[1][1], b = val[2][0], bd = val[2][1];
  for (int i = NUM_LEDS/2; i <= NUM_LEDS/2 + k - 1; i++) {
    leds[i].setRGB(r, g, b);
    if (rop == 1) r += rd;
    else if (rop == 0) r -= rd;
    if (gop == 1) g += gd;
    else if (gop == 0) g -= gd;
    if (bop == 1) b += bd;
    else if (bop == 0) b -= bd;
    if (r > 255) r = 255;
    if (r < 0) r = 0;
    if (g > 255) g = 255;
    if (g < 0) g = 0;
    if (b > 255) b = 255;
    if (b < 0) b = 0;
  }
  for (int i = NUM_LEDS/2 + k - 1; i < NUM_LEDS; i++)
    leds[i] = CRGB::Black;
  FastLED.show();
}

void showVUtwo(int k, byte val[3][3]) {
  //Serial.println("three");
  int r = val[0][0], rd = val[0][1], g = val[1][0], gd = val[1][1], b = val[2][0], bd = val[2][1];
  bool rop = (bool)val[0][2], gop = (bool)val[1][2], bop = (bool)val[2][2];
  for (int i = 0; i < k * 2; i++) {
    leds[i].setRGB(r, g, b);
    if (rop == 1) r += rd;
    else if (rop == 0) r -= rd;
    if (gop == 1) g += gd;
    else if (gop == 0) g -= gd;
    if (bop == 1) b += bd;
    else if (bop == 0) b -= bd;
    if (r > 255) r = 255;
    if (r < 0) r = 0;
    if (g > 255) g = 255;
    if (g < 0) g = 0;
    if (b > 255) b = 255;
    if (b < 0) b = 0;
  }
  for (int i = k * 2; i < NUM_LEDS; i++)
    leds[i] = CRGB::Black;
  FastLED.show();
}

void showVUfour(int k, byte val[3][3]) {
  int r = val[0][0], rd = val[0][1], g = val[1][0], gd = val[1][1], b = val[2][0], bd = val[2][1];
  bool rop = (bool)val[0][2], gop = (bool)val[1][2], bop = (bool)val[2][2];
  for (int i = k; i < NUM_LEDS - 30; i++)
    leds[i] = CRGB::Black;
  for (int i = 0; i < k; i++) {
    leds[i].setRGB(r, g, b);
    if (rop == 1) r += rd;
    else if (rop == 0) r -= rd;
    if (gop == 1) g += gd;
    else if (gop == 0) g -= gd;
    if (bop == 1) b += bd;
    else if (bop == 0) b -= bd;
    if (r > 255) r = 255;
    if (r < 0) r = 0;
    if (g > 255) g = 255;
    if (g < 0) g = 0;
    if (b > 255) b = 255;
    if (b < 0) b = 0;
  }
  r = val[0][0], rd = val[0][1], g = val[1][0], gd = val[1][1], b = val[2][0], bd = val[2][1];
  for (int i = NUM_LEDS - 1; i > NUM_LEDS - k - 1; i--) {
    leds[i].setRGB(r, g, b);
    if (rop == 1) r += rd;
    else if (rop == 0) r -= rd;
    if (gop == 1) g += gd;
    else if (gop == 0) g -= gd;
    if (bop == 1) b += bd;
    else if (bop == 0) b -= bd;
    if (r > 255) r = 255;
    if (r < 0) r = 0;
    if (g > 255) g = 255;
    if (g < 0) g = 0;
    if (b > 255) b = 255;
    if (b < 0) b = 0;
  }
  for (int i = NUM_LEDS - k - 1; i > NUM_LEDS - 30; i--)
    leds[i] = CRGB::Black;
  FastLED.show();
}

