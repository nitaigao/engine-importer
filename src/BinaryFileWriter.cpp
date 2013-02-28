#include "BinaryFileWriter.h"

#include "Model.h"

#include "BinaryFileStream.h"

#include <stdint.h>


#include <iostream>

unsigned int swap_uint32a(unsigned int val) {
  val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
  return (val << 16) | (val >> 16);
}

bool BinaryFileWriter::acceptExtension(const std::string& extension) {
  bool isModelBinary = extension.compare("modelbinary") == 0;
  return isModelBinary;
}

void BinaryFileWriter::writeModel(Model* model, const std::string& outputFilename) {
  std::ofstream stream(outputFilename.c_str(), std::ofstream::trunc | std::ofstream::binary);

  if (!stream.is_open()) {
    std::cerr << "Failed to open file " << outputFilename << std::endl;
  }

  unsigned int bigEndianOffset = 0;
  stream.write((char*)&bigEndianOffset, sizeof(int32_t));

  BinaryFileStream littleEndianStream(false, &stream);
  model->write(&littleEndianStream);

  bigEndianOffset = stream.tellp();
	unsigned int actualBigEndianOffset = swap_uint32a(bigEndianOffset);
  stream.seekp(0);

  stream.write((char*)&actualBigEndianOffset, sizeof(int32_t));
  stream.seekp(bigEndianOffset);

  BinaryFileStream bigEndianStream(true, &stream);
  model->write(&bigEndianStream);
}
