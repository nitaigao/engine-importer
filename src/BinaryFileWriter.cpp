#include "BinaryFileWriter.h"

#include "Model.h"

#include "BinaryFileStream.h"

#include <iostream>

bool BinaryFileWriter::acceptExtension(const std::string& extension) {
  bool isModelBinary = extension.compare("modelbinary") == 0;
  return isModelBinary;
}

void BinaryFileWriter::writeModel(Model* model, const std::string& outputFilename) {
  std::ofstream stream;
  stream.open(outputFilename.c_str(), std::ofstream::trunc | std::ofstream::binary);

  if (!stream.is_open()) {
    std::cerr << "Failed to open file " << outputFilename << std::endl;
  }

  unsigned int bigEndianOffset = 0;
  stream.write((char*)&bigEndianOffset, sizeof(unsigned int));

  BinaryFileStream littleEndianStream(false, &stream);
  model->write(&littleEndianStream);

  bigEndianOffset = stream.tellp();
  stream.seekp(0);

  stream.write((char*)&bigEndianOffset, sizeof(unsigned int));
  stream.seekp(bigEndianOffset);

  BinaryFileStream bigEndianStream(true, &stream);
  model->write(&bigEndianStream);
}
