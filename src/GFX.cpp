/*
 * GFX.cpp
 *
 *  Created on: 23 gen 2017
 *      Author: paolo
 */
#include <stdlib.h>
#include <algorithm>
#include "GFX.h"

const static uint8_t font16_16Data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //  <Space>
        0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x0F, 0x80, 0x0F, 0x80, 0x0F, 0x80, 0x0F, 0x80, 0x0F, 0x80, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, // !
        0x00, 0x00, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x06, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "
        0x00, 0x00, 0x0C, 0x30, 0x0C, 0x30, 0x0C, 0x30, 0x7F, 0xFE, 0x7F, 0xFE, 0x0C, 0x30, 0x0C, 0x30, 0x0C, 0x30, 0x0C, 0x30, 0x7F, 0xFE, 0x7F, 0xFE, 0x0C, 0x30, 0x0C, 0x30, 0x0C, 0x30, 0x00, 0x00, // #
        0x00, 0x00, 0x02, 0x40, 0x02, 0x40, 0x0F, 0xF8, 0x1F, 0xF8, 0x1A, 0x40, 0x1A, 0x40, 0x1F, 0xF0, 0x0F, 0xF8, 0x02, 0x58, 0x02, 0x58, 0x1F, 0xF8, 0x1F, 0xF0, 0x02, 0x40, 0x02, 0x40, 0x00, 0x00, // $
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x10, 0x0E, 0x30, 0x0E, 0x70, 0x00, 0xE0, 0x01, 0xC0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x70, 0x0C, 0x70, 0x08, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // %
        0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x19, 0x80, 0x19, 0x80, 0x19, 0x80, 0x0F, 0x00, 0x0F, 0x08, 0x0F, 0x98, 0x19, 0xF8, 0x18, 0xF0, 0x18, 0xE0, 0x19, 0xF0, 0x0F, 0x98, 0x00, 0x00, 0x00, 0x00, // &
        0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // '
        0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x01, 0xC0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x07, 0x00, 0x03, 0x80, 0x01, 0xC0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, // (
        0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x03, 0x80, 0x01, 0xC0, 0x00, 0xE0, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0xE0, 0x01, 0xC0, 0x03, 0x80, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, // )
        0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x11, 0x88, 0x09, 0x90, 0x07, 0xE0, 0x07, 0xE0, 0x3F, 0xFC, 0x3F, 0xFC, 0x07, 0xE0, 0x07, 0xE0, 0x09, 0x90, 0x11, 0x88, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, // *
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x0F, 0xF0, 0x0F, 0xF0, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // +
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x0E, 0x00, 0x00, 0x00, // ,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // -
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, // ,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0x00, 0xE0, 0x01, 0xC0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, // /

        0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x1C, 0x38, 0x1C, 0x78, 0x1C, 0xF8, 0x1C, 0xF8, 0x1D, 0xB8, 0x1D, 0xB8, 0x1F, 0x38, 0x1F, 0x38, 0x1E, 0x38, 0x1C, 0x38, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, // 0
        0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x01, 0x80, 0x03, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x1F, 0xF0, 0x00, 0x00, 0x00, 0x00, // 1
        0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x1C, 0x70, 0x1C, 0x38, 0x00, 0x38, 0x00, 0x70, 0x00, 0xE0, 0x01, 0xC0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x38, 0x1C, 0x38, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00, // 2
        0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x1C, 0x70, 0x1C, 0x38, 0x00, 0x38, 0x00, 0x70, 0x03, 0xC0, 0x03, 0xC0, 0x00, 0x70, 0x00, 0x38, 0x1C, 0x38, 0x1C, 0x70, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, // 3
        0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0xE0, 0x03, 0xE0, 0x06, 0xE0, 0x0C, 0xE0, 0x18, 0xE0, 0x1F, 0xF8, 0x1F, 0xF8, 0x00, 0xE0, 0x00, 0xE0, 0x00, 0xE0, 0x03, 0xF8, 0x00, 0x00, 0x00, 0x00, // 4
        0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1F, 0xE0, 0x1F, 0xF0, 0x00, 0x78, 0x00, 0x38, 0x1C, 0x38, 0x1C, 0x70, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, // 5
        0x00, 0x00, 0x00, 0x00, 0x03, 0xE0, 0x07, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1F, 0xF0, 0x1F, 0xF8, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, // 6
        0x00, 0x00, 0x00, 0x00, 0x1F, 0xFC, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0x00, 0xE0, 0x01, 0xC0, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, // 7
        0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x1F, 0x38, 0x07, 0xE0, 0x07, 0xE0, 0x1C, 0xF8, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, // 8
        0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x1F, 0xF8, 0x0F, 0xF8, 0x00, 0x38, 0x00, 0x38, 0x00, 0x70, 0x00, 0xE0, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, // 9
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // :
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ;
        0x00, 0x00, 0x00, 0x70, 0x00, 0xE0, 0x01, 0xC0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x07, 0x00, 0x03, 0x80, 0x01, 0xC0, 0x00, 0xE0, 0x00, 0x70, 0x00, 0x00, // <
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // =
        0x00, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x07, 0x00, 0x03, 0x80, 0x01, 0xC0, 0x00, 0xE0, 0x00, 0x70, 0x00, 0x70, 0x00, 0xE0, 0x01, 0xC0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00, 0x1C, 0x00, 0x00, 0x00, // >
        0x00, 0x00, 0x03, 0xC0, 0x0F, 0xF0, 0x1E, 0x78, 0x18, 0x38, 0x00, 0x38, 0x00, 0x70, 0x00, 0xE0, 0x01, 0xC0, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x00, 0x00, // ?

        0x00, 0x00, 0x0F, 0xF8, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0xFC, 0x1C, 0xFC, 0x1C, 0xFC, 0x1C, 0xFC, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1F, 0xF0, 0x07, 0xF8, 0x00, 0x00, // @
        0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x07, 0xE0, 0x0E, 0x70, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x1F, 0xF8, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x00, 0x00, 0x00, 0x00, // A
        0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0F, 0xF0, 0x0F, 0xF0, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x1F, 0xF0, 0x00, 0x00, 0x00, 0x00, // B
        0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x0E, 0x38, 0x1C, 0x38, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x38, 0x0E, 0x38, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, // C
        0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0x0E, 0x70, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x70, 0x1F, 0xE0, 0x00, 0x00, 0x00, 0x00, // D
        0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x0E, 0x18, 0x0E, 0x08, 0x0E, 0x00, 0x0E, 0x30, 0x0F, 0xF0, 0x0F, 0xF0, 0x0E, 0x30, 0x0E, 0x00, 0x0E, 0x08, 0x0E, 0x18, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00, // E
        0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x0E, 0x18, 0x0E, 0x08, 0x0E, 0x00, 0x0E, 0x30, 0x0F, 0xF0, 0x0F, 0xF0, 0x0E, 0x30, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, // F
        0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x0E, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0xF8, 0x1C, 0x38, 0x1C, 0x38, 0x0E, 0x38, 0x07, 0xF8, 0x00, 0x00, 0x00, 0x00, // G
        0x00, 0x00, 0x00, 0x00, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1F, 0xF0, 0x1F, 0xF0, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x00, 0x00, 0x00, 0x00, // H
        0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, // I
        0x00, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x38, 0x70, 0x38, 0x70, 0x38, 0x70, 0x38, 0x70, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, // J
        0x00, 0x00, 0x00, 0x00, 0x1E, 0x38, 0x0E, 0x38, 0x0E, 0x70, 0x0E, 0xE0, 0x0F, 0xC0, 0x0F, 0x80, 0x0F, 0x80, 0x0F, 0xC0, 0x0E, 0xE0, 0x0E, 0x70, 0x0E, 0x38, 0x1E, 0x38, 0x00, 0x00, 0x00, 0x00, // K
        0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x08, 0x0E, 0x18, 0x0E, 0x38, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00, // L
        0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x1E, 0x3C, 0x1F, 0x7C, 0x1F, 0xFC, 0x1F, 0xFC, 0x1D, 0xDC, 0x1C, 0x9C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, // M
        0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x1C, 0x1C, 0x1E, 0x1C, 0x1F, 0x1C, 0x1F, 0x9C, 0x1D, 0xDC, 0x1C, 0xFC, 0x1C, 0x7C, 0x1C, 0x3C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, // N
        0x00, 0x00, 0x00, 0x00, 0x03, 0xE0, 0x07, 0xF0, 0x0E, 0x38, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x0E, 0x38, 0x07, 0xF0, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x00, // O

        0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0F, 0xF0, 0x0F, 0xF0, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, // P
        0x00, 0x00, 0x00, 0x00, 0x03, 0xE0, 0x0F, 0x78, 0x0E, 0x38, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x7C, 0x1C, 0xFC, 0x0F, 0xF8, 0x0F, 0xF8, 0x00, 0x38, 0x00, 0xFC, 0x00, 0x00, // Q
        0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0F, 0xF0, 0x0F, 0xF0, 0x0E, 0x70, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x1E, 0x38, 0x00, 0x00, 0x00, 0x00, // R
        0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x00, 0x0F, 0xE0, 0x07, 0xF0, 0x00, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x1C, 0x38, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, // S
        0x00, 0x00, 0x00, 0x00, 0x1F, 0xFC, 0x19, 0xCC, 0x11, 0xC4, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, // T
        0x00, 0x00, 0x00, 0x00, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, // U
        0x00, 0x00, 0x00, 0x00, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x0E, 0xE0, 0x07, 0xC0, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, // V
        0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x9C, 0x1C, 0x9C, 0x1C, 0x9C, 0x0F, 0xF8, 0x0F, 0xF8, 0x07, 0x70, 0x07, 0x70, 0x00, 0x00, 0x00, 0x00, // W
        0x00, 0x00, 0x00, 0x00, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x0E, 0xE0, 0x07, 0xC0, 0x03, 0x80, 0x03, 0x80, 0x07, 0xC0, 0x0E, 0xE0, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x00, 0x00, 0x00, 0x00, // X
        0x00, 0x00, 0x00, 0x00, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x0E, 0xE0, 0x07, 0xC0, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, // Y
        0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x1C, 0x38, 0x18, 0x38, 0x10, 0x70, 0x00, 0xE0, 0x01, 0xC0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x08, 0x1C, 0x18, 0x1C, 0x38, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00, // Z
        0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, // [
        0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x18, 0x00, 0x1C, 0x00, 0x0E, 0x00, 0x07, 0x00, 0x03, 0x80, 0x01, 0xC0, 0x00, 0xE0, 0x00, 0x70, 0x00, 0x38, 0x00, 0x1C, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, // <Backslash>
        0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, // ]
        0x00, 0x00, 0x01, 0x80, 0x03, 0xC0, 0x07, 0xE0, 0x0E, 0x70, 0x1C, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ^
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x7F, 0xFF, // _

        0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // '
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x70, 0x00, 0x70, 0x0F, 0xF0, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x0F, 0xD8, 0x00, 0x00, 0x00, 0x00, // a
        0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0F, 0xF0, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x1B, 0xF0, 0x00, 0x00, 0x00, 0x00, // b
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x70, 0x1C, 0x70, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, // c
        0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x0F, 0xF0, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x0F, 0xD8, 0x00, 0x00, 0x00, 0x00, // d
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x1C, 0x70, 0x1C, 0x70, 0x1F, 0xF0, 0x1C, 0x00, 0x1C, 0x70, 0x1C, 0x70, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, // e
        0x00, 0x00, 0x00, 0x00, 0x03, 0xE0, 0x07, 0x70, 0x07, 0x70, 0x07, 0x00, 0x07, 0x00, 0x1F, 0xE0, 0x1F, 0xE0, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x1F, 0xC0, 0x00, 0x00, 0x00, 0x00, // f
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xD8, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x0F, 0xF0, 0x07, 0xF0, 0x00, 0x70, 0x1C, 0x70, 0x0F, 0xE0, // g
        0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0xF0, 0x0F, 0x38, 0x0F, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x1E, 0x38, 0x00, 0x00, 0x00, 0x00, // h
        0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x00, 0x00, 0x0F, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00, // i
        0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x00, 0x03, 0xF0, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x00, 0x70, 0x1C, 0x70, 0x0C, 0xF0, 0x07, 0xE0, // j
        0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x38, 0x0E, 0x70, 0x0E, 0xE0, 0x0F, 0xC0, 0x0E, 0xE0, 0x0E, 0x70, 0x0E, 0x38, 0x1E, 0x38, 0x00, 0x00, 0x00, 0x00, // k
        0x00, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00, // l
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x1C, 0x9C, 0x1C, 0x9C, 0x1C, 0x9C, 0x1C, 0x9C, 0x1C, 0x9C, 0x1C, 0x9C, 0x1C, 0x9C, 0x00, 0x00, 0x00, 0x00, // m
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x00, 0x00, 0x00, 0x00, // n
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, // o

        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0xF0, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0F, 0xF0, 0x0E, 0x00, 0x0E, 0x00, 0x1F, 0x00, // p
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xB0, 0x38, 0xE0, 0x38, 0xE0, 0x38, 0xE0, 0x38, 0xE0, 0x38, 0xE0, 0x1F, 0xE0, 0x00, 0xE0, 0x00, 0xE0, 0x01, 0xF0, // q
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0xF0, 0x0F, 0xF8, 0x0F, 0x38, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, // r
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x1C, 0x30, 0x1C, 0x30, 0x0F, 0x80, 0x03, 0xE0, 0x18, 0x70, 0x18, 0x70, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, // s
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x07, 0x00, 0x1F, 0xF0, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x70, 0x07, 0x70, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x00, // t
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x0F, 0xD8, 0x00, 0x00, 0x00, 0x00, // u
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x1C, 0x70, 0x0E, 0xE0, 0x07, 0xC0, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, // v
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x9C, 0x1C, 0x9C, 0x0F, 0xF8, 0x07, 0x70, 0x07, 0x70, 0x00, 0x00, 0x00, 0x00, // w
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xE0, 0x1C, 0xE0, 0x0F, 0xC0, 0x07, 0x80, 0x07, 0x80, 0x0F, 0xC0, 0x1C, 0xE0, 0x1C, 0xE0, 0x00, 0x00, 0x00, 0x00, // x
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x0E, 0x38, 0x07, 0xF0, 0x03, 0xE0, 0x00, 0xE0, 0x01, 0xC0, 0x1F, 0x80, // y
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0x18, 0xE0, 0x11, 0xC0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x20, 0x1C, 0x60, 0x1F, 0xE0, 0x00, 0x00, 0x00, 0x00, // z
        0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x07, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x07, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x01, 0xF8, 0x00, 0x00, 0x00, 0x00, // {
        0x00, 0x00, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x00, 0x00, // |
        0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x00, 0xE0, 0x00, 0x38, 0x00, 0x38, 0x00, 0xE0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00, // }
        0x00, 0x00, 0x00, 0x00, 0x1F, 0x1C, 0x3B, 0x9C, 0x39, 0xDC, 0x38, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ~
        };

