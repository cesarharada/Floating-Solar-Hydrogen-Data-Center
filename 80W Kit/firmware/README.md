# Firmware — FiSH DataLogger

Arduino sketches for the FiSH (Floating Solar Hydrogen) DataLogger, an
Arduino Uno-based board that measures solar and electrolyser
current/voltage, ambient light, and water temperature, then logs the
averaged readings to a microSD card every two minutes.

Each subsystem was first tested in isolation (sketches `01`–`05`) before
being combined into the integrated logger (`FiSH_DataLogger_main`), which
is what actually ran on the prototype. This progression is kept here so
future builders can bring up and debug one sensor at a time rather than
the whole board at once — standard practice for a first electronics bring-up.

## Sketches

| Folder | Purpose |
| --- | --- |
| `01_current_sensor_ACS712/` | Standalone test of the ACS712 Hall-effect current sensor |
| `02_voltage_sensor/` | Standalone test of the resistive voltage-divider sensor (0–25 V) |
| `03_light_sensor_BH1750/` | Standalone test of the BH1750 digital ambient-light sensor (I2C) |
| `04_waterproof_thermometer_DS18B20/` | Standalone test of the DS18B20 1-Wire waterproof temperature probe |
| `05_sd_card_test/` | Standalone test that the microSD module can open/write/close a log file |
| `FiSH_DataLogger_main/` | **The integrated sketch that ran on the prototype** — all sensors + 2-minute averaging + SD logging + status LEDs |

Each folder is a self-contained Arduino sketch (folder name == `.ino`
filename) so it opens directly in the Arduino IDE.

## Hardware target

- Board: Arduino Uno (ATmega328, 16 MHz) — see [`../bom/BOM.md`](../bom/BOM.md)
- Custom shield: "FiSH-GenShield" — see [`../hardware/pcb/`](../hardware/pcb/) for Gerbers

## Required libraries

Install via the Arduino Library Manager (Sketch → Include Library → Manage Libraries):

- `BH1750` (by Christopher Laws) — I2C ambient light sensor
- `OneWire` (by Jim Studt et al.) — 1-Wire bus driver
- `DallasTemperature` (by Miles Burton) — DS18B20 temperature driver
- `SD` and `SPI` — bundled with the Arduino IDE

## Pin map (FiSH DataLogger main sketch)

| Pin | Function |
| --- | --- |
| A0 | Solar-side current sensor (ACS712) |
| A1 | Electrolyser-side current sensor (ACS712) |
| A2 | Solar-side voltage sensor (0–25 V divider) |
| A3 | Electrolyser-side voltage sensor (0–25 V divider) |
| A4 / A5 | I2C bus (SDA/SCL) — BH1750 light sensor |
| D7 | Status LED A (red) — on at boot, off once the CSV header is written |
| D8 | DS18B20 waterproof thermometer (1-Wire, needs a 4.7 kΩ pull-up to 5 V) |
| D9 | Status LED B (blue) — on while measuring, off once each SD write completes |
| D10 + SPI (11/12/13) | microSD card module (chip-select on D10) |

## Output format

`FiSH_DataLogger_main` writes one CSV row to `data.txt` on the SD card
every 2 minutes (values are the average of ~120 one-second samples):

```
Solar Current,Electrolyser Current,Solar Voltage,Electrolyser Voltage,Light intensity,Temperature
```

Currents below 0.15 A are treated as noise and logged as `0` (see the
`abs(avgcurrentS) > 0.15` checks in the code) — tune this threshold if you
find it clips real low-current readings on your build.

## Known limitations (see [`../FUTURE_WORK.md`](../FUTURE_WORK.md))

- The ACS712 offset (`QOV`) and voltage-divider scale factor (`40.92`)
  were calibrated for the specific modules used in this prototype;
  recalibrate against a multimeter if you swap sensor modules.
- No wireless telemetry — data must be retrieved by pulling the SD card.
  Doruk's handover notes flag an ESP32 + FTDI upgrade path for a future
  revision.
