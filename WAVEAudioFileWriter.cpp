/*
 * WAVEAudioFileWriter.cpp
 *
 *  Created on: 2016-12-08
 *      Author: dannyphantom
 */

#include "WAVEAudioFileWriter.h"
#include "AudioFile.h"
#include <stdio.h>
#include <stdlib.h>

WAVEAudioFileWriter::WAVEAudioFileWriter() {
	// TODO Auto-generated constructor stub

}

WAVEAudioFileWriter::~WAVEAudioFileWriter() {
	// TODO Auto-generated destructor stub
}

void WAVEAudioFileWriter::writeToFile(char *fileName, AudioFile *file) {

	FILE *outFile = fopen(fileName, "wb");

	header_file *meta = new header_file();
	meta->chunk_id[0] = 'R'; meta->chunk_id[1] = 'I'; meta->chunk_id[2] = 'F'; meta->chunk_id[3] = 'F';
	meta->chunk_size = 36 + file->getDataSize() * (file->getBitsPerSample() / 8);
	meta->format[0] = 'W'; meta->format[1] = 'A'; meta->format[2] = 'V'; meta->format[3] = 'E';
	meta->subchunk1_id[0] = 'f'; meta->subchunk1_id[1] = 'm'; meta->subchunk1_id[2] = 't'; meta->subchunk1_id[3] = ' ';
	meta->subchunk1_size = 16;
	meta->audio_format = 1;
	meta->num_channels = file->getNumChannels();
	meta->sample_rate = file->getSampleRate();
	meta->byte_rate = file->getSampleRate() * file->getNumChannels() * (file->getBitsPerSample() / 8);
	meta->block_align = file->getNumChannels() * (file->getBitsPerSample() / 8);
	meta->bits_per_sample = file->getBitsPerSample();

	fwrite(meta, 1, sizeof(*meta), outFile);

	subchunk2_header *meta2 = new subchunk2_header();
	meta2->subchunk2_id[0] = 'd'; meta2->subchunk2_id[1] = 'a'; meta2->subchunk2_id[2] = 't'; meta2->subchunk2_id[3] = 'a';
	meta2->subchunk2_size = file->getDataSize() * (file->getBitsPerSample() / 8);

	fwrite(meta2, 1, sizeof(*meta2), outFile);

	std::vector<short int> data = file->getDataShortInt();
	for (int i=0; i<data.size(); i++) {
		fwrite(&data[i], sizeof(short int), 1, outFile);
	}

	fclose(outFile);
}
