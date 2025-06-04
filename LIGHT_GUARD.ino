// Pin definitions
const int lightSensorPin = A0;
const int buzzerPin = 9;
const int ledGreen = 11;
const int ledOrange = 12;
const int ledRed = 13;
const int armButtonPin = A4;
const int disarmButtonPin = A5;

// System state
bool systemArmed = false;
int lightThreshold = 640;

// Password definitions
const int passwordLength = 3;
char password[passwordLength] = {'S', 'L', 'S'}; // S = Short, L = Long
char input[passwordLength];
int inputIndex = 0;
unsigned long pressStartTime = 0;
bool waitingForRelease = false;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledOrange, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(armButtonPin, INPUT);
  pinMode(disarmButtonPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  int light = analogRead(lightSensorPin);
  int armButton = analogRead(armButtonPin);
  int disarmButton = analogRead(disarmButtonPin);

  Serial.print("Light: ");
  Serial.println(light);

  // Arm the system if Arm button is pressed
  if (armButton > 1000 && !systemArmed) {
    systemArmed = true;
    Serial.println("🔒 System Armed");
    delay(1000);
  }

  // Handle password input only if system is armed
  if (systemArmed) {
    handleDisarmInput(disarmButton);
  }

  // Trigger alarm if system is armed and it's dark
  if (systemArmed && light < lightThreshold) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledOrange, LOW);
    tone(buzzerPin, 3000); // Highest audible tone
  } else if (systemArmed) {
    digitalWrite(ledOrange, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    noTone(buzzerPin);
  } else {
    // Disarmed state
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledOrange, LOW);
    noTone(buzzerPin);
  }

  delay(100);
}

void handleDisarmInput(int disarmButton) {
  if (disarmButton > 1000 && !waitingForRelease) {
    pressStartTime = millis();
    waitingForRelease = true;
  }

  if (waitingForRelease && disarmButton < 100) {
    unsigned long pressDuration = millis() - pressStartTime;
    char pressType = (pressDuration < 800) ? 'S' : 'L';
    input[inputIndex++] = pressType;
    Serial.print("Input: ");
    Serial.println(pressType);
    waitingForRelease = false;

    if (inputIndex == passwordLength) {
      if (checkPassword()) {
        systemArmed = false;
        Serial.println("🔓 System Disarmed - Password Correct!");
      } else {
        Serial.println("❌ Incorrect Password");
      }
      inputIndex = 0;
    }
  }
}

bool checkPassword() {
  for (int i = 0; i < passwordLength; i++) {
    if (input[i] != password[i]) return false;
  }
  return true;
}
