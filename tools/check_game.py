"""Exercise the original LED Matrix Game handlers with host-side driver stubs."""

import argparse
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
DRIVERS = """
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint32_t u32;
typedef struct { int unused; } XTtcPs;
static uint8_t display[8][9][3];
static void SetPixel(unsigned x, unsigned y, uint8_t r, uint8_t g, uint8_t b) {
    if (x >= 9 || y >= 8) abort();
    display[y][x][0] = r;
    display[y][x][1] = g;
    display[y][x][2] = b;
}
static void run(unsigned line) { (void)line; }
static void open_line(unsigned line) { (void)line; }
static void Xil_ExceptionDisable(void) {}
static void Xil_ExceptionEnable(void) {}
static u32 XTtcPs_GetInterruptStatus(XTtcPs *timer) { (void)timer; return 0; }
static void XTtcPs_ClearInterruptStatus(XTtcPs *timer, u32 status) {
    (void)timer; (void)status;
}
"""
CHECKS = """
#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "Check failed at line %d: %s\\n", __LINE__, #condition); \
    return 1; \
} } while (0)
int main(void) {
    TickHandler(NULL);
    CHECK(display[7][3][0] == 255 && display[6][4][0] == 255);
    for (int i = 0; i < 10; ++i) ButtonHandler(NULL, 0, 0x01);
    CHECK(spaceship_position == 1);
    for (int i = 0; i < 10; ++i) ButtonHandler(NULL, 0, 0x04);
    CHECK(spaceship_position == 6);
    ButtonHandler(NULL, 0, 0x02);
    CHECK(trigger == 1);
    TickHandler1(NULL);
    CHECK(position_bullet == 6);
    ButtonHandler(NULL, 0, 0x02);
    CHECK(trigger == 1 && position_bullet == 6);
    for (int hit = 1; hit <= 4; ++hit) {
        position = spaceship_position;
        position_bullet = 1;
        trigger = 1;
        collision();
        CHECK(score == 8 - hit && trigger == 0);
    }
    CHECK(game_over && display[3][5][0] == 255 && display[3][5][1] == 255);
    ButtonHandler(NULL, 0, 0x08);
    CHECK(!game_over && score == 8 && position_bullet == 7 && spaceship_position == 4);
    puts("Ship movement, single shot, four hits, and restart passed.");
    return 0;
}
"""


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cc", default=os.environ.get("CC", "cc"), help="Host C compiler")
    compiler = parser.parse_args().cc
    source = (ROOT / "src" / "main.c").read_text(encoding="utf-8-sig")
    handlers = source[source.index("static uint8_t spaceship_position"):]
    with tempfile.TemporaryDirectory() as folder:
        program = Path(folder) / "game.c"
        executable = Path(folder) / ("game.exe" if os.name == "nt" else "game")
        program.write_text(DRIVERS + handlers + CHECKS, encoding="utf-8")
        subprocess.run([compiler, "-std=c99", str(program), "-o", str(executable)],
                       check=True, timeout=20)
        subprocess.run([str(executable)], check=True, timeout=5)


if __name__ == "__main__":
    main()
