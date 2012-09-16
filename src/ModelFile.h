#ifndef MODELFILE_H_
#define MODELFILE_H_

#include <vector>

#include "SubMesh.h"

class IFileWriter;

class ModelFile {

public:

  void write(IFileWriter* writer);

  void addSubMesh(const SubMesh& submesh);

private:

  std::vector<SubMesh> submeshes_;

};

inline void ModelFile::addSubMesh(const SubMesh& submesh) {
  submeshes_.push_back(submesh);
}

#endif