#include "FloatMaterialParameter.h"

#include "IFileWriter.hpp"

void FloatMaterialParameter::write(IFileWriter* writer) {
  writer->writeKeyValue(name_, value);
}