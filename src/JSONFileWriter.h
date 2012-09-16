#ifndef JSONFILEWRITER_H_
#define JSONFILEWRITER_H_

#include "IFileWriter.h"

#include <writer.h>

class JSONFileWriter : public IFileWriter {

public:

  void openFile(const char* filePath) { };

  void writeKeyValue(const std::string& key, const Vector3& value);

  void writeKeyValue(const std::string& key, const std::string& value);

  void writeKeyValue(const std::string& key, float value);

  void writeSubMeshArray(const std::vector<SubMesh>& submeshes);

  void writeMaterial(const Material& material);

  void writeVertexArray(std::vector<VertexDefinition>& vertices);

  void close();

private:

  json::Object rootObject;


};

#endif