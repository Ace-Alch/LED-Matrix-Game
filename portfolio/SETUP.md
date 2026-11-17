# Bare-Metal LED Matrix Game: setup

## Current entry point

1. Read the source map in `src/`.
2. Import the C and ARM assembly files into an Xilinx SDK project for the matching PYNQ-Z1 hardware platform.
3. Resolve the BSP, timer and GPIO addresses against that platform.
4. Check the matrix wiring and power supply before loading the program.
5. Confirm timer interrupts, display refresh, controls and scoring on the board.

The SDK release and hardware export must be supplied before this becomes a fully reproducible build.

## Required records

- Hardware platform export
- Matrix wiring and supply
- SDK release
- Reproduced board test

## Reproducibility record

Record the source commit, operating system, tool versions, dependencies, input files, configuration and command. Store the output separately from the expected result. Mark any manual step.
