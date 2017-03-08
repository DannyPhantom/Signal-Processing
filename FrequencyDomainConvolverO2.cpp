/*
 * FrequencyDomainConvolverO2.cpp
 *
 *  Created on: 2016-12-09
 *      Author: dannyphantom
 */

#include "FrequencyDomainConvolverO2.h"
#include "AudioFile.h"
#include <math.h>
#include <iterator>
#include <iostream>

#define PI 3.141592653589793
#define TWO_PI (2.0 * PI)
#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

FrequencyDomainConvolverO2::FrequencyDomainConvolverO2() {
	// TODO Auto-generated constructor stub

}

FrequencyDomainConvolverO2::~FrequencyDomainConvolverO2() {
	// TODO Auto-generated destructor stub
}

AudioFile *FrequencyDomainConvolverO2::convolve(AudioFile *dryFile, AudioFile *irFile) {
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

	int i = 0;
	for(i = 0; i < L * 2 - 4; i += 6)
	{
		resultData[i] = newDryData[i] * newIrData[i] - newDryData[i+1] * newIrData[i+1];
		resultData[i+1] = newDryData[i] * newIrData[i+1] + newDryData[i+1] * newIrData[i];

		resultData[i+2] = newDryData[i+2] * newIrData[i+2] - newDryData[i+3] * newIrData[i+3];
		resultData[i+3] = newDryData[i+2] * newIrData[i+3] + newDryData[i+3] * newIrData[i+2];

		resultData[i+4] = newDryData[i+4] * newIrData[i+4] - newDryData[i+5] * newIrData[i+5];
		resultData[i+5] = newDryData[i+4] * newIrData[i+5] + newDryData[i+5] * newIrData[i+4];
	}

	if (i == L * 2 - 2) {
		resultData[L*2-2] = newDryData[L*2-2] * newIrData[L*2-2] - newDryData[L*2-1] * newIrData[L*2-1];
		resultData[L*2-1] = newDryData[L*2-2] * newIrData[L*2-1] + newDryData[L*2-1] * newIrData[L*2-2];
	} else if (i == L * 2 - 4) {
		resultData[L*2-2] = newDryData[L*2-2] * newIrData[L*2-2] - newDryData[L*2-1] * newIrData[L*2-1];
		resultData[L*2-1] = newDryData[L*2-2] * newIrData[L*2-1] + newDryData[L*2-1] * newIrData[L*2-2];

		resultData[L*2-4] = newDryData[L*2-4] * newIrData[L*2-4] - newDryData[L*2-3] * newIrData[L*2-3];
		resultData[L*2-3] = newDryData[L*2-4] * newIrData[L*2-3] + newDryData[L*2-3] * newIrData[L*2-4];
	}

	fft(resultData - 1, L, -1);
	int expectedFinalLength = drySize + irSize - 1;
	for (int i = 0; i < L * 2, i < expectedFinalLength * 2; i += 2) {
		result->addSignal(resultData[i] / (L * 2));
	}
	result->normalizeData();

	return result;
}

double *FrequencyDomainConvolverO2::vectorOfNormalToArrayOfComplex(std::vector<double> input) {
	double *complexArray = new double[input.size() * 2];
	for (int i=0; i<input.size(); i++) {
		complexArray[i*2] = input[i];
		complexArray[i*2+1] = 0.0;
	}
	return complexArray;
}

void FrequencyDomainConvolverO2::fft(double *data, int nn, int isign) {
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

int FrequencyDomainConvolverO2::closestPowerOfTwo(int N, int M) {
	int k = std::max(N, M);
	if (k <= 2) return 2;
	if (k <= 4) return 4;
	if (k <= 8) return 8;
	if (k <= 16) return 16;
	if (k <= 32) return 32;
	if (k <= 64) return 64;
	if (k <= 128) return 128;
	if (k <= 256) return 256;
	if (k <= 512) return 512;
	if (k <= 1024) return 1024;
	if (k <= 2048) return 2048;
	if (k <= 4096) return 4096;
	if (k <= 8192) return 8192;
	if (k <= 16384) return 16384;
	if (k <= 32768) return 32768;
	if (k <= 65536) return 65536;
	if (k <= 131072) return 131072;
	if (k <= 262144) return 262144;
	if (k <= 524288) return 524288;
	if (k <= 1048576) return 1048576;
	if (k <= 2097152) return 2097152;
	if (k <= 4194304) return 4194304;
	if (k <= 8388608) return 8388608;
	if (k <= 16777216) return 16777216;
	if (k <= 33554432) return 33554432;
	if (k <= 67108864) return 67108864;
	if (k <= 134217728) return 134217728;
	if (k <= 268435456) return 268435456;
	if (k <= 536870912) return 536870912;
	if (k <= 1073741824) return 1073741824;
	return 2147483648;
}


double *FrequencyDomainConvolverO2::zeroPad(double *array, int currentSize, int wantedSize) {
	double *newArray = new double[wantedSize];
	std::copy(array, array + currentSize - 1, newArray);
	for (int i=currentSize; i<wantedSize; i++) {
		newArray[i] = 0.0;
	}
	return newArray;
}


