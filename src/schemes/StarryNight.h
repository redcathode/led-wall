#include "FastLED.h"
#include "SchemeConstants.h"
#include "SchemeBase.h"
#include <vector>

struct Star {
    float position;
    float speed;
    CRGB color;
};

class StarryNight : public Scheme{
    public:
        StarryNight(CRGB *leds);
        void drawFrame();
        std::vector<Preference> * getPreferenceList();
        CRGB* leds;
        virtual ~StarryNight();
    private:
        std::vector<Star> stars;
        std::vector<Preference> preferenceList;

};