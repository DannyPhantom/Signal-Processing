/*
 * FrequencyDomainConvolver.h
 *
 *  Created on: Dec 8, 2016
 *      Author: igor.sarcovschi
 */

#ifndef FREQUENCYDOMAINCONVOLVER_H_
#define FREQUENCYDOMAINCONVOLVER_H_

#include <vector>

class FrequencyDomainConvolver {
public:
	FrequencyDomainConvolver();
	virtual ~FrequencyDomainConvolver();

	AudioFile *convolve(AudioFile *dryFile, AudioFile *irFile);

private:
	double *vectorOfNormalToArrayOfComplex(std::vector<double> input);
	void fft(double *data, int nn, int isign);
};

#endif /* FREQUENCYDOMAINCONVOLVER_H_ */
