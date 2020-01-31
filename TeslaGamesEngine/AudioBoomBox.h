#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <openAL/al.h>
#include <openAL/alc.h>

class AudioBoomBox
{  
	public:
		AudioBoomBox(ALuint* buffer);
		~AudioBoomBox();
		void initialize();
		void playSound();
		void stopSound();
		bool isSoundPlaying();
		void cleanup();

		ALuint source;
		ALint source_state;
};

