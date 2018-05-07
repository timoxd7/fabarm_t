void serialEvent() {
  if (Serial.available() <= 0) return;

  char incomingChar = Serial.read();

  if (incomingChar == 'b' || incomingChar == 'B') {
    if (activeProgram == 1 || activeProgram == 3) {
      Serial.println("Button digitally pressed\n");
      onButtonPress();
    } else {
      Serial.println("Button-Program deactivated!\n\tTo activate, send AB over Serial\n");
    }
  } else if (incomingChar == 'r' || incomingChar == 'R') {
    Serial.print("RC control ");
    if (activeProgram == 2) Serial.println("active. You can use your remote to control the fabarm\n");
    else Serial.println("not active\n\tTo activate, send AR over Serial\n");
  } else if (incomingChar == 'a' || incomingChar == 'A') {
    { //Wait if got the second expression at the same time -> no need to print the explanation
      unsigned long waitSince = millis();
      while ((Serial.available() <= 0) && ((millis() - waitSince) < 1));
    }

    if (Serial.available() <= 0) {
      //Activate or deactivate a Program
      Serial.print("What to (de)activate?\n\nB == Button (currently ");
      programActive(1);

      Serial.print(")\nR == RC control (currently ");
      programActive(2);

      Serial.print(")\nD == (only) digital Button control (currently ");
      programActive(3);

      Serial.println(")\nS == Stop any active Program\n");

      while (Serial.available() <= 0);
    }

    incomingChar = Serial.read();

    if (incomingChar == 'b' || incomingChar == 'B') {
      if (activeProgram == 1) {
        activeProgram = 0;
        sendSerialDeactivated();
      } else {
        activeProgram = 1;
        prepareButton();
        sendSerialActivated();
      }
      Serial.println("Button-Program\n");
    } else if (incomingChar == 'r' || incomingChar == 'R') {
      if (activeProgram == 2) {
        activeProgram = 0;
        sendSerialDeactivated();
      } else {
        activeProgram = 2;
        sendSerialActivated();
      }
      Serial.println("RC-Program\n");
    } else if (incomingChar == 'd' || incomingChar == 'D') {
      if (activeProgram == 3) {
        activeProgram = 0;
        sendSerialDeactivated();
      } else {
        activeProgram = 3;
        sendSerialActivated();
      }
      Serial.println("(only)Digital-Button-Program\n");
    } else if (incomingChar == 's' || incomingChar == 'S') {
      activeProgram = 0;
      Serial.println("Stopped all active programs\n");
    } else {
      falseInput();
    }

  } else {
    falseInput();
  }

  emptySerial();
}

void emptySerial() {
  while (Serial.available() > 0) Serial.read();
}

void programActive(uint8_t program) {
  if (activeProgram == program) Serial.print("active");
  else Serial.print("not active");
}

void falseInput() {
  Serial.println("False input\n");
}

void sendSerialDeactivated() {
  Serial.print("Deactivated ");
}

void sendSerialActivated() {
  Serial.print("Activated ");
}

