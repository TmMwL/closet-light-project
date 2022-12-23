void setStripColor() {
  int centerLed = 15; // 14 leds to each side, 14th in the middle
  int centerLedMany = 70; // 69 leds to each side, 70th in the middle
  int redBrightness = getRedBrightness();
  int blueBrightness = getBlueBrightness();
  int greenBrightness = getGreenBrightness();
  int additionalLeds = LED_COUNT / LED_COUNT_DRAWER;
  
  for (int leds=0; leds <= centerLed; leds++) {
    strip1.setPixelColor(centerLedMany, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    for (int manyLeds = 0; manyLeds <= 5; manyLeds++) {
      strip1.setPixelColor(centerLedMany + (leds * 5) + manyLeds, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
      strip1.setPixelColor(centerLedMany - (leds * 5) + manyLeds, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    }
    
    strip2.setPixelColor(centerLed + leds, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    strip2.setPixelColor(centerLed - leds, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    
    strip3.setPixelColor(centerLed + leds, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    strip3.setPixelColor(centerLed - leds, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    
    strip4.setPixelColor(centerLed + leds, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    strip4.setPixelColor(centerLed - leds, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    
    strip5.setPixelColor(centerLed + leds, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    strip5.setPixelColor(centerLed - leds, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);

    strip1.show();
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    delay(15);
  }

  PULSE = true;
}

void updateBrightness(int changeBy) {
  int changeToNext = 0;
  
  if (changeBy > 1) {
    BRIGHTNESS += 2;
    changeToNext = changeBy - 2;
  } else if (changeBy < 1) {
    BRIGHTNESS -= 2;
    changeToNext = changeBy + 2;
  } else {
    BRIGHTNESS += changeBy;
  }
  
  int redBrightness = getRedBrightness();
  int blueBrightness = getBlueBrightness();
  int greenBrightness = getGreenBrightness();

  for (int manyLed = 0; manyLed < LED_COUNT; manyLed++) {
    strip1.setPixelColor(manyLed, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
  }
  
  for (int fewLed = 0; fewLed < LED_COUNT_DRAWER; fewLed++) {
    strip2.setPixelColor(fewLed, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    strip3.setPixelColor(fewLed, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    strip4.setPixelColor(fewLed, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
    strip5.setPixelColor(fewLed, redBrightness, greenBrightness, blueBrightness, BRIGHTNESS);
  }

  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();

  if (changeToNext != 0) {
    updateBrightness(changeToNext);
  }
}

void turnOffStrip() {
  int centerLed = 14; // 13 leds to each side, 14th in the middle
  int centerLedMany = 70; // 69 leds to each side, 70th in the middle
  
  for(int leds=centerLed; leds >= 0; leds--) {
    for (int manyLeds = 0; manyLeds <= 5; manyLeds++) {
      strip1.setPixelColor(centerLedMany + (leds * 5) + manyLeds, 0, 0, 0, 0);
      strip1.setPixelColor(centerLedMany - (leds * 5) + manyLeds, 0, 0, 0, 0); 
    }
    
    strip2.setPixelColor(centerLed + leds, 0, 0, 0, 0);
    strip2.setPixelColor(centerLed - leds, 0, 0, 0, 0);
    
    strip3.setPixelColor(centerLed + leds, 0, 0, 0, 0);
    strip3.setPixelColor(centerLed - leds, 0, 0, 0, 0);
    
    strip4.setPixelColor(centerLed + leds, 0, 0, 0, 0);
    strip4.setPixelColor(centerLed - leds, 0, 0, 0, 0);
    
    strip5.setPixelColor(centerLed + leds, 0, 0, 0, 0);
    strip5.setPixelColor(centerLed - leds, 0, 0, 0, 0);

    strip1.show();
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    delay(15);
  }

  PULSE = false;
}

void pulseLed() {
  // pulse light. Needs to be implemented
}

int getRedBrightness() {
  return WARMNESS * BRIGHTNESS / 100;
}

int getGreenBrightness() {
  return BRIGHTNESS * 75 / 100;
}

int getBlueBrightness() {
  return (100 - WARMNESS) * BRIGHTNESS / 100;
}
