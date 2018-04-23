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
void loop() {
  //Do something by button press
  if (digitalRead(BUTTON_PIN)) onButtonPress();

  if (Serial.available() > 0) serialEvent();
}


void onButtonPress() {
  if (loaded) {
    loaded = !dropAnim();
  } else {
    loaded = pickupAnim();
  }
}

void serialEvent() {
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();

    if (incomingChar == 'b' || incomingChar == 'B') {
      onButtonPress();
    } else if (incomingChar == 'r' || incomingChar == 'R') {
      //Here will come code for RC control in the future
    }

    emptySerial();
  }
}

void emptySerial() {
  while (Serial.available() > 0) Serial.read();
}

bool pickupAnim() {
  uint8_t filledPlace = findPlace(true);

  if (filledPlace >= 0 && filledPlace < POSITION_COUNT) {
    animator(PICKUP_DURATION, pickup[filledPlace], MAX_SPEED);
    return true;
  } else {
    animator(NOTHING_FOUND_DURATION, nothingFound, MAX_SPEED);
    return false;
  }
}

bool dropAnim() {
  uint8_t freePlace = findPlace(false);

  if (freePlace >= 0 && freePlace < POSITION_COUNT) {
    animator(DROP_DURATION, drop[freePlace], MAX_SPEED);
    return true;
  } else {
    animator(NOTHING_FOUND_DURATION, nothingFound, MAX_SPEED);
    return false;
  }
}

uint8_t findPlace(bool filled) {
  uint8_t matchingPlaces[POSITION_COUNT];
  uint8_t matchingCount = 0;

  for (uint8_t i = 0; i < POSITION_COUNT; i++) {
    if (analogRead(positionPin[i]) < POSITION_LOADED_THRESHHOLD) {
      if (filled) {
        matchingPlaces[matchingCount++] = i;
      }
    } else {
      if (!filled) {
        matchingPlaces[matchingCount++] = i;
      }
    }
  }

  if (matchingCount <= 0) return POSITION_COUNT;

  uint8_t randomPlace = millis() % matchingCount;

  return matchingPlaces[randomPlace];
}

void animator(uint8_t duration, uint8_t animation[][SERVO_COUNT], float speed) {
  for (uint8_t i = 0; i < duration; i++) {
    { //To delet local Vars after using them while the loop is active
      int16_t servoMovement[SERVO_COUNT];
      bool homeServo[SERVO_COUNT];

      //First, get the incremental change of each servo
      for (uint8_t j = 0; j < SERVO_COUNT; j++) {
        if (animation[i][j] == NO_CHANGE) {
          //Do nothing
          servoMovement[j] = 0;
        } else if (animation[i][j] == HOME) {
          //Go home
          servoMovement[j] = servo[j].getHome() - servo[j].getCurrentPosition();
          homeServo[j] = true;
        } else {
          servoMovement[j] = animation[i][j] - servo[j].getCurrentPosition();
        }
      }

      //Then compare them to define the Time wich the movement will take
      uint8_t highestChange;
      for (uint8_t j = 0; j < SERVO_COUNT; j++) {
        uint8_t currentValue = 0;
        if (servoMovement[j] < 0) currentValue -= servoMovement[j];
        else currentValue = servoMovement[j];

        if (currentValue > highestChange) highestChange = currentValue;
      }

      //calculating the movement time
      unsigned long movementTime = highestChange * speed;
      unsigned long currentTime = millis();

      for (uint8_t j = 0; j < SERVO_COUNT; j++) {
        if (homeServo[j]) {
          servo[j].home(movementTime, currentTime);
        } else {
          servo[j].move(servoMovement[j], movementTime, currentTime);
        }
      }

    }

    bool movement = true;
    while (movement) {
      movement = false;

      for (uint8_t j = 0; j < SERVO_COUNT; j++) {
        movement |= servo[j].loop();
      }
    }
  }
}

