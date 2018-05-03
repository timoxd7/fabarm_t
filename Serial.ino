void serialEvent() {
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();

    if (incomingChar == 'b' || incomingChar == 'B') {
      Serial.print("Button digitally pressed!\n\n");
      onButtonPress();
    } else if (incomingChar == 'r' || incomingChar == 'R') {
      //Here will come code for RC control in the future
      Serial.print("RC is not implemented yet (0x03)\n\n");
    } else if (incomingChar == 'a' || incomingChar == 'A') {
      //Activate or deactivate a Program
      Serial.print("What to deactivate?\n\nB == Button (currently ");
      if (activeProgram == 1) Serial.print("active");
      else Serial.print("not active");

      Serial.print(")\nS == Stop any active Program\n\n");

      while (Serial.available() <= 0);
      incomingChar = Serial.read();

      if (incomingChar == 'b' || incomingChar == 'B') {
        if (activeProgram == 1) {
          activeProgram = 0;
        } else {
          activeProgram = 1;
        }
      } else if (incomingChar == 'r' || incomingChar == 'R') {
        Serial.print("RC is not implemented yet (0x04)\n\n");
      } else if (incomingChar == 's' || incomingChar == 'S') {
        activeProgram = 0;
      } else {
        Serial.print("False input! (0x02)\n\n");
      }

    } else {
      Serial.print("False input! (0x01)\n\n");
    }

    emptySerial();
  }
}

void emptySerial() {
  while (Serial.available() > 0) Serial.read();
}


