#include <EEPROM.h>

void setup() {
  Serial.begin(9600); // Start serial for debugging
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0); // Reset every byte to 0
  }
  Serial.println("EEPROM has been cleared!");
}

void loop() {
  // Nothing to do here, reset happens once in setup
}
