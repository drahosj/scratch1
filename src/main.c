/* main.c
 * 
 * */

#include <stm32f4xx.h>
#include "usart.h"

#define bitSet(reg, bit) (reg |= bit)
#define bitClear(reg, bit) (reg &= (~bit))

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
    
    bitClear(GPIOA->MODER, GPIO_MODER_MODER5_1);
    bitClear(GPIOA->MODER, GPIO_MODER_MODER6_1);
    
    bitSet(GPIOA->MODER, GPIO_MODER_MODER5_0);
    bitSet(GPIOA->MODER, GPIO_MODER_MODER6_0);
    
    bitClear(GPIOA->OTYPER, GPIO_OTYPER_OT_5);
    bitClear(GPIOA->OTYPER, GPIO_OTYPER_OT_6);
    
    bitClear(GPIOA->OSPEEDR, (GPIO_OSPEEDER_OSPEEDR5_0 | GPIO_OSPEEDER_OSPEEDR5_1));
    bitClear(GPIOA->OSPEEDR, (GPIO_OSPEEDER_OSPEEDR6_0 | GPIO_OSPEEDER_OSPEEDR6_1));
    
    bitClear(GPIOA->PUPDR, (GPIO_PUPDR_PUPDR5_0 | GPIO_PUPDR_PUPDR5_1));
    bitClear(GPIOA->PUPDR, (GPIO_PUPDR_PUPDR6_0 | GPIO_PUPDR_PUPDR6_1));
    
    /* Configure GPIOA for UART2 */
    /* Pull-up (01) */
    bitSet(GPIOA->PUPDR, GPIO_PUPDR_PUPDR2_0);
    bitSet(GPIOA->PUPDR, GPIO_PUPDR_PUPDR3_0);
    bitClear(GPIOA->PUPDR, GPIO_PUPDR_PUPDR2_1);
    bitClear(GPIOA->PUPDR, GPIO_PUPDR_PUPDR3_1);
    
    /* Mode = AF (10) */
    bitSet(GPIOA->MODER, GPIO_MODER_MODER2_1);
    bitSet(GPIOA->MODER, GPIO_MODER_MODER3_1);
    bitClear(GPIOA->MODER, GPIO_MODER_MODER2_0);
    bitClear(GPIOA->MODER, GPIO_MODER_MODER3_0);
    
    /* AF=7 */
    GPIOA->AFR[0] |= (7 << 8);
    GPIOA->AFR[0] |= (7 << 12);
    GPIOA->AFR[1] |= (7 << 8);
    GPIOA->AFR[1] |= (7 << 12);
    
    /* OTYPE = PP (0) */
    bitClear(GPIOA->OTYPER, GPIO_OTYPER_OT_2);
    bitClear(GPIOA->OTYPER, GPIO_OTYPER_OT_3);
    
    /* OSPEED = High Speed */
    bitSet(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR2_0);
    bitSet(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR3_0);
    bitSet(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR2_1);
    bitSet(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR3_1);
    
    /* Enable USART2 in RCC */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    
    /* Configure and enable UART2 */
    initialize_usart(USART2);
    
    /* SysTick */
    SysTick_Config(SystemCoreClock/4);
}
void SysTick_Handler()
{
    systick_count++;
    if (systick_count == 1)
    {
        GPIOA->BSRRH = GPIO_BSRR_BS_5;
        GPIOA->BSRRH = GPIO_BSRR_BS_6;
        //usart_putc( USART2, 'a');
    }
    if (systick_count >= 2)
    {
        GPIOA->BSRRL = GPIO_BSRR_BS_5;
        GPIOA->BSRRL = GPIO_BSRR_BS_6;
        systick_count = 0;
    }
}