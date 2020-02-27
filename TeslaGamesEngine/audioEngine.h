#pragma once
//We are using fopen, silence the error
#define _CRT_SECURE_NO_WARNINGS
#include "AudioBoomBox.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <memory>

namespace audioConstants
{
	const int SOUND_FILE_BOUNCE = 0;
	const int SOUND_FILE_FINALCOUNT = 1;
	const int SOUND_FILE_TTG_MAIN_MENU = 2;
	const int SOUND_FILE_TTG_RACE = 3;
	const int SOUND_FILE_ACCEL_REST = 4;
	const int SOUND_FILE_ACCEL_MOTION = 5;
	const int SOUND_FILE_BOOST_START = 6;
	const int SOUND_FILE_BOOST_MAX = 7;
	const int SOUND_FILE_SPEED_MAX = 8;
	const int SOUND_FILE_TURRET_FIRE = 9;
	
}

class AudioEngine
{
	public:
		AudioEngine();
		~AudioEngine();
		void initialize();
		void initializeBuffers();
		AudioBoomBox& createBoomBox(int soundFile);
		void killSources();

	private:
		void CheckError();
		bool _strcmp(const char* base, const char* cp);
		bool loadWavFile(const char* filename, ALuint* buffer);

		static const int NUM_OF_SOUND_EFFECTS_POSSIBLE = 10;
		const char* soundFiles[NUM_OF_SOUND_EFFECTS_POSSIBLE];

		ALuint bufferArray[NUM_OF_SOUND_EFFECTS_POSSIBLE];
		std::vector<std::unique_ptr<AudioBoomBox>> listOfSources;

		ALCdevice *device;
		ALCcontext *context;

};

