/* main.c
 * 
 * */

#include <stm32f4xx.h>


/* LED is on PA5 */

static void setupPeripherals();
static int systick_count;

void main()
{
    systick_count = 0;
    GPIO_TypeDef * gpioa;
    gpioa = GPIOA;
    setupPeripherals();
    GPIOA->ODR = GPIO_ODR_ODR_5;
    for(;;)
        gpioa = GPIOA;
}

static void setupPeripherals()
{
    /*Enable clock to GPIOA*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    
    GPIOA->MODER &= ~GPIO_MODER_MODER5_1;
    GPIOA->MODER |= GPIO_MODER_MODER5_0;
    
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT_5;
    
    GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR5_0 | GPIO_OSPEEDER_OSPEEDR5_1);
    
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR5_0 | GPIO_PUPDR_PUPDR5_1);
    
    /* SysTick */
    SysTick_Config(SystemCoreClock / 1000);
}
void SysTick_Handler()
{
    systick_count++;
    if (systick_count == 1000)
    {
        GPIOA->BSRRH = GPIO_BSRR_BS_5;
    }
    if (systick_count > 2000)
    {
        GPIOA->BSRRL = GPIO_BSRR_BS_5;
        systick_count = 0;
    }
}