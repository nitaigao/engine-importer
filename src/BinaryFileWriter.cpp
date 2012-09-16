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

void BinaryFileWriter::openFile(const char* filePath) {
  stream_.open(filePath, std::ofstream::binary);

  if (!stream_.is_open()) {
    std::cerr << "Failed to open file " << filePath << std::endl;
  }
}

void BinaryFileWriter::close() {
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
  stream_.write(value.c_str(), value.length() * sizeof(char));

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
