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
    if (_currentLevel < 0) return;

    int currentHeight = _currentLevel * _height;
    int previousHeight = _previousLevel * _height;
    //_tft->drawFastVLine(_xOffset, 128-height, height, _color);
    //_tft->drawFastVLine(_xOffset, 0, 128 - height, _backgroundColor);

    if (currentHeight > previousHeight) {
        // need to add pixels
        int deltaPixels = (currentHeight - previousHeight);
        for (int i=0;i<deltaPixels;i++) {
            uint16_t color = alphaBlendRGB565(ST7735_RED, _color, (_previousLevel * 128 + i) * 2);
            _tft->drawFastHLine(_xOffset, _yOffset + _height - (previousHeight + i), _width, color);
//            _tft->drawPixel(_xOffset, _yOffset + _height - (previousHeight + i), color);
        }
    } else if (currentHeight < previousHeight) {
        int deltaPixels = (previousHeight - currentHeight );
        for (int i=0;i<deltaPixels;i++) {
            _tft->drawFastHLine(_xOffset, _yOffset + _height - (previousHeight - i), _width, _backgroundColor);
            //_tft->drawPixel(_xOffset, _yOffset + _height - (previousHeight - i), _backgroundColor);
        }
    }

    _previousLevel = _currentLevel;
}

void AudioLevelView::updateLevel(float newLevel) {
    if (_currentLevel != abs(newLevel)) {
        _currentLevel = abs(newLevel);
        draw();
    }
}