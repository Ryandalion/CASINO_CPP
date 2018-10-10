#include "Location.hpp"
#include "Poker.hpp"

#ifndef POKERROOM_H
#define POKERROOM_H

class PokerRoom : public Location
{
public:
	PokerRoom();
	void enter(Account *user);
	~PokerRoom();
private:
};

#endif