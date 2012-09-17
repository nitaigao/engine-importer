#ifndef Model_H_
#define Model_H_

#include <vector>

#include "SubMesh.h"

class IOutputStream;

class Model {

public:

  void write(IOutputStream* writer);

  void addSubMesh(const SubMesh& submesh);

private:

  std::vector<SubMesh> submeshes_;

};

inline void Model::addSubMesh(const SubMesh& submesh) {
  submeshes_.push_back(submesh);
}

#endif