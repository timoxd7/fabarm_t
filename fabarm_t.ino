//#include "FastRCReader.h"
#include "animations.h"
#include "ServoProperties.h"
#include "MotionServo.h"

//Button and Block-Positions port definitions
#define BUTTON_PIN 2
#define POSITION_A_PIN 0 //A0
#define POSITION_B_PIN 1 //A1
#define POSITION_C_PIN 2 //A2

//How many positions where the Block can be placed are there?
#define POSITION_COUNT 3

//Photo-sensor threshholde to think there is a block in place or not
#define POSITION_LOADED_THRESHHOLD 50

/*
  //RC Port definitions
  #define CHANNEL_AMOUNT 4
  const uint8_t rcChannels[] = {3, 4, 5, 6};

  RCChannelMapper RC;
*/

const uint8_t positionPin[POSITION_COUNT] = {POSITION_A_PIN, POSITION_B_PIN, POSITION_C_PIN};

MotionServo servo[SERVO_COUNT];


void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);

  /*
    RC.begin();
    for (uint8_t i = 0; i < CHANNEL_AMOUNT; i++){
    RC.addChannel(rcChannels[i]);
    }
  */

  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    servo[i].begin(servoProperties[i][PORT_ID], servoProperties[i][MIN_ID], servoProperties[i][MAX_ID], servoProperties[i][HOME_ID]);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  for (uint8_t i = 0; i < POSITION_COUNT; i++) {
    pinMode(positionPin[i], INPUT);
  }
}

bool loaded;
uint8_t activeProgram = 1;
void loop() {
  switch (activeProgram) {
    case 1:
      //Do something by button press
      if (digitalRead(BUTTON_PIN)) onButtonPress();
      break;
  }

  if (Serial.available() > 0) serialEvent();
}


void LED(bool status) {
  digitalWrite(LED_BUILTIN, status);
}


