//
// Created by Nicholas Newdigate on 13/04/2020.
//

#ifndef ARDUINO_MIDI_WRITER_SCOPEVIEW_H
#define ARDUINO_MIDI_WRITER_SCOPEVIEW_H

#include "Arduino.h"
#include <ST7735_t3.h> // Hardware-specific library

#undef swap
#include <functional>
using namespace std;

class AudioLevelView {
public:
    inline AudioLevelView(
            ST7735_t3 &tft,
            int16_t color,
            int16_t backgroundColor,
            int8_t xOffset,
            int8_t yOffset,
            uint8_t height,
            uint8_t width) :
            _tft(&tft),
            _backgroundColor(backgroundColor),
            _color(color),
            _xOffset(xOffset),
            _yOffset(yOffset),
            _height(height),
            _width(width){
    };

    void draw();
    void updateLevel(float newLevel);

private:
    ST7735_t3 *_tft;
    float _currentLevel = 0.0, _previousLevel = 0.0;

    int16_t _backgroundColor;
    int16_t _color;
    int8_t _yOffset;
    int8_t _xOffset;
    uint8_t _height;
    uint8_t _width;
};

#endif //ARDUINO_MIDI_WRITER_SCOPEVIEW_H
