#include "Model.h"

#include "IFileWriter.h"

void Model::write(IFileWriter* writer) {
  writer->writeValue(submeshes_.size());
  for (std::vector<SubMesh>::iterator i = submeshes_.begin(); i != submeshes_.end(); ++i) {
  	(*i).write(writer);
  }
}