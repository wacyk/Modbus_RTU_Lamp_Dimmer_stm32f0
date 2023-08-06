#include <stm32f0xx.h>
#include <stddef.h>
#include <math.h>
#include "Modbus\modbus_slave.h"

#define VAR_N_bytes 10

float value;

union _variables {
    uint8_t var[VAR_N_bytes];
    #pragma pack(push, 1)
    struct {
	uint16_t set_time;
        uint16_t set_value;
        uint16_t get_value;
        float step_value;
    };
    #pragma pack(pop)
};

union _variables var;

void MODBUS_Slave_Changed_Handler(uint16_t addr_mas, uint16_t length_byte){
    switch (addr_mas){
        case (offsetof(union _variables, set_time)): 
        case (offsetof(union _variables, set_value)):
            if (var.set_time == 0) break;
            if (var.set_value > 100) var.set_value = 100;
            var.step_value = (float)fabs(var.get_value - var.set_value) / var.set_time * 100;
            break;
        default:
            break;
    }
}

void SetPll48(){
    RCC -> CR |= RCC_CR_HSEON;
    while (!(RCC -> CR & RCC_CR_HSERDY));
    RCC -> CFGR |= RCC_CFGR_PLLMUL6 | RCC_CFGR_PLLSRC_HSE_PREDIV;
    RCC -> CR |= RCC_CR_PLLON;
    while (!(RCC -> CR & RCC_CR_PLLRDY));
    RCC -> CFGR |= RCC_CFGR_SW_PLL;
}

void Dimmer_Init(){
    RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
    GPIOA -> MODER |= GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1;
    GPIOA -> OSPEEDR = 0xFFFFFFFF;
    GPIOA -> AFR[0] |= (1 << 28) | (1 << 24);
    TIM3 -> PSC = 48 - 1;
    TIM3 -> ARR = 10000;
    TIM3 -> SMCR = TIM_SMCR_TS_2 | TIM_SMCR_TS_0 | TIM_SMCR_SMS_2;
    TIM3 -> CCMR1 = TIM_CCMR1_OC2M | TIM_CCMR1_IC1F_1 | TIM_CCMR1_IC1F_0 | TIM_CCMR1_CC1S_0 | TIM_CCMR1_OC2PE;
    TIM3 -> CCER = TIM_CCER_CC2E | TIM_CCER_CC1E | TIM_CCER_CC1P;
    TIM3 -> CCR2 = 100;
    TIM3 -> CR1 = TIM_CR1_CEN;
}

void Dimmer_SetVal(uint16_t percent){
    if (percent > 10000) percent = 10000;
    TIM3 -> CCR2 = 10000 - percent;
}

uint16_t Dimmer_GetVal(){
    return (10000 - TIM3 -> CCR2);
}

void SysTick_Handler(){
    if (value < var.set_value * 100) {
        value += var.step_value;
    }
    if (value > var.set_value * 100) {
        value -= var.step_value;
    }
    Dimmer_SetVal(value);
}

void main(){
    var.set_time = 1000;
    SetPll48();
    SystemCoreClockUpdate();
    Dimmer_Init();
    Modbus_Slave_Init(1, var.var);
    SysTick_Config(48000);

    IWDG -> KR = 0x0000CCCC;
    IWDG -> KR = 0x00005555;
    IWDG -> PR = 3;
    IWDG -> RLR = 0xFFF;
    while (IWDG -> SR);
    IWDG -> KR = 0x0000AAAA;

    while(1){
        IWDG -> KR = 0x0000AAAA;
        var.get_value = Dimmer_GetVal() / 100;
    }
}