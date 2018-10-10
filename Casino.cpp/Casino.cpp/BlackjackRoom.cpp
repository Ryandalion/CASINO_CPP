#include "BlackjackRoom.hpp"

BlackjackRoom::BlackjackRoom() : Location("Blackjack Tables")
{

}

void BlackjackRoom::enter(Account *user)
{
	cout << "In the Blackjack room" << endl;
}

BlackjackRoom::~BlackjackRoom()
{

}