#include "SlotsRoom.hpp"


SlotsRoom::SlotsRoom() : Location ("Slots Room")
{

}

void SlotsRoom::enter(Account *user)
{
	cout << "In the slots room now" << endl;
	Slots machine;
	machine.startSlots(user);
}

SlotsRoom::~SlotsRoom()
{

}