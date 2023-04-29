#include "stm32f103xb.h"
#include "RccConfig.h"


void SysClockConfig (void)
{

    // 1. ENABLE HSE and wait for HSE to become ready
    RCC -> CR |= RCC_CR_HSEON;
    while (!(RCC -> CR & RCC_CR_HSERDY));

    // 2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
    // RCC -> APB1ENR |= RCC_APB1ENR_PWREN;

    // 3. Set prescalers
    // AHB prescaler
    RCC -> CFGR &= ~(1 << 4);

    // APB1 prescaler
    RCC -> CFGR |= (4 << 8);

    // APB2 prescaler
    RCC -> CFGR &= ~(1 << 11);

    //4. Configure the MAIN PLL



    RCC -> CFGR |= RCC_CFGR_SW_HSE;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE);
}


