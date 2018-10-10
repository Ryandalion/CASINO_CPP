#include "Location.hpp"
#include "Slots.hpp"

#ifndef SLOTSROOM_H
#define SLOTSROOM_H

class SlotsRoom : public Location
{
public:
	SlotsRoom();
	void enter(Account *user);
	~SlotsRoom();
};



#endif