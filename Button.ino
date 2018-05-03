void prepareButton() {
  LED(HIGH);

  unsigned long currentTime = millis(), movementTime = 180 * MAX_SPEED;

  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    servo[i].home(movementTime, currentTime);
  }

  waitTillMovementEnds();

  LED(LOW);
}

bool loaded;
void onButtonPress() {
  if (loaded) {
    loaded = !dropAnim();
  } else {
    loaded = pickupAnim();
  }
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


