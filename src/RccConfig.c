#include "stm32f103xb.h"
#include "RccConfig.h"


void SysClockConfig (void)
{
    // ENABLE HSE and wait for HSE to become ready
    RCC -> CR |= RCC_CR_HSEON;
    while (!(RCC -> CR & RCC_CR_HSERDY));

    // Configure flash
    FLASH -> ACR |= FLASH_ACR_LATENCY_1;    // Flash latency : 2 wait states
    FLASH -> ACR |= FLASH_ACR_PRFTBE;       // Enable prefetch buffer

    // Set prescalers
    RCC -> CFGR &= ~(RCC_CFGR_HPRE_0);   // AHB prescaler set to 1

    RCC -> CFGR |= RCC_CFGR_PPRE1_2;    // APB1 prescaler set to 2

    RCC -> CFGR &= ~(RCC_CFGR_PPRE2_0);  // APB2 prescaler set to 1

    // Configure the MAIN PLL
    RCC -> CFGR |= RCC_CFGR_PLLSRC;   // set PLL clock source
    RCC -> CFGR |= RCC_CFGR_PLLMULL9;   // set PLLMul to 9

    // Enable PLL and wait for it to become ready
    RCC -> CR |= RCC_CR_PLLON;
    while (!(RCC -> CR & RCC_CR_PLLRDY));

    // Select clock source and wait for it to be set
    RCC -> CFGR |= RCC_CFGR_SW_PLL;
    while (!(RCC -> CFGR & RCC_CFGR_SWS_PLL));
}


