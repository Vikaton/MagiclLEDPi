#include "FastLED.h"

#define BRIGHTNESS 75

#define LEFT_LEDS 24
#define RIGHT_LEDS 24

#define LEFT 0
#define RIGHT 1

#define PINR 7
#define PINL 6

class Headlights {
  public:
    Headlights(int lef, int righ);
    void setColor(CRGB lef, CRGB righ);
    void setColor(CRGB col);
    void fade();
    void heartbeat();
    CRGB all[RIGHT_LEDS + LEFT_LEDS];
    CRGB *headL, *headR;
    CRGB leftC = CRGB::White, rightC = CRGB::White, allC = CRGB::White;
};

Headlights::Headlights(int lef, int righ) {
  headL = all;
  headR = all + RIGHT_LEDS;
  FastLED.addLeds<NEOPIXEL, PINL>(headL, LEFT_LEDS);
  FastLED.addLeds<NEOPIXEL, PINR>(headR, RIGHT_LEDS);
}
void Headlights::setColor(CRGB lef, CRGB righ) {
  leftC = lef;
  rightC = righ;
  for (int i = 0; i<24; i++) {
    headL[i] = lef;
    headR[i] = righ;
  }
  FastLED.show();
}
void Headlights::setColor(CRGB col) {
  allC = col;
  for (int i = 0; i<48; i++) {
    all[i] = col;
  }
  FastLED.show();
}

void Headlights::fade() {
  for (int i = BRIGHTNESS; i<=250; i++) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(1);
  }
  for (int i = 250; i>=BRIGHTNESS; i--) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(1);
  }
}

void Headlights::heartbeat() {
  FastLED.clear(); FastLED.show();
  this->setColor(allC);
  delay(100);
  FastLED.clear(); FastLED.show();
  delay(100);
  this->setColor(allC);
  delay(100);
  FastLED.clear(); FastLED.show();
  delay(500);
}

Headlights ledring(6,7);

class Singlelight {
  public:
    Singlelight(int sid);
    void setColor(CRGB col);
    void fade();
    void heartbeat();
  private:
    int side;
    CRGB leftC = ledring.leftC, rightC = ledring.rightC;
};

Singlelight::Singlelight(int sid) {
  side = sid;
}

void Singlelight::setColor(CRGB col) {
  if (side == LEFT) {
      leftC = col;
      for (int i = 0; i<24; i++) {
        ledring.headL[i] = col;
    }
  }
    else {
      rightC = col;
      for (int i = 0; i<24; i++) {
        ledring.headR[i] = col;
    }
  }
  FastLED.show();
}

void Singlelight::fade() {
  for (int i = BRIGHTNESS; i<=250; i++) {
    FastLED[side].showLeds(i);
    delay(1);
  }
  for (int i = 250; i>=BRIGHTNESS; i--) {
    FastLED[side].showLeds(i);
    delay(1);
  }
}

void Singlelight::heartbeat() {
  if (side == LEFT) {
    FastLED[LEFT].clearLedData(); FastLED.show();
    this->setColor(leftC);
    delay(100);
    FastLED[LEFT].clearLedData(); FastLED.show();
    delay(100);
    this->setColor(leftC);
    delay(100);
    FastLED[LEFT].clearLedData(); FastLED.show();
    delay(100);
    this->setColor(leftC);
  }
  else {
    FastLED[RIGHT].clearLedData(); FastLED.show();
    this->setColor(rightC);
    delay(100);
    FastLED[RIGHT].clearLedData(); FastLED.show();
    delay(100);
    this->setColor(rightC);
    delay(100);
    FastLED[RIGHT].clearLedData(); FastLED.show();
    delay(100);
    this->setColor(rightC);
  }
}

Singlelight right(RIGHT);
Singlelight left(LEFT);  // 6: left, 7: right

void setup() {
  FastLED.setBrightness(BRIGHTNESS);
  right.setColor(CRGB::Red);
  left.setColor(CRGB::Blue);
  FastLED.show();
}

void loop() {
  right.heartbeat();
  left.heartbeat();
}
