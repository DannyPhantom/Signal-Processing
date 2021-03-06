/*
 * FrequencyDomainConvolver.h
 *
 *  Created on: Dec 8, 2016
 *      Author: igor.sarcovschi
 */

#ifndef FREQUENCYDOMAINCONVOLVER_H_
#define FREQUENCYDOMAINCONVOLVER_H_

#include <vector>

class AudioFile;

class FrequencyDomainConvolver {
public:
	FrequencyDomainConvolver();
	virtual ~FrequencyDomainConvolver();

	AudioFile *convolve(AudioFile *dryFile, AudioFile *irFile);

private:
	double *vectorOfNormalToArrayOfComplex(std::vector<double> input);
	void fft(double *data, int nn, int isign);
	int closestPowerOfTwo(int N, int M);
	double *zeroPad(double *array, int currentSize, int wantedSize);
};

#endif /* FREQUENCYDOMAINCONVOLVER_H_ */
