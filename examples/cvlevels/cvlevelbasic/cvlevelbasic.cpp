#include <ST7735_t3.h> // Hardware-specific library for ST7735
#include "CVLevelView.h"

#ifdef BUILD_FOR_OPENGL_EMULATOR
#include "st7735_opengl.h"
st7735_opengl TFT = st7735_opengl();
#else
#define TFT_CS   6  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    2  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   -1 // RST can use any pin
ST7735_t3 TFT = ST7735_t3(TFT_CS, TFT_DC, TFT_RST);
#endif

CVLevelView scopeViewCV1 = CVLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 10, 10, 64, 10);

void setup() {
  Serial.begin(9600);

  TFT.initR(INITR_144GREENTAB);
  TFT.setRotation(3);
  TFT.fillScreen(ST7735_BLACK);
  scopeViewCV1.draw();
}

uint16_t currentLevel = 32786;

void loop() {
    while (Serial.available()) {
        int i = Serial.read();
        if (i > 0)
            Serial.printf("input: %d\n", i);

    }
    //Serial.printf(":%d\n",currentLevel );
    scopeViewCV1.updateLevel(currentLevel);
    currentLevel ++;
    if (currentLevel % 16 == 0)
        delay(1);
}

void my_yield() {
    if(!TFT.shouldClose()) {
        TFT.update();
    }
}

#ifdef BUILD_FOR_OPENGL_EMULATOR
int main() {
    yield_impl = my_yield;

    setup();
    while(!TFT.shouldClose()) {
        loop();
    }
}
#endif