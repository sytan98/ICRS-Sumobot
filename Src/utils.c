//
// Created by tansi on 16/1/2020.
//
#include "stm32f3xx_hal.h"
#include "utils.h"

// Util functions
void error(int errorCode) {
    /* Error codes:
     * 1 - Undefined
     */
    while (1) {
        u_int8_t errorMsg[12];
        sprintf(errorMsg, "error: %02d\r\n", errorCode);
        print_f(errorMsg);
        HAL_Delay(1000);
    }
}

void print_f(char msg[]) {
    HAL_UART_Transmit(&huart2, msg, strlen(msg), 1000);
}


/**
 * Initialization routine.
 * You might need to enable access to DWT registers on Cortex-M7
 *   DWT->LAR = 0xC5ACCE55
 */
void DWT_Init(void)
{
    if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
        DWT->CYCCNT = 0;
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    }
}

#if DWT_DELAY_NEWBIE
/**
 * If you are a newbie and see magic in DWT_Delay, consider this more
 * illustrative function, where you explicitly determine a counter
 * value when delay should stop while keeping things in bounds of uint32.
*/
void DWT_Delay(uint32_t us) // microseconds
{
    uint32_t startTick  = DWT->CYCCNT,
             targetTick = DWT->CYCCNT + us * (SystemCoreClock/1000000);

    // Must check if target tick is out of bounds and overflowed
    if (targetTick > startTick) {
        // Not overflowed
        while (DWT->CYCCNT < targetTick);
    } else {
        // Overflowed
        while (DWT->CYCCNT > startTick || DWT->CYCCNT < targetTick);
    }
}
#else
/**
 * Delay routine itself.
 * Time is in microseconds (1/1000000th of a second), not to be
 * confused with millisecond (1/1000th).
 *
 * No need to check an overflow. Let it just tick :)
 *
 * @param uint32_t us  Number of microseconds to delay for
 */
void delayMicroseconds(uint32_t us) // microseconds
{
    uint32_t startTick = DWT->CYCCNT,
            delayTicks = us * (SystemCoreClock/1000000);

    while (DWT->CYCCNT - startTick < delayTicks);
}

volatile unsigned int *DWT_CYCCNT = (volatile unsigned int *)0xE0001004; //address of the register
volatile unsigned int *DWT_CONTROL = (volatile unsigned int *)0xE0001000; //address of the register
volatile unsigned int *SCB_DEMCR = (volatile unsigned int *)0xE000EDFC; //address of the register
void timer_init(void){
    *SCB_DEMCR = *SCB_DEMCR | 0x01000000;
    *DWT_CYCCNT = 0; // reset the counter
    *DWT_CONTROL = *DWT_CONTROL | 1 ; // enable the counter
}

void delay(unsigned int tick){
    // Compare current time with start time to see if delay period has ended.
    unsigned int start, current;
    start = *DWT_CYCCNT;

    do {
        current = *DWT_CYCCNT;
    }
    while((current - start) < tick * 10);
}

#endif

