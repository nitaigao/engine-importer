#include "Vector3MaterialParameter.h"

#include "IFileWriter.hpp"

void Vector3MaterialParameter::write(IFileWriter* writer) {
  writer->writeKeyValue(name_, value);
}
