#pragma once
//We are using fopen, silence the error
#define _CRT_SECURE_NO_WARNINGS
#include <openAL/al.h>
#include <openAL/alc.h>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
#include "AudioBoomBox.h"

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

		static const int NUM_OF_SOUND_EFFECTS_POSSIBLE = 4;
		const char* soundFiles[NUM_OF_SOUND_EFFECTS_POSSIBLE];

		ALuint bufferArray[NUM_OF_SOUND_EFFECTS_POSSIBLE];
		std::vector<std::unique_ptr<AudioBoomBox>> listOfSources;

		ALCdevice *device;
		ALCcontext *context;

};

