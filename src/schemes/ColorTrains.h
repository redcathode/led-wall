

#include "FastLED.h"
#include "SchemeConstants.h"
#include "SchemeBase.h"
#include <vector>
struct Train {
    int length;
    float position;
    float speed;
    CRGB color;
};

class ColorTrains : public Scheme {
    public:
        ColorTrains
        (CRGB *leds);
        void drawFrame();
        std::vector<Preference> * getPreferenceList();
        CRGB* leds;
        virtual ~ColorTrains();
    private:
        std::vector<Train> trains;
        std::vector<Preference> preferenceList;
        
        

};