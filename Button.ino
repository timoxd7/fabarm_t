void prepareButton() {
  LED(HIGH);

  unsigned long currentTime = millis(), movementTime;

  if (useSmooth) movementTime = 180 * SMOOTH_ANIMATION_SPEED;
  else movementTime = 180 * ANIMATION_SPEED;

  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    servo[i].home(movementTime, currentTime);
  }

  waitTillMovementEnds(useSmooth);

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
  float speed;
  if (useSmooth) speed = SMOOTH_ANIMATION_SPEED;
  else speed = ANIMATION_SPEED;

  if (filledPlace >= 0 && filledPlace < POSITION_COUNT) {
    animator(PICKUP_DURATION, pickup[filledPlace], speed, useSmooth);
    return true;
  } else {
    bool smooth = false;
    if (USE_SMOOTH_NOTHING_FOUND) smooth = useSmooth;
    animator(NOTHING_FOUND_DURATION, nothingFound, speed, smooth);
    return false;
  }
}

bool dropAnim() {
  uint8_t freePlace = findPlace(false);
  float speed;
  if (useSmooth) speed = SMOOTH_ANIMATION_SPEED;
  else speed = ANIMATION_SPEED;

  if (freePlace >= 0 && freePlace < POSITION_COUNT) {
    animator(DROP_DURATION, drop[freePlace], speed, useSmooth);
    return true;
  } else {
    bool smooth = false;
    if (USE_SMOOTH_NOTHING_FOUND) smooth = useSmooth;
    animator(NOTHING_FOUND_DURATION, nothingFound, speed, smooth);
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
