#include "stm32f10x.h"
 
void initial (void)
{
    RCC->APB2ENR |= 1 << 4; 
    GPIOC->CRH &= ~GPIO_CRH_CNF8;
    GPIOC->CRH |= GPIO_CRH_MODE8_0; 
    GPIOC->CRH &= ~GPIO_CRH_CNF9;
    GPIOC->CRH |= GPIO_CRH_MODE9_0; 
     
    /*timer config*/
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6->PSC = 8000-1;
    TIM6->CR1 |= TIM_CR1_OPM;
}  
 
void delay_ms (uint16_t value)
{
    TIM6->ARR = value;
    TIM6->CNT = 0;
    TIM6->CR1 = TIM_CR1_CEN;
    while((TIM6->SR & TIM_SR_UIF)==0){} // дождаться конца задержки
  TIM6->SR &= ~TIM_SR_UIF;
}
 
int main (void)
{
    initial ();
    while (1)
    {
        GPIOC->BSRR |= 1 << 8;
        delay_ms (1000);
        GPIOC->BRR |= 1 << 8;
        GPIOC->BSRR |= 1 << 9;
        delay_ms (1000);
        GPIOC->BRR |= 1 << 9;
    }
}
