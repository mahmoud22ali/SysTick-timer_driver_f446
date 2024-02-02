/**********************************************/
/* Author  			: Abdelsattar Muhammad    */
/* Date    			: 30 DEC 2023             */
/* Version 			: V01                     */
/* Microcontroller  : STM32F4xx               */
/**********************************************/

#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

/*********************** Function Definitions *****************************/


/*****************************************************
* @fn MSTK_voidInit
* @brief  Function Select SysTick Clock Input  .
* @param[in] void.
* @retval void
*/

void MSTK_voidInit(void);

/*****************************************************
* @fn Delay_ms
* @brief  This is delay function, That's Make Processor Busy until SysTick Finished from Counting (Synch.).
* @param[in] Copy_u32mSecond : Number of Mili Second Want to be Delay.
* @retval void
*/

void Delay_ms(uint32_t Copy_u32mSecond);

/*****************************************************
* @fn MSTK_voidSetSingleInterval
* @brief  Enable SysTick to Counting Given Ticks Single Time and Fire Interrupt (Asynch.)
* @param[in] Copy_u32Ticks : Number of Tick Want to Counting.
* @param[in] Copy_FPtr : Pointer to function that's Executing when ISR Fired.
* @retval void
*/
void MSTK_voidSetSingleInterval(uint32_t Copy_u32Ticks,void (*Copy_FPtr)(void));

/*****************************************************
* @fn MSTK_voidSetPeriodicInterval
* @brief  Enable SysTick To Count Given Ticks and Make Interrupt Periodic (Asynch.)
* @param[in] Copy_u32Ticks : Number of Tick Want to Counting.
* @param[in] Copy_FPtr : Pointer to function that's Executing when ISR Fired.
* @retval void
*/
void MSTK_voidSetPeriodicInterval(uint32_t Copy_u32Ticks,void (*Copy_FPtr)(void));

/*****************************************************
* @fn MSTK_voidStopSysTick
* @brief  Function of Stop interval
* @param[in] void
* @retval void
*/
void MSTK_voidStopSysTick(void);

/*****************************************************
* @fn MSTK_u32GetElapsedTime
* @brief   Function OF Get Elapsed Time
* @param[in] void
* @retval uint32_t, Number of elapsed Time
*/

uint32_t MSTK_u32GetElapsedTime(void);

/*****************************************************
* @fn MSTK_u32GetRemainingTime
* @brief   Function OF Get Remaining Time  
* @param[in] void
* @retval uint32_t, Number of Remaining Time
*/
uint32_t MSTK_u32GetRemainingTime(void);

#endif
