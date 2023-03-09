// #include "Firework.h"
// #include "FastLED.h"
// #include "SchemeConstants.h"

// FireworkParticle currentFirework;
// bool fireworkExploded = false;

// void Firework::createFireworkParticles() {
//     CRGB color = CHSV(random(0, 255), 255, 255);
//     currentFirework.color = color;
//     currentFirework.currentPos = 0;
//     currentFirework.currentSpeed = random(10, 15);
//     fireworkParticles.clear();
//     for (int i = 0; i < 25; i++) {
//         FireworkParticle newFirework;
//         newFirework.color = color;
//         newFirework.currentPos = 0;
//         newFirework.currentSpeed = random(-10, 10);
//         fireworkParticles.push_back(newFirework);
//     }
// }

// Firework::Firework(CRGB *l):leds(l) {

// };
// Firework::~Firework() {

// }
// void Firework::drawFrame() {
//     FastLED.clearData();
//     createFireworkParticles();
//     if (!fireworkExploded) {
//         leds[(int) currentFirework.currentPos] = currentFirework.color;
//         currentFirework.currentPos += currentFirework.currentSpeed;
//         currentFirework.currentSpeed -= 0.5;
//         if (currentFirework.currentPos > STRIP_LENGTH) {
//             currentFirework.currentPos -= STRIP_LENGTH;
//         }
//         if (currentFirework.currentSpeed < 0) {
//             fireworkExploded = true;
//             for (auto & currentParticle: fireworkParticles) {
//                 currentParticle.currentPos = currentFirework.currentPos;
//             }
//         }
//     } else {
//         for (auto & currentParticle : fireworkParticles) {
//             leds[(int) currentParticle.currentPos] = currentParticle.currentPos;
//             currentParticle.currentPos += currentParticle.currentSpeed;
//             if ...
//         }
//         // if (0) {
//         //     fireworkExploded = false;
//         // }
//     }


// }
// std::vector<Preference> * Firework::getPreferenceList() {
//     return &preferenceList;
// }