#include "audioEngine.h"
#include <openAL/al.h>
#include <openAL/alc.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

static ALCdevice *device;
static ALCcontext *context;
static ALuint source;
static ALuint buffer;
static ALint source_state;
static char* data;

static bool IsBigEndian(void)
{
	int a = 1;
	return !((char*)&a)[0];
}

static int ConvertToInt(char* buffer, int len)
{
	int a = 0;

	if (!IsBigEndian())
	{
		for (int i = 0; i < len; ++i)
		{
			((char*)&a)[i] = buffer[i];
		}
	}
	else
	{
		for (int i = 0; i < len; ++i)
		{
			((char*)&a)[3 - i] = buffer[i];
		}
	}

	return a;
}

//Location and size of data is found here: http://www.topherlee.com/software/pcm-tut-wavformat.html
static char* loadWAV(std::string filename, int& channels, int& sampleRate, int& bps, int& size)
{
	char buffer[4];

	std::ifstream in(filename.c_str());
	in.read(buffer, 4);

	if (strncmp(buffer, "RIFF", 4) != 0)
	{
		std::cout << "Error here, not a valid WAV file, RIFF not found in header\n This was found instead: "
			<< buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
	}

	in.read(buffer, 4);//size of file. Not used. Read it to skip over it.  

	in.read(buffer, 4);//Format, should be WAVE

	if (strncmp(buffer, "WAVE", 4) != 0)
	{
		std::cout << "Error here, not a valid WAV file, WAVE not found in header.\n This was found instead: "
			<< buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
	}

	in.read(buffer, 4);//Format Space Marker. should equal fmt (space)

	if (strncmp(buffer, "fmt ", 4) != 0)
	{
		std::cout << "Error here, not a valid WAV file, Format Marker not found in header.\n This was found instead: "
			<< buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
	}

	in.read(buffer, 4);//Length of format data. Should be 16 for PCM, meaning uncompressed.

	if (ConvertToInt(buffer, 4) != 16)
	{
		std::cout << "Error here, not a valid WAV file, format length wrong in header.\n This was found instead: "
			<< ConvertToInt(buffer, 4) << std::endl;
	}

	in.read(buffer, 2);//Type of format, 1 = PCM

	if (ConvertToInt(buffer, 2) != 1)
	{
		std::cout << "Error here, not a valid WAV file, file not in PCM format.\n This was found instead: "
			<< ConvertToInt(buffer, 4) << std::endl;
	}

	in.read(buffer, 2);//Get number of channels. 

	//Assume at this point that we are dealing with a WAV file. This value is needed by OpenAL
	channels = ConvertToInt(buffer, 2);

	in.read(buffer, 4);//Get sampler rate. 

	sampleRate = ConvertToInt(buffer, 4);

	//Skip Byte Rate and Block Align. Maybe use later?
	in.read(buffer, 4);//Block Align
	in.read(buffer, 2);//ByteRate

	in.read(buffer, 2);//Get Bits Per Sample

	bps = ConvertToInt(buffer, 2);

	//Skip character data, which marks the start of the data that we care about. 
	in.read(buffer, 4);//"data" chunk. 

	in.read(buffer, 4); //Get size of the data

	size = ConvertToInt(buffer, 4);

	if (size < 0)
	{
		std::cout << "Error here, not a valid WAV file, size of file reports 0.\n This was found instead: "
			<< size << std::endl;
	}

	char* data = new char[size];

	in.read(data, size);//Read audio data into buffer, return.

	in.close();

	return data;
}

static int getAudioFileFormat(int channel, int bps) {
	if (channel == 1) {
		if (bps == 8) {
			return AL_FORMAT_MONO8;
		}
		else if (bps == 16) {
			return AL_FORMAT_MONO16;
		}
	}
	else if (channel == 2) {
		if (bps == 8) {
			return AL_FORMAT_STEREO8;
		}
		else if (bps == 16) {
			return AL_FORMAT_STEREO16;
		}
	}
}

static void initialize() {
	int channel, samplerate, bps, size, format;
	device = alcOpenDevice(NULL);
	if (!device) {
		// handle errors
	}
	else {
		context = alcCreateContext(device, NULL);
		if (!alcMakeContextCurrent(context)) {
			// failed to make context current
			// test for errors here using alGetError();
		}
		else {
			ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
			alListener3f(AL_POSITION, 0, 0, 1.0f);
			// check for errors
			alListener3f(AL_VELOCITY, 0, 0, 0);
			// check for errors
			alListenerfv(AL_ORIENTATION, listenerOri);
			// check for errors

			
			int numOfSourcesToGenerate = 1;

			alGenSources((ALuint)numOfSourcesToGenerate, &source);
			// check for errors
			alSourcef(source, AL_PITCH, 1);
			// check for errors
			alSourcef(source, AL_GAIN, 1);
			// check for errors
			alSource3f(source, AL_POSITION, 0, 0, 0);
			// check for errors
			alSource3f(source, AL_VELOCITY, 0, 0, 0);
			// check for errors
			alSourcei(source, AL_LOOPING, AL_TRUE); //AL_FALSE for no looping
			// check for errros

			data = loadWAV("bounce.wav", channel, samplerate, bps, size);
			format = getAudioFileFormat(channel, bps);

			alGenBuffers((ALuint)numOfSourcesToGenerate, &buffer);
			alBufferData(buffer, format, data, size, samplerate);

			alSourcei(source, AL_BUFFER, buffer);
			// check for errors
		}
	}
}
static void playSound() {
	alSourcePlay(source);
}
static void stopSound() {
	alSourceStop(source);
}
static bool isSoundPlaying() {
	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	return source_state == AL_PLAYING;
}
static void cleanup() {
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
	delete[] data;
}