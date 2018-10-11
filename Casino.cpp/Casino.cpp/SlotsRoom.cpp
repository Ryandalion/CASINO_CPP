#include "SlotsRoom.hpp"

SlotsRoom::SlotsRoom() : Location ("Slots Room")
{

}

void SlotsRoom::enter(Account *user)
{
	int choice = 0;
	Validate userInput;
	
	cout << "SLOTS ROOM" << endl;
	cout << "1. Go to a different room" << endl;
	cout << "2. Play slots" << endl;

	choice = userInput.inputValidate(1, 2);
	
	if (choice == 2)
	{
		cout << "You have chosen to play slots" << endl;
		Slots machine;
		machine.startSlots(user);
	}
}

SlotsRoom::~SlotsRoom()
{

}