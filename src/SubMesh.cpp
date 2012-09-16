#include "SubMesh.h"

#include "IFileWriter.h"

void SubMesh::write(IFileWriter* writer) {
  material_.write(writer);

  writer->writeVertexData(&vertices_[0], vertices_.size());
}
