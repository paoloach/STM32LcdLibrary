/*
 * GFX.h
 *
 *  Created on: 23 gen 2017
 *      Author: paolo
 */

#ifndef GFX_H_
#define GFX_H_

#include <stdint.h>
#include "BaseAcccess.h"

enum class LcdID {
    ID_932X, ID_7575, ID_9341, ID_HX8357D, ID_SPFD5408, ID_S6D0129, ID_UNKNOWN
};

enum class RotationId {
    ROT_0, ROT_90, ROT_180, ROT_270
};

enum class DriverQuality {
    OFF,
    SMALL,
    MEDIUM_LOW,
    MEDIUM,
    MEDIUM_HIGH,
    HIGHT
};

struct Font {
    uint8_t xSize;
    uint8_t ySize;
    uint8_t offset;
    uint16_t numchars;
    bool row;
    const uint8_t * data;
};




class Color6Bit {
private:
    uint8_t components[3];
public:
    Color6Bit(uint8_t red, uint8_t blue, uint8_t green) {
        components[0] = red;
        components[1] = green;
        components[2] = blue;
    }

    bool operator==(Color6Bit & a) {
        return components[0] == a.components[0] && components[1] == a.components[1] && components[2] == a.components[2];
    }

    bool operator!=(Color6Bit & a) {
        return components[0] != a.components[0] || components[1] != a.components[1] || components[2] != a.components[2];
    }

    uint8_t getRed() {
        return components[0];
    }
    uint8_t getGreen() {
        return components[1];
    }
    uint8_t getBlue() {
        return components[2];
    }
    void setRGB(uint8_t r, uint8_t g, uint8_t b) {
        components[0] = r << 2;
        components[1] = g << 2;
        components[2] = b << 2;
    }
};

class Point {

public:
    constexpr Point(int16_t x, int16_t y) :
            x(x), y(y) {
    }
    constexpr Point(int x, int16_t y) :
            x(x), y(y) {
    }
    constexpr Point(int16_t x, int y) :
            x(x), y(y) {
    }
    constexpr Point(int x, int y) :
            x(x), y(y) {
    }
    constexpr Point() :
            x(0xFFFF), y(0xFFFF) {
    }

    int16_t x;
    int16_t y;
};

class GFX {
public:
    GFX();
    virtual ~GFX() = default;
    static void initIO() {
        initIOPort();
    }

    virtual void drawPixel(Point && point, Color6Bit color) =0;
    virtual void drawFastHLine(Point point, int16_t length, Color6Bit color) = 0;
    virtual void drawFastVLine(Point point, int16_t length, Color6Bit color) = 0;

    void drawLine(Point start, Point end, Color6Bit color);
    void drawCircle(Point center, int16_t r, Color6Bit color);
    void drawCircleHelper(Point center, int16_t r, uint8_t cornername, Color6Bit color);
    void fillCircle(Point center, int16_t r, Color6Bit color);
    void drawRect(Point leftTop, int16_t w, int16_t h, Color6Bit color);
    void fillRect(Point leftTop, int16_t w, int16_t h, Color6Bit color);
    void drawRoundRect(Point leftTop, int16_t w, int16_t h, int16_t r, Color6Bit color);
    void fillRoundRect(Point leftTop, int16_t w, int16_t h, int16_t r, Color6Bit color);
    void drawChar(Point p, unsigned char c, uint8_t size);
    void drawChar(Point p, unsigned char c);
    void setFont(Font * font){this->font = font; }
    void setForeground(Color6Bit color){foreground = color;}
    void setBackground(Color6Bit color){background = color;}
private:
    void fillCircleHelper(Point c, int16_t r, uint8_t cornername, int16_t delta, Color6Bit color);
    void putCharPixel(Point p, uint8_t bits, uint8_t size);
protected:
    LcdID driver;
    RotationId rotation;

    uint16_t width;
    uint16_t height;
    const Font * font;
    Color6Bit foreground;
    Color6Bit background;
};

#endif /* GFX_H_ */
