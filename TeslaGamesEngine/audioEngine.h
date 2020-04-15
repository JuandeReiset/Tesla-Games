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
#include <glm\ext\vector_float3.hpp>

namespace audioConstants
{
	const int SOUND_FILE_TTG_MAIN_MENU = 0;
	const int SOUND_FILE_TTG_RACE_HYPERLOOP = 1;
	const int SOUND_FILE_TTG_RACE_STARLINK = 2;
	const int SOUND_FILE_ACCEL_REST = 3;
	const int SOUND_FILE_ACCEL_MOTION = 4;
	const int SOUND_FILE_BOOST_MAX = 5;
	const int SOUND_FILE_SPEED_MAX = 6;
	const int SOUND_FILE_TURRET_FIRE = 7;
	const int SOUND_FILE_HIT_BULLET = 8;
	const int SOUND_FILE_HIT_TRAP = 9;
	const int SOUND_FILE_DEPLOY_CALTROPS = 10;
	const int SOUND_FILE_DEPLOY_OIL = 11;
	const int SOUND_FILE_DEPLOY_SMOKE = 12;

}

class AudioEngine
{
	public:
		AudioEngine();
		~AudioEngine();
		void initialize();
		void updateListenerPosition(float x, float y, float z);
		void updateListenerOrientatation(glm::vec3 front, glm::vec3 up);
		void initializeBuffers();
		AudioBoomBox& createBoomBox(int soundFile);
		void killSource(AudioBoomBox * boombox);
		void killSources();
		void pauseAllActiveSources();
		void resumeAllActiveSources();
		std::vector<int> sourcesPaused;
		bool allHaveBeenPaused;

	private:
		void CheckError();
		bool _strcmp(const char* base, const char* cp);
		bool loadWavFile(const char* filename, ALuint* buffer);

		static const int NUM_OF_SOUND_EFFECTS_POSSIBLE = 13;
		const char* soundFiles[NUM_OF_SOUND_EFFECTS_POSSIBLE];

		int sourcesMade;

		ALuint bufferArray[NUM_OF_SOUND_EFFECTS_POSSIBLE];
		std::vector<std::unique_ptr<AudioBoomBox>> listOfSources;

		ALCdevice *device;
		ALCcontext *context;

};