const unsigned char font8_12Data[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // <Space>
        0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20, 0x00, 0x00, // !
        0x00, 0x28, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "
        0x00, 0x00, 0x28, 0x28, 0xFC, 0x28, 0x50, 0xFC, 0x50, 0x50, 0x00, 0x00, // #
        0x00, 0x20, 0x78, 0xA8, 0xA0, 0x60, 0x30, 0x28, 0xA8, 0xF0, 0x20, 0x00, // $
        0x00, 0x00, 0x48, 0xA8, 0xB0, 0x50, 0x28, 0x34, 0x54, 0x48, 0x00, 0x00, // %
        0x00, 0x00, 0x20, 0x50, 0x50, 0x78, 0xA8, 0xA8, 0x90, 0x6C, 0x00, 0x00, // &
        0x00, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // '
        0x00, 0x04, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x04, 0x00, // (
        0x00, 0x40, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x40, 0x00, // )
        0x00, 0x00, 0x00, 0x20, 0xA8, 0x70, 0x70, 0xA8, 0x20, 0x00, 0x00, 0x00, // *
        0x00, 0x00, 0x20, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, // +
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x80, // ,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // -
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, // .
        0x00, 0x08, 0x10, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x80, 0x00, // /
        0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, // 0
        0x00, 0x00, 0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00, // 1
        0x00, 0x00, 0x70, 0x88, 0x88, 0x10, 0x20, 0x40, 0x80, 0xF8, 0x00, 0x00, // 2
        0x00, 0x00, 0x70, 0x88, 0x08, 0x30, 0x08, 0x08, 0x88, 0x70, 0x00, 0x00, // 3
        0x00, 0x00, 0x10, 0x30, 0x50, 0x50, 0x90, 0x78, 0x10, 0x18, 0x00, 0x00, // 4
        0x00, 0x00, 0xF8, 0x80, 0x80, 0xF0, 0x08, 0x08, 0x88, 0x70, 0x00, 0x00, // 5
        0x00, 0x00, 0x70, 0x90, 0x80, 0xF0, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, // 6
        0x00, 0x00, 0xF8, 0x90, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, // 7
        0x00, 0x00, 0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, // 8
        0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x78, 0x08, 0x48, 0x70, 0x00, 0x00, // 9
        0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, // :
        0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x20, 0x00, // ;
        0x00, 0x04, 0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00, // <
        0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, // =
        0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00, // >
        0x00, 0x00, 0x70, 0x88, 0x88, 0x10, 0x20, 0x20, 0x00, 0x20, 0x00, 0x00, // ?
        0x00, 0x00, 0x70, 0x88, 0x98, 0xA8, 0xA8, 0xB8, 0x80, 0x78, 0x00, 0x00, // @
        0x00, 0x00, 0x20, 0x20, 0x30, 0x50, 0x50, 0x78, 0x48, 0xCC, 0x00, 0x00, // A
        0x00, 0x00, 0xF0, 0x48, 0x48, 0x70, 0x48, 0x48, 0x48, 0xF0, 0x00, 0x00, // B
        0x00, 0x00, 0x78, 0x88, 0x80, 0x80, 0x80, 0x80, 0x88, 0x70, 0x00, 0x00, // C
        0x00, 0x00, 0xF0, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0xF0, 0x00, 0x00, // D
        0x00, 0x00, 0xF8, 0x48, 0x50, 0x70, 0x50, 0x40, 0x48, 0xF8, 0x00, 0x00, // E
        0x00, 0x00, 0xF8, 0x48, 0x50, 0x70, 0x50, 0x40, 0x40, 0xE0, 0x00, 0x00, // F
        0x00, 0x00, 0x38, 0x48, 0x80, 0x80, 0x9C, 0x88, 0x48, 0x30, 0x00, 0x00, // G
        0x00, 0x00, 0xCC, 0x48, 0x48, 0x78, 0x48, 0x48, 0x48, 0xCC, 0x00, 0x00, // H
        0x00, 0x00, 0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xF8, 0x00, 0x00, // I
        0x00, 0x00, 0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x90, 0xE0, 0x00, // J
        0x00, 0x00, 0xEC, 0x48, 0x50, 0x60, 0x50, 0x50, 0x48, 0xEC, 0x00, 0x00, // K
        0x00, 0x00, 0xE0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x44, 0xFC, 0x00, 0x00, // L
        0x00, 0x00, 0xD8, 0xD8, 0xD8, 0xD8, 0xA8, 0xA8, 0xA8, 0xA8, 0x00, 0x00, // M
        0x00, 0x00, 0xDC, 0x48, 0x68, 0x68, 0x58, 0x58, 0x48, 0xE8, 0x00, 0x00, // N
        0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, // O
        0x00, 0x00, 0xF0, 0x48, 0x48, 0x70, 0x40, 0x40, 0x40, 0xE0, 0x00, 0x00, // P
        0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x88, 0xE8, 0x98, 0x70, 0x18, 0x00, // Q
        0x00, 0x00, 0xF0, 0x48, 0x48, 0x70, 0x50, 0x48, 0x48, 0xEC, 0x00, 0x00, // R
        0x00, 0x00, 0x78, 0x88, 0x80, 0x60, 0x10, 0x08, 0x88, 0xF0, 0x00, 0x00, // S
        0x00, 0x00, 0xF8, 0xA8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00, // T
        0x00, 0x00, 0xCC, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x30, 0x00, 0x00, // U
        0x00, 0x00, 0xCC, 0x48, 0x48, 0x50, 0x50, 0x30, 0x20, 0x20, 0x00, 0x00, // V
        0x00, 0x00, 0xA8, 0xA8, 0xA8, 0x70, 0x50, 0x50, 0x50, 0x50, 0x00, 0x00, // W
        0x00, 0x00, 0xD8, 0x50, 0x50, 0x20, 0x20, 0x50, 0x50, 0xD8, 0x00, 0x00, // X
        0x00, 0x00, 0xD8, 0x50, 0x50, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00, // Y
        0x00, 0x00, 0xF8, 0x90, 0x10, 0x20, 0x20, 0x40, 0x48, 0xF8, 0x00, 0x00, // Z
        0x00, 0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38, 0x00, // [
        0x00, 0x40, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x10, 0x08, 0x00, 0x00, // <Backslash>
        0x00, 0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00, // ]
        0x00, 0x20, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ^
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, // _
        0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // '
        0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x48, 0x38, 0x48, 0x3C, 0x00, 0x00, // a
        0x00, 0x00, 0xC0, 0x40, 0x40, 0x70, 0x48, 0x48, 0x48, 0x70, 0x00, 0x00, // b
        0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x48, 0x40, 0x40, 0x38, 0x00, 0x00, // c
        0x00, 0x00, 0x18, 0x08, 0x08, 0x38, 0x48, 0x48, 0x48, 0x3C, 0x00, 0x00, // d
        0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x48, 0x78, 0x40, 0x38, 0x00, 0x00, // e
        0x00, 0x00, 0x1C, 0x20, 0x20, 0x78, 0x20, 0x20, 0x20, 0x78, 0x00, 0x00, // f
        0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x48, 0x30, 0x40, 0x78, 0x44, 0x38, // g
        0x00, 0x00, 0xC0, 0x40, 0x40, 0x70, 0x48, 0x48, 0x48, 0xEC, 0x00, 0x00, // h
        0x00, 0x00, 0x20, 0x00, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00, // i
        0x00, 0x00, 0x10, 0x00, 0x00, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0xE0, // j
        0x00, 0x00, 0xC0, 0x40, 0x40, 0x5C, 0x50, 0x70, 0x48, 0xEC, 0x00, 0x00, // k
        0x00, 0x00, 0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xF8, 0x00, 0x00, // l
        0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xA8, 0xA8, 0xA8, 0xA8, 0x00, 0x00, // m
        0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x48, 0x48, 0x48, 0xEC, 0x00, 0x00, // n
        0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x48, 0x48, 0x48, 0x30, 0x00, 0x00, // o
        0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x48, 0x48, 0x48, 0x70, 0x40, 0xE0, // p
        0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x48, 0x48, 0x48, 0x38, 0x08, 0x1C, // q
        0x00, 0x00, 0x00, 0x00, 0x00, 0xD8, 0x60, 0x40, 0x40, 0xE0, 0x00, 0x00, // r
        0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x40, 0x30, 0x08, 0x78, 0x00, 0x00, // s
        0x00, 0x00, 0x00, 0x20, 0x20, 0x70, 0x20, 0x20, 0x20, 0x18, 0x00, 0x00, // t
        0x00, 0x00, 0x00, 0x00, 0x00, 0xD8, 0x48, 0x48, 0x48, 0x3C, 0x00, 0x00, // u
        0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0x48, 0x50, 0x30, 0x20, 0x00, 0x00, // v
        0x00, 0x00, 0x00, 0x00, 0x00, 0xA8, 0xA8, 0x70, 0x50, 0x50, 0x00, 0x00, // w
        0x00, 0x00, 0x00, 0x00, 0x00, 0xD8, 0x50, 0x20, 0x50, 0xD8, 0x00, 0x00, // x
        0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0x48, 0x50, 0x30, 0x20, 0x20, 0xC0, // y
        0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x10, 0x20, 0x20, 0x78, 0x00, 0x00, // z
        0x00, 0x18, 0x10, 0x10, 0x10, 0x20, 0x10, 0x10, 0x10, 0x10, 0x18, 0x00, // {
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, // |
        0x00, 0x60, 0x20, 0x20, 0x20, 0x10, 0x20, 0x20, 0x20, 0x20, 0x60, 0x00, // }
        0x40, 0xA4, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ~
        };

