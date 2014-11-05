#include <stm32f4xx.h>
#include "common.h"

status_t initialize_usart(USART_TypeDef *);
status_t usart_putc(USART_TypeDef *, uint8_t);
status_t usart_send_byte(USART_TypeDef *);
