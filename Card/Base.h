#ifndef __COLORS__
#define __COLORS__

#include <Windows.h>
#include <iostream>

#define RED         (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define GREEN       (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define BLUE        (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define WHITE       (RED | GREEN | BLUE)

#define RED_BG      (BACKGROUND_RED | BACKGROUND_INTENSITY)
#define GREEN_BG    (BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define BLUE_BG     (BACKGROUND_BLUE | BACKGROUND_INTENSITY)

#define Base (RED_BG | GREEN_BG | BLUE_BG)
#define Color (Base | RED)

// #define __DEBUG__
using namespace std;

#endif
