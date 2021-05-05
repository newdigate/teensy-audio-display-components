#include <ST7735_t3.h> // Hardware-specific library for ST7735
#include "AudioLevelView.h"

#ifdef BUILD_FOR_OPENGL_EMULATOR
#include <st7735_opengl_main.h>
#include "st7735_opengl.h"
st7735_opengl TFT = st7735_opengl();
#else
#define TFT_CS   6  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC    2  //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST   -1 // RST can use any pin
ST7735_t3 TFT = ST7735_t3(TFT_CS, TFT_DC, TFT_RST);
#endif

AudioLevelView scopeViewCV1 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 10, 10, 64, 10);

void setup() {
  Serial.begin(9600);

  TFT.initR(INITR_144GREENTAB);
  TFT.setRotation(3);
  TFT.fillScreen(ST7735_BLACK);
  TFT.useFrameBuffer(true);
  TFT.updateScreenAsync(true);
  scopeViewCV1.draw();
}

int currentLevel = 0;

char serialInput[255];
uint8_t serialInputIndex = 0;

void loop() {
    while (Serial.available()) {
        int i = Serial.read();
        if (i >= 0) {
            if (i != 10) {
                serialInput[serialInputIndex] = (char) i;
                serialInputIndex++;
            } else {
                serialInput[serialInputIndex] = 0;
                Serial.printf("input: %s\n", serialInput);
                serialInputIndex = 0;
                char *p_end;
                currentLevel = strtol(serialInput, &p_end, 10);
                scopeViewCV1.updateLevel(currentLevel / 1024.0);
            }
        }

    }

    delay(10);
}