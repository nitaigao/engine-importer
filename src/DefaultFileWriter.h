#ifndef DEFAULTFILEWRITER_H_
#define DEFAULTFILEWRITER_H_

#include "IFileWriter.h"

class DefaultFileWriter : public IFileWriter {

public:

  void openFile(const char* filePath) {  }

  void close() {  }

  void writeValue(unsigned int value) {  }

  void writeVertexData(VertexDefinition* data, unsigned int size) {  }

  void writeString(const std::string& value) {  }

  void writeKeyValue(const std::string& key, const Vector3& value) {  }

  void writeKeyValue(const std::string& key, const std::string& value) {  }

  void writeKeyValue(const std::string& key, float value) {  }

  bool acceptExtension(const std::string& extension);

};

#endif