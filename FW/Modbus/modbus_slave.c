#include "modbus_slave.h"

#define LED_ON	    GPIOA -> BSRR = GPIO_BSRR_BS_0
#define LED_OFF	    GPIOA -> BSRR = GPIO_BSRR_BR_0

uint8_t slave_addr, *pointer;
uint8_t slave_buf[MODBUS_SLAVE_BUF_SIZE], slave_in_cnt, slave_answer_buf[256];

uint16_t crc_chk(uint8_t* dat, uint8_t length){
    uint16_t j;
    uint16_t reg_crc=0xFFFF;
    while(length--){
	reg_crc ^= *dat++;
	for(j=0;j<8;j++){
	    if(reg_crc & 0x01) reg_crc=(reg_crc>>1) ^ 0xA001; // LSB(b0)=1
	    else reg_crc=reg_crc>>1;
	}
    }
    return reg_crc;
}

void MODBUS_Swap_Byte(uint8_t *mas, uint16_t len){
    uint16_t i;
    uint8_t temp;
    for (i = 0; i < len - 1; i += 2){
	temp = mas[i];
	mas[i] = mas[i+1];
	mas[i+1] = temp;
    }
}

void USART1_IRQHandler(){
    uint8_t temp, a, b;
    uint16_t crc, start, length;
    if (USART1 -> ISR & USART_ISR_RTOF){
	USART1 -> ICR = USART_ICR_RTOCF;
	if (slave_in_cnt > 0) {
	    crc = crc_chk(slave_buf, slave_in_cnt - 2);
	    if (crc == (slave_buf[slave_in_cnt - 2] | (slave_buf[slave_in_cnt - 1] << 8))){
		LED_ON;
		slave_answer_buf[0] = slave_buf[0];
		slave_answer_buf[1] = slave_buf[1];
                start = ((slave_buf[2] << 8) | slave_buf[3]) * 2;
                switch (slave_buf[1]){
		case 1:
		case 2:
		    start /= 2;
		    a = start % 8;
		    start /= 8; 
		    length = (slave_buf[4] << 8) | slave_buf[5];
		    if ((length % 8) == 0){
			length /= 8;
		    } else length = (length / 8) + 1;
		    slave_answer_buf[2] = length;
		    for (b = 0; b < length; b++){
			slave_answer_buf[3 + b] = (pointer[start + b] >> a) | (pointer[start + b + 1] << (8 - a));
		    }
		    crc = crc_chk(slave_answer_buf, length + 3);
		    slave_answer_buf[length + 3] = crc;
		    slave_answer_buf[length + 4] = crc >> 8;
		    break;
		case 3:
		case 4:
		    length = slave_buf[5] * 2;
		    slave_answer_buf[2] = length;
		    memcpy(&slave_answer_buf[3], &pointer[start], length);
		    MODBUS_Swap_Byte(&slave_answer_buf[3], length);
		    crc = crc_chk(slave_answer_buf, length + 3);
		    slave_answer_buf[length + 3] = crc;
		    slave_answer_buf[length + 4] = crc >> 8;
		    break;
		case 5:
		    start /= 2;
		    a = start % 8;
		    start /= 8; 
		    if (slave_buf[4] == 0){
			pointer[start] &= ~(1 << a);
		    } else {
			pointer[start] |= (1 << a);
		    }
		    length = 3;
		    memcpy(slave_answer_buf, slave_buf, 8);
                    MODBUS_Slave_Changed_Handler(start, 1);
		    break;
		case 6:
		    pointer[start] = slave_buf[5];
		    pointer[start + 1] = slave_buf[4];
                    length = 3;
                    memcpy(slave_answer_buf, slave_buf, 8);
                    MODBUS_Slave_Changed_Handler(start, 2);
		    break;
		case 16:
		    length = slave_buf[5] * 2;
		    MODBUS_Swap_Byte(&slave_buf[7], length);
		    memcpy(&pointer[start], &slave_buf[7], length);
		    memcpy(slave_answer_buf, slave_buf, 6);
		    crc = crc_chk(slave_answer_buf, 6);
		    slave_answer_buf[6] = crc;
		    slave_answer_buf[7] = crc >> 8;
                    MODBUS_Slave_Changed_Handler(start, length);
                    length = 3;
		    break;
		default:
		    slave_answer_buf[1] |= 0x80;
                    slave_answer_buf[2] = 0x01;
                    crc = crc_chk(slave_answer_buf, 3);
		    slave_answer_buf[3] = crc;
		    slave_answer_buf[4] = crc >> 8;
                    length = 0;
		    break;
		}
		DMA1_Channel2 -> CCR &= ~(DMA_CCR_EN);
		DMA1_Channel2 -> CNDTR = length + 5;
		DMA1_Channel2 -> CCR |= DMA_CCR_EN;
	    }
	}
	slave_in_cnt = 0;
    } 
    if (USART1 -> ISR & USART_ISR_RXNE){
	temp = USART1 -> RDR;
	if (slave_in_cnt == 0){
	    if (temp != slave_addr){
		USART1 -> RQR = USART_RQR_MMRQ;
	    } else {
		slave_buf[0] = temp;
		slave_in_cnt = 1;
	    }
	} else {
	    slave_buf[slave_in_cnt] = temp;
	    if (slave_in_cnt < (MODBUS_SLAVE_BUF_SIZE - 1)) slave_in_cnt++;
	    else slave_in_cnt = 0;
	}
    }
}

void DMA1_CH2_3_IRQHandler(){
    DMA1 -> IFCR = DMA_IFCR_CTCIF2;
    LED_OFF;
}

void Modbus_Slave_Init(uint8_t addr, uint8_t *mas){
    slave_addr = addr;
    slave_in_cnt = 0;
    pointer = mas;
    RCC -> AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_DMA1EN;
    RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;

    GPIOA -> MODER |= GPIO_MODER_MODER0_0;

    GPIOA -> MODER |= GPIO_MODER_MODER1_1 | GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;
    GPIOA -> OSPEEDR = 0xFFFFFFFF;
    GPIOA -> AFR[0] |= (1 << 12) | (1 << 8) | (1 << 4);

    USART1 -> CR1 = USART_CR1_RTOIE | USART_CR1_DEAT | USART_CR1_DEDT | USART_CR1_MME | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
    USART1 -> CR2 = USART_CR2_RTOEN | USART_CR2_STOP;
    USART1 -> CR3 = USART_CR3_DEM | USART_CR3_DMAT | USART_CR3_OVRDIS;
    USART1 -> BRR = 48000000 / 9600;
    USART1 -> RTOR = 30;
    USART1 -> CR1 |= USART_CR1_UE;

    DMA1_Channel2 -> CMAR = (uint32_t)slave_answer_buf;
    DMA1_Channel2 -> CPAR = (uint32_t)&USART1 -> TDR;
    DMA1_Channel2 -> CCR = DMA_CCR_PL | DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE;

    NVIC_EnableIRQ(DMA1_Ch2_3_DMA2_Ch1_2_IRQn);
    NVIC_EnableIRQ(USART1_IRQn);
}