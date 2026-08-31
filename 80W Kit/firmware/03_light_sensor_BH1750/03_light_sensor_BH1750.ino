/*
  FiSH Floating Solar Hydrogen Prototype — 80W Kit
  Light sensor test (BH1750FVI digital ambient light sensor, I2C)

  Reads illuminance (lux) from the BH1750 over I2C and prints it to Serial.
  Requires the "BH1750" Arduino library (by Christopher Laws).

  Wiring: BH1750 SDA -> A4/SDA, SCL -> A5/SCL, VCC -> 5V (or 3.3V per
  breakout), GND -> GND
*/

#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter;

void setup() {
  Serial.begin(9600);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use
  // Wire.begin(D2, D1);

  lightMeter.begin();

}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}
