/*
 * RegisterILI9341.h
 *
 *  Created on: 20 gen 2017
 *      Author: paolo
 */

#ifndef REGISTERILI9341_H_
#define REGISTERILI9341_H_

#include "BaseAcccess.h"
#include <array>

enum class ILI9341_REG {
    NOP = 0,
    Reset = 0x01,
    ReadID = 0x04,
    ReadStatus = 0x09,
    ReadDispPowerMode = 0x0A,
    ReadDispMADCTL = 0x0B,
    ReadDispPixelFormat = 0x0C,
    ReadDispImgFormat = 0x0D,
    ReadDispSignMode = 0x0E,
    ReadDispDiagnostic = 0x0F,
    SleepModeOn = 0x10,
    SleepModeOff = 0x11,
    PartialModeOn = 0x12,
    NormalDispOn = 0x13,
    DispInvertOff = 0x20,
    DispInvertOn = 0x21,
    GammaSet = 0x26,
    DisplayOff = 0x28,
    DisplayOn = 0x29,
    ColAddrSet = 0x2A,
    PageAddrSet = 0x2B,
    ColorSet = 0x2D,
    MemoryRead = 0x2E,
    PartialArea = 0x30,
    ViewScrollDef = 0x33,
    TearOff = 0x34,
    TearOn = 0x35,
    MemAccessCtrl = 0x36,
    VertScrollStartAddr = 0x37,
    IdleOff = 0x38,
    IdleOn = 0x39,
    PixelFormatSet = 0x3A,
    WriteMemCont = 0x3C,
    ReadMemCont = 0x3E,
    SetTearScanline = 0x44,
    GetScanLine = 0x45,
    WriteDisplBrightness = 0x51,
    ReadDisplBrightness = 0x52,
    WriteCtrlDispl = 0x53,
    ReadCtrlDispl = 0x54,
    WriteAdaptBrightness = 0x55,
    ReadAdaptBrightness = 0x56,
    WriteCABCMinBrightness = 0x5E,
    ReadCABCMinBrightness = 0x5F,
    ReadID1 = 0xDA,
    ReadID2 = 0xDB,
    ReadID3 = 0xDC,

};

class RegisterBaseILI9341 {
protected:
    static void writeIndex(uint8_t index) {
        RS_PORT->BRR = RS_PIN;
        WR_PORT->BRR = WR_PIN;
        setData(index);
        WR_PORT->BSRR = WR_PIN;
    }

};

class RegisterReadILI9341 : public RegisterBaseILI9341{
protected:
    static uint8_t readData() {
        RD_PORT->BRR = RD_PIN;
        uint8_t data = ::readData();
        RD_PORT->BSRR = RD_PIN;
        return data;
    }
};

template<ILI9341_REG r>
class RegisterILI9341Apply: public RegisterBaseILI9341 {
public:
    static void apply() {
        RegisterBaseILI9341::writeIndex(static_cast<uint8_t>(index));
    }
private:
    const static ILI9341_REG index = r;
};

template<ILI9341_REG r>
class RegisterILI9341Read3Bytes: public RegisterReadILI9341 {
public:
    static std::array<uint8_t, 3> read() {
        std::array<uint8_t, 3> result;
        RegisterBaseILI9341::writeIndex(static_cast<uint8_t>(index));
        readData();
        result[0] = readData();
        result[1] = readData();
        result[2] = readData();
        return result;
    }
private:
    const static ILI9341_REG index = r;
};

using ILI9341Reset= RegisterILI9341Apply<ILI9341_REG::Reset>;
using ILI9341ReadId= RegisterILI9341Read3Bytes<ILI9341_REG::ReadID>;

#endif /* REGISTERILI9341_H_ */
