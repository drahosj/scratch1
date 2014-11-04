
#include "usart.h"

#define bitSet(reg, bit) (reg |= bit)
#define bitClear(reg, bit) (reg &= (~bit))


int8_t initialize_usart(USART_TypeDef *usart)
{
    
    /* Set baud rate to 9600 baud. Assumes 16MHz Fck */
    /* Mantissa = 0d104, Frac = 3/16 */
    
    usart->BRR = 0;
    usart->BRR |= (104 << 4);
    usart->BRR |= 3;
    
    //bitSet(usart->CR1, USART_CR1_RE); /* RX Enable */
    bitSet(usart->CR1, USART_CR1_TE); /* TX Enable */
    bitSet(usart->CR1, USART_CR1_UE); /* USART Enable */
}

void usart_putc(USART_TypeDef * usart, uint8_t byte)
{
    while(!(usart->SR & USART_SR_TXE)) {}
    usart->DR = byte & 0xff;
}