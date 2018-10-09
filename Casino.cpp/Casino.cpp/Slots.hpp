#include "Casino.hpp"

#ifndef SLOTS_H
#define SLOTS_H

class Slots : public Casino
{
public:
	Slots();
	void printMessage();
	friend class SlotsRoom;
	~Slots();
};

#endif