void rcLoop() {
  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    uint8_t rcValue = RC.getChannel(rcChannels[i]);
    servo[i].moveTo(rcValue, 0, 0);
    Serial.print(rcValue); Serial.print("\t");
  } Serial.println("");
}