const Font bigFont = { 16, 16, 0x20, 0x5F, false, font16_16Data };
const Font smallFont = { 8, 12, 0x20, 0x5F, false, font8_12Data };

GFX::GFX() :
        foreground(255, 255, 255), background(0, 0, 0) {
    driver = LcdID::ID_UNKNOWN;
    width = 0xFFFF;
    height = 0xFFFF;
    font = &bigFont;
}

void GFX::drawFastVLine(Point p, uint16_t length, Color6Bit color) {
    int16_t y2;

    // Initial off-screen clipping
    if ((p.x < 0) || (p.x >= width) || (p.y >= height) || ((y2 = (p.y + length - 1)) < 0))
        return;
    if (p.y < 0) {
        length += p.y;
        p.y = 0;
    }
    if (y2 >= height) {
        y2 = height - 1;
        length = y2 - p.y + 1;
    }

    p.x = width - p.x;
    activeCS();
    setAddrWindow(p.x, p.y, p.x, y2);
    flood(color, length);
    idleCS();
}

void GFX::drawFastHLine(Point p, uint16_t length, Color6Bit color) {
    int16_t x2;

    // Initial off-screen clipping
    if ((p.y < 0) || (p.y >= height) || (p.x >= width) || ((x2 = (p.x + length - 1)) < 0))
        return;

    if (p.x < 0) {        // Clip left
        length += p.x;
        p.x = 0;
    }
    if (x2 >= width) { // Clip right
        x2 = width - 1;
        length = x2 - p.x + 1;
    }

    activeCS();
    setAddrWindow(p.x, p.y, x2, p.y);
    flood(color, length);
    idleCS();
}

