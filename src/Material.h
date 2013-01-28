#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>
#include <vector>
#include <map>

class IMaterialParameter;
class IOutputStream;

class Material {

public:

  void setEffect(const std::string& effectFilePathRelative);

  void addParameter(IMaterialParameter* parameter);

  void addTexture(const std::string& key, const std::string& fileName);

  void setName(const std::string& name);

  bool hasTextures() const;

public:

  void write(IOutputStream* writer);

private:

  std::string name_;

  std::string effectFilePath_;

  std::vector<IMaterialParameter*> parameters_;

  std::map<std::string, std::string> textures_;

};

inline void Material::setName(const std::string& name) {
  name_ = name;
}

inline void Material::setEffect(const std::string& effectFilePathRelative) {
  effectFilePath_ = effectFilePathRelative;
}

inline void Material::addParameter(IMaterialParameter* parameter) {
  parameters_.push_back(parameter);
}

inline void Material::addTexture(const std::string& key, const std::string& fileName) {
  textures_[key] = fileName;
}

inline bool Material::hasTextures() const {
  return textures_.size() > 0;
}


#endif