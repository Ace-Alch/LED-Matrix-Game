# Bare-Metal LED Matrix Game: validation

## Current evidence

This documentation update inspected available text and file inventories. It did not execute the project, simulate a model or test hardware. Existing recorded results must be cited with their original conditions.

## Proposed checks

These are test plans. No row below is marked as passed.

| Check | Action | Evidence to retain | Status |
| :-- | :-- | :-- | :-- |
| V01: Buttons and GPIO | Inspect the relevant artifact and run one normal case plus one boundary case. | Source revision, inputs, expected result, observed result and log or image. | Not run |
| V02: Interrupts and timers | Inspect the relevant artifact and run one normal case plus one boundary case. | Source revision, inputs, expected result, observed result and log or image. | Not run |
| V03: Game state | Inspect the relevant artifact and run one normal case plus one boundary case. | Source revision, inputs, expected result, observed result and log or image. | Not run |
| V04: RGB matrix driver | Inspect the relevant artifact and run one normal case plus one boundary case. | Source revision, inputs, expected result, observed result and log or image. | Not run |
| V05: Score | Inspect the relevant artifact and run one normal case plus one boundary case. | Source revision, inputs, expected result, observed result and log or image. | Not run |

## Project-specific checks

- Verify or recover: Hardware platform export.
- Verify or recover: Matrix wiring and supply.
- Verify or recover: SDK release.
- Verify or recover: Reproduced board test.

## Reporting rule

Report units, sample size, configuration, error bounds and failures. Separate a simulation result from a hardware result. Separate an emulator check from a physical-device check. A screenshot alone does not establish numerical accuracy.
