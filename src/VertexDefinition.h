#ifndef VERTEXDEFINITION_H_
#define VERTEXDEFINITION_H_

class IOutputStream;

#include "Vector3.h"
#include "Vector2.h"

class VertexDefinition {

public:

  void write(IOutputStream* writer);

public:

  Vector3 vertex;
  Vector3 normal;
  Vector2 uv;

};

#endif