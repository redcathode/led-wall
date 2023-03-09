#include <Arduino.h>

#include "FastLED.h"

#include <esp_now.h>
#include <WiFi.h>

#include "schemes/SolidColor.h"
#include "schemes/RandomWalk.h"
#include "schemes/ColorTrains.h"
#include "schemes/StarryNight.h"
#include "schemes/WholeStripWalk.h"
#include "schemes/MusicVis.h"
#include "SchemeBase.h"
#include "SchemeConstants.h"

int numSchemes = 6; // MAKE SURE TO CHANGE THIS WHEN ADDING A SCHEME

uint8_t broadcastAddress[] = {0xF4, 0x12, 0xFA, 0x1B, 0x72, 0xE4};

enum TypeOfUpdate {
  PreferenceChange,
  SceneChange,
  BrightnessChange,
  SceneGet,
  SceneInform,
  PreferenceGet,
  PreferenceInform,
  Status
};

CRGB leds[STRIP_LENGTH];
bool isOff = false;
std::vector<Scheme*> schemeList;


int currentSchemeNum = 5; // currently active scheme
int setSchemeNum = 0; // desired scheme. If the value of this isn't the same as currentScheme, it should set up the set scheme and then set currentScheme to setScheme

typedef struct ChangeMessage { // message sent between remote and wall, see ChangeMessage.md
  TypeOfUpdate typeOfUpdate;
  char stringVal[64];
  int val1; 
  int val2; 
  int val3; 
  int val4;
  int val5;
  bool boolVal;
} ChangeMessage;

ChangeMessage incomingMessage;
std::vector<ChangeMessage> outgoingMessages;

esp_now_peer_info_t peerInfo;
int wallBrightness = 125; // don't wanna change this while a frame is being drawn

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // do nothing
}

void doPreferenceInform(int sceneNum, int prefNum) {
  if (sceneNum != currentSchemeNum) { // this should prevent a segfault/UB
    return;
  }
  ChangeMessage newMsg;
  newMsg.typeOfUpdate = PreferenceInform;
  newMsg.val1 = sceneNum;
  newMsg.val2 = prefNum;

  auto preference = schemeList[sceneNum]->getPreferenceList()->at(prefNum);
  newMsg.val3 = preference.value;
  newMsg.val4 = preference.minValue;
  newMsg.val5 = preference.maxValue;

  outgoingMessages.push_back(newMsg);
}

void doSceneInform(int sceneNum) {
  if (sceneNum != currentSchemeNum) {
    return;
  }
  ChangeMessage newMsg;
  newMsg.typeOfUpdate = SceneInform;
  newMsg.val1 = sceneNum;
  newMsg.val2 = schemeList[sceneNum]->getPreferenceList()->size();

  outgoingMessages.push_back(newMsg);
}

void doPreferenceChange(int sceneNum, int prefNum, int newPrefValue) {
  if (sceneNum != currentSchemeNum) {
    return;
  }
  if (prefNum >= schemeList[sceneNum]->getPreferenceList()->size()) {
    return;
  }
  if (newPrefValue > schemeList[sceneNum]->getPreferenceList()->at(prefNum).maxValue) {
    return;
  }
  if (newPrefValue < schemeList[sceneNum]->getPreferenceList()->at(prefNum).minValue) {
    return;
  }
  schemeList[sceneNum]->getPreferenceList()->at(prefNum).value = newPrefValue;
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingMessage, incomingData, sizeof(incomingMessage));
  switch (incomingMessage.typeOfUpdate) {
    case BrightnessChange:
      wallBrightness = incomingMessage.val1;
      break;
    case SceneChange:
      setSchemeNum = incomingMessage.val1;
      
      break;
    case Status:
      ChangeMessage newMsg;
      newMsg.typeOfUpdate = Status;
      newMsg.val1 = currentSchemeNum;
      newMsg.val2 = wallBrightness;
      newMsg.val3 = numSchemes;
      newMsg.boolVal = isOff;
      outgoingMessages.push_back(newMsg);
      break;
    case PreferenceGet:
      doPreferenceInform(incomingMessage.val1, incomingMessage.val2);
      break;
    case SceneGet:
      doSceneInform(incomingMessage.val1);
      break;
    case PreferenceChange:
      doPreferenceChange(incomingMessage.val1, incomingMessage.val2, incomingMessage.val3);
      break;
  }
}




// deletes all schemes, then creates the desired scheme
void deleteAllSchemesAndReinstate() {
  for (auto & scheme : schemeList) {
    if (scheme != NULL) { // this avoids a double free
      delete scheme;
      scheme = NULL;
    }
  }

  switch(setSchemeNum) {
    case 0:
      schemeList[0] = new StarryNight(leds);
      break;
    case 1:
      schemeList[1] = new ColorTrains(leds);
      break;
    case 2:
      schemeList[2] = new WholeStripWalk(leds);
      break;
    case 3:
      schemeList[3] = new SolidColor(leds);
      break;
    case 4:
      schemeList[4] = new RandomWalk(leds);
      break;
    case 5:
      schemeList[5] = new MusicVis(leds);
      break;
  }
  currentSchemeNum = setSchemeNum;
  doSceneInform(currentSchemeNum);
}

void sendOutgoingMessages() {
  while (outgoingMessages.size() > 0) {
    ChangeMessage outgoingMessage = outgoingMessages.back();
    outgoingMessages.pop_back();
    esp_now_send(broadcastAddress, (uint8_t *) &outgoingMessage, sizeof(outgoingMessage));
  }
  
}

void setup() { 
  WiFi.mode(WIFI_STA);

  schemeList.reserve(numSchemes);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);


  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, STRIP_LENGTH);
  FastLED.setBrightness(255);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_MILLIWATTS);

  deleteAllSchemesAndReinstate();
  
}
#define NOT_MUSIC_VIDEO

void setStripColor(int r, int g, int b) {
  for (int i = 0; i < STRIP_LENGTH; i++) {
    leds[i] = CRGB(r, g, b);
  }
}

void loop() {
  #ifdef NOT_MUSIC_VIDEO
  sendOutgoingMessages();
  if (isOff) {
    FastLED.clear();
    FastLED.show();
    while (isOff) {
      delay(20);
    }
    
  } else if (setSchemeNum == currentSchemeNum) {
    FastLED.setBrightness(wallBrightness);
    schemeList[currentSchemeNum]->drawFrame();
    FastLED.show();
  } else {
    deleteAllSchemesAndReinstate();
  }
  #else
  FastLED.setBrightness(0);
  FastLED.show();
  delay(8000);
  FastLED.clear();
  for (int i = 0; i < 150; i++) {
    leds[i] = CRGB(255, 0, 0);
  }
  FastLED.setBrightness(255);
  FastLED.show();
  delay(2000);
  setStripColor(255, 255, 255);
  for (int i = 60; i > 0; i -= 4) {
    FastLED.setBrightness(i);
    FastLED.show();
  }
  FastLED.clear();
  for (int i = 0; i < 150; i++) {
    leds[i] = CRGB(255, 255, 0);
  }
  FastLED.setBrightness(255);
  FastLED.show();
  
  delay(1700);
  setStripColor(255, 255, 255);
  for (int i = 60; i > 0; i -= 4) {
    FastLED.setBrightness(i);
    FastLED.show();
  }
  FastLED.clear();
  FastLED.setBrightness(255);
  for (int i = 0; i < 150; i++) {
    leds[i] = CRGB(255, 255, 0);
  }
  FastLED.show();
  while (1) {
    ;
  }
  #endif
}