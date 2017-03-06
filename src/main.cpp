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
        );
        return data;
    }
    static void read() {
        CS_PORT->BRR = CS_PIN;
        writeIndex(static_cast<uint8_t>(index));
        dataPortToRead();
        RS_PORT->BRR = RS_PIN;

        trace_printf("Reg %02X: ", index);
        for (int i = 0; i < 2; i++) {
            trace_printf("%02X ", readData());
        }
        trace_printf("\n");
        dataPortToWrite();
    }

private:
    const static int index = r;
}
;

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

    trace_printf("Checking for LCD\n");
    GFX * graphics;
    while (true) {
        if (ILI9341::ILI9341::checkPresence()) {
            trace_printf("Found ILI9341\n");
            graphics = new ILI9341::ILI9341 { };
            break;
        }
        if (ILI9325::checkPresence()) {
            trace_printf("Found ILI925\n");
            graphics = new ILI9325 { };
            break;
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

    TouchScreen ts(240,320);
    while (true){
        auto point = ts.getPoint();
        trace_printf("touch: %d, %d\n", point.x, point.y );
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
