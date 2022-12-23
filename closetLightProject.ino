#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include <math.h> // round
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN_1   6
#define LED_PIN_2   5
#define LED_PIN_3   4
#define LED_PIN_4   3
#define LED_PIN_5   8

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  140
#define LED_COUNT_DRAWER 29

// Joystick analog ports
#define JOYSTICK_X A7
#define JOYSTICK_Y A5
#define JOYSTICK_PRESS 2

#define DOOR_PIN   10
#define MENU_PIN   13

// NeoPixel brightness, 0 (min) to 255 (max)
int BRIGHTNESS = 25;
float WARMNESS = 50; // 100: warn, 50: neutral, 0: cold

bool DOOR_OPEN = false;
bool FADE_IN = false;
bool PULSE = false;
int FADE_IN_LEDS = 1;
int LDR = 0;
bool LAST_DOOR_STATE = false;
bool TURN_OFF = false;
bool MENU_OPEN = false;
bool SHUT_DOWN = false;

Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN_1, NEO_GRBW + NEO_KHZ800); // LED Strip
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN_2, NEO_GRBW + NEO_KHZ800); // LED Strip
Adafruit_NeoPixel strip3(LED_COUNT, LED_PIN_3, NEO_GRBW + NEO_KHZ800); // LED Strip
Adafruit_NeoPixel strip4(LED_COUNT, LED_PIN_4, NEO_GRBW + NEO_KHZ800); // LED Strip
Adafruit_NeoPixel strip5(LED_COUNT, LED_PIN_5, NEO_GRBW + NEO_KHZ800); // LED Strip

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, U8X8_PIN_NONE, A1, A3);   // OLED Display

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to my light project.");
  
  u8g2.begin();         // Initiate OLED Display
  u8g2.enableUTF8Print();

  // Joystick
  pinMode(A7, INPUT);       // Joystick X axis
  pinMode(A5, INPUT);       // Joystick Y axis
  pinMode(JOYSTICK_PRESS, INPUT_PULLUP); // Pressing the Joystick

  // Brightness sensor
  pinMode(A0, INPUT);

  // Door magnet
  pinMode(DOOR_PIN, INPUT_PULLUP);

  // Menu button
  pinMode(MENU_PIN, INPUT_PULLUP);
  
  // Initialize LED Strip
  strip1.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip1.show();            // Turn OFF all pixels ASAP
  
  strip2.begin();
  strip2.show();
  
  strip3.begin();
  strip3.show();
  
  strip4.begin();
  strip4.show();
  
  strip5.begin();
  strip5.show();
}

void loop() {
  if (SHUT_DOWN) {
    Serial.println("System is shut down");
    handleTurnedOff();
  } else {
    handleLoop(); 
  }
}
