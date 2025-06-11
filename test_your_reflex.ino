const int ledPin = 13;
const int buttonPin = A4;

unsigned long startTime;
unsigned long reactionTime;
unsigned long bestTime = 9999;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT); // Don't use INPUT_PULLUP
  Serial.begin(9600);
  Serial.println("== Reaction Timer Game ==");
  delay(1000);
}

void loop() {
  // Wait for button to be released (LOW means not pressed)
  while (digitalRead(buttonPin) == 1) {
    Serial.println("👉 Press and release the button to begin...");
    delay(500);
  }

  delay(1000); // short pause

  // Random wait before signal
  int waitTime = random(2000, 5000);
  unsigned long waitStart = millis();
  while (millis() - waitStart < waitTime) {
    if (digitalRead(buttonPin) == 1) { // Pressed too early
      Serial.println("🚫 False start! You pressed too early.");
      delay(2000);
      return;
    }
  }

  Serial.println("NOW! Press the button!");
  digitalWrite(ledPin, HIGH);
  startTime = millis();

  // Wait for user to press the button
  while (digitalRead(buttonPin) == 0) {
    // do nothing
  }

  reactionTime = millis() - startTime;
  digitalWrite(ledPin, LOW);

  Serial.print("⏱️ Reaction Time: ");
  Serial.print(reactionTime);
  Serial.println(" ms");

  if (reactionTime < 300) {
    Serial.println("⚡ Lightning Fast!");
  } else if (reactionTime < 700) {
    Serial.println("👍 Good Reflexes!");
  } else {
    Serial.println("🐢 Too slow... try again!");
  }

  if (reactionTime < bestTime) {
    bestTime = reactionTime;
    Serial.print("🏆 New Best Time: ");
    Serial.print(bestTime);
    Serial.println(" ms 🎉");
  } else {
    Serial.print("🔥 Current Best Time: ");
    Serial.print(bestTime);
    Serial.println(" ms");
  }

  delay(3000);
}
