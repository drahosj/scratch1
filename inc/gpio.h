#include "stm32f411xe.h"
#include "common.h"

void setup_gpio_output(GPIO_TypeDef * gpio, int pin);
void setup_gpio_af_pu(GPIO_TypeDef * gpio, int pin);