/*
 * FrequencyDomainConvolverO1.h
 *
 *  Created on: 2016-12-08
 *      Author: dannyphantom
 */

#ifndef FREQUENCYDOMAINCONVOLVERO1_H_
#define FREQUENCYDOMAINCONVOLVERO1_H_

#include <vector>
class AudioFile;

class FrequencyDomainConvolverO1 {
public:
	FrequencyDomainConvolverO1();
	virtual ~FrequencyDomainConvolverO1();

	AudioFile *convolve(AudioFile *dryFile, AudioFile *irFile);

private:
	double *vectorOfNormalToArrayOfComplex(std::vector<double> input);
	void fft(double *data, int nn, int isign);
	int closestPowerOfTwo(int N, int M);
	double *zeroPad(double *array, int currentSize, int wantedSize);
};

#endif /* FREQUENCYDOMAINCONVOLVERO1_H_ */
