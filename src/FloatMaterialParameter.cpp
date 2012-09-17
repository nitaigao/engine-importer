#include "FloatMaterialParameter.h"

#include "IOutputStream.h"

void FloatMaterialParameter::write(IOutputStream* writer) {
  writer->writeKeyValue(name_, value);
}