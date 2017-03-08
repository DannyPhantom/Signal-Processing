#include "AudioFile.h"
#include <math.h>
#include <iostream>

AudioFile::AudioFile() {

}

AudioFile::~AudioFile() {

}

void AudioFile::addSignal(short int signal) {
	data.push_back(signal / 32768.0);
	dataShortInt.push_back(signal);
}

void AudioFile::addSignal(double signal) {
	data.push_back(signal);
	dataShortInt.push_back(rint(signal * 32767));
}

std::vector<double> AudioFile::getData() {
	return data;
}

std::vector<short int> AudioFile::getDataShortInt() {
	return dataShortInt;
}

void AudioFile::setNumChannels(short int numChannels) {
	this->numChannels = numChannels;
}

void AudioFile::setBitsPerSample(short int bitsPerSample) {
	this->bitsPerSample = bitsPerSample;
}

void AudioFile::normalizeData() {
	double maxSignal = 0;
	for (int i=0; i<data.size(); i++) {
		if (abs(data[i]) > maxSignal) {
			maxSignal = abs(data[i]);
		}
	}

	std::cout << maxSignal << std::endl;

	if (maxSignal > 1.0) {
		for (int i=0; i < data.size(); i++) {
			data[i] = data[i] / maxSignal;
			dataShortInt[i] = data[i] * 32767;
		}
	}
}

short int AudioFile::getNumChannels() {
	return numChannels;
}

void AudioFile::setSampleRate(int sampleRate) {
	this->sampleRate = sampleRate;
}

long AudioFile::getSampleRate() {
	return sampleRate;
}

short int AudioFile::getBitsPerSample() {
	return bitsPerSample;
}

int AudioFile::getDataSize() {
	return data.size();
}
