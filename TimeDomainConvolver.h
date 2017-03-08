/*
 * TimeDomainConvolver.h
 *
 *  Created on: 2016-12-08
 *      Author: dannyphantom
 */

#ifndef TIMEDOMAINCONVOLVER_H_
#define TIMEDOMAINCONVOLVER_H_

#include "Convolver.h"

class TimeDomainConvolver: public Convolver {
public:
	TimeDomainConvolver();
	virtual ~TimeDomainConvolver();

	AudioFile *convolve(AudioFile *dryFile, AudioFile *irFile);
};

#endif /* TIMEDOMAINCONVOLVER_H_ */
