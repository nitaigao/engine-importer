#include "DefaultFileReader.h"

#include <iostream>

#include "Extension.h"
#include "Model.h"

bool DefaultFileReader::acceptExtension(const std::string& extension) {
  return true;
}

Model* DefaultFileReader::read(const char* filename) {
  std::string ext = extension(filename);
  std::clog << "Failed to find reader for extension *." << ext << std::endl;

  Model* model = new Model();
  return model;
}
