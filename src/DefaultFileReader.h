#ifndef DEFAULTFILEREADER_H_
#define DEFAULTFILEREADER_H_

#include "IFileReader.h"

class DefaultFileReader : public IFileReader {

public:

  bool acceptExtension(const std::string& extension);

  Model* read(const char* filename);

  std::string type() const;

};

inline std::string DefaultFileReader::type() const {
	return "Default";
}

#endif