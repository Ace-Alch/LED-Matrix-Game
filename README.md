<h1 align="center">LED MATRIX ARCADE</h1>
<p align="center"><b>A spaceship game on a PYNQ-Z1, driven by timer and button interrupts.</b></p>

<p align="center"><img src="media/demo.gif" alt="Recording of the original RGB LED matrix game running on the board" width="640"></p>

<p align="center"><a href="media/demo.mp4"><b>Watch the full hardware recording</b></a> &nbsp; | &nbsp; <a href="src/main.c"><b>Read the game code</b></a></p>

## The arcade controls

| Input | Action |
| :-- | :-- |
| BTN0 | Move right |
| BTN1 | Fire one shot |
| BTN2 | Move left |
| BTN3 | Restart |

A red alien traverses the top of the playfield. A blue shot moves up from the white ship. Green LEDs mark hits. A yellow check mark appears after the fourth hit.

## Inside one game tick

| Event | What runs |
| :-- | :-- |
| **800 Hz timer** | Updates the two ship rows. |
| **10 Hz game timer** | Advances the shot, checks collisions, and advances the alien every third tick at the default setting. |
| **GPIO interrupt** | Reads the button event and updates the ship or game state. |

Start with the [interrupt handlers and game state](src/main.c). Follow `SetPixel` into the [matrix driver](src/Pixel.c), or inspect the [TTC and GPIO setup](src/Interrupt_setup.c) and [ARM assembly startup LED routine](src/blinker.S).

## Reproduce the game checks

```sh
python tools/check_game.py
```

The host test executes the original game handlers with mock GPIO and display functions. It checks movement limits, the single-shot rule, four hits, and restart. The hardware video shows the physical panel. Rebuilding the target firmware requires the PYNQ-Z1 hardware platform and the matching Xilinx BSP. See the [setup notes](portfolio/SETUP.md).

[Hardware evidence](portfolio/EVIDENCE.md) · [Source inventory](portfolio/SOURCE-INVENTORY.md) · [MIT License](LICENSE)
