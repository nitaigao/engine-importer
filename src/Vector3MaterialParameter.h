#ifndef VECTOR3MATERIALPARAMETER_H_
#define VECTOR3MATERIALPARAMETER_H_

#include <string>

#include "IMaterialParameter.h"

#include "Vector3.h"

class Vector3MaterialParameter : public IMaterialParameter {

public:

  Vector3MaterialParameter(const std::string& name)
    : name_(name) { }

public:

  void write(IFileWriter* writer);

private:

  std::string name_;

public:

  Vector3 value;

};

#endif