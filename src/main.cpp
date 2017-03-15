//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "RegisterILI9325.h"
#include "RegisterILI9341.h"

#include "Timer.h"
#include "SPFD5408.h"
#include "ILI9325.h"
#include "ILI9341.h"
#include "HX8367.h"
#include "TouchScreen.h"

// Definitions visible only within this translation unit.
namespace {
// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ - BLINK_ON_TICKS;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

template<int r>
class GenericRegister {
public:
    static void writeIndex(uint8_t index) {
        RS_PORT->BRR = RS_PIN;
        WR_PORT->BRR = WR_PIN;
        setData(0);
        WR_PORT->BSRR = WR_PIN;
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
        WR_PORT->BRR = WR_PIN;
        setData(index);
        WR_PORT->BSRR = WR_PIN;

    }

    static void writeDataByte(uint8_t byte) {
        RS_PORT->BSRR = RS_PIN;
        WR_PORT->BRR = WR_PIN;
        setData(byte);
        WR_PORT->BSRR = WR_PIN;
    }

    static void writeDataByte(std::vector<uint8_t> & bytes) {
        CS_PORT->BRR = CS_PIN;
        writeIndex(static_cast<uint8_t>(index));
        RS_PORT->BSRR = RS_PIN;
        for (uint8_t byte : bytes) {
            WR_PORT->BRR = WR_PIN;
            setData(byte);
            WR_PORT->BSRR = WR_PIN;
            __asm(
                    "nop\n" // 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
                    "nop\n"// 14 ns at 70 Mhz
            );
        }
    }
    static uint8_t readData() {
        RD_PORT->BRR = RD_PIN;
        uint8_t data = ::readData();
        RD_PORT->BSRR = RD_PIN;
        __asm(
                "nop\n" // 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
                "nop\n"// 14 ns at 70 Mhz
        );
        return data;
    }
    static void read() {
        CS_PORT->BRR = CS_PIN;
        writeIndex(static_cast<uint8_t>(index));
        dataPortToRead();
        RS_PORT->BRR = RS_PIN;

        trace_printf("Reg %02X: ", index);
        for (int i = 0; i < 4; i++) {
            trace_printf("%02X ", readData());
        }
        trace_printf("\n");
        dataPortToWrite();
    }

    static uint16_t read16() {
        CS_PORT->BRR = CS_PIN;
        writeIndex(static_cast<uint8_t>(index));
        dataPortToRead();
        RS_PORT->BRR = RS_PIN;

        uint16_t hi = readData();
        uint16_t low = readData();
        dataPortToWrite();
        return (hi << 8) | low;
    }

    static uint32_t read32() {
        CS_PORT->BRR = CS_PIN;
        writeIndex(static_cast<uint8_t>(index));
        dataPortToRead();
        RS_PORT->BRR = RS_PIN;

        uint32_t a = readData();
        uint32_t b = readData();
        uint32_t c = readData();
        uint32_t d = readData();
        dataPortToWrite();
        return (a << 24) | (b << 16) | (c << 8) | d;
    }

