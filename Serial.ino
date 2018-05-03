void serialEvent() {
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();

    if (incomingChar == 'b' || incomingChar == 'B') {
      Serial.print("Button digitally pressed!\n\n");
      onButtonPress();
    } else if (incomingChar == 'r' || incomingChar == 'R') {
      Serial.print("RC control is ");
      if (activeProgram == 2) Serial.print("active. You can use your remote to control the fabarm.");
      else Serial.print("not active.\n\tTo activate it, send AR over Serial.");
    } else if (incomingChar == 'a' || incomingChar == 'A') {
      //Activate or deactivate a Program
      Serial.print("What to (de)activate?\n\nB == Button (currently ");
      if (activeProgram == 1) Serial.print("active");
      else Serial.print("not active");

      Serial.print(")\nR == RC control (currently ");
      if (activeProgram == 2) Serial.print("active");
      else Serial.print("not active");

      Serial.print(")\nS == Stop any active Program\n\n");

      while (Serial.available() <= 0);
      incomingChar = Serial.read();

      if (incomingChar == 'b' || incomingChar == 'B') {
        if (activeProgram == 1) {
          activeProgram = 0;
        } else {
          activeProgram = 1;
          prepareButton();
        }
      } else if (incomingChar == 'r' || incomingChar == 'R') {
        if (activeProgram == 2) {
          activeProgram = 0;
        } else {
          activeProgram = 2;
        }
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


