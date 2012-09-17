#include "IFileWriter.h"

#include "Extension.h"
#include "BinaryFileWriter.h"
#include "DefaultFileWriter.h"

#include <vector>

IFileWriter* IFileWriter::writerForFile(const std::string& outputFilename) {
  std::string outputExtension = extension(outputFilename);

  std::vector<IFileWriter*> writers;
  writers.push_back(new BinaryFileWriter);
  writers.push_back(new DefaultFileWriter);

  for (std::vector<IFileWriter*>::iterator i = writers.begin(); i != writers.end(); ++i) {
    if ((*i)->acceptExtension(outputExtension)) {
      return (*i);
    }
  }

  return NULL;
}

