
//#include "SchemeConstants.h"
#include "FastLED.h"
#include "SchemeBase.h"
#include <vector>

struct VisualizerBand {
    CRGB barColor;
    int barLength;
    int maxBarLength;
    int bandOrWhateverTodo;
    int bandNum;
    int startingPos;
};

class MusicVis : public Scheme{
    public:
        MusicVis(CRGB *leds);
        void drawFrame();
        std::vector<Preference> * getPreferenceList();
        CRGB* leds;
        virtual ~MusicVis();
    private:
        std::vector<Preference> preferenceList;
        std::vector<VisualizerBand> visualizerBands;
        float currentHue;
        
        
};