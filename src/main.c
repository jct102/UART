#include "delay.h"
#include "stm32f103xb.h"
#include "RccConfig.h"



// enable UART clock
// set "alternative function" pin mode for RX and TX pins
// set baud rate (receive/trnasmit clock frequency) via BRR register
// enable the peripheral, receive, and transmit via the CR1 register


void USART2_SendChar (uint8_t c)
{
    USART2 -> DR = c;   // load the data
    while (!(USART2 -> SR & USART_SR_TC));  // wait for transmission complete

}

void USART2_SendString (char *string)
{
    while (*string) USART2_SendChar (*string++);
}


uint8_t USART2_GetChar (void)
{
    uint8_t Temp;
    while (!(USART2 -> SR & USART_SR_RXNE));    // wait for RXNE to be set
    Temp = USART2 -> DR;    // read the data
    return Temp;
}



void USART2_init (void)
{
    // enable APB1 bus
    RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
    // enable GPIOA bus
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;


    // reset PA2 and PA3
    GPIOA -> CRL &= ~(GPIO_CRL_MODE2_Msk| GPIO_CRL_MODE3_Msk);
    GPIOA -> CRL &= ~(GPIO_CRL_CNF2_Msk | GPIO_CRL_CNF2_Msk);
    // set PA2 to push-pull output
    GPIOA -> CRL |= GPIO_CRL_MODE2_0;
    GPIOA -> CRL |= GPIO_CRL_CNF2_1;
    // set PA3 to input - MODE3 already reset to 0 input mode
    GPIOA -> CRL |= GPIO_CRL_CNF3_1;
    GPIOA -> CRL &= ~(GPIO_CRL_CNF3_Msk);


    USART2 -> CR1 = 0x00;  // clear ALL
    USART2 -> CR1 |= USART_CR1_UE;  // enable USART

    USART2 -> CR1 &= ~(USART_CR1_PCE_Msk);  // set word length to 8 data bits, 1 start bit, n stop bit
    USART2 -> CR2 &= ~(USART_CR2_STOP_Msk);

    // set baud rate
    USART2 -> BRR = (26 << 4) | (1 << 0);

    // enable TE and RE via CR1 register
    USART2 -> CR1 |= (USART_CR1_TE | USART_CR1_RE);
}


void delay (uint32_t time)
{
    while (time--);
}


int main (void)
{
    SysClockConfig();
    // TIM4_Config();
    USART2_init();

    while (1)
    {
        // output
        USART2_SendString ("Hello World\n");
        delay(1000000000);
        // Delay_ms(1000);


        // input
        // uint8_t data = USART2_GetChar ();
		// USART2_SendChar (data);
    }
}


