#ifndef SUBMESH_H_
#define SUBMESH_H_

#include <vector>

#include "VertexDefinition.h"
#include "Material.h"

class IFileWriter;

class SubMesh {

public:

  void addVertex(const VertexDefinition& vertex);

  void setMaterial(const Material& material);

public:

  void write(IFileWriter* writer);

private:

  std::vector<VertexDefinition> vertices_;
  
  Material material_;

};

inline void SubMesh::addVertex(const VertexDefinition& vertex) {
  vertices_.push_back(vertex);
}

inline void SubMesh::setMaterial(const Material& material) {
  material_ = material;
}

#endif