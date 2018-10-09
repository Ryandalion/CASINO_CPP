#include "area.hpp"

#ifndef BLACKJACKROOM_H
#define BLACKJACKROOM_H

class BlackjackRoom : public Area
{
public:
	BlackjackRoom();
	Account* playGame(Account *user);
	~BlackjackRoom();

};


#endif
