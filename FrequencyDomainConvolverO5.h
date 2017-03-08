/*
 * FrequencyDomainConvolverO5.h
 *
 *  Created on: 2016-12-09
 *      Author: dannyphantom
 */

#ifndef FREQUENCYDOMAINCONVOLVERO5_H_
#define FREQUENCYDOMAINCONVOLVERO5_H_

#include <vector>
class AudioFile;

class FrequencyDomainConvolverO5 {
public:
	FrequencyDomainConvolverO5();
	virtual ~FrequencyDomainConvolverO5();

	AudioFile *convolve(AudioFile *dryFile, AudioFile *irFile);

private:
	double *vectorOfNormalToArrayOfComplex(std::vector<double> input);
	void fft(double *data, int nn, int isign);
	int closestPowerOfTwo(int N, int M);
	double *zeroPad(double *array, int currentSize, int wantedSize);
};

#endif /* FREQUENCYDOMAINCONVOLVERO5_H_ */
