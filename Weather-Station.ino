/*
* Hardware designed for:
* Arduino Mega 2560, DHT11, LCD1602
* Written by matthewyang204
* Credits (MLA):
* 1. TheLostGhost. "Weather Station with DHT11 Sensor and LCD 1602 Display." Hackster.Io, 27 Apr. 2024, www.hackster.io/TheLostGhost/weather-station-with-dht11-sensor-and-lcd-1602-display-68f6a7. Accessed 27 Dec. 2024.
* Copyrights:
* (c) matthewyang204 2024
* (c) TheLostGhost 2020
*/

#include <dht_nonblocking.h>
#include <LiquidCrystal.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11
#define DHT_SENSOR_PIN 8

// Initialize the DHT sensor and LCD
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  static float init0 = 0, init1 = 0; // Create temporary placeholders
  lcd.begin(16, 2);  // Initialize the LCD with a 16x2 size
  lcd.clear(); // Clear the screen at the start
  lcd.clear();
  String initText = String("Retrieving data..."); // Set text for init
  // Print text on display, wrapping characters correctly
  if (initText.length() <= 16) {
    lcd.setCursor(0, 0);
    lcd.print(initText);
  } else {
    lcd.setCursor(0, 0);
    lcd.print(initText.substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(initText.substring(16));
  }
  dht_sensor.measure(&init0, &init1); // Initialize DHT11 sensor by measuring to placeholder init variables
  delay(5000); // Wait 5000ms for sensor init
  lcd.clear(); // Clear screen before continuing
}

void loop() {
  static float temperature = 0.0, humidity = 0.0;  // Stored temperature and humidity values

  // Attempt to measure temperature and humidity
  dht_sensor.measure(&temperature, &humidity);

  // Prepare display text with the last measured values
  String displayText = String(temperature, 0) + " C, " + String(humidity, 0) + "%";

  // Clear and update the LCD display
  lcd.clear();
  if (displayText.length() <= 16) {
    lcd.setCursor(0, 0);
    lcd.print(displayText);
  } else {
    lcd.setCursor(0, 0);
    lcd.print(displayText.substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(displayText.substring(16));
  }

  // Delay for 1000ms
  delay(1000);
}
