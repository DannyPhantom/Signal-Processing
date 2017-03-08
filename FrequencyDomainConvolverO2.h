/*
 * FrequencyDomainConvolverO2.h
 *
 *  Created on: 2016-12-09
 *      Author: dannyphantom
 */

#ifndef FREQUENCYDOMAINCONVOLVERO2_H_
#define FREQUENCYDOMAINCONVOLVERO2_H_

#include <vector>
class AudioFile;

class FrequencyDomainConvolverO2 {
public:
	FrequencyDomainConvolverO2();
	virtual ~FrequencyDomainConvolverO2();

	AudioFile *convolve(AudioFile *dryFile, AudioFile *irFile);

private:
	double *vectorOfNormalToArrayOfComplex(std::vector<double> input);
	void fft(double *data, int nn, int isign);
	int closestPowerOfTwo(int N, int M);
	double *zeroPad(double *array, int currentSize, int wantedSize);
};

#endif /* FREQUENCYDOMAINCONVOLVERO2_H_ */
