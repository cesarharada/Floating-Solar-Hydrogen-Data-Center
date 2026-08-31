# Bill of Materials — FiSH 80W Kit

Two sub-assemblies: the **structural / power / hydrogen** system (frame,
solar panels, electrolysers, plumbing) and the **FiSH DataLogger**
electronics (Arduino Uno + sensor shield). Raw distributor export CSVs
(Octopart) for the DataLogger are kept in [`raw-export/`](raw-export/)
for traceability; the tables below are the cleaned-up, human-readable
versions.

> **Note on units:** the original build notes mix imperial and metric
> measurements for the steel frame (see [`../BUILD_GUIDE.md`](../BUILD_GUIDE.md)
> for both versions as recorded). Verify actual lengths against your own
> frame design before cutting steel.

## 1. Structure, solar, and electrolysis

| Qty | Item | Notes |
| ---: | --- | --- |
| 73,000 mm total | Slotted steel angle bar, 1.5" × 1.5" × 1/16" | Cut list: 7× 44", 10× 32", 4× 14", 2× 4" (imperial, per parts list) — cross-check against the metric cut list in the build guide (8× 810 mm, 6× 1120 mm, 2× 100 mm) before cutting |
| 64 | M6 square-neck carriage bolts, 12 mm, zinc yellow-chromate-plated steel | Wet-environment rated |
| 64 | M6 hex nuts, zinc yellow-chromate-plated steel | Wet-environment rated |
| 2 | Clear acrylic sheet, 3 mm, 312 × 812 mm | |
| 2 | Clear acrylic sheet, 3 mm, 312 × 1112 mm | |
| 3 | Steel mortise hinges, 3" | Welded to join the vertical (triangle) and base frames |
| 1 | Extruded polystyrene foam board, 815 × 1115 × 55 mm | Floatation core |
| — | Paper, < 80 gsm | Fibreglass-style skin over the foam |
| — | PVA glue, 1:1 mix with water | Paper adhesive |
| — | Polyester resin + hardener, 3% mix | Foam board waterproofing |
| — | NS90 polyurethane gun foam | Seam filling |
| 2 | Heavy-duty cargo tension belts, 5 m | Secures foam float to steel frame |
| 2 | Polycrystalline solar panels, 40 W each | **80 W total array** — the number this kit is named for |
| 1 | PP box, 45 L, with lid (e.g. IKEA SAMLA) | Outer waterproof enclosure |
| 3 | PP box, 5 L, with lid (e.g. IKEA SAMLA) | Electronics box, electrolyser box, water-tank box |
| 2 | PEM electrolysers, 14 A / 3.5 V, ~100 mL H₂/min each | |
| 1 | Air–gas separator | Keeps liquid water out of the hydrogen line |
| 1 | Water filter | Protects electrolysers from particulates |
| 1 | Water pump (USB-powered) | Circulates deionised water |
| 1 | Solar charge controller | |
| 1 | 12 V battery (sealed lead-acid used in bench tests) | |
| 1 | Step-down converter, 12 V → ~7 V | Output tuned to 7 V / 14 A for the two electrolysers in series |
| 2 | Voltmeters (panel-mount) | Solar and electrolyser sides |
| 1 | On/off switch | |
| — | Deionised water | Electrolyte feed |
| — | 6 mm and 8 mm tubing | See [`../FUTURE_WORK.md`](../FUTURE_WORK.md) — PVC/silicone tubing used in this prototype leaked ~58% of the hydrogen produced; polyethylene (PE) tubing is recommended for a rebuild |
| — | Tube anti-leak connectors, 7 mm / 9 mm / 14 mm | |

## 2. FiSH DataLogger electronics

Sourced via an Octopart BOM tool export; total indicative cost **~SGD 68.53**
at batch size 1 (see [`raw-export/octopart-export-datalogger.csv`](raw-export/octopart-export-datalogger.csv)).

| Qty | Part / MPN | Manufacturer | Description | Unit price (indicative) |
| ---: | --- | --- | --- | ---: |
| 1 | A000066 | Arduino | Uno board, ATmega328, 16 MHz, 2 KB RAM, 1 KB/32 KB EEPROM/Flash | ~US$25.81 |
| 2 | VMA323 | Velleman | ACS712 20 A current-sensor module | — |
| 2 | 101991032 | Seeed Studio | Grove AC/DC voltage sensor (MCP6002) | ~US$3.54 |
| 1 | SEN0097 | DFRobot | Analog light-intensity sensor breakout | ~US$4.50 — evaluated as an alternative to the BH1750; **the deployed firmware uses the I2C BH1750**, see [`../firmware/`](../firmware/) |
| 1 | DFR0198 | DFRobot | Waterproof DS18B20 digital temperature sensor | ~US$6.90 |
| 1 | 410-380 | Digilent | Pmod microSD card slot | ~US$7.55 |
| 1 | 151051BS04000 | Würth Elektronik | Blue LED, T-1¾, 4.9 mm | ~US$0.26 |
| 1 | SSL-LX3052ID | Lumex | Red LED, 627 nm, T1 (3 mm) | ~US$0.41 |
| 1 | MFR50SJT-52-1K2 | Yageo | Metal-film resistor, 1.2 kΩ, ½ W, 5% | ~US$0.10 |

Additional sensors referenced in design notes but not in the final
distributor export (sourced locally in Singapore, see
[`../FUTURE_WORK.md`](../FUTURE_WORK.md)):

| Item | Purpose |
| --- | --- |
| BH1750FVI digital ambient light sensor (I2C) | Solar illuminance — this is the light sensor actually used in firmware |
| F1031V mass air-flow sensor (DFRobot) | Proposed for direct hydrogen/oxygen flow measurement in a future revision |
| ESP32 + FTDI USB-serial adapter | Proposed for wireless telemetry in a future revision |
| 30 A / 12 V relay module | Proposed remote/kill-switch |

## Sources

- [`raw-export/octopart-export-datalogger.csv`](raw-export/octopart-export-datalogger.csv) — Octopart BOM tool export, DataLogger parts only
- [`raw-export/octopart-export-generator-full.csv`](raw-export/octopart-export-generator-full.csv) — Octopart BOM tool export, full generator parts list
- Original Octopart project: https://octopart.com/bom-tool/nmw67ERl/mSImbz9xk7tV0ekL
