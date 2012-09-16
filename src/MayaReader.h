#ifndef MAYAREADER_H_
#define MAYAREADER_H_

#include "IFileReader.h"

class Model;

class MayaReader : public IFileReader {

public:

	Model* read(const char* filename);

  bool acceptExtension(const std::string& extension);

};

#endif