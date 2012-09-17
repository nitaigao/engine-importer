#include <iostream>

#include "Model.h"
#include "IFileReader.h"
#include "IFileWriter.h"

int main(int argc, char **argv)  {
  char* inputFilename = argv[1];

  Model* model = IFileReader::readFile(inputFilename);

  char* outputFilename = argv[2];

  IFileWriter* writer = IFileWriter::writerForFile(outputFilename);
  writer->writeModel(model, outputFilename);

  std::clog << "Finished" << std::endl;

  return 0;
}