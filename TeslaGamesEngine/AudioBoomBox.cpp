#include "AudioBoomBox.h"

ALCdevice *device;
ALCcontext *context;
ALuint  buffer;
ALuint  source;
ALsizei size, freq;
ALenum  format;
ALvoid  *data;
ALint source_state;
const char* soundFileName;

AudioBoomBox::AudioBoomBox(const char* name)
{
	soundFileName = name;
}

AudioBoomBox::~AudioBoomBox()
{
	this->stopSound();
	this->cleanup();
}

struct RIFF_Header {
	char chunkID[4];
	int chunkSize;//size not including chunkSize or chunkID
	char format[4];
};

/*
 * Struct to hold fmt subchunk data for WAVE files.
 */

struct WAVE_Format {
	char subChunkID[4];
	int subChunkSize;
	short audioFormat;
	short numChannels;
	int sampleRate;
	int byteRate;
	short blockAlign;
	short bitsPerSample;
};

/*
 * Struct to hold the data of the wave file
 */

struct WAVE_Data {
	char subChunkID[4]; //should contain the word data
	int subChunk2Size; //Stores the size of the data block
};

//https://gist.github.com/mudream4869/34541dfbd12a747b027e
void CheckError(int op = -1, int _err = 0) {
	int err;
	if (op == -1) {
		err = alGetError(); // clear any error messages
	}
	else {
		err = _err;
	}

	if (err != AL_NO_ERROR) {
		if (err == AL_INVALID_NAME)
			fprintf(stderr, "Error : Invalid Name\n");
		else if (err == AL_INVALID_ENUM)
			fprintf(stderr, "Error : Invalid Enum\n");
		else if (err == AL_INVALID_VALUE)
			fprintf(stderr, "Error : Invalid Value\n");
		else if (err == AL_INVALID_OPERATION)
			fprintf(stderr, "Error : Invalid Operation\n");
		else if (err == AL_OUT_OF_MEMORY)
			fprintf(stderr, "Error : Out of Memory\n");
		exit(1);
	}
	return;
}
bool _strcmp(const char* base, const char* cp) {

	for (int lx = 0; base[lx] != 0; lx++) {
		if (cp[lx] != base[lx])
			return false;
	}
	return true;
}

bool loadWavFile(const char* filename, ALuint* buffer, ALsizei* size, ALsizei* frequency, ALenum* format) {

	//Local Declarations
	fprintf(stderr, "[1] filename = %s\n", filename);
	FILE* soundFile = NULL;
	WAVE_Format wave_format;
	RIFF_Header riff_header;
	WAVE_Data wave_data;
	unsigned char* data = 0;

	try {

		soundFile = fopen(filename, "rb");
		if (!soundFile) {
			throw (filename);
		}

		// Read in the first chunk into the struct
		fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);
		//check for RIFF and WAVE tag in memeory

		if (_strcmp("RIFF", riff_header.chunkID) == false or _strcmp("WAVE", riff_header.format) == false) {
			throw ("Invalid RIFF or WAVE Header");
		}

		//Read in the 2nd chunk for the wave info
		fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);

		//check for fmt tag in memory
		if (_strcmp("fmt ", wave_format.subChunkID) == false) {
			throw ("Invalid Wave Format");
		}

		//check for extra parameters;
		if (wave_format.subChunkSize > 16) {
			fseek(soundFile, sizeof(short), SEEK_CUR);
		}

		//Read in the the last byte of data before the sound file
		fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);

		//check for data tag in memory
		if (_strcmp("data", wave_data.subChunkID) == false) {
			throw ("Invalid data header");
		}


		//Allocate memory for data
		data = new unsigned char[wave_data.subChunk2Size];

		// Read in the sound data into the soundData variable
		if (!fread(data, wave_data.subChunk2Size, 1, soundFile)) {
			throw ("error loading WAVE data into struct!");
		}


		//Now we set the variables that we passed in with the

		//data from the structs

		*size = wave_data.subChunk2Size;
		*frequency = wave_format.sampleRate;

		//The format is worked out by looking at the number of
		//channels and the bits per sample.

		if (wave_format.numChannels == 1) {
			if (wave_format.bitsPerSample == 8) {
				*format = AL_FORMAT_MONO8;
			}
			else if (wave_format.bitsPerSample == 16) {
				*format = AL_FORMAT_MONO16;
			}
		}
		else if (wave_format.numChannels == 2) {

			if (wave_format.bitsPerSample == 8) {
				*format = AL_FORMAT_STEREO8;
			}

			else if (wave_format.bitsPerSample == 16) {
				*format = AL_FORMAT_STEREO16;
			}
		}

		//create our openAL buffer and check for success

		CheckError();
		alGenBuffers(1, buffer);
		CheckError();

		//now we put our data into the openAL buffer and
		//check for success

		alBufferData(*buffer, *format, (void*)data, *size, *frequency);
		CheckError();

		//clean up and return true if successful
		fclose(soundFile);
		fprintf(stderr, "load ok\n");
		delete[] data;
		return true;
	}
	catch (std::string error) {

		//our catch statement for if we throw a string
		std::cout << error << std::endl;
		//clean up memory if wave loading fails
		if (soundFile != NULL)
			fclose(soundFile);
		if (data)
			delete[] data;
		//return false to indicate the failure to load wave
		return false;
	}

}

void AudioBoomBox::initialize() {
	device = alcOpenDevice(NULL);
	if (!device) {
		std::cout << "NO DEVICE";
	}
	else {
		context = alcCreateContext(device, NULL);
		if (!alcMakeContextCurrent(context)) {
			// failed to make context current
			// test for errors here using alGetError();
			std::cout << "No context";
		}
		else {
			ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
			alListener3f(AL_POSITION, 0, 0, 1.0f);
			alListener3f(AL_VELOCITY, 0, 0, 0);
			alListenerfv(AL_ORIENTATION, listenerOri);

			alGenSources(1, &source);
			alSourcef(source, AL_PITCH, 1.0f);
			alSourcef(source, AL_GAIN, 1);
			alSource3f(source, AL_POSITION, 0, 0, 0);
			alSource3f(source, AL_VELOCITY, 0, 0, 0);
			alSourcei(source, AL_LOOPING, AL_FALSE); //AL_FALSE for no looping
			// check for errros

			//loadWavFile
			loadWavFile(soundFileName, &buffer, &size, &freq, &format);

			alSourcei(source, AL_BUFFER, buffer);
			// check for errors
		}
	}
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
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}