void GFX::drawCircle(Point center, int16_t r, Color6Bit color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    Point p { 0, r };

    drawPixel(Point(center.x, center.y + r), color);
    drawPixel(Point(center.x, center.y - r), color);
    drawPixel(Point(center.x + r, center.y), color);
    drawPixel(Point(center.x - r, center.y), color);

    while (p.x < p.y) {
        if (f >= 0) {
            p.y--;
            ddF_y += 2;
            f += ddF_y;
        }
        p.x++;
        ddF_x += 2;
        f += ddF_x;

        drawPixel(Point { center.x + p.x, center.y + p.y }, color);
        drawPixel(Point { center.x - p.x, center.y + p.y }, color);
        drawPixel(Point { center.x + p.x, center.y - p.y }, color);
        drawPixel(Point { center.x - p.x, center.y - p.y }, color);
        drawPixel(Point { center.x + p.y, center.y + p.x }, color);
        drawPixel(Point { center.x - p.y, center.y + p.x }, color);
        drawPixel(Point { center.x + p.y, center.y - p.x }, color);
        drawPixel(Point { center.x - p.y, center.y - p.x }, color);

    }
}

void GFX::fillCircle(Point c, int16_t r, Color6Bit color) {
    drawFastVLine(Point { c.x, c.y - r }, 2 * r + 1, color);

    fillCircleHelper(c, r, 3, 0, color);
}

