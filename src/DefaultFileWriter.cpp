#include "DefaultFileWriter.h"

#include <iostream>

bool DefaultFileWriter::acceptExtension(const std::string& extension) {
  std::clog << "Failed to find writer for extension *." << extension << std::endl;
  return true;
}

void DefaultFileWriter::writeModel(Model* model, const std::string& outputFilename) { }


