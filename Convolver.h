/*
 * Convolver.h
 *
 *  Created on: 2016-12-08
 *      Author: dannyphantom
 */

#ifndef CONVOLVER_H_
#define CONVOLVER_H_

#include "AudioFile.h"

class Convolver {
public:
	Convolver();
	virtual ~Convolver();

	virtual AudioFile *convolve(AudioFile *dryFile, AudioFile *irFile) = 0;
};

#endif /* CONVOLVER_H_ */
