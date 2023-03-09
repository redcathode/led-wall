#include "RandomWalk.h"
#include "FastLED.h"
#include "SchemeConstants.h"

RandomWalk::RandomWalk(CRGB *l):leds(l) {
    

};
RandomWalk::~RandomWalk() {}
void RandomWalk::drawFrame() {
    // todo: make transition work (lol)
    //FastLED.clearData();
    // if (!stripCleared) {
        // for (int i = currentLed; i < currentLed + 12; i++) {
        //     if (i == STRIP_LENGTH) {
        //         stripCleared = true;
        //         break;
        //     }
        //     leds[i].r = 0;
        //     leds[i].g = 0;
        //     leds[i].b = 0;
        // }
    // } else {
        currentLed += 1;
        currentLed %= STRIP_LENGTH;
        currentHue += random(-10, 10);
        currentHue %= 255;
        // for (int i = 0; i < STRIP_LENGTH; i++) {
        //     leds[i] = CHSV(currentHue, 187, 255);
        // }
        leds[currentLed] = CHSV(currentHue, 187, 255);
    //}
   
}

std::vector<Preference> * RandomWalk::getPreferenceList() {
    return &preferenceList;
}