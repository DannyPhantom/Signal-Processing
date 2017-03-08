/*
 * TimeDomainConvolver.cpp
 *
 *  Created on: 2016-12-08
 *      Author: dannyphantom
 */

#include "TimeDomainConvolver.h"

#include <iostream>
#include <time.h>
#include <math.h>

TimeDomainConvolver::TimeDomainConvolver() {
	// TODO Auto-generated constructor stub

}

TimeDomainConvolver::~TimeDomainConvolver() {
	// TODO Auto-generated destructor stub
}

AudioFile *TimeDomainConvolver::convolve(AudioFile *dryFile, AudioFile *irFile) {

	AudioFile *resultingFile = new AudioFile();

	resultingFile->setBitsPerSample(dryFile->getBitsPerSample());
	resultingFile->setNumChannels(dryFile->getNumChannels());
	resultingFile->setSampleRate(dryFile->getSampleRate());

	std::vector<double> x = dryFile->getData();
	std::vector<double> h = irFile->getData();

	int resultSize = x.size() + h.size() - 1;
	std::cout << resultSize;
	double *result = new double[resultSize];
	for (int i=0; i<resultSize; i++) {
		result[i] = 0.0;
	}

	clock_t start = clock();

	for (int n=0; n<x.size(); n++) {
		for (int m=0; m<h.size(); m++) {
			result[n+m] += x[n] * h[m];
		}

		if (!(n % 1000)) {
			float perc = (float) n/x.size() * 100;
			double timeSpent = (double)(clock() - start)/CLOCKS_PER_SEC;
			double timeSpentPerCol = timeSpent / (n+1);
			double timeLeft = timeSpentPerCol *(x.size() - n+1);
			if (timeLeft < 0) {
					timeLeft = 0;
			}
			double minLeft = floor(timeLeft / 60);
			double secondsLeft = floor(timeLeft - minLeft * 60);

			fprintf(stdout,"\r%8.2f%%. Remaining time: %3d minutes, %2d seconds",(double)perc, (int)minLeft, (int)secondsLeft);
			fflush(stdout);
		}
	}

	for (int i=0; i<resultSize; i++) {
		resultingFile->addSignal(result[i]);
	}

	resultingFile->normalizeData();

	return resultingFile;
}

