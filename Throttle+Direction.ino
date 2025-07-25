#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define RELAY_PIN 14     // Relay IN1 for direction control
#define DAC_PIN 25       // DAC output for speed control

int speedValue = 0;  // Range: 0 (0V) to 255 (~3.3V)

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32-EV-Control");

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);     // Default: Forward
  dacWrite(DAC_PIN, speedValue);    // Default: 0V

  Serial.println("ESP32 EV Control Ready");
  Serial.println("➡️  F = Forward | B = Reverse");
  Serial.println("⚡ L = Speed UP | R = Speed DOWN");
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();

    switch (command) {
      case 'F':
        digitalWrite(RELAY_PIN, LOW);  // Forward
        Serial.println("Direction: FORWARD");
        SerialBT.println("Direction: FORWARD");
        break;

      case 'B':
        digitalWrite(RELAY_PIN, HIGH); // Reverse
        Serial.println("Direction: REVERSE");
        SerialBT.println("Direction: REVERSE");
        break;

      case 'L':
        speedValue += 10;
        if (speedValue > 255) speedValue = 255;
        dacWrite(DAC_PIN, speedValue);

        Serial.println("⚡ Speed UP → DAC: " + String(speedValue) + 
                       " → Voltage: " + String((speedValue * 3.3) / 255.0, 2) + "V");
        SerialBT.println("⚡ Speed: " + String(speedValue));
        break;

      case 'R':
        speedValue -= 10;
        if (speedValue < 0) speedValue = 0;
        dacWrite(DAC_PIN, speedValue);

        Serial.println("Speed DOWN → DAC: " + String(speedValue) + 
                       " → Voltage: " + String((speedValue * 3.3) / 255.0, 2) + "V");
        SerialBT.println("Speed: " + String(speedValue));
        break;

      default:
        Serial.println("Unknown command: " + String(command));
        SerialBT.println("Use F, B, L, R only");
        break;
    }
  }
}
