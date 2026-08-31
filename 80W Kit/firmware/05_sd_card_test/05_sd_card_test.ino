/*
  FiSH Floating Solar Hydrogen Prototype — 80W Kit
  microSD logging test (YwRobot MicroSD module + BH1750 light sensor)

  Minimal test that confirms the SD card module is wired correctly and
  can open/write/close "data.txt" before the full sensor suite is added.
  Requires the "SD", "SPI", "BH1750" and "Wire" Arduino libraries.

  Wiring: SD module CS -> pin 10, MOSI -> 11, MISO -> 12, SCK -> 13
  (standard Arduino Uno SPI pins), plus BH1750 on I2C (A4/A5) as in
  ../03_light_sensor_BH1750.
*/

#include <SPI.h>
#include <SD.h>
#include <BH1750.h>
#include <Wire.h>

File data;
BH1750 lightMeter;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();
  lightMeter.begin();

  Serial.println("SD card initializing...");
  if (!SD.begin(10)){
   Serial.println("initialization  failed.");
   while (1);
 }
  Serial.println("initialization done");

  data = SD.open("data.txt",FILE_WRITE);

  if(data){
    Serial.println("File opened");
    data.println("Light intensity");
  }
data.close();
}

void loop() {
  // put your main code here, to run repeatedly:
  float lux = lightMeter.readLightLevel();
  data = SD.open("data.txt",FILE_WRITE);

  if(data){
    data.print(lux);
    data.println();
    data.close();
  }else{
    Serial.println("Cannot open file");
  }
}
