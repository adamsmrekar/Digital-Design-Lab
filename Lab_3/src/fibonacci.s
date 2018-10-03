/******************************************************************************
 * @Title: fibonacci.s
 *
 * @authors Adam Smrekar & Olivia Treitman
 * @date June 28th, 2018
 *
 * Compiled using NXP LPCXpresso
 * Description:
 * CU Boulder: Digital Design Lab 3
 *
 * Implemented on LPCXpresso LPC1115 Board (ARM Cortex M0).
 * Create an ARM assembly version of the following Fibonacci C code:
 * -----------------------------------
 *     int fibonacci(int n){
 *  	     if(n == 0)
 *	     	return 0;
 *	     if(n == 1)
 *		return 1;
 *	     else
 *		return fibonacci(n-1) + fibonacci(n-2);
 *     }
 *
 * ***************************************************************************/


 	.syntax unified
 	.cpu cortex-m0
 	.align	2
 	.global fibonacci
 	.thumb
	.thumb_func

fibonacci:
	push {r2, r7, lr}	 // Setup Stack
	sub	sp, sp, #12
	add	r7, sp, #0
	str r0, [r7, #4]	 // Store return r0 on stack

	cmp r0, #0 		 // if(n == 0)
	beq ZERO
	cmp r0, #1		 // if(n == 1)
	beq ONE
	cmp r0, #21	  	 // if(n <= 20)
	beq EXIT

	/* return fibonacci(n-1) + fibonacci(n-2); */
	ldr r1, [r7, #4]	 // Store n in r1
	subs r1, #1		 // n-1
	movs r0, r1		 // Store return on stack to be used recursively
	bl fibonacci		 // Recursive call

	movs r2, r0		 // Move output into temp register
	ldr r1, [r7, #4]	 // Grab n value
	subs r1, #2		 // n-2
	movs r0, r1		 // Store return on stack to be used recursively
	bl fibonacci		 // Recursive call

	movs r1, r0		 // Move output to r1
	adds r1, r2, r1		 // Add current + previous
	movs r0, r1		 // Move to r0 which is return
	b EXIT

ZERO:
	movs r0, #0
	b EXIT

ONE:
	movs r0, #1
	b EXIT

EXIT:
	mov	sp, r7	         // Restore Stack
	add	sp, sp, #12
	pop	{r2, r7, pc}
