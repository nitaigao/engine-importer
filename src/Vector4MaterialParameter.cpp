#include "Vector4MaterialParameter.h"

#include "IOutputStream.h"

void Vector4MaterialParameter::write(IOutputStream* writer) {
  writer->writeKeyValue(name_, value);
}
