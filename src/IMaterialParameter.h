#ifndef IMATERIALPARAMETER_H_
#define IMATERIALPARAMETER_H_

class IOutputStream;

class IMaterialParameter {

public:

	virtual void write(IOutputStream* writer) = 0;

};

#endif