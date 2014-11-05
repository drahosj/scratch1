/* main.c
 * 
 * */

#include <stm32f4xx.h>
#include "usart.h"
#include "gpio.h"
#include "string.h"

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
    uint8_t testBuffer[16];
    int16_t len = 0;
    
    systick_count++;
    if (systick_count == 1)
    {
        GPIOA->BSRRH = GPIO_BSRR_BS_5;
        GPIOA->BSRRH = GPIO_BSRR_BS_6;
        usart_print(USART2, "TEST!\r\n", strlen("TEST!\r\n"));
        usart_print(USART2, testBuffer, len);
    }
    if (systick_count == 3)
    {
        //len = usart_gets(USART2, testBuffer, 4);
        len = 1;
        usart_getc(USART2, testBuffer);
        
    }
    if (systick_count >= 4)
    {
        GPIOA->BSRRL = GPIO_BSRR_BS_5;
        GPIOA->BSRRL = GPIO_BSRR_BS_6;
        systick_count = 0;
    }
}