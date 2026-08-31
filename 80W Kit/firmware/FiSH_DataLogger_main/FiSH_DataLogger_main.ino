/*
  FiSH Floating Solar Hydrogen Prototype — 80W Kit
  FiSH DataLogger — integrated sensor suite

  Written by Li Congxiao, 02/09/2024.
  Part of the Floating Solar Hydrogen Data Center open-hardware project.

  Reads solar current/voltage, electrolyser current/voltage, ambient
  light (BH1750) and water temperature (DS18B20) every second, averages
  the readings over a 2-minute window, prints the averages to Serial and
  appends a CSV row to data.txt on the microSD card. Two status LEDs
  (LEDA = red, LEDB = blue) indicate boot/header-write and SD-write
  status respectively.

  CSV columns written to data.txt:
  Solar Current,Electrolyser Current,Solar Voltage,Electrolyser Voltage,Light intensity,Temperature

  Required libraries: SD, SPI (bundled with Arduino IDE), BH1750, Wire
  (bundled), OneWire, DallasTemperature.

  Wiring:
    A0 - Solar current sensor (ACS712) output
    A1 - Electrolyser current sensor (ACS712) output
    A2 - Solar voltage sensor output
    A3 - Electrolyser voltage sensor output
    A4/A5 (I2C) - BH1750 light sensor
    Pin 8 - DS18B20 waterproof thermometer (1-Wire, 4.7k pull-up to 5V)
    Pin 7 - Status LED A (red)
    Pin 9 - Status LED B (blue)
    Pin 10 (CS) + SPI - microSD card module
*/

#include <SPI.h>
#include <SD.h>
#include <BH1750.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8
const int LEDA = 7; //red status LED
const int LEDB = 9; //blue status LED

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
BH1750 lightMeter;
File data;

void setup() {
  Serial.begin(9600);  // Start Serial Monitor to display current read value

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use
  // Wire.begin(D2, D1);

  lightMeter.begin();
  sensors.begin();
  pinMode(LEDA, OUTPUT);
  pinMode(LEDB, OUTPUT);
  //LED light up once the power on
  digitalWrite(LEDA, HIGH);
  digitalWrite(LEDB, HIGH);
  delay(2000);

  //Initializing SD card
  Serial.println("SD card initializing...");
  if (!SD.begin(10)){
   Serial.println("initialization  failed.");
   while (1);
 }
  Serial.println("initialization done");

 data = SD.open("data.txt",FILE_WRITE);

  if(data){
    Serial.println("File opened");
    data.println("Solar Current,Electrolyser Current,Solar Voltage,Electrolyser Voltage,Light intensity,Temperature");
  }
  Serial.println("Data header written");
  data.close();
  //red LED off when the header is written
  digitalWrite(LEDA, LOW);
  delay(2000);

}

void loop() {
  digitalWrite(LEDA, HIGH);
  digitalWrite(LEDB, HIGH);
  const unsigned long interval = 120000;  // 2 minutes in milliseconds
  unsigned long previousMillis = millis();  // Store the last time interval was checked

  const int maxReadings = 120;  // Maximum number of readings (assuming one reading per second)
  int tempReadingIndex = 0;  // Index for storing temperature readings
  float totalcurrentS = 0.0, totalcurrentE = 0.0, totalSvolt = 0.0, totalEvolt = 0.0, totallux = 0.0, totalTemp = 0.0; // To accumulate the total readings
  unsigned int readingCount = 0;  // To count the number of readings

  while (millis() - previousMillis < interval) {
    //Current sensor
    const float QOV = 0.5* 5;
    float voltage_rawS = (5.0 / 1023.0)*analogRead(A0);
    float voltageS = voltage_rawS - QOV + 0.012;
    float currentS = voltageS / 0.066;

    float voltage_rawE = (5.0 / 1023.0)*analogRead(A1);
    float voltageE = voltage_rawE - QOV + 0.012;
    float currentE = voltageE / 0.066;

    //Read volt sensor values
    int Svolt;
    float Stemp;
    Svolt=analogRead(A2);//This divider module will divide the measured voltage by 5, the maximum voltage it can measure is 25V.
    Stemp=Svolt/40.92; //
    Svolt=(int)Stemp;//
    int Evolt;
    float Etemp;
    Evolt=analogRead(A3);
    Etemp=Evolt/40.92; //
    Evolt=(int)Etemp;//

    //Read light sensor values
    float lux = lightMeter.readLightLevel();

    // Read temperature
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);

    // Accumulate the total values over 2 minutes
    totalcurrentS += currentS;
    totalcurrentE += currentE;
    totalSvolt += Svolt;
    totalEvolt += Evolt;
    totallux += lux;
    totalTemp += tempC;

    readingCount++;  // Increment the reading count

    delay(1000);  // Delay 1 second before the next reading
  }

  // After 2 minutes, calculate the average current
  float avgcurrentS = totalcurrentS / readingCount;
  float avgcurrentE = totalcurrentE / readingCount;
  float avgSvolt = totalSvolt / readingCount;
  float avgEvolt = totalEvolt / readingCount;
  float avglux = totallux / readingCount;
  float avgTemp = totalTemp / readingCount;

  // Print the average values on the Serial Monitor
  if (abs(avgcurrentS) > 0.15, abs(avgcurrentE) > 0.15){
    Serial.print("Average Current Solar (over 2 mins)");
    Serial.print(avgcurrentS);
    Serial.println("A");
    Serial.print("Average Current Electrolyser (over 2 mins)");
    Serial.print(avgcurrentE);
    Serial.println("A");
  }else{
    Serial.println("No current");
  }

  Serial.print("Average Voltage Solar (over 2 mins): ");
  Serial.print(avgSvolt);
  Serial.println(" V");
  Serial.print("Average Voltage Electrolyser (over 2 mins): ");
  Serial.print(avgEvolt);
  Serial.println(" V");

  Serial.print("Average light intensity (over 2 mins):");
  Serial.print(avglux);
  Serial.println (" lx");
 
  Serial.print("Average Temperature (over 2 mins): ");
  Serial.print(avgTemp);
  Serial.println(" C");
  Serial.println();

 //store data into SD card
 data = SD.open("data.txt",FILE_WRITE);

  if(data){
    
    Serial.println("writing data...");
    if (abs(avgcurrentS) > 0.15){
       data.print(avgcurrentS);
       data.print(",");
       
    }else{
       data.print("0");
       data.print(",");
    }
    if (abs(avgcurrentE) > 0.15){
      
       data.print(avgcurrentE);
       data.print(","); 
    }else{
       data.print("0");
       data.print(",");
    }
  data.print(avgSvolt);
  data.print(",");
  data.print(avgEvolt);
  data.print(",");

  data.print(avglux);
  data.print(",");

  data.print(avgTemp);
  data.print(",");

  data.println();
  }
  digitalWrite(LEDB, LOW); // blue LED off when data is written on SD card
  delay(2000);
  Serial.println("data complete");
  data.close();
  // Delay before starting the next 2-minute interval
  delay(1000);

}
