/*
 * AudioFileWriter.h
 *
 *  Created on: 2016-12-08
 *      Author: dannyphantom
 */

#ifndef AUDIOFILEWRITER_H_
#define AUDIOFILEWRITER_H_

class AudioFile;

class AudioFileWriter {
public:
	AudioFileWriter();
	virtual ~AudioFileWriter();

	virtual void writeToFile(char *fileName, AudioFile *file) = 0;

protected:
	struct header_file
	{
		char chunk_id[4];
		int chunk_size;
		char format[4];
		char subchunk1_id[4];
		int subchunk1_size;
		short int audio_format;
		short int num_channels;
		int sample_rate;
		int byte_rate;
		short int block_align;
		short int bits_per_sample;
	} header;

	struct subchunk2_header
	{
		char subchunk2_id[4];
		int subchunk2_size;			// subchunk2_size specifies the number of samples.
	} header2;
};

#endif /* AUDIOFILEWRITER_H_ */
