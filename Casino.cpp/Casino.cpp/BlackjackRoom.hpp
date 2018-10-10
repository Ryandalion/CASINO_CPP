#include "Location.hpp"
#include "Blackjack.hpp"

#ifndef BLACKJACKROOM_H
#define BLACKJACKROOM_H

class BlackjackRoom : public Location
{
public:
	BlackjackRoom();
	void enter(Account *user);
	~BlackjackRoom();
private:
};

#endif