#include "PokerRoom.hpp"

PokerRoom::PokerRoom() : Location("Poker Room")
{

}

void PokerRoom::enter(Account *user)
{
	cout << "Inside the Poker room" << endl;
}

PokerRoom::~PokerRoom()
{

}