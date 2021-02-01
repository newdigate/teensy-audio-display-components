#include <ST7735_t3.h> // Hardware-specific library for ST7735
#include "AudioLevelView.h"
#include "AudioLevelAnnotationView.h"
#ifdef BUILD_FOR_OPENGL_EMULATOR
#include "st7735_opengl.h"
st7735_opengl TFT = st7735_opengl();
#else
#define TFT_CS   6  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    2  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   -1 // RST can use any pin
ST7735_t3 TFT = ST7735_t3(TFT_CS, TFT_DC, TFT_RST);
#endif
AudioLevelAnnotationView audioLevelAnnotationView1 = AudioLevelAnnotationView(TFT, 0x1111, 0, 0, 64, 128);
AudioLevelAnnotationView audioLevelAnnotationView2 = AudioLevelAnnotationView(TFT, 0x1111, 0, 63, 64, 128);

AudioLevelView scopeViewCV1 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 0, 0, 64, 3);
AudioLevelView scopeViewCV2 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 15, 0, 64, 3);
AudioLevelView scopeViewCV3 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 31, 0, 64, 3);
AudioLevelView scopeViewCV4 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 47, 0, 64, 3);
AudioLevelView scopeViewCV5 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 63, 0, 64, 3);
AudioLevelView scopeViewCV6 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 79, 0, 64, 3);
AudioLevelView scopeViewCV7 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 95, 0, 64, 3);
AudioLevelView scopeViewCV8 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 111, 0, 64, 3);

AudioLevelView scopeViewCV9 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 0, 63, 64, 3);
AudioLevelView scopeViewCV10 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 15, 63, 64, 3);
AudioLevelView scopeViewCV11 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 31, 63, 64, 3);
AudioLevelView scopeViewCV12 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 47, 63, 64, 3);
AudioLevelView scopeViewCV13 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 63, 63, 64, 3);
AudioLevelView scopeViewCV14 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 79, 63, 64, 3);
AudioLevelView scopeViewCV15 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 95, 63, 64, 3);
AudioLevelView scopeViewCV16 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 111, 63, 64, 3);

AudioLevelView levelViews[16] = {scopeViewCV1, scopeViewCV2, scopeViewCV3, scopeViewCV4, scopeViewCV5, scopeViewCV6, scopeViewCV7, scopeViewCV8,
                                 scopeViewCV9, scopeViewCV10, scopeViewCV11, scopeViewCV12, scopeViewCV13, scopeViewCV14, scopeViewCV15, scopeViewCV16};

int currentLevels[16] = {0};

void setup() {
  Serial.begin(9600);

  TFT.initR(INITR_144GREENTAB);
  TFT.setRotation(3);
  TFT.fillScreen(ST7735_BLACK);
  for (int i=0;i<16; i++) {
      levelViews[i].draw();
      currentLevels[i] = rand() % 4096;
  }
  audioLevelAnnotationView1.draw();
  audioLevelAnnotationView2.draw();
}

void loop() {
    for (int i=0;i<16; i++) {
        levelViews[i].updateLevel(currentLevels[i] / 4096.0);
        currentLevels[i] += ( rand() % 33 ) - 16;
        currentLevels[i] %= 4096;
        if (currentLevels[i] < 0) currentLevels[i] = 0;
    }
    delay(1);
}

#ifdef BUILD_FOR_OPENGL_EMULATOR
int main() {
    setup();
    while(!TFT.shouldClose()) {
        loop();
    }
}
#endif