    static uint32_t read40() {
        CS_PORT->BRR = CS_PIN;
        writeIndex(static_cast<uint8_t>(index));
        dataPortToRead();
        RS_PORT->BRR = RS_PIN;

        readData();
        uint32_t a = readData();
        uint32_t b = readData();
        uint32_t c = readData();
        uint32_t d = readData();
        dataPortToWrite();
        return (a << 24) | (b << 16) | (c << 8) | d;
    }

private:
    const static int index = r;
};

static void readID(void);

int main(int argc, char* argv[]) {
    // At this stage the system clock should have already been configured
    // at high speed.
    trace_printf("System clock: %u Hz\n", SystemCoreClock);
    Timer timer;

    timer.start();

    GFX::initIO();

    activeCS();
    resetOn();
    Timer::sleep(5);
    resetOff();
    Timer::sleep(150);
    trace_printf("Read generic register:\n");
    GenericRegister<0>::read();
    GenericRegister<1>::read();
    GenericRegister<0xd3>::read();

    trace_printf("Checking for LCD\n");
    GFX * graphics;
    while (true) {
        if (ILI9341::ILI9341::checkPresence()) {
            trace_printf("Found ILI9341\n");
            graphics = new ILI9341::ILI9341 { };
            break;
        } else if (ILI9325::checkPresence()) {
            trace_printf("Found ILI925\n");
            graphics = new ILI9325 { };
            break;
        } else if (HX8367::HX8367::checkPresence()) {
            trace_printf("Found HX8367\n");
            graphics = new HX8367::HX8367 { };
            break;
        } else {
            readID();
        }

    }

    trace_printf("---  START ----\n");
    graphics->drawLine(Point { 50, 0 }, Point { 100, 100 }, Color6Bit(255, 255, 255));
    graphics->drawFastHLine(Point { 100, 100 }, 100, Color6Bit(255, 0, 0));
    graphics->drawFastHLine(Point { 100, 200 }, 100, Color6Bit(0, 255, 0));
    graphics->drawFastVLine(Point { 100, 100 }, 100, Color6Bit(255, 255, 0));
    graphics->drawFastVLine(Point { 200, 100 }, 100, Color6Bit(255, 255, 0));

    graphics->fillRect(Point { 101, 101 }, 98, 98, Color6Bit(0, 0, 255));

    graphics->drawCircle(Point { 150, 150 }, 47, Color6Bit { 0, 255, 255 });

    graphics->fillRoundRect(Point(10, 150), 50, 20, 10, Color6Bit(255, 0, 2));

    graphics->drawChar( { 10, 250 }, 'c', 1);
    graphics->drawChar( { 20, 250 }, 'i', 1);
    graphics->drawChar( { 30, 250 }, 'a');
    graphics->drawChar( { 40, 250 }, 'o');

    trace_printf("---  END ----\n");

    TouchScreen ts(240, 320);
    while (true) {
        auto point = ts.getPoint();
        trace_printf("touch: %d, %d\n", point.x, point.y);
    }
}

void readID(void) {
    uint16_t ret;
    uint8_t msb;
    activeCS();
    resetOn();
    Timer::sleep(5);
    resetOff();
    Timer::sleep(120);

    uint16_t reg0 = GenericRegister<0>::read16();

    if (reg0 == 0x5408) {          //the SPFD5408 fails the 0xD3D3 test.
        trace_printf("SPFD5408");
        return;
    }
    if (reg0 == 0x5420) {          //the SPFD5420 fails the 0xD3D3 test.
        trace_printf("SPFD5420");
        return;
    }
    if (reg0 == 0x8989) {         //SSD1289 is always 8989
        trace_printf("SSD1289");
        return;
    }
    uint16_t reg67 = GenericRegister<67>::read16();
    if (reg67 == 0x4747) {
        trace_printf("HX8347-A");
        return;
    }
    uint32_t regBF = GenericRegister<0xBF>::read40();
    if (regBF == 0x8357) {         //HX8357B: [xx 01 62 83 57 FF]
        trace_printf("HX8357B");
        return;
    }
    if (regBF == 0x9481) {        //ILI9481: [xx 02 04 94 81 FF]
        trace_printf("ILI9481");
        return;
    }
    if (regBF == 0x1511) {         //?R61511: [xx 02 04 15 11] not tested yet
        trace_printf("R61511");
        return;
    }
    if (regBF == 0x1520) {          //?R61520: [xx 01 22 15 20]
        trace_printf("R61520");
        return;
    }
    if (regBF == 0x1526) {        //?R61526: [xx 01 22 15 26]
        trace_printf("R61526");
        return;
    }
    if (regBF == 0x1581) {        //R61581:  [xx 01 22 15 81]
        trace_printf("R61581");
        return;
    }
    if (regBF == 0x1400) {       //?RM68140:[xx FF 68 14 00] not tested yet
        trace_printf("RM68140");
        return;
    }
    uint32_t regEF = GenericRegister<0xEF>::read40();
    if (regEF == 0x9327) {
        trace_printf("ILI9327");
        return;
    }
    uint32_t reg04 = GenericRegister<0x04>::read32();
    msb = reg04 >> 16;
    ret = reg04;
    if (msb == 0x00 && ret == 0x8000) { //HX8357-D [xx 00 80 00]
        std::vector<uint8_t> cmds = { 0xFF, 0x83, 0x57 };
        GenericRegister<0xB9>::writeDataByte(cmds);
        auto regD0 = GenericRegister<0xD0>::read16();
        if (regD0 == 0x99 || regD0 == 0x90) {
            trace_printf("HX8357");
            return;
        }
    }
    if (ret == 0x1526) {       //R61526 [xx 06 15 26] if I have written NVM
        trace_printf("R61526");
        return;
    }
    if (ret == 0x8552) {      //ST7789V: [xx 85 85 52]
        trace_printf("ST7789V");
        return;
    }
    uint32_t regD3 = GenericRegister<0xD3>::read32();
    msb = regD3 >> 8;
    if (msb == 0x93 || msb == 0x94 || msb == 0x77 || msb == 0x16) {
        trace_printf("ILI9488, 9486, 9340, 9341");
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
