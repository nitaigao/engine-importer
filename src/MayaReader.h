#ifndef MAYAREADER_H_
#define MAYAREADER_H_

#include "IFileReader.h"

class Model;

class MayaReader : public IFileReader {

public:

	Model* read(const char* filename);

	bool acceptExtension(const std::string& extension);

	std::string type() const;

};

inline std::string MayaReader::type() const {
	return "Maya Binary/ASCII";
}

#endif