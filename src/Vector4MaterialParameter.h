#ifndef VECTOR4MATERIALPARAMETER_H_
#define VECTOR4MATERIALPARAMETER_H_

#include <string>

#include "IMaterialParameter.h"

#include "Vector4.h"

class Vector4MaterialParameter : public IMaterialParameter {

public:

  Vector4MaterialParameter(const std::string& name)
    : name_(name) { }

public:

  void write(IOutputStream* writer);

private:

  std::string name_;

public:

  Vector4 value;

};

#endif