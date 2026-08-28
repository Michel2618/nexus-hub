# Smart Gate Bell Notification System

A connected doorbell node that bridges physical hardware with digital notifications. When a visitor presses the physical gate button, this module triggers a local chime via a relay and securely pushes a notification to a mobile device via Telegram.

## Features
*   **Hardware Trigger:** Reads a physical button press with hardware debounce considerations.
*   **Local Chime:** Activates a 5V relay for a set duration to ring a traditional bell.
*   **Cloud Notification:** Connects securely to the Telegram API to send instant chat messages.
*   **Spam Protection:** Built-in cooldown timer prevents rapid re-triggering of the bell and notification spam.

## Hardware Pinout

| Component | Pin | Notes |
| :--- | :--- | :--- |
| **Push Button** | `GPIO 4` | Uses `INPUT_PULLUP`. Connect button between Pin 4 and GND. |
| **Relay Module** | `GPIO 5` | Controls the local bell circuit. |

## Software Dependencies
Install the following libraries via the Arduino Library Manager before compiling:
*   `UniversalTelegramBot` by Brian Lough
*   `ArduinoJson` by Benoit Blanchon

## Setup Instructions

1. **Telegram Bot Setup:**
   * Message `@BotFather` on Telegram to create a new bot and retrieve your `BOT_TOKEN`.
   * Message `@myidbot` to find your personal `CHAT_ID`.
2. **Configuration:**
   * Open the `.ino` file and update the Network & Telegram settings block with your Wi-Fi credentials, Bot Token, and Chat ID.
3. **Upload:**
   * Flash the code to your ESP board using the Arduino IDE. 
   * Open the Serial Monitor (115200 baud) to verify the Wi-Fi connection and test the button.
