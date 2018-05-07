#include "FastRCReader.h"
#include "PortDefinitions.h"
#include "animations.h"
#include "ServoProperties.h"
#include "MotionServo.h"
#include "RCProperties.h"
#include <EEPROM.h>

//Photo-sensor threshholde to detect if there is a block in place or not
#define POSITION_LOADED_THRESHHOLD 50

//Create RC Object
RCChannelMapper RC;

const uint8_t positionPin[POSITION_COUNT] = {POSITION_A_PIN, POSITION_B_PIN, POSITION_C_PIN};

MotionServo servo[SERVO_COUNT];


void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  LED(HIGH);

  Serial.println("Starting Setup!\n");

  char buffer[50];

  //Prepare the RC-RX and add all needed Channels
  Serial.println("RC:");
  RC.begin();
  for (uint8_t i = 0; i < CHANNEL_AMOUNT; i++) {
    RC.addChannel(rcChannels[i]);
    sprintf(buffer, "Added Channel %i on Pin %i", i, rcChannels[i]);
    Serial.println(buffer);
  }

  //Get saved calibration from EEPROM
  Serial.print("\nRead EEPROM ");
  EEPROM.get(EEPROM_ADRESS, RC);
  Serial.println("finish\n");

  //Set the mapping from the RC-Channels to output values between 0 and 180
  Serial.println("Set mapping:");
  for (uint8_t i = 0; i < CHANNEL_AMOUNT; i++) {
    RC.setTo180(rcChannels[i]);
    sprintf(buffer, "Changed Channel %i mapping to 0-180", i);
    Serial.println(buffer);
  }

  //Prepare all servos to be ready
  Serial.println("\nConfigure all servos:");
  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    servo[i].begin(servoProperties[i][PORT_ID], servoProperties[i][MIN_ID], servoProperties[i][MAX_ID], servoProperties[i][HOME_ID]);
    sprintf(buffer, "Set Servo %i to\tPort %i\tMin %i\tMax %i\tHome %i", i, servoProperties[i][PORT_ID], servoProperties[i][MIN_ID], servoProperties[i][MAX_ID], servoProperties[i][HOME_ID]);
    Serial.println(buffer);
  }

  Serial.println("\nAdd all Position-pins:");
  for (uint8_t i = 0; i < POSITION_COUNT; i++) {
    pinMode(positionPin[i], INPUT);
    sprintf(buffer, "Added Position %i at pin A%i", i, positionPin[i]);
    Serial.println(buffer);
  }

  Serial.println("\nSetup finish!\n");
  LED(LOW);
}

uint8_t activeProgram = 3;
void loop() {
  switch (activeProgram) {
    case 1:
      //Do something by button press
      if (digitalRead(BUTTON_PIN)) {
        Serial.println("Button pressed\n");
        onButtonPress();
      }
      break;
    case 2:
      //Response to RC once
      rcLoop();
      break;
  }

  if (Serial.available() > 0) serialEvent();
}


void LED(bool status) {
  digitalWrite(LED_BUILTIN, status);
}


