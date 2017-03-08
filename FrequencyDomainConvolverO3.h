/*
 * FrequencyDomainConvolverO3.h
 *
 *  Created on: 2016-12-09
 *      Author: dannyphantom
 */

#ifndef FREQUENCYDOMAINCONVOLVERO3_H_
#define FREQUENCYDOMAINCONVOLVERO3_H_

#include <vector>
class AudioFile;

class FrequencyDomainConvolverO3 {
public:
	FrequencyDomainConvolverO3();
	virtual ~FrequencyDomainConvolverO3();

	AudioFile *convolve(AudioFile *dryFile, AudioFile *irFile);

private:
	double *vectorOfNormalToArrayOfComplex(std::vector<double> input);
	void fft(double *data, int nn, int isign);
	int closestPowerOfTwo(int N, int M);
	double *zeroPad(double *array, int currentSize, int wantedSize);
};

#endif /* FREQUENCYDOMAINCONVOLVERO3_H_ */
