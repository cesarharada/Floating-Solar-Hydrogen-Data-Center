# Testing & Results

Four rounds of testing were carried out between **7 August and 13 August
2024** as the prototype moved from bench electronics to a fully floating
device, culminating in a field test in the water at **31 Nassim Road,
Singapore, on 13 August 2024, 10:00–13:00**, as part of the residency
*"Cesar Jung-Harada: An Ocean City Imagined"* at the ArtScience Museum.

Raw measurements for every round are in [`testing/data/`](testing/data/) as CSV files.

## What was measured

- Hydrogen produced (mL / hour)
- Oxygen produced (mL / hour)
- Voltage into the electrolyser (V)
- Solar illuminance (lux)
- (Bonus, not consistently captured: pipe pressure, precise amperage)

## 1. Lab testing

*Only one electrolyser used. Only hydrogen quantity recorded. Powered
from lab mains electricity — no solar panels.*

**Method:** hydrogen was trapped in a plastic bottle submerged in water,
marked at 100 mL intervals; the time to fill each 100 mL increment was
recorded, then cross-checked against a fixed 10-minute interval read.

- [`data/lab-test_hydrogen-per-100ml.csv`](testing/data/lab-test_hydrogen-per-100ml.csv) — 32 readings, **average ≈ 463 mL / 10 min**
- [`data/lab-test_hydrogen-per-10min.csv`](testing/data/lab-test_hydrogen-per-10min.csv) — 7 readings, **average ≈ 476 mL / 10 min**

## 2. Land testing

*Full prototype used on land. 2 electrolysers and solar panels used.*

**Method:** hydrogen and oxygen trapped in marked plastic bottles;
readings taken every 10 minutes alongside solar illuminance and voltage.

[`data/land-test_results.csv`](testing/data/land-test_results.csv) —
average **337.5 mL H₂ / 10 min (2025 mL/h)**, electrolyser voltage steady
at **3.66 V**, solar voltage **~11.55 V**, illuminance **~5400 lux**.

## 3. Water testing

*Full prototype, floating. 2 electrolysers and solar panels used.*
Video: see [`media/`](media/) and the project's
[Google Photos album](https://photos.app.goo.gl/MF1NY26gttw1StrU9).

**Method:** as above, plus oxygen readings; for the last two runs, time
to produce a fixed 800 mL of hydrogen was timed instead of a fixed
interval.

[`data/water-test_results.csv`](testing/data/water-test_results.csv) — average
**2873 mL H₂/h**, average **3373 mL O₂/h**, electrolyser voltage steady
at **3.63 V**, solar voltage **~11.6–11.7 V**.

## 4. FiSH DataLogger prototype testing

*2 electrolysers used. Only hydrogen quantity recorded. Powered indoors
from a sealed lead-acid battery through the solar charge controller;
panels connected but not directly generating. The FiSH DataLogger board
([`firmware/`](firmware/)) recorded voltage and current
automatically for the first time in this round.*

- [`data/fish-prototype-test_first-experiment.csv`](testing/data/fish-prototype-test_first-experiment.csv)
- [`data/fish-prototype-test_second-experiment.csv`](testing/data/fish-prototype-test_second-experiment.csv)
- Video recordings: `media/fish-prototype-test-video-1.mov`, `media/fish-prototype-test-video-2.mov`

**Summary:** an average hydrogen production rate of 26.8 s per 100 mL
across 2 electrolysers, compared with the manufacturer spec of
100 mL/min per electrolyser, works out to **≈110% of rated output** —
within the error margin of the manual bottle-and-stopwatch measurement
method.

## Cross-check: oxygen vs. hydrogen, and the leakage estimate

Oxygen (O₂) is a larger molecule than hydrogen (H₂), so it leaks far less
readily from PVC/silicone tubing and fittings. That makes measured O₂
output a more trustworthy proxy for *actual* electrolysis rate than
measured H₂ output:

- Measured average O₂ production rate (with losses): **3373 mL/h**
- Ideal H₂ production rate implied by that O₂ rate (2:1 stoichiometry): **6746 mL/h**
- Measured average H₂ production rate (with losses): **2873 mL/h**
- Captured hydrogen fraction: 2873 / 6746 ≈ **42%**
- **Estimated hydrogen leakage: ~58%** — see [`FUTURE_WORK.md`](FUTURE_WORK.md) for the tubing/fitting fix this points to

## What worked

1. The device is easy to transport with a trolley.
2. Battery voltage level was quite consistent.
3. The device floats as-is.
4. Because O₂ leaks much less than H₂, measured oxygen output can be used as a cross-check on true hydrogen production.

## What didn't work

1. Gas-measurement technique (manual bottle + stopwatch) was imprecise; digitising this is a priority for the next prototype.
2. Hydrogen leakage of ~58%, attributed mainly to PVC/silicone tubing and fittings — see [`FUTURE_WORK.md`](FUTURE_WORK.md).
3. On cloudy days, solar output was sometimes insufficient to fully power the electrolysers.
4. The device floats but is not well balanced — water constantly collects inside the enclosure.
5. The hatch cannot be safely opened while the device is on the water: it is too heavy and unbalances the whole unit. This may be less of an issue with several modules linked together and a separate maintenance buoy.

## Discussion

Despite its high energy density and abundance, hydrogen still has real
limitations: the energy cost of electrolysis, and its tendency to leak
through materials that hold liquids just fine. Floating hydrogen solar
cells remain a promising direction, but this prototype shows there is
real engineering work left before the concept is deployment-ready.

Scaled naively, the demonstrated ~6746 mL/h ideal hydrogen production
rate (≈5.65 × 10⁻⁴ kg/h) corresponds to roughly 140.6 Wh at 100%
round-trip efficiency (0.04 kg H₂ ≈ 1 kWh). Compared with per-capita
electricity consumption in Indonesia (order of 1 MWh/year), that would
take on the order of 7000+ hours of continuous operation to cover one
month of energy use for a family of four at this scale — and the current
prototype ran its electrolysers at only 1.5 V each, well below an
efficient operating point. That gap is the honest headline result: this
kit demonstrates the *principle* end-to-end (solar → electrolysis →
storage → measurement), not yet a deployable power source, and scaling
this concept up is exactly what the "10 kW Kit" and larger reference
designs elsewhere in this repository are for.

The case for floating hydrogen solar cells remains strong on cost and
decentralisation grounds — locally producible, no rare-earth or
critical-mineral dependence beyond a small amount of catalyst platinum —
but leakage, storage, and low-light performance all need further
iteration, which is exactly what [`FUTURE_WORK.md`](FUTURE_WORK.md)
lays out.
