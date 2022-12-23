int MAX_MENU_COUNT = 3;
int currentMenu = 0;
bool isMainMenu = true;
int ignoreCount = 0;
bool joystickIsMoving = false;
bool joystickIsPressed = false;

void handleMenu() {
  handleMenuJoystick();
  writeMenuText();
}

void writeMenuText() {
  if (isMainMenu == true) {
    writeMainMenu();
  } else {
    writeSubMenu();
  }
}

void writeMainMenu() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
  u8g2.drawGlyph(0, 40, 81); // <
  u8g2.drawGlyph(112, 40, 82); // >
  u8g2.setFont(u8g2_font_open_iconic_embedded_4x_t);
  int menuIcon;
  String menuText;
  if (currentMenu == 0) {
    // Effects
    menuIcon = 77;
    menuText = "Effekte";
  } else if (currentMenu == 1) {
    // Info
    menuIcon = 70;
    menuText = "Info";
  } else if (currentMenu == 2) {
    // Settings
    menuIcon = 66;
    menuText = "Einstellungen";
  } else {
    // Turn off
    menuIcon = 78;
    menuText = "Ausschalten";
  }
  u8g2.drawGlyph(48, 40, menuIcon);
  u8g2.setFont(u8g2_font_8x13_mf);
  char menuChar[14] = {0};
  menuText.toCharArray(menuChar,14);
  int charLength = u8g2.getStrWidth(menuChar);
  int startPosition = 64 - (charLength / 2);
  u8g2.setCursor(startPosition, 60);
  u8g2.print(menuText);
  u8g2.sendBuffer();
}

void handleMenuJoystick() {
  int joystickX = analogRead(JOYSTICK_X);
  int joystickY = analogRead(JOYSTICK_Y);

  int joystickDirectionX = 0;
  // Joystick to right
  if (joystickX > 700 && joystickIsMoving == false) {
    joystickDirectionX = 1;
    joystickIsMoving = true;
  } else if (joystickX < 300 && joystickIsMoving == false) {
    joystickDirectionX = -1;
    joystickIsMoving = true;
  } else if (joystickX < 450 && joystickX > 400 && joystickIsMoving == true) {
    joystickIsMoving = false;
  }

  if (isMainMenu && joystickDirectionX != 0) {
    currentMenu += joystickDirectionX;

    if (currentMenu > MAX_MENU_COUNT) {
      currentMenu = 0;
    } else if (currentMenu < 0) {
      currentMenu = MAX_MENU_COUNT;
    }
  }
  
  int joystickStateMenu = digitalRead(JOYSTICK_PRESS);

  if (joystickStateMenu == LOW && isMainMenu == true && joystickIsPressed == false) {
    isMainMenu = false;
    joystickIsPressed = true;
  } else if (joystickStateMenu == LOW && isMainMenu == false && joystickIsPressed == false) {
    isMainMenu = true;
    joystickIsPressed = true;
  } else if (joystickStateMenu == HIGH && joystickIsPressed == true) {
    joystickIsPressed = false;
  }
}

int getPositionForInt(int &value) {
  String stringValue = String(value);
  return getPositionForString(stringValue);
}

int getPositionForString(String &value) {
  char stringChar[4] = {0};
  value.toCharArray(stringChar,4);
  int stringValueLength = u8g2.getStrWidth(stringChar);
  int stringPosition = 128 - stringValueLength;

  return stringPosition;
}
