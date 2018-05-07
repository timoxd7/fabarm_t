void rcLoop() {
  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    servo[i].moveTo(RC.getChannel(rcChannels[i]), 0, 0);
  }
}
