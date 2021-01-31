//
// Created by Nicholas Newdigate on 13/04/2020.
//

#ifndef TEENSY_AUDIO_DISPLAY_COMPONENTS_AUDIO_ANNOTATION_LEVEL_VIEW_H
#define TEENSY_AUDIO_DISPLAY_COMPONENTS_AUDIO_ANNOTATION_LEVEL_VIEW_H

#include "Arduino.h"
#include <ST7735_t3.h> // Hardware-specific library

#undef swap
#include <functional>
using namespace std;

class AudioLevelAnnotationView {
public:
    inline AudioLevelAnnotationView(
            ST7735_t3 &tft,
            int16_t color,
            int8_t xOffset,
            int8_t yOffset,
            uint8_t height,
            uint8_t width) :
            _tft(&tft),
            _color(color),
            _xOffset(xOffset),
            _yOffset(yOffset),
            _height(height),
            _width(width){
    };

    void draw();

private:
    ST7735_t3 *_tft;

    int16_t _color;
    int8_t _yOffset;
    int8_t _xOffset;
    uint8_t _height;
    uint8_t _width;
};

#endif //TEENSY_AUDIO_DISPLAY_COMPONENTS_AUDIO_ANNOTATION_LEVEL_VIEW_H
