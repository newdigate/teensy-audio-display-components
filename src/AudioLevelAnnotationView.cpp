#include "AudioLevelAnnotationView.h"

void AudioLevelAnnotationView::draw() {
    _tft->drawFastHLine(_xOffset, _yOffset, _width, _color);
    _tft->drawFastHLine(_xOffset, _yOffset+(_height/8), _width, _color);
    _tft->drawFastHLine(_xOffset, _yOffset+(_height/4), _width, _color);
    _tft->drawFastHLine(_xOffset, _yOffset+(_height/2), _width, _color);
    _tft->drawFastHLine(_xOffset, _yOffset+(3 *_height/ 4), _width, _color);
    _tft->drawString1("-0db", 6, _xOffset+4,_yOffset-4);
    _tft->drawString1("-3db", 6, _xOffset+4,_yOffset+(_height/8)-4);
    _tft->drawString1("-6db", 6, _xOffset+4,_yOffset+(_height/4)-4);


}