void GFX::fillCircleHelper(Point c, int16_t r, uint8_t cornername, int16_t delta, Color6Bit color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        if (cornername & 0x1) {
            drawFastVLine(Point { c.x + x, c.y - y }, 2 * y + 1 + delta, color);
            drawFastVLine(Point { c.x + y, c.y - x }, 2 * x + 1 + delta, color);
        }
        if (cornername & 0x2) {
            drawFastVLine(Point { c.x - x, c.y - y }, 2 * y + 1 + delta, color);
            drawFastVLine(Point { c.x - y, c.y - x }, 2 * x + 1 + delta, color);
        }
    }
}

// Bresenham's algorithm
void GFX::drawLine(Point start, Point end, Color6Bit color) {
    int16_t steep = abs(end.y - start.y) > abs(end.x - start.x);
    if (steep) {
        std::swap(start.x, start.y);
        std::swap(end.x, end.y);
    }

    if (start.x > end.x) {
        std::swap(start.x, end.x);
        std::swap(start.y, end.y);
    }

    int16_t dx, dy;
    dx = end.x - start.x;
    dy = abs(end.y - start.y);

    int16_t err = dx / 2;
    int16_t ystep;

    if (start.y < end.y) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; start.x <= end.x; start.x++) {
        if (steep) {
            drawPixel(Point { start }, color);
        } else {
            drawPixel(Point { start }, color);
        }
        err -= dy;
        if (err < 0) {
            start.y += ystep;
            err += dx;
        }
    }
}

