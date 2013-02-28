#include <iostream>
#include <fstream>

#include "Model.h"
#include "IFileReader.h"
#include "IFileWriter.h"

int main(int argc, char **argv)  {
	int a = sizeof(unsigned int);
  char* inputFilename = argv[1];

  std::ifstream inputFile(inputFilename);
  if (!inputFile.is_open()) {
	  std::cerr << "Failed to open file " << inputFilename << std::endl;
	  return -1;
  }

  IFileReader* reader = IFileReader::readerForFile(inputFilename);
  std::clog << "Selected reader of type: " << reader->type() << std::endl;
  Model* model = reader->read(inputFilename);

  char* outputFilename = argv[2];

  IFileWriter* writer = IFileWriter::writerForFile(outputFilename);
  std::clog << "Selected writer of type: " << writer->type() << std::endl;
  writer->writeModel(model, outputFilename);

  std::clog << "Finished" << std::endl;

#ifdef _DEBUG
	system("pause");
#endif
	
  return 0;
}