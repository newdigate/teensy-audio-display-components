#include "CVLevelView.h"
#include "alphaBlendRGB565.h"

void CVLevelView::draw() {
    int currentHeight = 16 * _height/2 * (_currentLevel-32786)/32786;
    if (currentHeight == _currentHeight) {
        return;
    }
    // work-in-progress!! please look somewhere else
    int8_t new_top = currentHeight / 16;
    uint8_t new_shade = abs(currentHeight) % 16;

    // edge cases where an overflow (+positive or -negative)
    if (new_top > 0 && _top <= 0) {
        // positive overflow
        for (int i = 0; i < -_top + 1; i++) {
            _tft->drawFastHLine(_xOffset, _yOffset + _height/2 + i, _width, _backgroundColor);
        }
    } else if (new_top < 0 && _top >= 0) {
        // negative overflow
        for (int i = 0; i < _top; i++) {
            _tft->drawFastHLine(_xOffset, _yOffset + _height/2 - i, _width, _backgroundColor);
        }
    }

    if (new_top == _top && new_shade != _fraction) {
        uint8_t alpha =  ( 256 * abs(_top) / (_height/2) );
        uint16_t color;
        if (alpha > 127) {
            color = blendRGB565(ST7735_RED, ST7735_YELLOW, 2 * (alpha - 127));
        } else {
            color = blendRGB565(ST7735_YELLOW, _color, alpha * 2);
        }
        color = blendRGB565(color, _backgroundColor, new_shade * 16);
        _tft->drawFastHLine(_xOffset, _yOffset + _height/2 - _top , _width, color);
    }
    else if (new_top > 0 && _top >= 0) {
        if (new_top >= _top) {
            // need to add pixels
            int deltaPixels = new_top - _top;
            for (int i = 0; i < deltaPixels - 1; i++) {
//                uint8_t alpha = (_currentHeight / 16 + i) * 4;
                uint8_t alpha =  ( 256 * abs(_top + i) / (_height/2) );
                uint16_t color;
                if (alpha > 127) {
                    color = blendRGB565(ST7735_RED, ST7735_YELLOW, 2 * (alpha - 127));
                } else {
                    color = blendRGB565(ST7735_YELLOW, _color, alpha * 2);
                }
                _tft->drawFastHLine(_xOffset, _yOffset + _height/2 - (_top + i), _width, color);
            }

//            uint8_t alpha = (currentHeight / 16) * 4;
            uint8_t alpha =  ( 256 * abs(new_top) / (_height/2) );
            uint16_t color;
            if (alpha > 127) {
                color = blendRGB565(ST7735_RED, ST7735_YELLOW, 2 * (alpha - 127));
            } else {
                color = blendRGB565(ST7735_YELLOW, _color, alpha * 2);
            }
            color = blendRGB565(color, _backgroundColor, new_shade * 16);
            _tft->drawFastHLine(_xOffset, (_yOffset + _height/2 - (_top + deltaPixels)), _width, color);

            if (_fraction != 16) {
                //alpha = (_top) * 4;
                alpha =  ( 256 * abs(new_top) / (_height/2) );
                if (alpha > 127) {
                    color = blendRGB565(ST7735_RED, ST7735_YELLOW, 2 * (alpha - 127));
                } else {
                    color = blendRGB565(ST7735_YELLOW, _color, alpha * 2);
                }
                _tft->drawFastHLine(_xOffset, (_yOffset + _height/2 - _top) + 1, _width, color);
            }

        }
        else if (new_top < _top) {
            int deltaPixels = _top - new_top;

            for (int i = 0; i < deltaPixels; i++) {
                _tft->drawFastHLine(_xOffset, _yOffset + _height/2 - (_top - i), _width, _backgroundColor);
            }

            if (new_shade > 0) {
                uint8_t alpha =  ( 256 * abs(new_top) / (_height/2) );
                uint16_t color;
                if (alpha > 127) {
                    color = blendRGB565(ST7735_RED, ST7735_YELLOW, 2 * (alpha - 127));
                } else {
                    color = blendRGB565(ST7735_YELLOW, _color, alpha * 2);
                }

                color = blendRGB565(color, _backgroundColor, new_shade * 16);
                _tft->drawFastHLine(_xOffset, _yOffset + _height/2 - (_top - deltaPixels), _width, color);
            }
        }
    } else if (new_top > 0 && _top <= 0) {
        for (int i = 0; i < new_top; i++) {
            uint8_t alpha = ( 256 * i / (_height/2) );
            uint16_t color;
            if (alpha > 127) {
                color = blendRGB565(ST7735_RED, ST7735_YELLOW, 2 * (alpha - 127));
            } else {
                color = blendRGB565(ST7735_YELLOW, _color, alpha * 2);
            }
            _tft->drawFastHLine(_xOffset, _yOffset + _height/2 - i , _width, color);
        }
    }
    _top = new_top;
    _fraction = new_shade;
    _currentHeight = currentHeight;

}

void CVLevelView::updateLevel(uint16_t newLevel) {
    if (_currentLevel != newLevel) {
        _currentLevel = newLevel;
        draw();
    }
}