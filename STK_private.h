/**********************************************/
/* Author  			: Abdelsattar Muhammad    */
/* Date    			: 30 DEC 2023             */
/* Version 			: V01                     */
/* Microcontroller  : STM32F4xx               */
/**********************************************/


#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

/********************** SYSTICK REGISTERS Definitions *****************************/

typedef struct{
	
		volatile uint32_t CTRL; /*SysTick control and status register */
		volatile uint32_t LOAD; /*SysTick reload value register */
		volatile uint32_t VAL;  /*SysTick current value register */
		volatile uint32_t CALIB;
		
}STK_RegDef_t;
	
typedef enum
{
	ENABLE=0,		 /*Counter enable*/
	TICKINT=1,		/* SysTick exception request enable	*/
	CLKSOURCE=2, 	/*Clock source selection*/
	COUNTFLAG=16,	/*Returns 1 if timer counted to 0 since last time this was read.*/
}CTRL_Bits;

#define STK_SRC_AHB_8 		 0U 
#define STK_SRC_AHB   		 1U	 
#define EXTERNAL	         0U  /* means external Oscillator equal 25MHZ */
#define INTERNAL	         1U  /* means external Oscillator equal 16MHZ */

static void MSTK_voidSetBusyWait(uint32_t Copy_uint32_tTicks);

/********************** BASE ADDRESS REGISTER  *****************************/

#define STK_BASE_ADDRESS  0xE000E010 

#define STK ((STK_RegDef_t *)STK_BASE_ADDRESS)


#endif
