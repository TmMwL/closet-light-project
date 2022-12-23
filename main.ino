void handleLoop() {
  int state = digitalRead(DOOR_PIN);

  // If door opens, first if is matched
  // If door closes, second if is matched
  // If light has been turned off by button, third if matches
  if (state == HIGH && DOOR_OPEN == false && TURN_OFF == false) {
    Serial.println("Door is opening");
    doorOpens();
  } else if (state == LOW && DOOR_OPEN == true && TURN_OFF == false) {
    Serial.println("Door closes");
    doorCloses();
  } else if (state == LOW && DOOR_OPEN == false && TURN_OFF == true) {
    Serial.println("System has been turned off");
    TURN_OFF = false;
    u8g2.clearBuffer();
    u8g2.sendBuffer();
  }

  int menuButton = digitalRead(MENU_PIN);

  if (menuButton == LOW && MENU_OPEN == false) {
    MENU_OPEN = true;
    delay(50);
  } else if (menuButton == LOW && MENU_OPEN == true) {
    MENU_OPEN = false;
    delay(50);
  }

  if (MENU_OPEN == true) {
    handleMenu();
  } else {
    handleJoystick();

    writeText();
  }

  if (PULSE == true) {
    pulseLed();
  }
  
  delay(25);
}

void doorOpens() {
  determineBrightness();
  DOOR_OPEN = true;
  writeText();
  setStripColor(); 
}

void doorCloses() {
  DOOR_OPEN = false;
  turnOffStrip();
  FADE_IN_LEDS = 1;
  FADE_IN = false;
  PULSE = false;
  MENU_OPEN = false;

  u8g2.clearBuffer();
  u8g2.sendBuffer(); 
}

void writeText() {
  if (DOOR_OPEN == true) {
    u8g2.clearBuffer();

    u8g2.setFont(u8g2_font_open_iconic_weather_2x_t);
    u8g2.drawGlyph(0, 17, 69);

    String BrightnessString = String(BRIGHTNESS);
    char brightnessChar[4] = {0};
    BrightnessString.toCharArray(brightnessChar,4);
    
    u8g2.setFont(u8g2_font_8x13_mf);
    u8g2.drawStr(20, 9, brightnessChar);

    String LDRString = String(LDR);
    char ldrChar[6] = {0};
    LDRString.toCharArray(ldrChar,6);

    u8g2.drawStr(64, 9, ldrChar);

    int joystickX = analogRead(JOYSTICK_X);
    int joystickY = analogRead(JOYSTICK_Y);

    u8g2.setFont(u8x8_font_open_iconic_arrow_1x1);

    if (joystickX > 700) {
      u8g2.drawGlyph(120, 9, 0x51); // >
    } else if (joystickX < 300) {
      u8g2.drawGlyph(104, 9, 0x52); // <
    }

    if (joystickY < 300) {
      u8g2.drawGlyph(120, 9, 53);
    } else if (joystickY > 700) {
      u8g2.drawGlyph(120, 9, 50);
    }

    u8g2.drawLine(20, 11, 128, 11);

    int horizontalX = (WARMNESS * 127 / 100); // Has to be implemented
    int horizontalY = 64 - (BRIGHTNESS * 51 / 255); // Brightness

    u8g2.drawLine(0, horizontalY, 128, horizontalY);
    u8g2.drawLine(horizontalX, 13, horizontalX, 64);
    u8g2.sendBuffer(); 
  } else if (TURN_OFF == true) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_open_iconic_weather_6x_t);
    u8g2.drawGlyph(30, 57, 66);
    u8g2.sendBuffer(); 
  }
}

void determineBrightness() {
  LDR = analogRead(A2);

  Serial.println("LDR: ");
  Serial.println(LDR);
//  BRIGHTNESS = 5;
//  WARMNESS = 100;
  
  // Turn on after development
  if (LDR > 900) {
    BRIGHTNESS = 50;
    WARMNESS = 100;
  } else if (LDR > 800) {
    BRIGHTNESS = 110;
    WARMNESS = 75;
  } else if (LDR > 500) {
    BRIGHTNESS = 160;
    WARMNESS = 40;
  } else {
    BRIGHTNESS = 250;
    WARMNESS = 10;
  }
}
