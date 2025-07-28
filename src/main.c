#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xgpiops.h"
#include "xttcps.h"
#include "xscugic.h"
#include "xparameters.h"
#include "Pixel.h"
#include "Interrupt_setup.h"

#define enable_interrupts

extern void blinker(void); // calling Blinker.s function in Assembly

int main()
{
	//**DO NOT REMOVE THIS****
	    init_platform();
	//************************


#ifdef	enable_interrupts
	    init_interrupts();
#endif


	    //setup screen
	    setup();


	    Xil_ExceptionEnable();

	    // calling Blinker.s function in Assembly
	    blinker();

	    //Try to avoid writing any code in the main loop.
		while(1){


		}


		cleanup_platform();
		return 0;
}

//	-----------------------------------------------------------------------------
static uint8_t spaceship_position = 4; // Start in the middle
static const uint8_t spaceship_width = 3; // Spaceship spans 3 columns (wings + head)
static uint8_t position = 0;  // Current position of the LED - Alien
static uint8_t direction = 1; // 1 for forward, 0 for backward
static uint8_t position_bullet = 7;
static uint8_t bullet_delay_counter = 0; // Counter for controlling bullet speed
static uint8_t bullet_speed = 1;
static uint8_t trigger = 0; // shooting bullet flag
static uint8_t score = 8; // Tracks the number of collisions
static uint8_t fact = 1; // to add up to points
static uint8_t alien_delay_counter = 0;
static uint8_t alien_speed = 3;
static uint8_t game_over = 0; // 1 when the game is over

//	-----------------------------------------------------------------------------
//Timer interrupt handler for led matrix update. Frequency is 800 Hz
void TickHandler(void *CallBackRef) {
	//Don't remove this
	uint32_t StatusEvent;

	// Exceptions must be disabled when updating screen
	Xil_ExceptionDisable();

    // Clear row 7 and 6 (turn off all LEDs)
    for (uint8_t col = 0; col < 9; col++) {
        SetPixel(col, 7, 0, 0, 0); // Turn off all LEDs in row 7
        SetPixel(col, 6, 0, 0, 0); // Turn off all LEDs in row 6
    }

    // Draw the spaceship in row 7 and row 6
    for (uint8_t i = 0; i < spaceship_width; i++) {
        int8_t col = spaceship_position + i - 1; // Adjust for the spaceship width
        if (col >= 0 && col < 9) { // Ensure we don't go out of bounds
            if (i == 1) {
                SetPixel(col, 7, 255, 255, 255); // Center
                SetPixel(col, 6, 255, 255, 255); // Center (row 6)
            } else {
                SetPixel(col, 7, 255, 255, 255); // Wings
            }
        }
    }

    // Refresh row 7 and 6
    for (uint8_t col = 0; col < 9; col++) {
        run(col);
        open_line(col);
    }

	//*********clear timer interrupt status. DO NOT REMOVE********
	StatusEvent = XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef);
	XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, StatusEvent);
	//*************************************************************
	//enable exceptions
	Xil_ExceptionEnable();
}

//	-----------------------------------------------------------------------------
// bullet-alien collision logic
void collision() {
    if (position_bullet == 1) {
        if (spaceship_position >= position - 1 && spaceship_position <= position + 1) {
            score--;
            if (fact > 0) {
                if (score > 4) {
                    SetPixel(score, 0, 0, 255, 0); // Showing score on the top row
                } else {
                    game_over = 1;
                }
            } else {
                game_over = 1;
            }

            if (game_over) {
                // Clear the LED matrix
                for (uint8_t row = 0; row < 8; row++) {
                    for (uint8_t col = 0; col < 9; col++) {
                        SetPixel(col, row, 0, 0, 0); // Turn off all LEDs
                    }
                }

                // Light up a check sign LED in the centre
                SetPixel(5, 3, 255, 255, 0);
                SetPixel(5, 4, 255, 255, 0);
                SetPixel(5, 5, 255, 255, 0);
                SetPixel(4, 4, 255, 255, 0);
                SetPixel(3, 3, 255, 255, 0);
                SetPixel(2, 2, 255, 255, 0);
                SetPixel(1, 1, 255, 255, 0);

                // Refresh the display
                for (uint8_t row = 0; row < 8; row++) {
                    run(row);
                    open_line(row);
                }
            }
//	-----------------------------------------------------------------------------
            // Reset bullet after collision
            position_bullet = 6;
            trigger = 0;
        }
    }
}


