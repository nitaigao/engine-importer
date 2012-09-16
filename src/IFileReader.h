#ifndef IFILEREADER_H_
#define IFILEREADER_H_

#include <vector>

class Model;

class IFileReader {

public:

  virtual Model* read(const char* filename) = 0;

  virtual bool acceptExtension(const std::string& extension) = 0;

public:

  static Model* readFile(const std::string& inputFilename);

};

#endif