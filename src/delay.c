#include "delay.h"
#include "stm32f103xb.h"


void TIM4_Config() 
{
    RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;   // enable timer 2 clock
    TIM2 -> PSC = 36-1;       // set prescaler: 72Mhz / 70 = 1Mhz ~~ 1us delay
    TIM2 -> ARR = 0xffff;   // set ARR value

    TIM2 -> CR1 |= TIM_CR1_CEN;     // enable counter
    while (!(TIM2 -> SR & TIM_SR_UIF)); // wait for update interrupt flag to set

}

void Delay_us (uint16_t us)
{
    TIM2 -> CNT = 0;
    while (TIM2 -> CNT < us);
}

void Delay_ms (uint16_t ms)
{
    for (uint16_t i = 0; i < ms; i++)
    {
        Delay_us (1000); //delay of 1 ms
    }
}