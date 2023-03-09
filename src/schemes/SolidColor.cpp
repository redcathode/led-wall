#include "SolidColor.h"
#include "FastLED.h"
#include "SchemeConstants.h"

SolidColor::SolidColor(CRGB *l):leds(l) {
    Preference redPref;
    redPref.name = "Red";
    redPref.value = 255;
    redPref.minValue = 0;
    redPref.maxValue = 255;

    Preference greenPref;
    greenPref.name = "Green";
    greenPref.value = 75;
    greenPref.minValue = 0;
    greenPref.maxValue = 255;

    Preference bluePref;
    bluePref.name = "Blue";
    bluePref.value = 75;
    bluePref.minValue = 0;
    bluePref.maxValue = 255;

    preferenceList.push_back(redPref);
    preferenceList.push_back(greenPref);
    preferenceList.push_back(bluePref);
};
SolidColor::~SolidColor() {}
void SolidColor::drawFrame() {
    int red = preferenceList.at(0).value;
    int green = preferenceList.at(1).value;
    int blue = preferenceList.at(2).value;
    for (int i = 0; i < STRIP_LENGTH; i++) {
        leds[i].r = red;
        leds[i].g = green;
        leds[i].b = blue;
    }
    
}


std::vector<Preference> * SolidColor::getPreferenceList() {
    return &preferenceList;
}