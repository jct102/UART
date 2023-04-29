#include "delay.h"
#include "stm32f103xb.h"


void TIM4_Config() 
{
    RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;   // enable timer 2 clock
    TIM4 -> PSC = 8-1;       // set prescaler
    TIM4 -> ARR = 72;   // set ARR value

    TIM4 -> CR1 |= TIM_CR1_URS;     // enable timer 4
    while (!(TIM4 -> SR & TIM_SR_UIF)); // wait for UIF update interrupt flag

}

void Delay_us (uint16_t us)
{
    TIM4 -> CNT = 0;
    while (TIM4 -> CNT < us);
}

void Delay_ms (uint16_t ms)
{
    for (uint16_t i = 0; i < ms; i++)
    {
        Delay_us (1000); //delay of 1 ms
    }
}