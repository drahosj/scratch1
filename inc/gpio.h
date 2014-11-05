#define bitSet(reg, bit) (reg |= (bit))
#define bitClear(reg, bit) (reg &= (~(bit)))

#include "stm32f411xe.h"

void setup_gpio_output(GPIO_TypeDef * gpio, int pin);
void setup_gpio_af_pu(GPIO_TypeDef  * gpio, int pin);