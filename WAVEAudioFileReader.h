#ifndef WAVE_AUDIO_FILE_READER_H
#define WAVE_AUDIO_FILE_READER_H

#include "AudioFileReader.h"
#include <fstream>

class WAVEAudioFileReader : public AudioFileReader 
{
public:
	WAVEAudioFileReader();
	~WAVEAudioFileReader();

	AudioFile *readFromFile(char *fileName);

};

#endif
