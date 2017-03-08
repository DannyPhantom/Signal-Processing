#ifndef AUDIO_FILE_H
#define AUDIO_FILE_H

#include <vector>

class AudioFile 
{
	
public:
	AudioFile();
	~AudioFile();

	void addSignal(short int signal);
	void addSignal(double signal);
	void setNumChannels(short int numChannels);
	void setSampleRate(int sampleRate);
	void setBitsPerSample(short int bitsPerSample);
	void normalizeData();

	std::vector<double> getData();
	std::vector<short int> getDataShortInt();
	short int getNumChannels();
	long getSampleRate();
	short int getBitsPerSample();
	int getDataSize();

private:
	std::vector<double> data;
	std::vector<short int> dataShortInt;
	short int numChannels;
	int sampleRate;
	short int bitsPerSample;

};


#endif


