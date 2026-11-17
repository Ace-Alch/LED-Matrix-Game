<div align="center">
<img src="https://raw.githubusercontent.com/Ace-Alch/Ace-Alch.github.io/main/banners/LED-Matrix-Game.webp" width="100%" alt="LED-Matrix-Game — project concept artwork">

# Bare-Metal LED Matrix Game

**Run a spaceship game on PYNQ-Z1 with C, ARM assembly and a custom display driver.**

PYNQ-Z1 · ARM Cortex-A9 · C · ARM assembly · Xilinx SDK

[Project record](#bench-card) · [Design](portfolio/DESIGN.md) · [Setup](portfolio/SETUP.md) · [Validation](portfolio/VALIDATION.md) · [Evidence](portfolio/EVIDENCE.md)
</div>

<!-- project-navigation:start -->
<p align="center">
  <a href="https://ace-alch.github.io/work/LED-Matrix-Game/"><img alt="View project" src="https://img.shields.io/badge/View%20project-58a6ff?style=for-the-badge&logo=githubpages&logoColor=white"></a>
  <a href="portfolio/DESIGN.md"><img alt="Explore design" src="https://img.shields.io/badge/Explore%20design-30363d?style=for-the-badge&logo=readthedocs&logoColor=white"></a>
  <a href="portfolio/SETUP.md"><img alt="Setup guide" src="https://img.shields.io/badge/Setup%20guide-30363d?style=for-the-badge&logo=github&logoColor=white"></a>
  <a href="portfolio/EVIDENCE.md"><img alt="Check evidence" src="https://img.shields.io/badge/Check%20evidence-30363d?style=for-the-badge&logo=readthedocs&logoColor=white"></a>
</p>
<p align="center"><strong>Implemented game</strong> &nbsp; / &nbsp; Engineering &nbsp; / &nbsp; <a href="https://ace-alch.github.io/">Mehdi's portfolio</a></p>
<!-- project-navigation:end -->


## Bench card

| Item | Record |
| :-- | :-- |
| Project type | Implemented game |
| Field | Engineering |
| Material in this package | Existing repository inspected |
| Documentation review | 17 November 2026 |

## The build

Run a spaceship game on PYNQ-Z1 with C, ARM assembly and a custom display driver. The documentation separates the stated project scope, inspected artifacts and future work. A listed feature is not a new test result.

### Subsystems

- Buttons and GPIO
- Interrupts and timers
- Game state
- RGB matrix driver
- Score

## Open the bench notes

1. Read the [design record](portfolio/DESIGN.md) for the system elements and boundaries.
2. Follow the [setup record](portfolio/SETUP.md) for available entry points.
3. Use the [validation plan](portfolio/VALIDATION.md) to record reproducible results.
4. Check the [evidence register](portfolio/EVIDENCE.md) before reusing claims.

## Project preview

![Project artifact](media/demo.gif)

This image is an existing repository artifact. It is not evidence of a new test.

<details>
<summary><strong>Browse source files and project artifacts</strong></summary>

| Path | Type |
| :-- | :-- |
| [LICENSE](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/LICENSE) | file |
| [README.md](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/README.md) | .md |
| [media/demo.gif](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/media/demo.gif) | .gif |
| [media/demo.mp4](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/media/demo.mp4) | .mp4 |
| [src/Interrupt_setup.c](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/src/Interrupt_setup.c) | .c |
| [src/Interrupt_setup.h](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/src/Interrupt_setup.h) | .h |
| [src/Pixel.c](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/src/Pixel.c) | .c |
| [src/Pixel.h](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/src/Pixel.h) | .h |
| [src/Xilinx.spec](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/src/Xilinx.spec) | .spec |
| [src/blinker.S](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/src/blinker.S) | .S |
| [src/lscript.ld](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/src/lscript.ld) | .ld |
| [src/main.c](https://github.com/Ace-Alch/LED-Matrix-Game/blob/main/src/main.c) | .c |

See the [complete source inventory](portfolio/SOURCE-INVENTORY.md) for all inspected file paths.

</details>

## Verification backlog

- [ ] Hardware platform export
- [ ] Matrix wiring and supply
- [ ] SDK release
- [ ] Reproduced board test

## Credits and reuse

Project record: Mehdi Moallemkolaei. Specific third-party and course contributions must retain their original notices.

Existing license terms remain in effect. This package does not grant a new license over source code, course material, models or datasets. See [reuse and contribution notes](portfolio/CONTRIBUTIONS.md).


---

![Project design system](portfolio-assets/section.svg)

[Visual design notes](portfolio/VISUAL-DESIGN.md) · [Design tokens](portfolio/design-tokens.json)
