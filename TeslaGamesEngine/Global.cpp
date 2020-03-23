#include "Global.h"

int dead_flag = 0;
Combat combat = Combat();

bool armed = true;

Window mainWindow;

bool startScreenFlag = true;
bool menuFlag = false;
bool closeWindowFlag = false;
bool gameFlag = false;
bool readyScreenFlag = false;
bool pauseFlag = false;
bool fromGameFlag = false;

float backTime = 0.f;