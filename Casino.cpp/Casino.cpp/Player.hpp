#include "Account.hpp"
#include "Casino.hpp"
#include "Slots.hpp"
#include "Blackjack.hpp"
#include "Poker.hpp"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Blackjack, public Slots, public Poker, public Account
{
public:
	Player();
	~Player();
private:
};



#endif
