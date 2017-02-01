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

// ----------------------------------------------------------------------------
//
// Standalone STM32F1 led blink sample (trace via DEBUG).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// Then demonstrates how to blink a led with 1 Hz, using a
// continuous loop and SysTick delays.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//
// The external clock frequency is specified as a preprocessor definition
// passed to the compiler via a command line option (see the 'C/C++ General' ->
// 'Paths and Symbols' -> the 'Symbols' tab, if you want to change it).
// The value selected during project creation was HSE_VALUE=8000000.
//
// Note: The default clock settings take the user defined HSE_VALUE and try
// to reach the maximum possible system clock. For the default 8 MHz input
// the result is guaranteed, but for other values it might not be possible,
// so please adjust the PLL settings in system/src/cmsis/system_stm32f10x.c
//

// Definitions visible only within this translation unit.
namespace {
// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ - BLINK_ON_TICKS;
}

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[]) {
    // Send a greeting to the trace device (skipped on Release).
    trace_puts("Hello ARM World!");

    // At this stage the system clock should have already been configured
    // at high speed.
    trace_printf("System clock: %u Hz\n", SystemCoreClock);
    Timer timer;

    timer.start();

    GFX::initIO();

    trace_printf("Check for ILI9325: %04X\n", ILI9325_DriverCodeRead::get());

//    while (ILI9325::checkPresence() == false) {
//        activeCS();
//        ILI9325_DriverCodeRead::get();
//        trace_printf("Check for ILI9325: %04X\n", ILI9325_DriverCodeRead::get());
//        idleCS();
//    }
    trace_printf("Found device");
    ILI9325 graphics { };

    trace_printf("---  START ----\n");
    graphics.drawLine(Point { 50, 0 }, Point { 100, 100 }, Color6Bit(255, 255, 255));
    graphics.drawFastHLine(Point { 100, 100 }, 100, Color6Bit(255, 0, 0));
    graphics.drawFastHLine(Point { 100, 200 }, 100, Color6Bit(0, 255, 0));
    graphics.drawFastVLine(Point { 100, 100 }, 100, Color6Bit(255, 255, 0));
    graphics.drawFastVLine(Point { 200, 100 }, 100, Color6Bit(255, 255, 0));

    graphics.fillRect(101, 101, 98, 98, Color6Bit(0, 0, 255));

    graphics.drawCircle(Point { 150, 150 }, 47, Color6Bit { 0, 255, 255 });

    graphics.fillRoundRect(Point(10, 150), 50, 20, 10, Color6Bit(255, 0, 2));

    graphics.drawChar( { 10, 250 }, 'c', 1);
    graphics.drawChar( { 20, 250 }, 'i', 1);
    graphics.drawChar( { 30, 250 }, 'a');
    graphics.drawChar( { 40, 250 }, 'o');


    trace_printf("---  END ----\n");
    while (true){
        trace_printf("SMALL\n");
        graphics.setDriverQuality(DriverQuality::SMALL);
        Timer::sleep(2000);
        trace_printf("HIGHT\n");
        graphics.setDriverQuality(DriverQuality::HIGHT);
        Timer::sleep(2000);
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
