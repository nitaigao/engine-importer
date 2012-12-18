#ifndef IFILEREADER_H_
#define IFILEREADER_H_

#include <vector>

class Model;

class IFileReader {

public:

  virtual Model* read(const char* filename) = 0;

  virtual bool acceptExtension(const std::string& extension) = 0;

  virtual std::string type() const = 0;

public:

  static IFileReader* readerForFile(const std::string& inputFilename);

};

#endif