#include "AudioBoomBox.h"

AudioBoomBox::AudioBoomBox() {};
AudioBoomBox::AudioBoomBox(ALuint* buffer, int id)
{
	this->id = id;
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
int AudioBoomBox::getId() {
	return this->id;
}
void AudioBoomBox::playSound() {
	alSourcePlay(source);
}
void AudioBoomBox::stopSound() {
	alSourceStop(source);
}
void AudioBoomBox::loopSound(bool loop) {
	bool use = loop ? AL_TRUE : AL_FALSE;
	alSourcei(source, AL_LOOPING, use);
}
void AudioBoomBox::pauseSound() {
	alSourcePause(source);
}
void AudioBoomBox::setVolume(float newVol) {
	alSourcef(source, AL_GAIN, newVol);
}
void AudioBoomBox::updateSourcePosition(float x, float y, float z) {
	printf("SOmeone updated source: %d\n", id);
	alSource3f(source, AL_POSITION, x, y, z);
}
bool AudioBoomBox::isSoundPlaying() {
	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	return source_state == AL_PLAYING;
}
void AudioBoomBox::cleanup() {
	this->stopSound();
	alDeleteSources(1, &source);
}
