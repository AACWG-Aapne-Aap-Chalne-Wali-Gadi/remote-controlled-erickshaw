# **Remote Control of Forward and Reverse Movement in an E-Rickshaw: A Practical Implementation**

## Introduction

In our ongoing effort to convert a second-hand e-rickshaw into an autonomous or semi-automated vehicle, we started with a basic but crucial function: remotely controlling the direction of motion—forward and reverse. This is typically done mechanically in conventional e-rickshaws, using a physical switch linked to the throttle/accelerator. Our aim was to replace this manual control with a remotely controlled system using an ESP32 microcontroller and relays.

This change not only allows remote operation but also lays the foundation for further automation, such as integrating this system with sensors or higher-level autonomy modules in future phases.

---

## The Traditional Setup

Originally, the e-rickshaw came with a mechanical switch for toggling between forward and reverse modes. This switch is directly connected to the motor controller and determines the current direction of movement. It works in sync with the accelerator (throttle)—meaning whichever direction is set using the switch, the motor would move in that direction as long as throttle input is provided.

While this setup is simple and robust, it is not suitable for remote or programmatic control, which is essential for autonomous applications.

![Traditional Setup](images/traditional-switch.jpg)

---

## Our New Setup: Relay + ESP32

To achieve wireless direction control, we removed the physical switch and introduced:

- 2 Relay Module  
- ESP32 microcontroller  
- Bluetooth-based command system  

### How It Works

- The wire that originally went from the switch to the motor controller is now connected to the relay's **K1** pin.
- The relay is triggered by the ESP32 through **IN1** using **GPIO pin 14**.
- When the relay is **OFF** → it allows **forward movement** (default).
- When the relay is **ON** → it switches the connection → the rickshaw goes in **reverse**.

By default, the system is in forward mode. When we send a command to the ESP32 to switch **ON** the relay, it connects the circuit in a way that mimics the reverse position of the original switch.

![ESP32 Relay Setup](images/esp32-relay-setup.jpg)

---

## Wiring Breakdown (Simplified Explanation)

To make the connections clear and simple:

| **Component**       | **Connection Details**             |
|---------------------|------------------------------------|
| Motor Controller    | Signal wire connected to K1 on relay |
| Relay (IN1)         | Connected to GPIO 14 on ESP32      |
| Relay (VCC)         | Connected to 3.3V from ESP32       |
| Relay (GND)         | Connected to GND of ESP32          |

**🔴 Red Wires – Power Supply**  
The red wire was used to provide 3.3V power from the ESP32 to the relay module.

**⚫ Black Wires – Ground**  
Black wires ensured a common ground between ESP32 and the relay module, which is critical for stable switching.

![Real Wiring Setup](images/real-wiring.jpg)

---

## Bluetooth-Based Direction Control

To allow remote operation, we used the ESP32’s built-in Bluetooth feature. The ESP32 listens for characters sent from a phone or Bluetooth terminal app.

### How it Works:

- **Send 'B'** → Relay turns **ON** → e-rickshaw moves in **Reverse**
- **Send 'F'** → Relay turns **OFF** → e-rickshaw moves **Forward**

---

**Remote Control of E‑Rickshaw Forward/Reverse Switch**

---

## **1\. How It’s Hooked Up**

* **ESP32 Module**

  * Brain of the system

  * Talks to your phone over Wi‑Fi or Bluetooth

* **Servo Motor**

  * Pushes the lever forward or backward

  * Needs a steady 5 V power supply

* **Power Supply**

  * One line for the ESP32 (3.3 V)

  * One line for the servo (5 V)

* **Mechanical Link**

  * A small arm or bracket connects the servo horn to the rickshaw’s switch

---

## **2\. Key Parts We will Use**

* **ESP32-WROOM-32**

  * Fast Wi‑Fi & Bluetooth, easy to program

* **High‑Torque Servo**

  * At least 10 kg·cm torque so it can move the lever

  * 180° range

* **Voltage Regulator**

  * Keeps 5 V steady for the servo

* **Mounting Bracket**

  * Holds the servo in place and lines it up with the lever

---

## **3\. Simple Wiring**

1. **Power**

   * Servo → 5 V, ground

   * ESP32 → 3.3 V (from USB or regulator), ground

   * Tie all grounds together

2. **Signal**

   * ESP32 PWM pin → Servo control pin

---

## **4\. Basic Program Flow**

1. **Connect** your phone app to the ESP32.

2. **Send** a command: “Forward,” “Reverse,” or “Neutral.”

3. ESP32 **reads** that command and writes the correct PWM signal to the servo:

   * Neutral → middle position

   * Forward → one end of range

   * Reverse → the other end

4. Servo **moves** the lever.

---

## **5\. Keeping It Safe**

* **Brake Override**

  * If the brake lever is pulled, force the servo to Neutral so it can’t switch direction.

* **Speed Lockout**

  * (Optional) Don’t allow switching if the rickshaw is moving above 3 km/h.

* **Signal Timeout**

  * If no command comes in for 0.2 s, go to Neutral automatically.

* **Physical Stops**

  * Add small blocks so the servo can’t push the lever past its safe limits.

---

## **6\. Testing Steps**

1. **Bench Test**

   * Power everything on your workbench.

   * Check the servo moves to all three positions.

2. **On‑Vehicle Test**

   * Mount it on the rickshaw.

   * Verify the lever moves smoothly forward and back.

3. **Field Trial**

   * Drive slowly and test from your phone.

   * Make sure the override features work if you hit the brake or drop signal.

---

## **7\. Next Improvements**

* **Position Feedback**: Add a small sensor so the ESP32 knows exactly where the lever is.

* **Better Linkage**: Use a sturdier bar or joint to reduce play.

* **Dashboard Display**: Show direction status and signal strength on a small screen.

---

## 📜 Code We Used

```cpp
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;  // Bluetooth object

#define RELAY_PIN 14  // GPIO connected to relay IN1

void setup() {
  Serial.begin(115200);          
  SerialBT.begin("ESP32-Relay"); // Bluetooth device name
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Default: Forward

  Serial.println("🔌 Relay Bluetooth Control Ready");
  Serial.println("📲 Connect to 'ESP32-Relay' and send 'B' or 'F'");
}

void loop() {
  if (SerialBT.available()) {
    char input = SerialBT.read();

    if (input == 'B') {
      digitalWrite(RELAY_PIN, HIGH);  // Reverse
      Serial.println("✅ Relay ON - Reverse Mode");
      SerialBT.println("✅ Relay ON - Reverse Mode");
    }
    else if (input == 'F') {
      digitalWrite(RELAY_PIN, LOW);   // Forward
      Serial.println("⛔ Relay OFF - Forward Mode");
      SerialBT.println("⛔ Relay OFF - Forward Mode");
    }
    else {
      Serial.println("❗ Invalid Input. Send 'B' or 'F'");
      SerialBT.println("❗ Invalid Input. Send 'B' or 'F'");
    }
  }
}
