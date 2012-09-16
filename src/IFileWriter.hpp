#ifndef IFILEWRITER_HPP_
#define IFILEWRITER_HPP_

class SubMesh;
class Vector3;
class Material;
class VertexDefinition;

#include <string>
#include <vector>

class IFileWriter {

public:

  virtual void openFile(const char* filePath) = 0;

  virtual void close() = 0;

public:

  virtual void writeValue(unsigned int value) = 0;

  virtual void writeVertexData(VertexDefinition* data, unsigned int size) = 0;

  virtual void writeString(const std::string& value) = 0;

  virtual void writeKeyValue(const std::string& key, const Vector3& value) = 0;

  virtual void writeKeyValue(const std::string& key, const std::string& value) = 0;

  virtual void writeKeyValue(const std::string& key, float value) = 0;

};

#endif