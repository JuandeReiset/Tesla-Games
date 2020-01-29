#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <openAL/al.h>
#include <openAL/alc.h>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
class AudioBoomBox
{  
public:
	AudioBoomBox(const char* name);
	~AudioBoomBox();
	static void initialize();
	static void playSound();
	static void stopSound();
	static bool isSoundPlaying();
	static void cleanup();
};

