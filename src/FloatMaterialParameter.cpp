#include "FloatMaterialParameter.h"

#include "IFileWriter.h"

void FloatMaterialParameter::write(IFileWriter* writer) {
  writer->writeKeyValue(name_, value);
}