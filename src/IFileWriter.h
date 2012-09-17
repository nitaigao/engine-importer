#ifndef IFILEWRITER_H_
#define IFILEWRITER_H_

#include <string>

class Model;

class IFileWriter {

public:

  static IFileWriter* writerForFile(const std::string& outputFilename);
  
public:

  virtual bool acceptExtension(const std::string& extension) = 0;
  
  virtual void writeModel(Model* model, const std::string& outputFilename) = 0;

};

#endif