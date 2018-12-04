void setup() {
  // Set outputs for the 4 cameras
  DDRD = DDRD | B11110000;
  PORTD = PORTD | B00000000;
  // Start Serial com
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  if (Serial.available() > 0) {
    menu();
  }
}

void menu() {
  String data = Serial.readString();
  if (data.startsWith("n")) {
    // Normal mode (nXX)
    // Get fps
    int fps = data.substring(1).toInt();
    // Trigger all cameras simultaneously
    return sendPWMtoAll(fps);
  } else if (data.startsWith("c")) {
    // Calibration mode (cX)
    // Get cameraId
    int cameraId = data.substring(1).toInt();
    // Trigger a single picture on a single camera
    return sendSingleSignalToSingleCamera(cameraId);
  } else if (data.startsWith("stop")) {
    // Stop whatever it's doing by returning to the loop function
    return;
  }
}

void sendPWMtoAll(int fps) {
  float period = 1/(float)fps; // T = 1/f
  float periodInMs = period * 1000;
  float halfPeriodInMs = periodInMs / (float)2;
  while (true) {
    // Stop if there's something coming in
    if (Serial.available() > 0) {
      // menu(); This doesnt work because the function is called, but the loop continues
      return menu();
    }
    // unsigned long timeNow = millis();
    PORTD = PORTD | B11110000;
    delay(halfPeriodInMs);
    PORTD = PORTD & B00000000;
    delay(halfPeriodInMs);
  }
}

void sendSingleSignalToSingleCamera(int cameraId) {
  PORTD = PORTD | (B00000000 | (1 << (cameraId + 3)));
  delay(10); // This delay can probably be (a lot?) less. I'm using 10 to test on LED's
  PORTD = PORTD & B00000000;
}