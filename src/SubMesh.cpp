#include "SubMesh.h"

#include "IOutputStream.h"

void SubMesh::write(IOutputStream* writer) {
  material_.write(writer);

  writer->writeVertexData(&vertices_[0], vertices_.size());
}
