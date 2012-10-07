#ifndef BINARYFILESTREAM_H_
#define BINARYFILESTREAM_H_

#include "IOutputStream.h"

#include <fstream>

class BinaryFileStream : public IOutputStream {

public:

  BinaryFileStream(bool isBigEndian, std::ofstream* stream)
    : isBigEndian_(isBigEndian)
    , stream_(stream) { }

public:

  void close();

  void writeValue(unsigned int value);

  void writeVertexData(VertexDefinition* data, unsigned int size);

  void writeString(const std::string& value);

  void writeKeyValue(const std::string& key, const std::string& value);

  void writeKeyValue(const std::string& key, float value);

  void writeKeyValue(const std::string& key, const Vector3& value);

  void writeKeyValueWithoutType(const std::string& key, const std::string& value);

private:

  bool isBigEndian_;

private:

  std::string filePath_;
  std::ofstream* stream_;

};

#endif