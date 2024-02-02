/**********************************************/
/* Author  			: Abdelsattar Muhammad    */
/* Date    			: 30 DEC 2023             */
/* Version 			: V01                     */
/* Microcontroller  : STM32F4xx               */
/**********************************************/

#include <stdint.h>
#include <stddef.h>
#include "STM32F446xx.h"
#include "STK_interface.h"
#include "STK_private.h"

/* Callback Function Global variable (pointer to function)*/ 
 
 static void (*STK_CallBack)(void)=NULL;


/* define variable for interval mode 		*/

 static uint8_t STK_u8ModeOfInterval=0;


/******************   STK interval mode Definition   ******************/

#define STK_SINGLE_INTERVAL			0
#define STK_PERIOD_INTERVAL			1


void MSTK_voidInit(void)
{
	
	#if (STK_SRC == STK_SRC_AHB_8)
	STK->CTRL=0x00000000 ; /* Disable STK & Disable STK interrupt & choice AHB/8 */
	#elif (STK_SRC == STK_SRC_AHB) 
	STK->CTRL=0x00000004 ;/*Disable STK & Disable STK interrupt & choice AHB*/
	#endif

}

/*
	This is function Like delay function, That's Maked Processor Busy Until SysTick Finished from Counting (Synch.) 
*/
static void MSTK_voidSetBusyWait(uint32_t Copy_u32Ticks)
{
	STK->LOAD = Copy_u32Ticks;     	 /* Load Number Of Ticks*/
	SET_BIT(STK->CTRL,ENABLE);  			/* Start Timer*/
	while(!GET_BIT(STK->CTRL,COUNTFLAG));  /* wait till Count Flag ==1*/
	/*********** Stop Timer **********/
	CLR_BIT(STK->CTRL,ENABLE);  			
	STK->LOAD =0; 
	STK->VAL  =0;			
}
void Delay_ms(uint32_t Copy_u32mSecond)
{
	uint32_t Local_u32Ticks;
	#if (CLOCKSOURCE == EXTERNAL)
		#if (STK_SRC == STK_SRC_AHB_8)
	    Local_u32Ticks=((0.001*25000000)/8);
		#elif(STK_SRC == STK_SRC_AHB)
		Local_u32mSecond=(0.001*25000000);
		#endif
	#elif (CLOCKSOURCE == INTERNAL)
		#if (STK_SRC == STK_SRC_AHB_8)
		Local_u32Ticks=((0.001*16000000)/8);
		#elif(STK_SRC == STK_SRC_AHB)
		Local_u32Ticks=(0.001*16000000);
		#endif
	#endif
	while (Copy_u32mSecond)
	{
		MSTK_voidSetBusyWait(Local_u32Ticks);
		Copy_u32mSecond--;
	}
}

/*
	Enable SysTick To Count Given Ticks Single Time and Enable SysTick Interrupt Then Disabled After Finished (Asynch.)
*/

void MSTK_voidSetSingleInterval(uint32_t Copy_u32Ticks,void (*Copy_FPtr)(void))
{
	STK->LOAD = Copy_u32Ticks; 	    				/*Load Number Of Ticks*/
	STK_CallBack=Copy_FPtr;			     	  		/* Save Callback*/
	STK_u8ModeOfInterval=STK_SINGLE_INTERVAL;  		/* Set Mode as Single*/
	SET_BIT(STK->CTRL,ENABLE);			    	    /* Start Timer*/
	SET_BIT(STK->CTRL,TICKINT);  				    /* Enable SysTick Interrupt*/	
}
/*
	Enable SysTick To Count Given Ticks every Periodic Time and Enable SysTick Interrupt Then Clear Flag To interrupt again(Asynch.)
*/
void MSTK_voidSetPeriodicInterval(uint32_t Copy_u32Ticks,void (*Copy_FPtr)(void))
{
	
	STK->LOAD = Copy_u32Ticks; 	    				/*Load Number Of Ticks*/
	STK_CallBack=Copy_FPtr;			     	  		/* Save Callback*/
	STK_u8ModeOfInterval=STK_PERIOD_INTERVAL;  		/* Set Mode of Periodic Interval*/
	SET_BIT(STK->CTRL,ENABLE);			    	    /* Start Timer*/
	SET_BIT(STK->CTRL,TICKINT);  				    /* Enable SysTick Interrupt*/	
}

/*
	Stop Interval 
*/
void MSTK_voidStopSysTick(void)
{
	/* Disable STk Interrupt */
	CLR_BIT(STK->CTRL, TICKINT);
	/*********** Stop STK Interval **********/
	CLR_BIT(STK->CTRL,ENABLE);  			
	STK->LOAD =0; 
	STK->VAL  =0;	
}
/* 
Function OF Get Elapsed Time
*/
/* Return the number of thicks that done (load - val) */
uint32_t MSTK_u32GetElapsedTime(void)
{
	uint32_t Local_u32ElapsedTime=(uint32_t)((STK->LOAD) - (STK->VAL));
	return Local_u32ElapsedTime;
	
}
/*
Function OF Get Remaining Time 
*/

/* Return the number of thicks that will count (val) */
uint32_t MSTK_u32GetRemainingTime(void)
{
	uint32_t Local_u32ElapsedTime=(uint32_t)(STK->VAL);
	return Local_u32ElapsedTime;
	
}
/*
Function OF STK Interrupt
*/


void SysTick_Handler(void)
{
	if (STK_CallBack !=NULL)
	{
		if(STK_u8ModeOfInterval == STK_SINGLE_INTERVAL )
		{
			STK_CallBack();
			MSTK_voidStopSysTick();
		}
		else
		{
			STK_CallBack();
			/* Read Flag Bit To Clear Flag */
			volatile uint8_t Local_u32Flag = GET_BIT(STK->CTRL,16);
		}
	}
	else
	{
			/* Error */
	}
	
}
		
		
		
