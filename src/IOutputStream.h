#ifndef IFILEWRITER_HPP_
#define IFILEWRITER_HPP_

class SubMesh;
class Vector3;
class Vector4;
class Material;
class VertexDefinition;

#include <string>
#include <vector>

class IOutputStream {

public:

  virtual void writeValue(unsigned int value) = 0;

  virtual void writeVertexData(VertexDefinition* data, unsigned int size) = 0;

  virtual void writeString(const std::string& value) = 0;

  virtual void writeKeyValue(const std::string& key, const Vector3& value) = 0;

  virtual void writeKeyValue(const std::string& key, const Vector4& value) = 0;

  virtual void writeKeyValue(const std::string& key, const std::string& value) = 0;

  virtual void writeKeyValue(const std::string& key, float value) = 0;

  virtual void writeKeyValueWithoutType(const std::string& key, const std::string& value) = 0;

};

#endif