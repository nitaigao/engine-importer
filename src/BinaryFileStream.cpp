#include "BinaryFileStream.h"

#include <fstream>
#include <iostream>
#include <stdint.h>

#include "VertexDefinition.h"

enum {
  PARAMETER_TYPE_UNKNOWN = 0,
  PARAMETER_TYPE_STRING = 1,
  PARAMETER_TYPE_FLOAT = 2,
  PARAMETER_TYPE_VECTOR3 = 3,
  PARAMETER_TYPE_VECTOR4 = 4,
};

unsigned int swap_uint32(unsigned int val) {
  val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
  return (val << 16) | (val >> 16);
}

float swap_float(float x) {
  unsigned int ui = *((unsigned int *)(void *)&x);
  ui = swap_uint32(ui);

  return *((float *)(void *)&ui);
}

void BinaryFileStream::writeValue(unsigned int value) {
  value = isBigEndian_ ? swap_uint32(value) : value;
  stream_->write((char*)&value, sizeof(int32_t));
}

void BinaryFileStream::writeVertexData(VertexDefinition* data, unsigned int size) {
  writeValue(size);

  if (isBigEndian_) {
    unsigned int vertexDefDataSize = size * 8; // size of vertexdef;
    float* vertexDefData = (float*)data;

    float* bigEndianVertexDefData = new float[vertexDefDataSize];

    for (unsigned int i = 0; i < vertexDefDataSize; i++) {
      float vertexDef = vertexDefData[i];
      vertexDef = swap_float(vertexDef);
      bigEndianVertexDefData[i] = vertexDef;
    }

    stream_->write((char*)bigEndianVertexDefData, size * sizeof(VertexDefinition));
  }
  else {
    stream_->write((char*)data, size * sizeof(VertexDefinition));
  }

}

void BinaryFileStream::writeString(const std::string& value) {
  unsigned int length = value.length() + 1;
  length = isBigEndian_ ? swap_uint32(length) : length;
  stream_->write((char*)&length, sizeof(unsigned int));

  stream_->write(value.c_str(), value.size() * sizeof(char));

  char terminator = '\0';
  stream_->write((char*)&terminator, sizeof(char));
}

void BinaryFileStream::writeKeyValue(const std::string& key, const std::string& value) {
  writeString(key);

  int valueType = isBigEndian_ ? swap_uint32(PARAMETER_TYPE_STRING) : PARAMETER_TYPE_STRING;
  stream_->write((char*)&valueType, sizeof(int32_t));

  writeString(value);
}

void BinaryFileStream::writeKeyValue(const std::string& key, float value) {
  writeString(key);

  int valueType = isBigEndian_ ? swap_uint32(PARAMETER_TYPE_FLOAT) : PARAMETER_TYPE_FLOAT;
  stream_->write((char*)&valueType, sizeof(int32_t));

  value = isBigEndian_ ? swap_float(value) : value;
  stream_->write((char*)&value, sizeof(float));
}

void BinaryFileStream::writeKeyValue(const std::string& key, const Vector3& value) {
  writeString(key);

  int valueType = isBigEndian_ ? swap_uint32(PARAMETER_TYPE_VECTOR3) : PARAMETER_TYPE_VECTOR3;
  stream_->write((char*)&valueType, sizeof(int32_t));

  if (isBigEndian_) {
    float* data = (float*)&value;

    for (unsigned int i = 0; i < 3; i++) {
      float littleEndian = data[i];
      float bigEndian = swap_float(littleEndian);
      data[i] = bigEndian;
    }
  }

  stream_->write((char*)&value, sizeof(Vector3));
}

void BinaryFileStream::writeKeyValue(const std::string& key, const Vector4& value) {
  writeString(key);

  int valueType = isBigEndian_ ? swap_uint32(PARAMETER_TYPE_VECTOR4) : PARAMETER_TYPE_VECTOR4;
  stream_->write((char*)&valueType, sizeof(int32_t));

  if (isBigEndian_) {
    float* data = (float*)&value;

    for (unsigned int i = 0; i < 4; i++) {
      float littleEndian = data[i];
      float bigEndian = swap_float(littleEndian);
      data[i] = bigEndian;
    }
  }

  stream_->write((char*)&value, sizeof(Vector4));
}

void BinaryFileStream::writeKeyValueWithoutType(const std::string& key, const std::string& value) {
  writeString(key);
  writeString(value);
}
