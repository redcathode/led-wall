#include "WholeStripWalk.h"
#include "FastLED.h"

WholeStripWalk::WholeStripWalk(CRGB *l):leds(l) {
    //Serial.println("begin constructor WholeStripWalk");
    // populate trains
    int currentHue = 0;
    int currentHueMax = 255 * WHOLESTRIPWALK_NUM_CYCLES;
    int currentHueMin = 0;
    for (int i = 0; i < STRIP_LENGTH; i++) {
        // Serial.print("i = ");
        // Serial.println(i);
        
        currentHue += 1;
        hues.push_back(map(currentHue, 0, STRIP_LENGTH, currentHueMin, currentHueMax) % 255);
    }
    //Serial.println("end constructor WholeStripWalk");
};
WholeStripWalk::~WholeStripWalk() {
}
void WholeStripWalk::drawFrame() {
    FastLED.clearData();
    for (int i = 0; i < STRIP_LENGTH; i++) {
        leds[i] = CHSV(hues[i], 255, 255);
        hues[i] += 1;
        hues[i] %= 255;
    }
}
std::vector<Preference> * WholeStripWalk::getPreferenceList() {
    return &preferenceList;
}