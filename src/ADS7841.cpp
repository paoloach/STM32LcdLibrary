/*
 * ADS7841.cpp
 *
 *  Created on: 29 mag 2017
 *      Author: paolo
 */

#include "ADS7841.h"
#include "Pins.h"
#include "diag/Trace.h"

ADS7841::ADS7841() {
    init();
}

void ADS7841::init() {
    GPIO_InitTypeDef GPIO_InitStructure;
    // Configure pin in output push/pull mode
    GPIO_InitStructure.GPIO_Pin = AD_SERIAL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(AD_SERIAL_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = AD_CS_PIN;
    GPIO_Init(AD_CS_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = AD_IN_PIN;
    GPIO_Init(AD_IN_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = AD_OUT_PIN;
    GPIO_Init(AD_OUT_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = AD_BUSY_PIN;
    GPIO_Init(AD_BUSY_PORT, &GPIO_InitStructure);
}

#define WAIT_200 __asm(\
                    "nop\n nop\n nop\n nop\n nop\n"\
                    "nop\n nop\n nop\n nop\n nop\n"\
                    "nop\n nop\n nop\n nop\n nop\n"\
);

#define WAIT_UNTIL_200A __asm(\
                    "nop\n nop\n nop\n nop\n nop\n"\
                    "nop\n nop\n nop\n nop\n nop\n"\
                    "nop\n nop\n nop\n nop\n nop\n"\
);

#define WAIT_UNTIL_200B __asm(\
                    "nop\n nop\n nop\n nop\n nop\n"\
                    "nop\n nop\n nop\n nop\n nop\n"\
                    "nop\n nop\n nop\n nop\n nop\n"\
);

uint16_t ADS7841::get(uint8_t channel) {
    init();

    uint32_t input[25];

    uint16_t result = 0;

    uint8_t toSend;
    switch(channel){
    case 0:
        toSend = 0x94;
        break;
    case 1:
        toSend = 0xD4;
        break;
    case 2:
        toSend = 0xA4;
        break;
    case 3:
        toSend = 0xE4;
        break;
    default:
        toSend = 0x090;
    }

    AD_SERIAL_PORT->BRR = AD_SERIAL_PIN;
    AD_CS_PORT->BRR = AD_CS_PIN;
    __asm(
            "nop\n" // 14 ns at 70 Mhz
            "nop\n"// 14 ns at 70 Mhz
            "nop\n"// 14 ns at 70 Mhz
            "nop\n"// 14 ns at 70 Mhz
    );

    for (uint8_t i = 0; i < 8; i++) {
        if (toSend & 0x80)
            AD_IN_PORT->BSRR = AD_IN_PIN;
        else
            AD_IN_PORT->BRR = AD_IN_PIN;
        toSend = toSend << 1;
      //  WAIT_UNTIL_200A
        AD_SERIAL_PORT->BSRR = AD_SERIAL_PIN;
        input[i] = AD_OUT_PORT->IDR;
        WAIT_200
        AD_SERIAL_PORT->BRR = AD_SERIAL_PIN;
    }
    AD_IN_PORT->BRR;
    // BUSY
    WAIT_200
    AD_SERIAL_PORT->BSRR = AD_SERIAL_PIN;
    input[8] = AD_OUT_PORT->IDR;
    WAIT_200
    for (uint8_t i = 0; i < 12; i++) {
        AD_SERIAL_PORT->BRR = AD_SERIAL_PIN;
        WAIT_200
        AD_SERIAL_PORT->BSRR = AD_SERIAL_PIN;
        input[i+9] = AD_OUT_PORT->IDR;
        if (AD_OUT_PORT->IDR & AD_OUT_PIN) {
            result |= 1;
        }
        result = result << 1;
        WAIT_UNTIL_200B
    }

    for (uint8_t i = 0; i < 4; i++) {
        AD_SERIAL_PORT->BRR = AD_SERIAL_PIN;
        WAIT_200
        AD_SERIAL_PORT->BSRR = AD_SERIAL_PIN;
        input[i+21] = AD_OUT_PORT->IDR;
        WAIT_200
    }

    AD_CS_PORT->BSRR = AD_CS_PIN;

    result = result >> 1;

    return result;
}

