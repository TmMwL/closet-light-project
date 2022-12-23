void handleJoystick() {
  int joystickX = analogRead(JOYSTICK_X);
  int joystickY = analogRead(JOYSTICK_Y);
  int changeBrightness = 0;
  bool warmnessChanged = false;

//  Serial.println("Joystick coordinates:");
//  Serial.println(joystickX);
//  Serial.println(joystickY);

  if (joystickX > 700 && WARMNESS <= 95) {
    WARMNESS += 5;
    warmnessChanged = true;
  } else if (joystickX < 300 && WARMNESS >= 5) {
    WARMNESS-= 5;
    warmnessChanged = true;
  }

  String joystickYString = "|";
  if (joystickY < 300) {
//    if (BRIGHTNESS < 230) {
//      changeBrightness = 25;
//    } else if (BRIGHTNESS < 240) {
//      changeBrightness = 10;
//    } else if (BRIGHTNESS <= 250) {
//      changeBrightness = 5;
//    }
  } else if (joystickY > 700) {
//      changeBrightness = -25;
//    } else if (BRIGHTNESS > 20) {
//      changeBrightness = -10;
//    } else if (BRIGHTNESS >= 10) {
//      changeBrightness = -5;
//    }
  }

  if (DOOR_OPEN == true && (changeBrightness != 0 || warmnessChanged == true)) {
    updateBrightness(changeBrightness); 
  }

  int joystickState = digitalRead(JOYSTICK_PRESS);

  if (joystickState == LOW && TURN_OFF == false) {
    TURN_OFF = true;
    doorCloses();
  } else if (joystickState == LOW && TURN_OFF == true) {
    TURN_OFF = false;
    doorOpens();
  }
}
