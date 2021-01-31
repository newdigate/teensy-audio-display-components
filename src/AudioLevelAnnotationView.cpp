#include "AudioLevelAnnotationView.h"

void AudioLevelAnnotationView::draw() {
    _tft->drawFastHLine(_xOffset, _yOffset, _width, _color);
    _tft->drawFastHLine(_xOffset, _yOffset+(_height/8), _width, _color);
    _tft->drawFastHLine(_xOffset, _yOffset+(_height/4), _width, _color);
    _tft->drawFastHLine(_xOffset, _yOffset+(_height/2), _width, _color);
    _tft->drawFastHLine(_xOffset, _yOffset+(3 *_height/ 4), _width, _color);
    _tft->drawString(" 0", _xOffset,_yOffset);
}