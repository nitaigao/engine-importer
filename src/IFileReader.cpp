#include "IFileReader.h"

#include "MayaReader.h"
#include "DefaultFileReader.h"
#include "Extension.h"

Model* IFileReader::readFile(const std::string& inputFilename) {
  std::string fileExtension = extension(inputFilename);

  std::vector<IFileReader*> readers;
  readers.push_back(new MayaReader);
  readers.push_back(new DefaultFileReader);

  IFileReader* reader = NULL;
  for (std::vector<IFileReader*>::iterator i = readers.begin(); i != readers.end(); ++i) {
    if ((*i)->acceptExtension(fileExtension)) {
      reader = (*i);
      break;
    }
  }

  Model* model = reader->read(inputFilename.c_str());
  return model;
}
