#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <openAL/al.h>
#include <openAL/alc.h>

class AudioBoomBox
{  
	public:
		AudioBoomBox();
		AudioBoomBox(ALuint* buffer, int id);
		~AudioBoomBox();
		void initialize();
		void playSound();
		void stopSound();
		void loopSound(bool loop);
		void pauseSound();
		void updateSourcePosition(float x, float y, float z);
		bool isSoundPlaying();
		void cleanup();
		int getId();

		ALuint source;
		ALint source_state;
		int id;
};