void GFX::drawCircleHelper(Point center, int16_t r, uint8_t cornername, Color6Bit color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        if (cornername & 0x4) {
            drawPixel(Point { center.x + x, center.y + y }, color);
            drawPixel(Point { center.x + y, center.y + x }, color);
        }
        if (cornername & 0x2) {
            drawPixel(Point { center.x + x, center.y - y }, color);
            drawPixel(Point { center.x + y, center.y - x }, color);
        }
        if (cornername & 0x8) {
            drawPixel(Point { center.x - y, center.y + x }, color);
            drawPixel(Point { center.x - x, center.y + y }, color);
        }
        if (cornername & 0x1) {
            drawPixel(Point { center.x - y, center.y - x }, color);
            drawPixel(Point { center.x - x, center.y - y }, color);
        }
    }
}

void GFX::drawRect(Point leftTop, int16_t w, int16_t h, Color6Bit color) {
    drawFastHLine(leftTop, w, color);
    drawFastHLine(Point { leftTop.x, leftTop.y + h - 1 }, w, color);
    drawFastVLine(leftTop, h, color);
    drawFastVLine(Point { leftTop.x + w - 1, leftTop.y }, h, color);
}

void GFX::fillRect(Point && leftTop, int16_t w, int16_t h, Color6Bit color) {
    int16_t x2, y2;

    if ((w <= 0) || (h <= 0) || (leftTop.x >= width) || (leftTop.y >= height) || ((x2 = leftTop.x + w - 1) < 0) || ((y2 = leftTop.y + h - 1) < 0))
        return;
    if (leftTop.x < 0) {
        w += leftTop.x;
        leftTop.x = 0;
    }
    if (leftTop.y < 0) {
        h += leftTop.y;
        leftTop.y = 0;
    }
    if (x2 >= width) {
        x2 = width - 1;
        w = x2 - leftTop.x + 1;
    }
    if (y2 >= height) {
        y2 = height - 1;
        h = y2 - leftTop.y + 1;
    }

    x2 = width - x2;

    activeCS();
    setAddrWindow(leftTop.x, leftTop.y, x2, y2);
    flood(color, w * h);
    setAddrWindow(0, 0, width - 1, height - 1);
    idleCS();
}

