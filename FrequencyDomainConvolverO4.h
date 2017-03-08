/*
 * FrequencyDomainConvolverO4.h
 *
 *  Created on: 2016-12-09
 *      Author: dannyphantom
 */

#ifndef FREQUENCYDOMAINCONVOLVERO4_H_
#define FREQUENCYDOMAINCONVOLVERO4_H_

#include <vector>
class AudioFile;

class FrequencyDomainConvolverO4 {
public:
	FrequencyDomainConvolverO4();
	virtual ~FrequencyDomainConvolverO4();

	AudioFile *convolve(AudioFile *dryFile, AudioFile *irFile);

private:
	double *vectorOfNormalToArrayOfComplex(std::vector<double> input);
	void fft(double *data, int nn, int isign);
	int closestPowerOfTwo(int N, int M);
	double *zeroPad(double *array, int currentSize, int wantedSize);
};

#endif /* FREQUENCYDOMAINCONVOLVERO4_H_ */
