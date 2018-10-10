#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::numeric_limits;
using std::streamsize;

#ifndef INPUTVALIDATE_H
#define INPUTVALIDATE_H

class Validate
{
public:
	Validate();
	int inputValidate(int min, int max);
	~Validate();
private:
};

#endif