void GFX::drawRoundRect(Point leftTop, int16_t w, int16_t h, int16_t r, Color6Bit color) {
    // smarter version
    drawFastHLine(Point { leftTop.x + r, leftTop.y }, w - 2 * r, color); // Top
    drawFastHLine(Point { leftTop.x + r, leftTop.y + h - 1 }, w - 2 * r, color); // Bottom
    drawFastVLine(Point { leftTop.x, leftTop.y + r }, h - 2 * r, color); // Left
    drawFastVLine(Point { leftTop.x + w - 1, leftTop.y + r }, h - 2 * r, color); // Right
    // draw four corners
    drawCircleHelper(Point { leftTop.x + r, leftTop.y + r }, r, 1, color);
    drawCircleHelper(Point { leftTop.x + w - r - 1, leftTop.y + r }, r, 2, color);
    drawCircleHelper(Point { leftTop.x + w - r - 1, leftTop.y + h - r - 1 }, r, 4, color);
    drawCircleHelper(Point { leftTop.x + r, leftTop.y + h - r - 1 }, r, 8, color);
}

void GFX::fillRoundRect(Point leftTop, int16_t w, int16_t h, int16_t r, Color6Bit color) {
    fillRect(Point(leftTop.x + r, leftTop.y), w - 2 * r, h, color);
    fillCircleHelper(Point { leftTop.x + w - r - 1, leftTop.y + r }, r, 1, h - 2 * r - 1, color);
    fillCircleHelper(Point { leftTop.x + r, leftTop.y + r }, r, 2, h - 2 * r - 1, color);
}

