

#include <stdint.h>
#include <stm32f4xx.h>

int8_t initialize_usart(USART_TypeDef *);
void usart_putc(USART_TypeDef *, uint8_t);