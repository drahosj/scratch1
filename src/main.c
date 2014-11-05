/* main.c
 * 
 * */

#include <stm32f4xx.h>
#include "usart.h"
#include "gpio.h"

/* LED is on PA5 */

static void setupPeripherals();
static int systick_count;

void main()
{
    systick_count = 0;
    setupPeripherals();
    GPIOA->ODR = GPIO_ODR_ODR_5;
    GPIOA->ODR = GPIO_ODR_ODR_6;
    
    GPIO_TypeDef * gpio = GPIOA;
    USART_TypeDef * usart = USART2;
    for(;;);
}

static void setupPeripherals()
{
    /*Enable clock to GPIOA*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    
    setup_gpio_output(GPIOA, 5);
    setup_gpio_output(GPIOA, 6);
    
    /* Configure GPIOA for UART2 */
    
    setup_gpio_af_pu(GPIOA, 2);
    setup_gpio_af_pu(GPIOA, 3);
    
    /* AF=7 */
    GPIOA->AFR[0] |= (7 << 8);
    GPIOA->AFR[0] |= (7 << 12);
    
    /* Enable USART2 in RCC */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    
    /* Configure and enable UART2 */
    initialize_usart(USART2);
    NVIC_EnableIRQ(USART2_IRQn);
    
    /* SysTick */
    SysTick_Config(SystemCoreClock/1);
}
void SysTick_Handler()
{
    systick_count++;
    if (systick_count == 1)
    {
        GPIOA->BSRRH = GPIO_BSRR_BS_5;
        GPIOA->BSRRH = GPIO_BSRR_BS_6;
        usart_putc( USART2, 'a');
        usart_putc( USART2, 'b');
        usart_putc( USART2, 'c');
        usart_putc( USART2, 'd');
        usart_putc( USART2, 'e');
        usart_putc( USART2, 'f');
        usart_putc( USART2, '\r');
        usart_putc( USART2, '\n');
    }
    if (systick_count >= 2)
    {
        GPIOA->BSRRL = GPIO_BSRR_BS_5;
        GPIOA->BSRRL = GPIO_BSRR_BS_6;
        systick_count = 0;
    }
}