// Define camera trigger pins
#define cam1pin 4
#define cam2pin 5
#define cam3pin 6
#define cam4pin 7

void setup() {
  // Set outputs for the 4 cameras
  pinMode(cam1pin, OUTPUT);
  pinMode(cam2pin, OUTPUT);
  pinMode(cam3pin, OUTPUT);
  pinMode(cam4pin, OUTPUT);
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
    digitalWrite(cam1pin, HIGH);
    digitalWrite(cam2pin, HIGH);
    digitalWrite(cam3pin, HIGH);
    digitalWrite(cam4pin, HIGH);
    // while (millis() <= timeNow + halfPeriodInMs) { ; }
    delay(halfPeriodInMs);
    digitalWrite(cam1pin, LOW);
    digitalWrite(cam2pin, LOW);
    digitalWrite(cam3pin, LOW);
    digitalWrite(cam4pin, LOW);
    // while (millis() <= timeNow + 2 * halfPeriodInMs) { ; }
    delay(halfPeriodInMs);
  }
}

void sendSingleSignalToSingleCamera(int cameraId)
{
  int cameraPin = 0;
  switch (cameraId)
  {
    case 1:
      cameraPin = cam1pin;
      break;
    case 2:
      cameraPin = cam2pin;
      break;
    case 3:
      cameraPin = cam3pin;
      break;
    case 4:
      cameraPin = cam4pin;
      break;
    default:
      break;
  }
  digitalWrite(cameraPin, HIGH);
  delay(10); // This delay can probably be (a lot?) less. I'm using 10 to test on LED's
  digitalWrite(cameraPin, LOW);
}