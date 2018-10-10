#include "Slots.hpp"


Slots::Slots()
{

}

void Slots::startSlots(Account *user)
{
	cout << "Starting up slot machine" << endl;
	cout << "USERNAME " << user->getName() << endl;
}

Slots::~Slots()
{

}