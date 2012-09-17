#ifndef BINARYFILEWRITER_H_
#define BINARYFILEWRITER_H_

#include "IFileWriter.h"

#include <fstream>

class BinaryFileWriter : public IFileWriter {

public:

	BinaryFileWriter() { };

public:

  void openFile(const char* filePath);

  void close();

  void writeValue(unsigned int value);

  void writeVertexData(VertexDefinition* data, unsigned int size);

  void writeString(const std::string& value);

  void writeKeyValue(const std::string& key, const std::string& value);

  void writeKeyValue(const std::string& key, float value);

  void writeKeyValue(const std::string& key, const Vector3& value);

  bool acceptExtension(const std::string& extension);

private:

  std::ofstream stream_;
  std::string filePath_;

};

#endif