#include "AudioBoomBox.h"

AudioBoomBox::AudioBoomBox(ALuint* buffer)
{
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, *buffer);
}

AudioBoomBox::~AudioBoomBox()
{
	this->cleanup();
}

void AudioBoomBox::initialize() {

	alSourcef(source, AL_PITCH, 1.0f);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE); //AL_FALSE for no looping
}

void AudioBoomBox::playSound() {
	alSourcePlay(source);
}
void AudioBoomBox::stopSound() {
	alSourceStop(source);
}
bool AudioBoomBox::isSoundPlaying() {
	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	return source_state == AL_PLAYING;
}
void AudioBoomBox::cleanup() {
	this->stopSound();
	alDeleteSources(1, &source);
}
