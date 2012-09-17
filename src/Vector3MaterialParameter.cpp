#include "Vector3MaterialParameter.h"

#include "IOutputStream.h"

void Vector3MaterialParameter::write(IOutputStream* writer) {
  writer->writeKeyValue(name_, value);
}
