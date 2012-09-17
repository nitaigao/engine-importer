#include "BinaryFileWriter.h"

#include <fstream>
#include <iostream>

#include "Vector3.h"
#include "VertexDefinition.h"

enum {
  PARAMETER_TYPE_UNKNOWN = 0,
  PARAMETER_TYPE_STRING = 1,
  PARAMETER_TYPE_FLOAT = 2,
  PARAMETER_TYPE_VECTOR3 = 3,
};

unsigned int swap_uint32( unsigned int val )
{
  val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
  return (val << 16) | (val >> 16);
}

void BinaryFileWriter::openFile(const char* filePath) {
  filePath_ = filePath;
  stream_.open(filePath, std::ofstream::binary);

  if (!stream_.is_open()) {
    std::cerr << "Failed to open file " << filePath << std::endl;
  }

  unsigned int bigEndianOffset = 0;
  stream_.write((char*)&bigEndianOffset, sizeof(unsigned int));
}

void BinaryFileWriter::close() {
  unsigned int bigEndianOffset = stream_.tellp();
  stream_.seekp(0);

  stream_.write((char*)&bigEndianOffset, sizeof(unsigned int));
  stream_.seekp(bigEndianOffset);

  std::ifstream input;
  input.open(filePath_.c_str(), std::ifstream::in | std::ios::binary);

  if (!input.is_open()) {
    std::cerr << "Failed to open file " << filePath_ << std::endl;
  }

  //seek past the offset marker
  input.seekg(0);
  input.seekg(sizeof(unsigned int));

  unsigned int marker = 0;
  while(marker < bigEndianOffset) {
    unsigned int data = 0;
    input.read((char*)&data, sizeof(unsigned int));

    data = swap_uint32(data);
    stream_.write((char*)&data, sizeof(unsigned int));
    marker += sizeof(unsigned int);
  }

  stream_.close();
}

void BinaryFileWriter::writeValue(unsigned int value) {
  stream_.write((char*)&value, sizeof(unsigned int));
}

void BinaryFileWriter::writeVertexData(VertexDefinition* data, unsigned int size) {
  stream_.write((char*)&size, sizeof(unsigned int));
  stream_.write((char*)data, size * sizeof(VertexDefinition));
}

void BinaryFileWriter::writeString(const std::string& value) {
  unsigned int length = value.length() + 1;
  stream_.write((char*)&length, sizeof(unsigned int));
  stream_.write(value.c_str(), value.size() * sizeof(char));

  char terminator = '\0';
  stream_.write((char*)&terminator, sizeof(char));
}

void BinaryFileWriter::writeKeyValue(const std::string& key, const std::string& value) {
  writeString(key);
  
  int valueType = PARAMETER_TYPE_STRING;
  stream_.write((char*)&valueType, sizeof(int));

  writeString(value);
}

void BinaryFileWriter::writeKeyValue(const std::string& key, float value) {
  writeString(key);
  int valueType = PARAMETER_TYPE_FLOAT;
  stream_.write((char*)&valueType, sizeof(int));
  stream_.write((char*)&value, sizeof(float));
}

void BinaryFileWriter::writeKeyValue(const std::string& key, const Vector3& value) {
  writeString(key);
  int valueType = PARAMETER_TYPE_VECTOR3;
  stream_.write((char*)&valueType, sizeof(int));
  stream_.write((char*)&value, sizeof(Vector3));
}

bool BinaryFileWriter::acceptExtension(const std::string& extension) {
  bool isModelBinary = extension.compare("modelbinary") == 0;
  return isModelBinary;
}
