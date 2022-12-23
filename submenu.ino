void writeSubMenu() {
  u8g2.clearBuffer();
  u8g2.drawLine(20, 11, 128, 11); // top line is on every menu
  if (currentMenu == 0) {
    writeEffectsMenu();
  } else if (currentMenu == 1) {
    writeInfoMenu();
  } else if (currentMenu == 2) {
    writeSettingsMenu();
  } else {
    writeTurnOffMenu();
  }
  u8g2.sendBuffer();
}

void writeEffectsMenu() {
  u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
  u8g2.drawGlyph(0, 17, 77);

  u8g2.setFont(u8g2_font_8x13_mf);
  u8g2.drawStr(20, 9, "Effekte");
}

void writeInfoMenu() {
  u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
  u8g2.drawGlyph(0, 17, 70);

  u8g2.setFont(u8g2_font_8x13_mf);
  u8g2.drawStr(20, 9, "Info");

  u8g2.setCursor(20, 25);
  u8g2.print("SEN-D");
  u8g2.setCursor(115, 25);
  u8g2.print("O");

  u8g2.setCursor(20, 40);
  u8g2.print("SEN-L");

  int currentLDR = analogRead(A2);
  int ldrPosition = getPositionForInt(currentLDR);
  u8g2.setCursor(ldrPosition, 40);
  u8g2.print(currentLDR);

  u8g2.setCursor(20, 55);
  u8g2.print("BRT");

  int brightnessPosition = getPositionForInt(BRIGHTNESS);
  u8g2.setCursor(brightnessPosition, 55);
  u8g2.print(BRIGHTNESS);
}

void writeSettingsMenu() {
  u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
  u8g2.drawGlyph(0, 17, 66);

  u8g2.setFont(u8g2_font_8x13_mf);
  u8g2.drawStr(20, 9, "Einstellungen");
}

void writeTurnOffMenu() {
  u8g2.setFont(u8g2_font_open_iconic_embedded_2x_t);
  u8g2.drawGlyph(0, 17, 78);

  u8g2.setFont(u8g2_font_8x13_mf);
  u8g2.drawStr(20, 9, "Ausschalten");
}
