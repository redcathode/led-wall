#ifndef SCHEME_BASE_H
#define SCHEME_BASE_H

#include "FastLED.h"
#include <vector>

struct Preference {
    std::string name;
    int value;
    int minValue;
    int maxValue;
};

class Scheme {
    public:
        //Scheme(CRGB *leds);
        virtual void drawFrame() = 0;
        virtual std::vector<Preference> * getPreferenceList() = 0;
        //virtual ~Scheme();

};
#endif