#include "BlackjackRoom.hpp"

BlackjackRoom::BlackjackRoom() : Location("Blackjack Tables")
{

}

void BlackjackRoom::enter(Account *user)
{
	int choice = 0;
	Validate userInput;

	cout << "BLACKJACK ROOM" << endl;
	cout << "1. Go to a different room" << endl;
	cout << "2. Play Blackjack" << endl;

	choice = userInput.inputValidate(1, 2);

	if (choice == 2)
	{
		cout << "You have chosen to play Blackjack" << endl;
		Blackjack table;
		table.startPlay(user);
	}

}

BlackjackRoom::~BlackjackRoom()
{

}