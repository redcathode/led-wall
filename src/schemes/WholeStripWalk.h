

#include "FastLED.h"
#include "SchemeConstants.h"
#include "SchemeBase.h"
#include <vector>

class WholeStripWalk : public Scheme
{
    public:
        WholeStripWalk(CRGB *leds);
        void drawFrame();
        std::vector<Preference> * getPreferenceList();
        CRGB* leds;
        virtual ~WholeStripWalk();
    private:
        std::vector<int> hues;
        std::vector<Preference> preferenceList;
};