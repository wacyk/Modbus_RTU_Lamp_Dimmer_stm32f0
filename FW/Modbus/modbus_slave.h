#include <stm32f0xx.h>
#include <string.h>

#define MODBUS_SLAVE_BUF_SIZE	100

extern void MODBUS_Slave_Changed_Handler(uint16_t addr_mas, uint16_t length_byte);
void Modbus_Slave_Init(uint8_t addr, uint8_t *mas);