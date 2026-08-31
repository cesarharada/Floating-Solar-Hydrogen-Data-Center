# Known Issues & Future Work

This prototype (informally "FSH002" in the original project notes) was
the second in a series. This section preserves the handover notes left
for the next builders — issues found, fixes already identified, and the
roadmap that was sketched for FSH003 through FSH006 — so this knowledge
isn't lost between prototype generations. Source: internal project
handover notes, August 2024.

## Priority fixes

### 1. Hydrogen leakage (~58%)

The single biggest gap between theoretical and measured hydrogen output
(see [`TESTING.md`](TESTING.md)). PVC and silicone tubing (5 mm/10 mm)
are both highly permeable to hydrogen.

- **Immediately available improvement:** switch to polyethylene (PE)
  tubing, which has substantially lower H₂ permeability. See:
  - [Gas Permeability — Silex Ltd](https://www.silex.co.uk/technical-faq/gas-permeability/)
  - [PPXIX: Modern PE pipe and hydrogen transport (Kiwa Technology)](https://www.kiwa.com/4acac6/globalassets/netherlands/kiwa-technology/downloads/ppxix-modern-pe-pipe-enables-the-transport-of-hydrogen-rene-hermkens-and-others-vs20180710.pdf)
- **For future experimental setups:** PFA tubing has permeability
  comparable to oxygen's and is well characterised for hydrogen service —
  see [Swagelok PFA flexible tubing](https://products.swagelok.com/en/all-products/hoses-flexible-tubing/flexible-tubing/pfa-flexible-tubing/pfa-flexible-tubing/p/hose-0005).
- **Fittings** in this prototype were a major leak source; replace with
  gas-rated fittings and joints — see
  [Swagelok: Hydrogen fitting anatomy](https://www.swagelok.com/en/blog/anatomy-of-hydrogen-fitting).

### 2. Balance and buoyancy

The device floats but is not well balanced, and constantly collects
water inside the enclosure. Opening the hatch while afloat is dangerous —
it is heavy enough to unbalance and potentially capsize the unit.

- Move electronics compartments toward the geometric centre of the
  enclosure (near the weight centre), or add counterweights on the
  opposite side.
- Consider sliding hatches on both sides so opening one does not shift
  the mass centre.
- Adding buoyancy pontoons at the base is expected to make balance much
  less sensitive, and would let a steel frame be mounted directly on
  the pontoons for a future revision.
- For a single module this is a real risk; for a poly-module system
  (several floats linked together, possibly with a dedicated maintenance
  buoy) it is expected to be far less of a problem.

### 3. Power delivery / voltage drop

The step-down converter used here could not comfortably supply the ~14 A
drawn by the two electrolysers in series, causing a voltage drop and
running its diodes up to ~100°C (see the photo in
[`BUILD_GUIDE.md`](BUILD_GUIDE.md#reference-photos)).

- A custom step-down/step-up module, sized for the real current draw
  and with proper heatsinking, is recommended for the next revision.
- Panels can be upgraded to monocrystalline for higher W/m² — aim for
  roughly 10% more supply capacity than the electrolysers require, and
  tune from there once real-world data is in.

### 4. Gas-flow measurement

Manual "time to fill a marked bottle" measurement (used throughout
[`TESTING.md`](TESTING.md)) is imprecise and labour-intensive.

- A dedicated mass air-flow sensor (e.g. DFRobot F1031V) on the hydrogen
  and/or oxygen lines would give a continuous, automatic flow reading and
  let gas losses be attributed to a specific point in the plumbing rather
  than inferred from an O₂/H₂ ratio.

### 5. Telemetry

The current FiSH DataLogger ([`firmware/`](firmware/)) only logs to a
local SD card — data has to be retrieved by hand.

- An ESP32 (with an FTDI adapter for development) was identified as a
  path to wireless telemetry, letting the logger publish data live
  instead of requiring a physical SD-card pull.
- A low-resolution camera was also proposed, to visually flag
  environmental or human interference with the panels (e.g. birds
  perching and shading cells).

## Prototype roadmap (as sketched after FSH002)

This was the forward plan sketched at the time; later prototypes in this
repository's [top-level history](../README.md) may already have
superseded parts of it — check there first.

| Codename | Focus | Environment |
| --- | --- | --- |
| **FSH003** | Starting efficiency, hydrogen production rate, and balance, with the tubing/step-down/measurement fixes above applied | Pool |
| **FSH004** | Long-term resilience: overheating, efficiency losses over time, buoy/pontoon-based balance | Ocean |
| **FSH005** | Pipe leakage and hydrogen-capture rate, with hydrogen-rated fittings sourced from trusted suppliers | Lab |
| **FSH006** | Scaled-up power stage: ~150 W solar (mono-facial or bifacial monocrystalline) feeding a ~100 W electrolyser system | — |

Two other ideas worth preserving:

- **Seawater/ocean cooling for electronics:** the ocean offers a stable,
  mildly cool heatsink for the PV and step-down electronics, potentially
  far more efficient than air-cooled heatsinks — see this
  [ScienceDirect article on ocean-based cooling](https://www.sciencedirect.com/science/article/pii/S2590174523000648)
  for a starting reference.
- **Grid-tied electrolyser-as-battery mode:** if connected to village
  power, the charge controller could be adapted to treat the
  electrolysers as a dispatchable "battery" — most efficient where
  hydrogen (for cooking, lighting, etc.) is genuinely the preferred
  end-use, which should be validated locally before building it in.

## See also

- [`README.md`](README.md) — project overview and credits
- [`TESTING.md`](TESTING.md) — measured results this future work responds to
- [`../README.md`](../README.md) — the wider Floating Solar Hydrogen Data Center project, including later/larger reference designs
