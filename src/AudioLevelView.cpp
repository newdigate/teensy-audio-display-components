#include "AudioLevelView.h"
uint16_t alphaBlendRGB565( uint32_t fg, uint32_t bg, uint8_t alpha )
{
    alpha = ( alpha + 4 ) >> 3; // from 0-255 to 0-31
    bg = (bg | (bg << 16)) & 0b00000111111000001111100000011111;
    fg = (fg | (fg << 16)) & 0b00000111111000001111100000011111;
    uint32_t result = ((((fg - bg) * alpha) >> 5) + bg) & 0b00000111111000001111100000011111;
    return (uint16_t)((result >> 16) | result); // contract result
}

void AudioLevelView::draw() {
    if (_currentLevel < 0.0) return;

    int currentHeight = int(1.0/log(10.0) * _height * float(16) * log(1.0 + 9.0 * _currentLevel));
    if (currentHeight == _currentHeight) {
        return;
    }

    uint8_t new_top = currentHeight / 16;
    uint8_t new_shade = currentHeight % 16;
    //if (new_shade > 0) new_top ++;

    if (new_top >= _top) {
        // need to add pixels
        int deltaPixels = new_top - _top;
        for (int i=0;i<deltaPixels-1;i++) {
            uint8_t alpha = (_currentHeight/16 + i) * 4;
            uint16_t color;
            if (alpha > 127) {
                color = alphaBlendRGB565(ST7735_RED, ST7735_YELLOW , 2 * (alpha-127));
            }
            else {
                color = alphaBlendRGB565(ST7735_YELLOW, _color, alpha * 2);
            }
            _tft->drawFastHLine(_xOffset, _yOffset + _height - (_top + i), _width, color);
        }

        uint8_t alpha = (currentHeight/16) * 4;
        uint16_t color;
        if (alpha > 127) {
            color = alphaBlendRGB565(ST7735_RED, ST7735_YELLOW , 2 * (alpha-127));
        }
        else {
            color = alphaBlendRGB565(ST7735_YELLOW, _color, alpha * 2);
        }
        color = alphaBlendRGB565(color, _backgroundColor, new_shade * 16);
        _tft->drawFastHLine(_xOffset, (_yOffset + _height - (_top + deltaPixels)), _width, color);

        if (_fraction != 16) {
            uint8_t alpha = (_top) * 4;
            if (alpha > 127) {
                color = alphaBlendRGB565(ST7735_RED, ST7735_YELLOW , 2 * (alpha-127));
            }
            else {
                color = alphaBlendRGB565(ST7735_YELLOW, _color, alpha * 2);
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
                color = alphaBlendRGB565(ST7735_RED, ST7735_YELLOW , 2 * (alpha-127));
            }
            else {
                color = alphaBlendRGB565(ST7735_YELLOW, _color, alpha * 2);
            }

            color = alphaBlendRGB565(color, _backgroundColor, new_shade * 16);
            _tft->drawFastHLine(_xOffset, _yOffset + _height - (_top - deltaPixels), _width, color);
        }
    }
    _top = new_top;
    _fraction = new_shade;

}

void AudioLevelView::updateLevel(float newLevel) {
    if (newLevel > 1.0) newLevel = 1.0;
    if (_currentLevel != abs(newLevel)) {
        _currentLevel = abs(newLevel);
        draw();
    }
}