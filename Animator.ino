void animator(uint8_t duration, uint8_t animation[][SERVO_COUNT], float speed) {
  LED(HIGH);

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

  LED(LOW);
}


