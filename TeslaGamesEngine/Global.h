#pragma once
#include"Combat.h"
#include "Window.h"

extern int dead_flag;
extern Combat combat;
extern bool armed;
extern Window mainWindow;

extern bool startScreenFlag;
extern bool menuFlag;
extern bool closeWindowFlag;
extern bool gameFlag;
extern bool readyScreenFlag;
extern bool pauseFlag;
extern bool fromGameFlag;
extern bool multiplayerFlag;
extern bool multiplayerScreenFlag;

extern int selectedTrackType; //0 for hyperloop, 1 for starlink

extern float backTime;