//Timer interrupt for moving alien, shooting... Frequency is 10 Hz by default
void TickHandler1(void *CallBackRef) {
    if (game_over == 0) {


		uint32_t StatusEvent;
//	-----------------------------------------------------------------------------
		// Bullet movement logic
		if (trigger == 1) {
			bullet_delay_counter++;
			if (bullet_delay_counter >= bullet_speed) {
				bullet_delay_counter = 0;

				// Clear bullet rows collectively
				for (uint8_t row = 2; row < 7; row++) {
					for (uint8_t col = 0; col < 9; col++) {
						SetPixel(col, row, 0, 0, 0); // Clear bullet space
					}
				}

				position_bullet--;
				if (position_bullet == 0) {
					position_bullet = 6; // Reset bullet position
					trigger = 0;         // Bullet no longer active
				}

				// Draw bullet
				SetPixel(spaceship_position, position_bullet, 0, 0, 110);

				// Collision check
				collision();

				// Refresh affected rows for bullets
				for (uint8_t row = 2; row < 7; row++) {
					run(row);
					open_line(row);
				}
			}
		}
//	------------------------------------------------------------------------------
		// Alien movement logic
		alien_delay_counter++; // this line is used to set alien's speed
		if (alien_delay_counter >= alien_speed) {
			alien_delay_counter = 0;

			// Clear and redraw alien in row 1
			for (uint8_t col = 0; col < 9; col++) {
				SetPixel(col, 1, 0, 0, 0); // Clear all LEDs in the row
			}

			SetPixel(position, 1, 255, 0, 0); // Draw alien at its current position

			// Update position by increasing/decreasing the position
			position = (direction == 1) ? position + 1 : position - 1;
			// check the boundaries
			if (position == 7){
				direction = 1 - direction; // Forward direction
			}
			if (position == 0 ) {
				direction = 1 - direction; // Backward direction
			}


			// Refresh row 1
			run(1);
			open_line(1);
		}

//	------------------------------------------------------------------------------
		//clear timer interrupt status. DO NOT REMOVE
		StatusEvent = XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef);
		XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, StatusEvent);
    }
}



//Interrupt handler for switches and buttons.
//Reading Status will tell which button or switch was used
//Bank information is useless in this exercise
void ButtonHandler(void *CallBackRef, u32 Bank, u32 Status) {
	//Hint: Status==0x01 ->btn0, Status==0x02->btn1, Status==0x04->btn2, Status==0x08-> btn3, Status==0x10->SW0, Status==0x20 -> SW1

    // BTN0, Move right (if pressed)
    if (Status == 0x01 && game_over==0) {
        if (spaceship_position > 1) { // Prevent moving past the right boundary
            spaceship_position--;
        }
    }

    // BTN1, Bullet Shooting (if pressed)
	if (Status == 0x02 && game_over==0) {
		if (trigger == 0) { // Only shoot if no bullet is currently active
			trigger = 1;
		}
	}

    // BTN2, Move left (if pressed)
    if (Status == 0x04 && game_over==0) {
        if (spaceship_position + spaceship_width - 2 < 7) { // Prevent moving past the left boundary
            spaceship_position++;
        }
    }

    // BTN3, Restart (if pressed)
    if (Status == 0x08) {
        // Reset all game variables
        game_over = 0;
        score = 8;
        position = 0;
        position_bullet = 7;
        direction = 1;
        trigger = 0;

        // Clear the LED matrix
        for (uint8_t row = 0; row < 8; row++) {
            for (uint8_t col = 0; col < 9; col++) {
                SetPixel(col, row, 0, 0, 0);
            }
        }

        // Reset spaceship position
        spaceship_position = 4;

        // Refresh the display
        for (uint8_t row = 0; row < 8; row++) {
            run(row);
            open_line(row);
        }
    }
}
