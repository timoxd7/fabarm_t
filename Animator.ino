void animator(uint8_t duration, uint8_t animation[][SERVO_COUNT], float speed, bool smooth) {
  LED(HIGH);
  Serial.print("Starting Animation ");
  if (smooth) Serial.print("with");
  else Serial.print("without");

  Serial.println(" smooth movement:");

  for (uint8_t i = 0; i < duration; i++) {
    { //To delet local Vars after using them while the loop is active
      Serial.print("Movement "); Serial.println(i);

      int16_t servoMovement[SERVO_COUNT];
      bool homeServo[SERVO_COUNT];

      //First, get the incremental change of each servo and find highest Change
      uint8_t highestChange = 0;
      for (uint8_t j = 0; j < SERVO_COUNT; j++) {
        //Print current Movement
        Serial.print(animation[i][j]); Serial.print("\t");

        //Set homing first off to prevent from false triggering
        homeServo[j] = false;

        if (animation[i][j] >= 0 && animation[i][j] <= 180) {
          //Calculate incremental change
          servoMovement[j] = animation[i][j] - servo[j].getCurrentPosition();
        } else if (animation[i][j] == HOME) {
          //Go home
          servoMovement[j] = servo[j].getHome() - servo[j].getCurrentPosition();
          homeServo[j] = true;
        } else {
          //Do nothing
          servoMovement[j] = 0;
        }

        //Find highest Change
        uint8_t currentChange = 0;
        if (servoMovement[j] < 0) currentChange = -servoMovement[j];
        else currentChange = servoMovement[j];

        #ifdef CLAW_DOUBLE_SPEED
        if (j == CLAW_ID) currentChange /= 2;
        #endif

        if (currentChange > highestChange) highestChange = currentChange;
      } Serial.println("");

      //calculating the movement time
      unsigned long movementTime = highestChange * speed;
      unsigned long currentTime = millis();
      Serial.print(" ->Movement Time: "); Serial.print(movementTime); Serial.println("mS");

      for (uint8_t j = 0; j < SERVO_COUNT; j++) {
        if (homeServo[j]) {
          servo[j].home(movementTime, currentTime);
        } else {
          servo[j].move(servoMovement[j], movementTime, currentTime);
        }
      }
    }

    waitTillMovementEnds(smooth);
  }

  Serial.println("Animation finished!\n");

  LED(LOW);
}

void waitTillMovementEnds(bool smooth) {
  bool movement = true;
  while (movement) {
    movement = false;
    unsigned long currentTime = millis();

    for (uint8_t i = 0; i < SERVO_COUNT; i++) {
      movement |= servo[i].loop(currentTime, smooth);
    }
  }
}

