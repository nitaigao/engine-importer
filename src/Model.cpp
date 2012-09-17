#include "Model.h"

#include "IOutputStream.h"

void Model::write(IOutputStream* writer) {
  writer->writeValue(submeshes_.size());
  for (std::vector<SubMesh>::iterator i = submeshes_.begin(); i != submeshes_.end(); ++i) {
  	(*i).write(writer);
  }
}