#include "WAVEAudioFileReader.h"
#include <stdint.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

WAVEAudioFileReader::WAVEAudioFileReader() {

}

WAVEAudioFileReader::~WAVEAudioFileReader() {

}

AudioFile *WAVEAudioFileReader::readFromFile(char *fileName) {
	AudioFile *file = new AudioFile();

	FILE * infile = fopen(fileName, "rb");
	header_file* meta = (header_file*)malloc(sizeof(header));
	fread(meta, 1, sizeof(header), infile);

	/*
	std::cout << "Chunk1ID " << meta->chunk_id << std::endl;
	std::cout << "ChunkSize " << meta->chunk_size << std::endl;
	std::cout << "Format " << meta->format << std::endl;
	std::cout << "Subchunk1ID " << meta->subchunk1_id << std::endl;
	std::cout << "Subchunk1Size " << meta->subchunk1_size << std::endl;
	std::cout << "AudioFormat " << meta->audio_format << std::endl;
	std::cout << "NumChannels " << meta->num_channels << std::endl;
	std::cout << "SampleRate " << meta->sample_rate << std::endl;
	std::cout << "ByteRate " << meta->byte_rate << std::endl;
	std::cout << "BlockAlign " << meta->block_align << std::endl;
	std::cout << "BitsPerSample " << meta->bits_per_sample << std::endl;
*/

	file->setBitsPerSample(meta->bits_per_sample);
	file->setSampleRate(meta->sample_rate);
	file->setNumChannels(meta->num_channels);

	int numBytesLeftInChunk1 = meta->subchunk1_size - 16;
	if (numBytesLeftInChunk1 > 0) {
		char *extra = new char[numBytesLeftInChunk1];
		fread(extra, 1, numBytesLeftInChunk1, infile);
	}

	subchunk2_header* meta2 = (subchunk2_header*)malloc(sizeof(header2));
	fread(meta2, 1, sizeof(header2), infile);

	/*
	std::cout << "Subchunk2ID " << meta2->subchunk2_id << std::endl;
	std::cout << "Subchunk2size " << meta2->subchunk2_size << std::endl;
	*/

	short int sample;
	for (int i=0; i<meta2->subchunk2_size / (meta->bits_per_sample / 8); i++) {
		int k =fread(&sample, sizeof(sample), 1, infile);
		file->addSignal(sample);

		if (k == 0) {
			std::cout << "Something went wrong when reading " << fileName << std::endl;
		}
	}

	return file;
}
