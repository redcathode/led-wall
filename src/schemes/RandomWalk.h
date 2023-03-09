
#include "FastLED.h"
#include "SchemeConstants.h"
#include "SchemeBase.h"
#include <vector>

class RandomWalk : public Scheme{
    public:
        RandomWalk(CRGB *leds);
        void drawFrame();
        std::vector<Preference> * getPreferenceList();
        CRGB* leds;
        virtual ~RandomWalk();
    private:
        int currentLed = 0;
        int currentHue = 0;
        bool stripCleared = false;
        std::vector<Preference> preferenceList;

};