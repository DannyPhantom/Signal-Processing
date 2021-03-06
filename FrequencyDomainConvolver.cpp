/*
 * FrequencyDomainConvolver.cpp
 *
 *  Created on: Dec 8, 2016
 *      Author: igor.sarcovschi
 */

#include "FrequencyDomainConvolver.h"
#include "AudioFile.h"
#include <math.h>
#include <iterator>
#include <iostream>

#define PI 3.141592653589793
#define TWO_PI (2.0 * PI)
#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

FrequencyDomainConvolver::FrequencyDomainConvolver() {
	// TODO Auto-generated constructor stub

}

FrequencyDomainConvolver::~FrequencyDomainConvolver() {
	// TODO Auto-generated destructor stub
}

AudioFile *FrequencyDomainConvolver::convolve(AudioFile *dryFile, AudioFile *irFile) {
	AudioFile *result = new AudioFile();

	result->setBitsPerSample(dryFile->getBitsPerSample());
	result->setNumChannels(dryFile->getNumChannels());
	result->setSampleRate(dryFile->getSampleRate());

	int drySize = dryFile->getDataSize();
	double *dryData = vectorOfNormalToArrayOfComplex(dryFile->getData());

	int irSize = irFile->getDataSize();
	double *irData = vectorOfNormalToArrayOfComplex(irFile->getData());

	int L = closestPowerOfTwo(drySize, irSize);
	double *newDryData = zeroPad(dryData, drySize * 2, L * 2);
	double *newIrData = zeroPad(irData, irSize * 2, L * 2);
	delete[] dryData;
	delete[] irData;

	fft(newDryData - 1, L, 1);
	fft(newIrData -1, L, 1);

	double *resultData = new double[L * 2];

	for(int i = 0; i < L * 2; i += 2)
	{
		resultData[i] = newDryData[i] * newIrData[i] - newDryData[i+1] * newIrData[i+1];
		resultData[i+1] = newDryData[i] * newIrData[i+1] + newDryData[i+1] * newIrData[i];
	}

	fft(resultData - 1, L, -1);
	int expectedFinalLength = drySize + irSize - 1;
	for (int i = 0; i < L * 2, i < expectedFinalLength * 2; i += 2) {
		result->addSignal(resultData[i] / (L * 2));
	}
	result->normalizeData();

	return result;
}

double *FrequencyDomainConvolver::vectorOfNormalToArrayOfComplex(std::vector<double> input) {
	double *complexArray = new double[input.size() * 2];
	for (int i=0; i<input.size(); i++) {
		complexArray[i*2] = input[i];
		complexArray[i*2+1] = 0.0;
	}
	return complexArray;
}

void FrequencyDomainConvolver::fft(double *data, int nn, int isign) {
	unsigned long n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta;
	double tempr, tempi;

	n = nn << 1;
	j = 1;

	for (i = 1; i < n; i+=2) {
		if (j > i) {
			SWAP(data[j], data[i]);
			SWAP(data[j+1], data[i+1]);
		}
		m = nn;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}

	mmax = 2;
	while (n > mmax) {
		istep = mmax << 1;
		theta = isign * (6.28318530717959 / mmax);
		wtemp = sin(0.5 * theta);
		wpr = -2.0 * wtemp * wtemp;
		wpi = sin(theta);
		wr = 1.0;
		wi = 0.0;
		for (m = 1; m < mmax; m += 2) {
			for (i = m; i <= n; i += istep) {
				j = i + mmax;
				tempr = wr * data[j] - wi * data[j+1];
				tempi = wr * data[j+1] + wi * data[j];
				data[j] = data[i] - tempr;
				data[j+1] = data[i+1] - tempi;
				data[i] += tempr;
				data[i+1] += tempi;
			}
			wr = (wtemp = wr) * wpr - wi * wpi + wr;
			wi = wi * wpr + wtemp * wpi + wi;
		}
		mmax = istep;
	}
}

int FrequencyDomainConvolver::closestPowerOfTwo(int N, int M) {
	int k = std::max(N, M);
	return std::pow(2, std::ceil(std::log(k)/log(2)));
}


double *FrequencyDomainConvolver::zeroPad(double *array, int currentSize, int wantedSize) {
	double *newArray = new double[wantedSize];
	std::copy(array, array + currentSize - 1, newArray);
	for (int i=currentSize; i<wantedSize; i++) {
		newArray[i] = 0.0;
	}
	return newArray;
}
