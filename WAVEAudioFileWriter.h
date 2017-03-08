/*
 * WAVEAudioFileWriter.h
 *
 *  Created on: 2016-12-08
 *      Author: dannyphantom
 */

#ifndef WAVEAUDIOFILEWRITER_H_
#define WAVEAUDIOFILEWRITER_H_

#include "AudioFileWriter.h"

class WAVEAudioFileWriter: public AudioFileWriter {
public:
	WAVEAudioFileWriter();
	virtual ~WAVEAudioFileWriter();

	void writeToFile(char *fileName, AudioFile *file);
};

#endif /* WAVEAUDIOFILEWRITER_H_ */
