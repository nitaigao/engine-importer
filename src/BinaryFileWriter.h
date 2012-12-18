#ifndef BINARYFILEWRITER_H_
#define BINARYFILEWRITER_H_

#include "IFileWriter.h"

#include <fstream>

class Model;

class BinaryFileWriter : public IFileWriter {

public:

	BinaryFileWriter() { };

public:

  bool acceptExtension(const std::string& extension);

  void writeModel(Model* model, const std::string& outputFilename);

  std::string BinaryFileWriter::type() const;

};

inline std::string BinaryFileWriter::type() const {
	return "Binary";
}

#endif