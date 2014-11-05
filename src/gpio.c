#include "gpio.h"
#include "stdint.h"

void setup_gpio_output(GPIO_TypeDef * gpio, int pin)
{
    uint32_t reg;
    
    reg = gpio->MODER;
    bitClear(reg, 1 << (pin * 2 + 1));\
    bitSet(reg, 1 << (pin * 2)); \
    gpio->MODER = reg;
    
    reg = gpio->OTYPER;
    bitClear(reg, 1 << (pin)); \
    gpio->OTYPER = reg;
    
    reg = gpio->OSPEEDR;
    bitClear(reg, 3 << (pin * 2)); \
    gpio->OSPEEDR = reg;
    
    reg = gpio->PUPDR;
    bitClear(reg, 3 << (pin * 2));
    gpio->PUPDR = reg;
}                                    
void setup_gpio_af_pu(GPIO_TypeDef * gpio, int pin) 
{
    uint32_t reg;
    
    reg = gpio->MODER;
    bitSet(reg, 1 << (pin * 2 + 1)); \
    bitClear(reg, 1 << (pin * 2)); \
    gpio->MODER = reg;
    
    reg = gpio->OTYPER;
    bitClear(reg, 1 << (pin)); \
    gpio->OTYPER = reg;
    
    reg = gpio->OSPEEDR;
    bitClear(reg, 3 << (pin)); \
    gpio->OSPEEDR = reg;
    
    reg = gpio->PUPDR;
    bitSet(reg, 1 << (pin * 2)); \
    bitClear(reg, 1 << (pin * 2 + 1));
    gpio->PUPDR = reg;
}