#include "Material.h"

#include "IMaterialParameter.h"

#include "IFileWriter.hpp"

void Material::write(IFileWriter* writer) {
  writer->writeString(effectFilePath_);

  writer->writeValue(parameters_.size());

  for (std::vector<IMaterialParameter*>::iterator i = parameters_.begin(); i != parameters_.end(); ++i) {
  	(*i)->write(writer);
  }

  writer->writeValue(textures_.size());

  for (std::vector<std::string>::iterator i = textures_.begin(); i != textures_.end(); ++i) {
  	writer->writeString(*i);
  }
}
