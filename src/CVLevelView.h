//
// Created by Nicholas Newdigate on 13/04/2020.
//

#ifndef TEENSY_AUDIO_DISPLAY_COMPONENTS_CV_LEVEL_VIEW_H
#define TEENSY_AUDIO_DISPLAY_COMPONENTS_CV_LEVEL_VIEW_H

#include "Arduino.h"
#include <ST7735_t3.h> // Hardware-specific library


class CVLevelView {
public:
    inline CVLevelView(
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
    void updateLevel(uint16_t newLevel);

private:
    ST7735_t3 *_tft;
    uint16_t _currentLevel = 0.0, _previousLevel = 0.0;

    uint8_t _top;
    uint8_t _fraction;
    uint16_t _currentHeight;

    int16_t _backgroundColor;
    int16_t _color;
    int8_t _yOffset;
    int8_t _xOffset;
    uint8_t _height;
    uint8_t _width;
};

#endif //TEENSY_AUDIO_DISPLAY_COMPONENTS_CV_LEVEL_VIEW_H
