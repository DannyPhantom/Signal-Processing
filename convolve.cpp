#include <iostream>
#include "AudioFile.h"
#include "WAVEAudioFileReader.h"
#include "WAVEAudioFileWriter.h"
#include "TimeDomainConvolver.h"
#include "FrequencyDomainConvolver.h"
#include "FrequencyDomainConvolverO1.h"
#include "FrequencyDomainConvolverO2.h"
#include "FrequencyDomainConvolverO3.h"
#include "FrequencyDomainConvolverO4.h"
#include "FrequencyDomainConvolverO5.h"

#include <iostream>
#include <time.h>

int main(int argc, char** argv) {
	if (argc != 4) {
		std::cout << "Wrong number of parameters" << std::endl;
		return -1;
	}
	clock_t t = clock();

	AudioFile *dryFile,
				*irFile,
				*resultFile;

	WAVEAudioFileReader reader;
	WAVEAudioFileWriter writer;

	dryFile = reader.readFromFile(argv[1]);
	irFile = reader.readFromFile(argv[2]);

	/*TimeDomainConvolver conv;*/
	/*FrequencyDomainConvolver conv;*/
	FrequencyDomainConvolverO5 conv;
	resultFile = conv.convolve(dryFile, irFile);

	writer.writeToFile(argv[3], resultFile);

	std::cout << "Completed. Whole process took " << ((float)(clock() - t) / CLOCKS_PER_SEC) << std::endl;

	return 0;
}
