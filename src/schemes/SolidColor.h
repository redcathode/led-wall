
//#include "SchemeConstants.h"
#include "FastLED.h"
#include "SchemeBase.h"
#include <vector>

class SolidColor : public Scheme{
    public:
        SolidColor(CRGB *leds);
        void drawFrame();
        std::vector<Preference> * getPreferenceList();
        CRGB* leds;
        virtual ~SolidColor();
    private:
        std::vector<Preference> preferenceList;
        
};