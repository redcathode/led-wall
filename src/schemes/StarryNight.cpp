#include "StarryNight.h"
#include "FastLED.h"
#include "SchemeConstants.h"

StarryNight::StarryNight(CRGB *l):leds(l) {
    //stars = new Star[NUM_STARS];
    for (int i = 0; i < NUM_STARS; i++) {
        Star newStar;
        if (STARRY_NIGHT_MULTICOLOR) {
                newStar.color = CHSV(random(0, 255), random(250, 255), random(10, 30));
        } else {
            int starBrightness = random(1, 5);
            newStar.color.r = 0;
            newStar.color.g = 0;
            newStar.color.b = 0;
            // switch (random(1, 80)) {
            //     case 2:
            //         newStar.color.g = starBrightness;
            //         break;
            //     case 3:
            //         newStar.color.b = starBrightness;
            //         break;
            //     default:
            //         newStar.color.r = starBrightness;
            //         break;

            // }
            newStar.color.r = starBrightness;
            
        }
        newStar.position = (float) random(0, STRIP_LENGTH); // random position
        newStar.speed = random(25.0, 75.0) / 10000.0; // random speed from 0.5 to 5
        stars.push_back(newStar);
    }
    //Serial.begin(115200);
};
StarryNight::~StarryNight() {

}
void StarryNight::drawFrame() {
    FastLED.clearData();
    for (auto & currentStar : stars) {
        currentStar.position += currentStar.speed;
        if (currentStar.position > STRIP_LENGTH) { // have to do this since modulo doesn't exist for floats
            currentStar.position -= STRIP_LENGTH; 
        }
        int basepos = (int) currentStar.position;
        if (STARRY_NIGHT_DO_DITHERING) {
            int secondpos = basepos + 1;
            float firstbright = abs(currentStar.position - secondpos);
            float secondbright = abs(currentStar.position - basepos);
            secondpos %= STRIP_LENGTH;
            leds[basepos].r = round(firstbright * currentStar.color.r);
            leds[basepos].g = round(firstbright * currentStar.color.g);
            leds[basepos].b = round(firstbright * currentStar.color.b);
            //Serial.print("basepos r: ");
            //Serial.println(leds[basepos].r);
            leds[secondpos].r = round(secondbright * currentStar.color.r);
            leds[secondpos].g = round(secondbright * currentStar.color.g);
            leds[secondpos].b = round(secondbright * currentStar.color.b);
            //Serial.print("secondpos r: ");
            //Serial.println(leds[secondpos].r);
        } else {
            leds[basepos] = currentStar.color;
        }
    }
}
std::vector<Preference> * StarryNight::getPreferenceList() {
    return &preferenceList;
}