void GFX::drawChar(Point p, unsigned char c, uint8_t size) {
    if ((p.x >= width) || (p.y >= height) || ((p.x + font->xSize * size - 1) < 0) || ((p.y + font->ySize * size - 1) < 0))
        return;

    if (c < font->offset)
        return;
    c -= font->offset;
    if (c > font->numchars)
        return;

    uint8_t dataLen = (font->xSize * font->ySize) / 8;
    const uint8_t * data = font->data + dataLen * c;
    Point pixelPos = p;
    int8_t x;
    int8_t y;
    if (font->row) {
        for (pixelPos.x = p.x, x = 0; x < font->xSize; x++, pixelPos.x += size) {
            uint8_t bit = 1;
            uint8_t row = *data;
            for (pixelPos.y = p.y, y = 0; y < font->xSize; y++, pixelPos.y += size) {
                putCharPixel(pixelPos, row, size);
                row >>= 1;
                bit++;
                if (bit == 8) {
                    data++;
                    row = *data;
                    bit = 0;
                }
            }
        }
    } else {
        for (pixelPos.y = p.y, y = 0; y < font->ySize; y++, pixelPos.y += size) {
            uint8_t bit = 1;
            uint8_t col = *data;
            for (pixelPos.x = p.x, x = 0; x < font->xSize; x++, pixelPos.x += size) {
                putCharPixel(pixelPos, col, size);
                col <<= 1;
                bit++;
                if (bit == 8) {
                    data++;
                    col = *data;
                    bit = 0;
                }
            }
        }
    }
}

void GFX::drawString(Point && p, const char * s) {
    while (*s != 0) {
        drawChar(p, *s);
        p.x += font->xSize;
        s++;
    }
}

void GFX::drawChar(Point p, unsigned char c) {
    if ((p.x >= width) || (p.y >= height) || ((p.x + font->xSize - 1) < 0) || ((p.y + font->ySize - 1) < 0))
        return;

    if (c < font->offset)
        return;
    c -= font->offset;
    if (c > font->numchars)
        return;

    uint8_t dataLen = (font->xSize * font->ySize) / 8;
    const uint8_t * data = font->data + dataLen * c;
    Point pixelPos = p;
    int8_t x;
    int8_t y;
    if (font->row) {
        for (pixelPos.x = p.x, x = 0; x < font->xSize; x++, pixelPos.x++) {
            uint8_t bit = 1;
            uint8_t row = *data;
            for (pixelPos.y = p.y, y = 0; y < font->xSize; y++, pixelPos.y++) {
                putCharPixel(pixelPos, row, 1);
                row >>= 1;
                bit++;
                if (bit == 8) {
                    data++;
                    row = *data;
                    bit = 0;
                }
            }
        }
    } else {
        for (pixelPos.y = p.y, y = 0; y < font->ySize; y++, pixelPos.y++) {
            uint8_t bit = 1;
            uint8_t col = *data;
            for (pixelPos.x = p.x, x = 0; x < font->xSize; x++, pixelPos.x++) {
                putCharPixel(pixelPos, col, 1);
                col <<= 1;
                bit++;
                if (bit == 8) {
                    data++;
                    col = *data;
                    bit = 0;
                }
            }
        }
    }
}

void GFX::putCharPixel(Point p, uint8_t bits, uint8_t size) {
    if (bits & 0x80) {
        if (size == 1)
            drawPixel(Point { p }, foreground);
        else {
            fillRect(Point { p }, size, size, foreground);
        }
    } else if (background != foreground) {
        if (size == 1)
            drawPixel(Point { p }, background);
        else {
            fillRect(Point { p }, size, size, background);
        }
    }
}
