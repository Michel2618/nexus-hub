#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// ==========================================
// --- NETWORK & TELEGRAM SETTINGS ---
// ==========================================
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Paste your Bot Token and Chat ID here
#define BOT_TOKEN "YOUR_BOT_TOKEN_HERE"
#define CHAT_ID "YOUR_CHAT_ID_HERE"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

// ==========================================
// --- HARDWARE & TIMING SETTINGS ---
// ==========================================
const int buttonPin = 4;
const int relayPin = 5;
const int ringDuration = 500; 
const int cooldownDuration = 5000; 

int lastButtonState = HIGH; 
unsigned long lastRingTime = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT); 
  digitalWrite(relayPin, HIGH); // Relay OFF
  
  // --- Connect to Wi-Fi ---
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Connected Successfully!");
  
  // Required for the ESP32 to securely connect to Telegram
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}

void loop() {
  int currentButtonState = digitalRead(buttonPin);

  // If button was just pressed
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    
    // If cooldown has passed
    if (millis() - lastRingTime >= cooldownDuration) {
      Serial.println("Gate Bell Triggered!");
      
      // 1. Ring the bell locally
      digitalWrite(relayPin, LOW); 
      delay(ringDuration);         
      digitalWrite(relayPin, HIGH);
      
      // 2. Send the Telegram notification
      Serial.println("Sending Telegram message...");
      bot.sendMessage(CHAT_ID, "Ding Dong! Someone is at the gate.", "");
      
      // 3. Reset the cooldown timer
      lastRingTime = millis();
    } else {
      Serial.println("Button pressed, but cooling down...");
    }
  }

  lastButtonState = currentButtonState;
  delay(50);
}
