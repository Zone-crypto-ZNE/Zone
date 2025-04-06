#include <EEPROM.h>

void setup() {
  Serial.begin(115200); // Start Serial at 115200 baud for zneavrminer.py
  pinMode(LED_BUILTIN, OUTPUT); // Built-in LED for mining status
  digitalWrite(LED_BUILTIN, HIGH); // LED on (mining in progress)
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command == "SYNC_DONE") {
      checkAndTurnOffLED(); // Check if 18 blocks are stored
    } else if (command.startsWith("STORE_BLOCK:")) {
      String hash = command.substring(12); // Extract hash
      storeHashInEEPROM(hash); // Store in EEPROM
    }
  }
}

void storeHashInEEPROM(String hash) {
  int addr = 0;
  while (EEPROM.read(addr) != 0 && addr < EEPROM.length()) {
    addr += 56; // 56-byte hash slots for 18 blocks
  }
  if (addr < EEPROM.length()) {
    for (int i = 0; i < hash.length() && i < 56 && (addr + i) < EEPROM.length(); i++) {
      EEPROM.write(addr + i, hash[i]);
      delay(10); // 10ms delay per write
    }
  }
}

void checkAndTurnOffLED() {
  int blockCount = 0;
  for (int i = 0; i < EEPROM.length(); i += 56) {
    if (EEPROM.read(i) != 0) { // Check if slot is used
      blockCount++;
    }
  }
  if (blockCount >= 18) { // Max 18 blocks
    digitalWrite(LED_BUILTIN, LOW); // LED off when 18 blocks hit
  }
}
