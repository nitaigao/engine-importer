#include "Material.h"

#include "IMaterialParameter.h"

#include "IOutputStream.h"

void Material::write(IOutputStream* writer) {
  writer->writeString(effectFilePath_);

  writer->writeValue(parameters_.size());

  for (std::vector<IMaterialParameter*>::iterator i = parameters_.begin(); i != parameters_.end(); ++i) {
  	(*i)->write(writer);
  }

  writer->writeValue(textures_.size());

  for (std::map<std::string, std::string>::iterator i = textures_.begin(); i != textures_.end(); ++i) {
  	writer->writeKeyValue((*i).first, (*i).second);
  }
}