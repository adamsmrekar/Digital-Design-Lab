/******************************************************************************
 * @Title: main.c
 *
 * @authors Adam Smrekar & Olivia Treitman
 * @date June 28th, 2018
 *
 * Compiled using NXP LPCXpresso
 * Description:
 * 		CU Boulder: Digital Design Lab 3
 *
 * 		Implemented on LPCXpresso LPC1115 Board (ARM Cortex M0).
 * 		This is a Fibonacci-driven Morse Code Generator. Fibonacci takes in a
 * 		number at each index from 1 to 20, outputs the calculated number,
 * 		then translates that number into a binary signal that turns the
 * 		Red LED on or off according to the Morse Code equivalent for its hex
 * 		value. Blinks Blue LED inbetween hex values. Blinks Green LED between
 * 		Fibonacci sequences.
 *
 * ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "driver_config.h"
#include "target_config.h"
#include "timer32.h"
#include "gpio.h"
#include "system_LPC11xx.c"

extern int fibonacci(int x);

/*******************************************************
 *
 * @Title: fibonacci
 * -----------------------
 *
 * @param: Number from 0 - 20
 * @return: Fibonacci Number
 *
 * 		C version of Fibonacci function, used for
 * 		testing. Assembly version will be used in
 * 		final version
 *******************************************************/
/*int fibonacci(int n){
	if(n == 0)
		return 0;
	if(n == 1)
		return 1;
	else
		return fibonacci(n-1) + fibonacci(n-2);
}
*/
/*******************************************************
 *
 * @Title: dot
 * -----------------------
 *
 * 		Blinks Red LED for a short time to represent
 * 		Morse code dot
 *******************************************************/
void dot(){
	printf("dot...");
	GPIOSetValue( LED_PORT_R, LED_BIT_R, LED_ON );
	delay32Ms(0, 70);
	GPIOSetValue(LED_PORT_R, LED_BIT_R, LED_OFF );
	delay32Ms(0, 40);
}

/*******************************************************
 *
 * @Title: dash
 * -----------------------
 *
 * 		Blinks Red LED for a long time (3x time for
 * 		dot to blink) to represent Morse code dot
 *******************************************************/
void dash(){
	printf("dash...");
	GPIOSetValue( LED_PORT_R, LED_BIT_R, LED_ON );
	delay32Ms(0, 210);
	GPIOSetValue(LED_PORT_R, LED_BIT_R, LED_OFF );
	delay32Ms(0, 40);
}

/*******************************************************
 *
 * @Title: pause
 * -----------------------
 *
 * 		Blinks Blue LED for a short time to represent
 * 		the pause between hex digits of Fibonacci
 * 		sequence. Delay function is from timer32.
 *******************************************************/
void pause(){
	printf("next\n");
	GPIOSetValue( LED_PORT_B, LED_BIT_B, LED_ON );
	delay32Ms(0, 160);
	GPIOSetValue(LED_PORT_B, LED_BIT_B, LED_OFF );
	delay32Ms(0, 10);
}

/*******************************************************
 *
 * @Title: pause2
 * -----------------------
 *
 * 		Blinks Green LED for a short time to represent
 * 		the pause between Fibonacci Sequences. Delay
 * 		function is from timer32.
 *******************************************************/
void pause2(){
	printf("...NEXT FIB NUMBER...\n");
	GPIOSetValue( LED_PORT_G, LED_BIT_G, LED_ON );
	delay32Ms(0, 180);
	GPIOSetValue(LED_PORT_G, LED_BIT_G, LED_OFF );
	delay32Ms(0, 10);
}


/*******************************************************
 *
 * @Title: parseFib
 * -----------------------
 *
 * @param: Fibonacci Number
 * @return: Array of size 4
 *
 * 		Parses Fibonacci sequence into 4 different
 * 		hex digits. Uses bit shifting and masking
 * 		to seperate stuff
 *******************************************************/
int * parseFib(int n){
	static int arr[4];

	arr[3] = (n & 0xf);
	arr[2] = ((n >> 4) & 0xf);
	arr[1] = ((n >> 8) & 0xf);
	arr[0] = ((n >> 12) & 0xf);

	return arr;
}

/*******************************************************
 *
 * @Title: translateFib
 * -----------------------
 *
 * @param: Fibonacci number
 *
 * 		Translates Fibonacci Number into Morse Code
 *******************************************************/
void translateFib(int fibNum){
	int *arr;				// Pointer for Array

	arr = parseFib(fibNum);			// Parse Fibonacci Hex

	for(int i = 0; i < 4; i++){		// Loop Array
		switch(arr[i]){			// Switch statement for each hex digit
			case 0x0:
				printf("0...");
				dash();
				dash();
				dash();
				dash();
				dash();
				pause();
				break;
			case 0x1:
				printf("1...");
				dot();
				dash();
				dash();
				dash();
				dash();
				pause();
				break;
			case 0x2:
				printf("2...");
				dot();
				dot();
				dash();
				dash();
				dash();
				pause();
				break;
			case 0x3:
				printf("3...");
				dot();
				dot();
				dot();
				dash();
				dash();
				pause();
				break;
			case 0x5:
				printf("5...");
				dot();
				dot();
				dot();
				dot();
				dot();
				pause();
				break;
			case 0x6:
				printf("6...");
				dash();
				dot();
				dot();
				dot();
				dot();
				pause();
				break;
			case 0x7:
				printf("7..");
				dash();
				dash();
				dot();
				dot();
				dot();
				pause();
				break;
			case 0x8:
				printf("8...");
				dash();
				dash();
				dash();
				dot();
				dot();
				pause();
				break;
			case 0x9:
				printf("9...");
				dash();
				dash();
				dash();
				dash();
				dot();
				pause();
				break;
			case 0xA:
				printf("A...");
				dot();
				dash();
				pause();
				break;
			case 0xB:
				printf("B...");
				dash();
				dot();
				dot();
				dot();
				pause();
				break;
			case 0xD:
				printf("D...");
				dash();
				dot();
				dot();
				pause();
				break;
			case 0xE:
				printf("E...");
				dot();
				pause();
				break;
			case 0xF:
				printf("F...");
				dot();
				dot();
				dash();
				dot();
				pause();
				break;
			default:
				printf("Error\n");
				break;
		}
	}
}

int main() {
	int x;
	init_timer32(0, TIME_INTERVAL);		// Initialize Timer_32_0
	enable_timer32(0);			// Enable Timer_32_0

	GPIOInit(); 				// Initialize GPIO (sets up clock)
	GPIOSetDir(LED_PORT_R, LED_BIT_R, 1 );  // Set LED port pin to output - Red
	GPIOSetDir(LED_PORT_G, LED_BIT_G, 1 );  // Set LED port pin to output - Green
	GPIOSetDir(LED_PORT_B, LED_BIT_B, 1 );  // Set LED port pin to output - Blue

	/* Loops through Fibonacci with inputs from 0-20, translates to Morse Code */
	for(int n = 0; n < 21; n++) {
		x = fibonacci(n);
		translateFib(x);
		pause2();
	}

	while(1){
		// Infinite Loop
	}
	return 0;
}
