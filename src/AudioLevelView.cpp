#include "AudioLevelView.h"
#include "alphaBlendRGB565.h"

void AudioLevelView::draw() {
    if (_currentLevel < 0.0) return;

    int currentHeight = int(1.0/log(10.0) * _height * 16.0 * log(1.0 + 9.0 * _currentLevel));
    if (currentHeight == _currentHeight) {
        return;
    }

    uint8_t new_top = currentHeight / 16;
    uint8_t new_shade = currentHeight % 16;

    if (new_top >= _top) {
        // need to add pixels
        int deltaPixels = new_top - _top;
        for (int i=0;i<deltaPixels;i++) {
            uint8_t alpha = (_currentHeight/16 + i) * 4;
            uint16_t color;
            if (alpha > 127) {
                color = blendRGB565(ST7735_RED, ST7735_YELLOW, 2 * (alpha - 127));
            }
            else {
                color = blendRGB565(ST7735_YELLOW, _color, alpha * 2);
            }
            _tft->drawFastHLine(_xOffset, _yOffset + _height - (_top + i), _width, color);
        }

        uint8_t alpha = (currentHeight/16) * 4;
        uint16_t color;
        if (alpha > 127) {
            color = blendRGB565(ST7735_RED, ST7735_YELLOW, 2 * (alpha - 127));
        }
        else {
            color = blendRGB565(ST7735_YELLOW, _color, alpha * 2);
        }
        color = blendRGB565(color, _backgroundColor, new_shade * 16);
        _tft->drawFastHLine(_xOffset, (_yOffset + _height - (_top + deltaPixels)), _width, color);

        if (_fraction != 16) {
            uint8_t alpha = (_top) * 4;
            if (alpha > 127) {
                color = blendRGB565(ST7735_RED, ST7735_YELLOW, 2 * (alpha - 127));
            }
            else {
                color = blendRGB565(ST7735_YELLOW, _color, alpha * 2);
            }
            _tft->drawFastHLine(_xOffset, (_yOffset + _height - _top)+1, _width, color);
        }

    } else if (new_top < _top) {
        int deltaPixels = _top - new_top;

        for (int i=0;i<deltaPixels;i++) {
            _tft->drawFastHLine(_xOffset, _yOffset + _height - (_top - i), _width, _backgroundColor);
        }

        if (new_shade > 0) {
            uint8_t alpha = (currentHeight/16) * 4;
            uint16_t color;
            if (alpha > 127) {
                color = blendRGB565(ST7735_RED, ST7735_YELLOW, 2 * (alpha - 127));
            }
            else {
                color = blendRGB565(ST7735_YELLOW, _color, alpha * 2);
            }

            color = blendRGB565(color, _backgroundColor, new_shade * 16);
            _tft->drawFastHLine(_xOffset, _yOffset + _height - (_top - deltaPixels), _width, color);
        }
    }
    _top = new_top;
    _fraction = new_shade;
    _currentHeight = currentHeight;
}

void AudioLevelView::updateLevel(float newLevel) {
    if (newLevel > 1.0) newLevel = 1.0;
    if (_currentLevel != abs(newLevel)) {
        _currentLevel = abs(newLevel);
        draw();
    }
}