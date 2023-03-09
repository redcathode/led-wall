#ifndef SCHEME_CONSTANTS_H
#define SCHEME_CONSTANTS_H



#define STRIP_LENGTH 1101
#define DATA_PIN 25
//#define MAX_MILLIWATTS 11000
#define MAX_MILLIWATTS 20000

// ColorTrains
#define NUM_TRAINS 60
#define TRAINS_USE_RAND_RGB false

// StarryNight
#define NUM_STARS 120
#define STARRY_NIGHT_DO_DITHERING true
#define STARRY_NIGHT_MULTICOLOR false

// WholeStripWalk
#define WHOLESTRIPWALK_NUM_CYCLES 4

// MusicVis
#define NUM_BANDS 11 // should be a multiple of STRIP_LENGTH. NTFS 5 10 11 20 22 25 44 50 55 100 110
#define BAR_LENGTH 1100/NUM_BANDS // sorry, last LED
// asdf
#define brekak break
#define flase false

#endif