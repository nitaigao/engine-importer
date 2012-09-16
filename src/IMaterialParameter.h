#ifndef IMATERIALPARAMETER_H_
#define IMATERIALPARAMETER_H_

class IFileWriter;

class IMaterialParameter {

public:

	virtual void write(IFileWriter* writer) = 0;

};

#endif