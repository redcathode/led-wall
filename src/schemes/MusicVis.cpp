#include "MusicVis.h"
#include "FastLED.h"
#include "SchemeConstants.h"
#include <HardwareSerial.h>
#include <sstream>

#define UART_RX_PIN 33 // GPIO2
#define UART_TX_PIN 32 // GPIO4

HardwareSerial SerialPort(1);



MusicVis::MusicVis(CRGB *l):leds(l) {
    // populate VisualizerList
    for (int i = 0; i < NUM_BANDS; i++) {
        VisualizerBand newBand;
        newBand.barColor = CHSV(map(i, 0, NUM_BANDS, 0, 255), 255, 85);
        newBand.maxBarLength = (BAR_LENGTH) - 1;
        newBand.barLength = BAR_LENGTH / 2;
        newBand.bandNum = i;
        newBand.startingPos = i * BAR_LENGTH;
        visualizerBands.push_back(newBand);
    }
    SerialPort.begin(921600, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
    SerialPort.setTimeout(1); // todo: this is a terrible, slow solution
};
MusicVis::~MusicVis() {}
void MusicVis::drawFrame() {
    FastLED.clearData();
    currentHue += 0.07;
    if (currentHue > 255) {
        currentHue -= 255;
    }
    for (int i = 0; i < STRIP_LENGTH; i++) {
        leds[i] = CHSV(currentHue, 150, 100);
    }
    for (auto & currentBand : visualizerBands) {
        int startingPos = currentBand.startingPos;
        leds[startingPos].r = 155; // first/divider pixel is white
        leds[startingPos].g = 155;
        leds[startingPos].b = 155;
        for (int i = startingPos + 1; i < startingPos + currentBand.barLength; i++) {
            leds[i] = currentBand.barColor;
        }
    }
    
    if (SerialPort.available() > 0) {
        //delayMicroseconds(400); // wait for entire thing to arrive, just in case
        
        String incomingString = SerialPort.readString();
        //std::string s = std::string(incomingString.c_str());
        std::string s = std::string(incomingString.c_str());
        std::istringstream incoming( s );
        int n;
        
        for (auto & currentBand : visualizerBands) {
            incoming >> n;
            if (n > 5 && currentBand.barLength < n) {
                currentBand.barLength = n;
            } else {
                currentBand.barLength *= 0.9;
            }
            // if (currentBand.barLength < n) {
            //     currentBand.barLength = n;
            // } else {
            //     currentBand.barLength -= 1;
            // }
        }
    }
    SerialPort.print("R");
    //Serial.println("finished frame");
}


std::vector<Preference> * MusicVis::getPreferenceList() {
    return &preferenceList;
}