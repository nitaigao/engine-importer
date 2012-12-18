#ifndef DEFAULTFILEWRITER_H_
#define DEFAULTFILEWRITER_H_

#include "IFileWriter.h"

class DefaultFileWriter : public IFileWriter {

public:

  void writeModel(Model* model, const std::string& outputFilename);

  bool acceptExtension(const std::string& extension);

  std::string DefaultFileWriter::type() const;

};

inline std::string DefaultFileWriter::type() const {
	return "Default";
}

#endif