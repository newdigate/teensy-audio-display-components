#include <ST7735_t3.h> // Hardware-specific library for ST7735
#include "../../../src/AudioLevelView.h"
#include <Audio.h>

#include "output_soundio.h"
#include "input_soundio.h"
#include <st7735_opengl_main.h>

// GUItool: begin automatically generated code
AudioOutputSoundIO       soundIoOut;           //xy=740,266
AudioInputSoundIO        soundIoIn;
AudioAnalyzeRMS         analyzeRms;
AudioAnalyzePeak         analyzePeak;
//AudioConnection connection1(soundIoIn, 0, soundIoOut, 0);
//AudioConnection connection2(soundIoIn, 1, soundIoOut, 1);
AudioConnection connection3(soundIoIn, 0, analyzeRms, 0);
AudioConnection connection4(soundIoIn, 0, analyzePeak, 0);
// GUItool: end automatically generated code

#include "st7735_opengl.h"
st7735_opengl TFT = st7735_opengl();

AudioLevelView levelViewCV1 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 10, 10, 64, 15);
AudioLevelView levelViewCV2 = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 30, 10, 64, 15);
AudioLevelView levelViewRef = AudioLevelView(TFT, ST7735_GREEN, ST7735_BLACK, 0, 10, 64, 1);

void setup() {
  Serial.begin(9600);
  AudioMemory(24);
  TFT.initR(INITR_144GREENTAB);
  TFT.setRotation(3);
  TFT.fillScreen(ST7735_BLACK);
  TFT.useFrameBuffer(true);
  TFT.updateScreenAsync(true);
  levelViewRef.updateLevel(1.0);
}

void loop() {
    if (analyzeRms.available()){
        levelViewCV1.updateLevel(analyzeRms.read());
    }

    if (analyzePeak.available()){
        levelViewCV2.updateLevel(analyzePeak.read());
    }
}