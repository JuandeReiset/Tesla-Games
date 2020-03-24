#include "AudioEngine.h"
#include "AudioBoomBox.h"

AudioEngine::AudioEngine() {
	this->initialize();
	this->initializeBuffers();
}
AudioEngine::~AudioEngine() {
	killSources();
	for (int i = 0; i < NUM_OF_SOUND_EFFECTS_POSSIBLE; i++) {
		ALuint bufferForFile = bufferArray[i];
		alDeleteBuffers(1, &bufferForFile);
	}
	
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void AudioEngine::initialize() {
	sourcesMade = 0;
	device = alcOpenDevice(NULL);
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	CheckError();

	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);
	CheckError();

	soundFiles[0] = "./audioFiles/bounce.wav";
	soundFiles[1] = "./audioFiles/finalCount.wav";
	soundFiles[2] = "./audioFiles/TTG_main_menu.wav";
	soundFiles[3] = "./audioFiles/TTG_race_music.wav";
	soundFiles[4] = "./audioFiles/vehicle_acceleration_from_rest_MONO.wav";
	soundFiles[5] = "./audioFiles/vehicle_acceleration_from_motion_MONO.wav";
	soundFiles[6] = "./audioFiles/vehicle_boost_start_MONO.wav";
	soundFiles[7] = "./audioFiles/vehicle_boost_speed_max_MONO.wav";
	soundFiles[8] = "./audioFiles/vehicle_top_speed_MONO.wav";
	soundFiles[9] = "./audioFiles/vehicle_turret_triple_burst_MONO.wav";
	soundFiles[10] = "./audioFiles/vehicle_damage_hit_bullet_MONO.wav";
	soundFiles[11] = "./audioFiles/vehicle_damage_hit_trap_MONO.wav";
	soundFiles[12] = "./audioFiles/vehicle_damage_impact_MONO.wav";
	soundFiles[13] = "./audioFiles/vehicle_weapons_caltrops_deploy_MONO.wav";
	soundFiles[14] = "./audioFiles/vehicle_weapons_oil_deploy_MONO.wav";
	soundFiles[15] = "./audioFiles/vehicle_weapons_smoke_deploy_MONO.wav";
	
}
void AudioEngine::updateListenerPosition(float x, float y, float z) {
	alListener3f(AL_POSITION, x, y, z);
}
void AudioEngine::updateListenerOrientatation(glm::vec3 front, glm::vec3 up) {
	ALfloat listenerOri[] = { front.x, front.y, front.z, up.x, up.y, up.z };
	alListenerfv(AL_ORIENTATION, listenerOri);
}

void AudioEngine::initializeBuffers() {
	for (int i = 0; i < NUM_OF_SOUND_EFFECTS_POSSIBLE; i++) {
		const char* file = soundFiles[i];
		ALuint bufferForFile;
		loadWavFile(file, &bufferForFile);
		bufferArray[i] = bufferForFile;
	}
}

AudioBoomBox& AudioEngine::createBoomBox(int soundFile)
{
	ALuint* buffer = &bufferArray[soundFile];
	sourcesMade++;
	listOfSources.push_back(std::make_unique<AudioBoomBox>(buffer, sourcesMade));
	return *listOfSources.back();
}

void AudioEngine::killSource(AudioBoomBox* boombox) {
	int paramId = boombox->getId();
	for (int i = 0; i < listOfSources.size(); i++) {
		int id = listOfSources[i]->getId();
		if (paramId == id) {
			listOfSources[i]->cleanup();
			listOfSources.erase(listOfSources.begin() + i);
		}
	}
}

void AudioEngine::pauseAllActiveSources() {
	for (int i = 0; i < listOfSources.size(); i++) {
		bool isPlaying = listOfSources[i]->isSoundPlaying();
		if (isPlaying) {
			listOfSources[i]->pauseSound();
			this->sourcesPaused.push_back(i);
		}
	}
	this->allHaveBeenPaused = true;
}

void AudioEngine::resumeAllActiveSources() {
	if (this->allHaveBeenPaused == true) {
		this->allHaveBeenPaused = false;
		for (int index : this->sourcesPaused) {
			listOfSources[index]->playSound();
		}
		this->sourcesPaused.clear();
	}
}

void AudioEngine::killSources() {
	listOfSources.clear();
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
void AudioEngine::CheckError() {
	int err;
	err = alGetError();

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


bool AudioEngine::_strcmp(const char* base, const char* cp) {

	for (int lx = 0; base[lx] != 0; lx++) {
		if (cp[lx] != base[lx])
			return false;
	}
	return true;
}

bool AudioEngine::loadWavFile(const char* filename, ALuint* buffer) {

	//Local Declarations
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

		ALsizei size = wave_data.subChunk2Size;
		ALsizei frequency = wave_format.sampleRate;

		ALenum format;

		//The format is worked out by looking at the number of
		//channels and the bits per sample.

		if (wave_format.numChannels == 1) {
			if (wave_format.bitsPerSample == 8) {
				format = AL_FORMAT_MONO8;
			}
			else if (wave_format.bitsPerSample == 16) {
				format = AL_FORMAT_MONO16;
			}
		}
		else if (wave_format.numChannels == 2) {

			if (wave_format.bitsPerSample == 8) {
				format = AL_FORMAT_STEREO8;
			}

			else if (wave_format.bitsPerSample == 16) {
				format = AL_FORMAT_STEREO16;
			}
		}

		//create our openAL buffer and check for success

		CheckError();
		alGenBuffers(1, buffer);
		CheckError();

		//now we put our data into the openAL buffer and
		//check for success

		alBufferData(*buffer, format, (void*)data, size, frequency);
		CheckError();

		//clean up and return true if successful
		fclose(soundFile);
		fprintf(stderr, "%s file load ok\n", filename);
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