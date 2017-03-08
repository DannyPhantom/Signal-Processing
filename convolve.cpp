#include <iostream>
#include "AudioFile.h"
#include "WAVEAudioFileReader.h"
#include "WAVEAudioFileWriter.h"
#include "TimeDomainConvolver.h"

#include <iostream>
#include <time.h>

int main(int argc, char** argv) {
	//if (argc != 4) {
	//	std::cout << "Wrong number of parameters" << std::endl;
	//}
	clock_t t = clock();

	AudioFile *dryFile,
				*irFile,
				*resultFile;

	WAVEAudioFileReader reader;
	WAVEAudioFileWriter writer;

	char fileName[] = "GuitarDry.wav";
	dryFile = reader.readFromFile(fileName);

	char fileName2[] = "BIG HALL E001 M2S.wav";
	irFile = reader.readFromFile(fileName2);

	TimeDomainConvolver conv;
	resultFile = conv.convolve(dryFile, irFile);

	char fileName3[] = "Result.wav";
	writer.writeToFile(fileName3, resultFile);

	std::cout << std::endl << "Completed. Whole process took " << ((float)(clock() - t) / CLOCKS_PER_SEC) << std::endl;

	return 0;
}
