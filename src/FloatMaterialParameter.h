#ifndef FLOATMATERIALPARAMETER_H_
#define FLOATMATERIALPARAMETER_H_

#include <string>

#include "IMaterialParameter.h"

class FloatMaterialParameter : public IMaterialParameter {

public:

  FloatMaterialParameter(const std::string& name)
    : name_(name) { };

public:

  void write(IFileWriter* writer);

private:

  std::string name_;

public:

  float value;

};

#endif