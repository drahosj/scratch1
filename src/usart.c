
#include "usart.h"
#include "stdio.h"
#include "stdlib.h"

#define RINGBUFFER_SIZE 32

uint8_t txBuffer[RINGBUFFER_SIZE];
uint8_t rxBuffer[RINGBUFFER_SIZE];

uint8_t *txHead = txBuffer;
uint8_t *txTail = txBuffer;

uint8_t *rxHead = txBuffer;
uint8_t *rxTail = txBuffer;

status_t initialize_usart(USART_TypeDef *usart)
{
    
    /* Set baud rate to 9600 baud. Assumes 16MHz Fck */
    /* Mantissa = 0d104, Frac = 3/16 */
    
    usart->BRR = 0;
    usart->BRR |= (104 << 4);
    usart->BRR |= 3;
    
    //bitSet(usart->CR1, USART_CR1_RE); /* RX Enable */
    bitSet(usart->CR1, USART_CR1_TE); /* TX Enable */
    bitSet(usart->CR1, USART_CR1_UE); /* USART Enable */
    bitSet(usart->CR1, USART_CR1_TCIE); /* TC Interrupt Enabled */
    
    return STATUS_SUCCESS;
}

status_t usart_putc(USART_TypeDef * usart, uint8_t byte)
{
    *txHead = byte;
    txHead++;
    if (txHead >= txBuffer + RINGBUFFER_SIZE)
        txHead = txBuffer;
    
    NVIC_SetPendingIRQ(USART2_IRQn);
    
    return STATUS_SUCCESS;
}

status_t usart_send_byte(USART_TypeDef * usart)
{
    if (txHead != txTail)
    {
        if (usart->SR & USART_SR_TXE)
        {
            usart->DR = *txTail & 0xff;
            txTail++;
            if (txTail >= txBuffer + RINGBUFFER_SIZE)
                txTail = txBuffer;
            return STATUS_SUCCESS;
        }
        else
            return STATUS_TXBUFFER_FULL;
    }
    else
    {
        bitClear(usart->SR, USART_SR_TC);
        return STATUS_RINGBUFFER_EMPTY;
    }
}

void USART2_IRQHandler()
{
    usart_send_byte(USART2);
    NVIC_ClearPendingIRQ(USART2_IRQn);
}