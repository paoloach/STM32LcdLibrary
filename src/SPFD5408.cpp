/*
 * SPFD5408.cpp
 *
 *  Created on: 16 gen 2017
 *      Author: paolo
 */

#include "SPFD5408.h"
#include "Register.h"

#define TFTWIDTH   240
#define TFTHEIGHT  320

SPFD5408::SPFD5408() {
    initIOPort();

    rotation = 0;
    cursor_y = cursor_x = 0;
    textsize = 1;
    textcolor = 0xFFFF;
    _width = TFTWIDTH;
    _height = TFTHEIGHT;
}

LcdID SPFD5408::readID(void) {
    activeCS();
    command();
    uint8_t hi = ::read8408();
    uint8_t low = ::read8408();

    uint16_t code = ((uint16_t) hi << 8) + low;
    if (code == 0x5408)
        return LcdID::ID_SPFD5408;
    else
        return LcdID::ID_UNKNOWN;
}

void SPFD5408::reset(void) {

    idleCS();
    idleWR();
    idleRD();

}

void SPFD5408::begin(LcdID id) {
    if (id == LcdID::ID_SPFD5408) {
        reset();

        driver = id;
        activeCS();

        SPFD5408_DriverOuput::write(0);
        SPFD5408_NVMReadData1::write(0);
        SPFD5408_PowerControl2::write(0);
        SPFD5408_NVMReadData2::write(0);

        // *** SPFD5408 change -- Begin
        // Not tested yet
        //writeRegister8(ILI9341_INVERTOFF, 0);
        //delay(500);
        // *** SPFD5408 change -- End
        setAddrWindow(0, 0, TFTWIDTH - 1, TFTHEIGHT - 1);
    }
}

void SPFD5408::initIOPort() {
    checkPorts();

    GPIO_InitTypeDef GPIO_InitStructure;
// Configure pin in output push/pull mode
    GPIO_InitStructure.GPIO_Pin = CS_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(CS_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = RS_PIN;
    GPIO_Init(RS_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = WR_PIN;
    GPIO_Init(WR_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = RD_PIN;
    GPIO_Init(RD_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = D0_PIN;
    GPIO_Init(D0_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = D1_PIN;
    GPIO_Init(D1_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = D2_PIN;
    GPIO_Init(D2_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = D3_PIN;
    GPIO_Init(D3_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = D4_PIN;
    GPIO_Init(D4_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = D5_PIN;
    GPIO_Init(D5_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = D6_PIN;
    GPIO_Init(D6_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = D7_PIN;
    GPIO_Init(D7_PORT, &GPIO_InitStructure);

    GPIO_ResetBits(CS_PORT, CS_PIN);
    GPIO_ResetBits(RS_PORT, RS_PIN);
    GPIO_ResetBits(WR_PORT, WR_PIN);
    GPIO_ResetBits(RD_PORT, RD_PIN);
    GPIO_ResetBits(D0_PORT, D0_PIN);
    GPIO_ResetBits(D1_PORT, D1_PIN);
    GPIO_ResetBits(D2_PORT, D2_PIN);
    GPIO_ResetBits(D3_PORT, D3_PIN);
    GPIO_ResetBits(D4_PORT, D4_PIN);
    GPIO_ResetBits(D5_PORT, D5_PIN);
    GPIO_ResetBits(D6_PORT, D6_PIN);
    GPIO_ResetBits(D7_PORT, D7_PIN);
}

void SPFD5408::drawPixel(int16_t x, int16_t y, uint16_t color) {

// Clip
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height))
        return;

    activeCS();
    setAddrWindow(x, y, _width - 1, _height - 1);
    activeCS();

    SDFP5408_COLOR::write(color);

    idleCS();
}

// Sets the LCD address window (and address counter, on 932X).
// Relevant to rect/screen fills and H/V lines.  Input coordinates are
// assumed pre-sorted (e.g. x2 >= x1).
void SPFD5408::setAddrWindow(int x1, int y1, int x2, int y2) {
    activeCS();
    SPFD5408_WindoHStartAddress::write(x1);
    SPFD5408_WindoHEndAddress::write(x2);
    SPFD5408_WindoVEndAddress::write(y1);
    SPFD5408_WindoVEndAddress::write(y2);
    idleCS();
}

void SPFD5408::flood(uint16_t , uint32_t ) {
//  uint16_t blocks;
//  uint8_t  i, hi = color >> 8,
//              lo = color;
//
//  activeCS();
//  command();
//  if (driver == ID_9341) {
//    write8(0x2C);
//  } else if (driver == ID_932X) {
//    write8(0x00); // High byte of GRAM register...
//    write8(0x22); // Write data to GRAM
//  } else if (driver == ID_HX8357D) {
//    write8(HX8357_RAMWR);
//  } else {
//    write8(0x22); // Write data to GRAM
//  }
//
//  // Write first pixel normally, decrement counter by 1
//  CD_DATA;
//  write8(hi);
//  write8(lo);
//  len--;
//
//  blocks = (uint16_t)(len / 64); // 64 pixels/block
//  if(hi == lo) {
//    // High and low bytes are identical.  Leave prior data
//    // on the port(s) and just toggle the write strobe.
//    while(blocks--) {
//      i = 16; // 64 pixels/block / 4 pixels/pass
//      do {
//        WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // 2 bytes/pixel
//        WR_STROBE; WR_STROBE; WR_STROBE; WR_STROBE; // x 4 pixels
//      } while(--i);
//    }
//    // Fill any remaining pixels (1 to 64)
//    for(i = (uint8_t)len & 63; i--; ) {
//      WR_STROBE;
//      WR_STROBE;
//    }
//  } else {
//    while(blocks--) {
//      i = 16; // 64 pixels/block / 4 pixels/pass
//      do {
//        write8(hi); write8(lo); write8(hi); write8(lo);
//        write8(hi); write8(lo); write8(hi); write8(lo);
//      } while(--i);
//    }
//    for(i = (uint8_t)len & 63; i--; ) {
//      write8(hi);
//      write8(lo);
//    }
//  }
//  CS_IDLE;
}

