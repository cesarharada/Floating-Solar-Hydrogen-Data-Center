/*
  FiSH Floating Solar Hydrogen Prototype — 80W Kit
  Waterproof thermometer test (DS18B20 1-Wire digital temperature probe)

  Waits for the reading to stabilise (< 0.3 C variation over 5 seconds)
  before printing the stable water temperature to Serial. Requires the
  "OneWire" and "DallasTemperature" Arduino libraries.

  Wiring: DS18B20 data -> pin 8 (with a 4.7k pull-up resistor to 5V),
  VCC -> 5V, GND -> GND
*/

#include <OneWire.h>
#include <DallasTemperature.h>

// Connect your yellow pin to Pin12 on Arduino
#define ONE_WIRE_BUS 8

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

const float stableThreshold = 0.3;   // Allowed variation in temperature to consider it stable (in Celsius)
const unsigned long stableTime = 5000; // Time in milliseconds to consider the temperature stable (5 seconds)

void setup(void) {
  // Initialize the Serial Monitor at a baud rate of 9600.
  Serial.begin(9600);
  sensors.begin();
}

void loop(void) {
  // Variables to keep track of temperature stability
  float lastTemp = sensors.getTempCByIndex(0);  // Initial temperature reading
  unsigned long startTime = millis();           // Get the current time

  while (millis() - startTime < stableTime) {
    sensors.requestTemperatures();  // Request temperature
    float currentTemp = sensors.getTempCByIndex(0);

    if (abs(currentTemp - lastTemp) > stableThreshold) {
      // Reset the timer if the temperature changes significantly
      startTime = millis();
      lastTemp = currentTemp;  // Update lastTemp to the new value
    }
    
    delay(500);  // Short delay to avoid rapid looping
  }

  // After 5 seconds of stability, print the stable temperature
  Serial.print("Stable Celsius temperature: ");
  Serial.println(lastTemp);

  delay(1000);  // Optional: Delay before the next check
}
