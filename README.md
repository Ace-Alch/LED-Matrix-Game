#  Bare-Metal LED Matrix Game on PYNQ-Z1 (ARM Cortex-A9)

A fully bare-metal RGB LED matrix game implemented on the **Digilent PYNQ-Z1** board using **C and Assembly**. No operating system. No PYNQ overlays. Just raw ARM Cortex-A9 power.

>  Demo:
> ![LED Matrix Game](media/demo.gif)

---

##  About the Project

- Written entirely in **C & ARM Assembly**
- Custom **interrupts**, **timers**, and **GPIO control**
- Built on **Xilinx SDK**, targeted at **Zynq-7000** SoC
- Includes:
  - Dual TTC timers (800Hz + 10Hz)
  - Custom RGB LED matrix driver
  - Game: Spaceship, bullets, alien, score tracking

---

##  What's Inside

All code is in `src/`:
- `main.c` – game logic, interrupt handlers
- `Pixel.c/h` – LED matrix driver (bit-banging)
- `Interrupt_setup.c/h` – GPIO and timer interrupt config
- `blinker.S` – LED sequence in Assembly
- `platform.*` – init UART, caches, and exit
- `lscript.ld` – custom linker script

---

##  Optional: Full Demo

If provided, watch full gameplay here: [`media/demo.mp4`](media/demo.mp4)

---

##  License

MIT License — feel free to adapt, reuse, or study this for your own projects.
