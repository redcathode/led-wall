#include "ColorTrains.h"
#include "FastLED.h"
#include "SchemeConstants.h"

ColorTrains::ColorTrains(CRGB *l):leds(l) {
    // populate trains
    for (int i = 0; i < NUM_TRAINS; i++) {
        Train newTrain;
        if (TRAINS_USE_RAND_RGB) {
            
            newTrain.color.r = random(0, 255);
            newTrain.color.g = random(0, 255);
            newTrain.color.b = random(0, 255);
        } else {
            newTrain.color = CHSV(random(0, 255), random(100, 255), random(200, 255)); // pick a random hue, sat, and val
        }
        newTrain.length = random(10, 20); // random length
        newTrain.position = (float) random(0, STRIP_LENGTH); // random position
        newTrain.speed = random(500, 5000) / 1000.0; // random speed from 0.5 to 5
        trains.push_back(newTrain);
    }
};
ColorTrains::~ColorTrains() {

}
std::vector<Preference> * ColorTrains::getPreferenceList() {
    return &preferenceList;
}
void ColorTrains::drawFrame() {
    FastLED.clearData();
    for (auto & currentTrain : trains) {
        currentTrain.position += currentTrain.speed;
        if (currentTrain.position > STRIP_LENGTH) { // have to do this since modulo doesn't exist for floats
            currentTrain.position -= STRIP_LENGTH; 
        }
        int basepos = (int) currentTrain.position;
        for (int j = 0; j < currentTrain.length; j++) {
            leds[(basepos + j) % STRIP_LENGTH] = currentTrain.color;
        }
    }
}