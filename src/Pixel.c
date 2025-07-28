#include "Pixel.h"

#define ctrl_signal_reg *(uint8_t *) 0x41220008
#define channel_signal_reg *(uint8_t *) 0x41220000

//Table for pixel dots.
//				 dots[X][Y][COLOR]
volatile uint8_t dots[8][8][3]={0};


// Here the setup operations for the LED matrix will be performed
void setup(){

	channel_signal_reg = 0;
	ctrl_signal_reg = 0;

	ctrl_signal_reg &= 0b11110;
	usleep(500);


	// Resetting the screen at start is a MUST to operation (Set RSTn to 1).
	ctrl_signal_reg |= 0b00001;
	usleep(500);
	// Change SDA to 1 (6 bit register bank)
	ctrl_signal_reg |= 0b10000;


	//Write code that sets 6-bit values in register of DM163 chip. Recommended that every bit in that register is set to 1. 6-bits and 24 "bytes", so some kind of loop structure could be nice.
	//24*6 bits needs to be transmitted
	for(uint8_t data_counter=0; data_counter < 144; data_counter++) {
		ctrl_signal_reg &= 0b10111; // Set the bit 3 to 0
		ctrl_signal_reg |= 0b01000; // Set the bit 3 to 1

	}




	//Final thing in this function is to set SB-bit to 1 to enable transmission to 8-bit register.
	ctrl_signal_reg |= 0b00100; // Set the bit 2 to 1

}

//Change value of one pixel at led matrix. This function is only used for changing values of dots array
void SetPixel(uint8_t x,uint8_t y, uint8_t r, uint8_t g, uint8_t b){

	//Hint: you can invert Y-axis quite easily with 7-y
	dots[x][y][0]=b;
	//Write rest of two lines of code required to make this function work properly (green and red colors to array).
	dots[x][y][1]=g;
	dots[x][y][2]=r;



}

//Put new data to led matrix. Hint: This function is supposed to send 24-bytes and parameter x is for channel x-coordinate.
void run(uint8_t x){

	ctrl_signal_reg &= 0b11101; //Set bit1 to 0

	// Change SDA to 1 (6 bit register bank)
	ctrl_signal_reg |= 0b10000;

	uint8_t data;

	for(uint8_t y=0; y < 8; y++) {


		for(uint8_t color=0; color < 3; color++) {
			data = dots[x][y][color];

			for(uint8_t bit_data=0; bit_data < 8; bit_data++) {

				if(data & 0x80){
					ctrl_signal_reg |= 0b10000; // Set bit4 to 1
				}
				else{
					ctrl_signal_reg &= 0b01111; // Set bit4 to 0
				}

				ctrl_signal_reg &= 0b10111; // Set the bit 3 to 0
				data<<=1;
				ctrl_signal_reg |= 0b01000; // Set the bit 3 to 1

			}

		}
		channel_signal_reg = 0; // remove ghost LEDs at the right side

	}

	latch();

    open_line(x);

	//Write code that writes data to led matrix driver (8-bit data). Use values from dots array
	//Hint: use nested loops (loops inside loops)
	//Hint2: loop iterations are 8,3,8 (pixels,color,8-bitdata)


}

//Latch signal. See colorsshield.pdf or DM163.pdf in project folder on how latching works
void latch(){
	ctrl_signal_reg |= 0b00010; //Set bit1 to 1
	ctrl_signal_reg &= 0b11101; //Set bit1 to 0
}


//Set one line (channel) as active, one at a time.
void open_line(uint8_t x){
	switch(x){
	 case 0: channel_signal_reg=0b10000000; break; // bit 7
	 case 1: channel_signal_reg=0b01000000; break; // bit 6
	 case 2: channel_signal_reg=0b00100000; break; // bit 5
	 case 3: channel_signal_reg=0b00010000; break; // bit 4
	 case 4: channel_signal_reg=0b00001000; break; // bit 3
	 case 5: channel_signal_reg=0b00000100; break; // bit 2
	 case 6: channel_signal_reg=0b00000010; break; // bit 1
	 case 7: channel_signal_reg=0b00000001; break; // bit 0
	 default: channel_signal_reg=0 ; // default
	}

}

//--------------------------------------------------------


