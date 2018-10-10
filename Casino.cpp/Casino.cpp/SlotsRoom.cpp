#include "SlotsRoom.hpp"
#include "InputValidate.hpp"


SlotsRoom::SlotsRoom() : Location ("Slots Room")
{

}

void SlotsRoom::enter(Account *user)
{
	int choice = 0;
	Validate userInput;
	
	cout << "SLOTS ROOM" << endl;
	cout << "1. Play Slots" << endl;
	cout << "2. Go to a different room" << endl;

	choice = userInput.inputValidate(1, 2);
	
	if (choice == 1)
	{
		cout << "Play slots" << endl;
		Slots machine;
		machine.startSlots(user);
	}
}

SlotsRoom::~SlotsRoom()
{

}