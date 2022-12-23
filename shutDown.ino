bool shutDownDisplayOn = false;

void handleTurnedOff() {
  int state = digitalRead(DOOR_PIN);

  if (state == HIGH) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_open_iconic_embedded_4x_t);
    u8g2.drawGlyph(48, 40, 78);
    String menuText = "Einschalten";
    u8g2.setFont(u8g2_font_8x13_mf);
    char menuChar[14] = {0};
    menuText.toCharArray(menuChar,14);
    int charLength = u8g2.getStrWidth(menuChar);
    int startPosition = 64 - (charLength / 2);
    u8g2.setCursor(startPosition, 60);
    u8g2.print(menuText);
    u8g2.sendBuffer();
    shutDownDisplayOn = true;
  } else if (shutDownDisplayOn == true) {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
    shutDownDisplayOn = false;
  }
}
